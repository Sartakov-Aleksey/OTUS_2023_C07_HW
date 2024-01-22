#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <wctype.h> 
#include <wchar.h> 
#include <time.h> 
#include <libpq-fe.h>   // есть /usr/include/postgresql/
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

#include <stdint.h>
#include <malloc.h>



int main(int argc, char **argv)
{

    double среднее=0;
    double максимум=0;
    double минимум=0;
    double дисперсия=0;
    double сумма=0;
            
    puts("Настройки при работе: БД PostgreSQL, localhost, port '5432', user 'postgres', пароль '123' схема = 'public'");

    if (argc != 4) // ошибка, нехватка ключей для запуска программы.
    {
        printf("\nПрограмма НЕ имеет нужного количества параметров на входе. "
                "Сейчас указан(о) %i параметр(ов).\n", argc);
        printf("Первый параметр 'название БД', второй ='название таблицы', третий='название колонки'\n");
        return 1; 
    }
    
    
    
    PGresult *результат_запроса; 
    char настройки_соединения[1024]=""; 
    char имя_бд[64];
    strncpy(имя_бд, argv[1], 63); 
        char имя_таблицы[64];
        strncpy(имя_таблицы, argv[2], 63);     
    char имя_столбца[64];
    strncpy(имя_столбца, argv[3], 63); 

    
    strcat(настройки_соединения, " dbname=");
    strcat(настройки_соединения, имя_бд); 
    strcat(настройки_соединения, " port=5432 user=postgres password=123"); 
    
    
    PGconn *соединение = PQconnectdb(настройки_соединения); 
    
    PQsetErrorContextVisibility(соединение,  PQSHOW_CONTEXT_ALWAYS);
    PQsetErrorVerbosity(соединение,  PQERRORS_VERBOSE);
    char er_msg[1000]="# ";
    strcat(er_msg, PQerrorMessage(соединение));   
    
    
    if (PQstatus(соединение) == CONNECTION_OK)
    {
        // было до проверки ДЗ_15
        /*
        char п_запрос_1[512]="select avg(";
        strcat(п_запрос_1,имя_столбца);
        strcat(п_запрос_1,"), max(");
        strcat(п_запрос_1,имя_столбца);
        strcat(п_запрос_1,"), min(");
        strcat(п_запрос_1,имя_столбца);
        strcat(п_запрос_1,"), var_pop(");
        strcat(п_запрос_1,имя_столбца);
        strcat(п_запрос_1,"), sum(");
        strcat(п_запрос_1,имя_столбца);
        strcat(п_запрос_1,") from ");
        strcat(п_запрос_1, имя_таблицы);    */
        
        
        // после рекомендации проверяющего ДЗ_15
        char п_запрос_1[512]={};
        const char *query_format = "SELECT AVG(%s), MAX(%s), MIN(%s), var_pop(%s), SUM(%s) FROM %s";
        sprintf(п_запрос_1, query_format, имя_столбца, имя_столбца, имя_столбца, имя_столбца, имя_столбца, имя_таблицы);        
        
        
        
        
        
        результат_запроса = PQexec(соединение, п_запрос_1); 
        printf("%s\n", п_запрос_1);
        
        if (PQresultStatus(результат_запроса) == PGRES_TUPLES_OK) // успешное завершение команды, которая возвращает данные 
        {   
            среднее  =atof(PQgetvalue(результат_запроса, 0, 0));
            максимум =atof(PQgetvalue(результат_запроса, 0, 1));
            минимум  =atof(PQgetvalue(результат_запроса, 0, 2));
            дисперсия=atof(PQgetvalue(результат_запроса, 0, 3));
            сумма    =atof(PQgetvalue(результат_запроса, 0, 4));            
        }
        else if (PQresultStatus(результат_запроса) != PGRES_TUPLES_OK)
        {
            strcat(er_msg, PQresultErrorMessage(результат_запроса)); 
            strcat(er_msg, " ");
            
            printf("\nОШИБКА. Вы пытаетесь получить математические расчёты из текстовых данных.\n"
                "Запрос: %s\n"
                "*** Описание ОШИБКИ: \n\t\t%s\n\n", п_запрос_1, er_msg); 
        }
    }
    else if (PQstatus(соединение) == CONNECTION_BAD)
    {
        printf("\nСоединение с БД  не установлено!!!\n"
        "*** Описание ошибки: %s. Проверьте имя БД, порт, пользователя и его пароль.\n\n", er_msg);
    }
    




    PQclear(результат_запроса);  
    PQfinish(соединение);
    
    
    
	printf("При запросе к БД='%s', таблице='%s', столбца='%s' \n", имя_бд, имя_таблицы, имя_столбца);
    puts("Получили следующие результаты: ");
    printf("\t среднее = %6.3lf \n", среднее);
    printf("\t максимум = %6.3lf \n", максимум);
    printf("\t минимум = %6.3lf \n", минимум);
    printf("\t дисперсия = %6.3lf \n", дисперсия);
    printf("\t сумма = %6.3lf \n", сумма);
    
    /*
    printf("\n\n*** В БД PostgreSQL имеется два вида дисперсии:\n "
    выбран этот!!!     " var_pop ( numeric_type ) → double precision для real или double precision,"
        " иначе numeric Вычисляет дисперсию для генеральной совокупности входных значений (квадрат стандартного отклонения).\n"
         
        "и   var_samp ( числовой_тип ) → double precision для real или double precision, иначе numeric"
        " Вычисляет дисперсию по выборке для входных значений (квадрат отклонения по выборке\n");
    */
    
	return 0;
}
