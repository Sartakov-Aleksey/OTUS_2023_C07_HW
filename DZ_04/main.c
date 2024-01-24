#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <wctype.h> 
#include <wchar.h> 
#include <time.h> 
#include <ctype.h>
#include <iso646.h>
#include <stdbool.h>
#include <uchar.h>  //  /usr/include/uchar.h
#include <locale.h>
#include <math.h>
#include <tgmath.h>
#include <threads.h> 
#include <unistd.h> // для sleep() read()
#include <errno.h> // return EXIT_SUCCESS; 


#include <curl/curl.h> 
#include <parson.h>


#define ДЛИНА_ИМЕНИ 128 



struct MemoryStruct {
  char *memory;
  size_t size;
};
 
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
  char *ptr = realloc(mem->memory, mem->size + realsize + 1);
  if(!ptr) 
  {
    /* память не выделена */
    printf("Не смогли выделить память (realloc вернул NULL)\n");
    return 0;
  }
 
  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
 
  return realsize;
}




int main(int argc, char **argv)
{
    if (argc != 3) // ошибка, нехватка ключей для запуска программы.
    {
        printf("\nПрограмма НЕ имеет нужного количества параметров на входе. "
                "Сейчас указан(о) %i параметр(ов).\n", argc);
        puts("Первый параметр: 'Название города' по которому хотите получить данные о погоде.\n"
        "Название города можно ввести русскими буквами.\n"
        "Если название города состоит из двух и более слов (Нижний Новгород, Великий Новгород, ...), "
        "то его нужно соединить 'нижним подчеркиванием' или поместить название в двойные кавычки.\n"
        "При этом, НЕ ГАРАНТИРУЕТСЯ, что при выводе результатов, название города так же будет на русском языке.\n");
        puts("Второй ключ = локаль (en или ru). Если en то данные более всежие, но описание погоды на английском языке.\n"
        "Если указать ru то описание погоды на русском языке, но данные более старые (разница примерно 2 часа от текущего времени).");
        return 1; 
    }
    
    
    
    char город_имя[ДЛИНА_ИМЕНИ]; 
    char город_имя_получено[ДЛИНА_ИМЕНИ];
    
    strncpy(город_имя, argv[1], ДЛИНА_ИМЕНИ-1);  
    char локаль_языка[3]; 
    strncpy(локаль_языка, argv[2], 2);  
    
    if (0!=strcmp(локаль_языка, "ru") and 0!=strcmp(локаль_языка, "en"))
    {
        puts("\nНеверно указали локаль языка для вывода сообщений. Возможны: en, ru.\n");
        return -1;
    }

      CURL *curl_соединение; 
      CURLcode res;
      char адрес_запроса[256]={};
     
      struct MemoryStruct память;
     
      память.memory = malloc(1);  /* будет расти по мере необходимости */
      память.size = 0;    // данных пока нет
     
      curl_global_init(CURL_GLOBAL_ALL);
     
      // активирует сеанс CURL
      curl_соединение = curl_easy_init();


      /* Получить URL */
      sprintf(адрес_запроса, "https://wttr.in/%s?lang=%s&format=j1", город_имя, локаль_языка);
      curl_easy_setopt(curl_соединение, CURLOPT_URL, адрес_запроса); 
     
      /* отправить все данные в эту функцию */
      curl_easy_setopt(curl_соединение, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
     
      /* мы передаем нашу структуру «память» функции обратного вызова */
      curl_easy_setopt(curl_соединение, CURLOPT_WRITEDATA, (void *)&память);
     
      /* some servers do not like requests that are made without a user-agent
         field, so we provide one */
      curl_easy_setopt(curl_соединение, CURLOPT_USERAGENT, "libcurl-agent/1.0");
     
      /* Получить данные */
      res = curl_easy_perform(curl_соединение); //  выполнить блокировку передачи файлов
     
      /* check for errors */
      if(res != CURLE_OK) 
      {
            printf("error: %s\n", curl_easy_strerror(res));
            //fprintf(stderr, "curl_easy_perform() failed: %s\n",  curl_easy_strerror(res));
      }
      else 
      {
        // Теперь наша память.memory указывает на блок памяти размером память.size байт и содержит дистанционный/скачанный файл
        printf("%lu получено байт. \n", (unsigned long)память.size);
        
        JSON_Value *root_value; 
        JSON_Array *current_condition_n; 
        JSON_Array *nearest_area_n;   
        JSON_Object* current_condition;
        JSON_Object* nearest_area;
        int i;        
        
        root_value = json_parse_string(память.memory);

        current_condition_n = json_object_dotget_array(json_value_get_object(root_value), "current_condition");
        nearest_area_n = json_object_get_array(json_value_get_object(root_value), "nearest_area");  // "nearest_area": [{"areaName": [{"value": "Москва"}], .... ]
        nearest_area = json_array_get_object(nearest_area_n, 0);            		// "nearest_area": {"areaName": [{"value": "Москва"}], .... = нулевой элемент массива
        nearest_area_n = json_object_get_array(nearest_area, "areaName");   		// {"areaName": [{"value": "Москва"}]
        nearest_area = json_array_get_object(nearest_area_n, 0);            		// {"value": "Москва"}
        strcat(город_имя_получено, json_object_get_string(nearest_area, "value")); 	// "Москва"
        
        printf("\nЗапросили город: %s, \tВернулся город в запросе: %s\n", город_имя, город_имя_получено); 
        
        for (i = 0; i < json_array_get_count(current_condition_n); i++) 
        {
            current_condition = json_array_get_object(current_condition_n, i);
            printf("Время прогноза: %s \n", json_object_get_string(current_condition, "localObsDateTime")); 
            
            nearest_area_n = json_object_get_array(current_condition, "lang_ru");
            nearest_area = json_array_get_object(nearest_area_n, 0);
            printf("Текущая погода (ru_описание): %s \n", json_object_get_string(nearest_area, "value")); 
            
            nearest_area_n = json_object_get_array(current_condition, "weatherDesc");
            nearest_area = json_array_get_object(nearest_area_n, 0);
            printf("Текущая погода (en_описание): %s \n", json_object_get_string(nearest_area, "value")); 
            
            printf("Направление ветра: %s \n", json_object_get_string(current_condition, "winddir16Point")); 
            printf("Скорость ветра: %s (м/с)\n", json_object_get_string(current_condition, "windspeedKmph")); 
            printf("Температура воздуха: %s (градусов цельсия)\n", json_object_get_string(current_condition, "temp_C")); 
            printf("Температура воздуха ощущается как: %s (градусов цельсия)\n\n", json_object_get_string(current_condition, "FeelsLikeC")); 
        }
        json_value_free(root_value);  //  очистка структур JSCON
      }
     
      // Завершить/очистить дескриптор libcurl
      curl_easy_cleanup(curl_соединение);
     
      free(память.memory);
     
      // мы закончили с libcurl, так что очистите его
      curl_global_cleanup();

      return 0;
}


