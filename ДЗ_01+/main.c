// анализ файлов на предмет наличия в них заархивированных данных
// файл указывается через окно терминала (указанием ссылки на требуемый файл)
// Все переменные на русском языке
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <iso646.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

// функция по выводу подсказки при работе с файлом
static void help(void);

#define MAX_символов 1024 // при использовании русских букв они считаются по 2 байта!
 
 
int main(int argc, char *argv[])
{
    FILE *наш_файл;
    unsigned char символ;
    int длина_файла;
    register unsigned long int цикл;    
    bool скрытый_архив=false;
    char полный_путь_кфайлу[MAX_символов] = "";
    int длина_строки =0;
    char метод_как_текст;
    int штук = 0;
    
    struct timespec время_старт;    
    struct timespec время_стоп;
    timespec_get(&время_старт, TIME_UTC);
    timespec_get(&время_стоп, TIME_UTC);





    // ЧАСТЬ 1 . Прием имя файла, каталога из консоли.
    // Размер файла ограничен signed 2^32, что равно 1/2 от 4,3 млд = 2,15 млрд символов = 2,1 Гб данных символ
    // проверка программы на количество вводимых аргументов
    if (argc < 4) 
    {        
        puts("\n************************\n \
        \rПри запуске программы не хватает ключей для её запуска.\n \
        \rПрограмма завершила работу.\n");
        help(); // указание что делать, нехватает аргументов при открытии файла
        return -1;
    }
    
    
    if (strncmp(argv[1], "-here", 6) == 0 ) // сработал ключ = "-here"
    {
        if ((наш_файл=fopen(argv[2], "rb")) == NULL)
        {
            perror(argv[2]);
            return 1;
        }
    }
    else
    {
        // сшиваем путь к папке и имя файла в одну строку с проверкой на переполнение
        strncat(полный_путь_кфайлу, argv[1], MAX_символов-1);
        длина_строки = strlen(полный_путь_кфайлу); 
        strncat(полный_путь_кфайлу, argv[2], MAX_символов - длина_строки - 1);
        printf("\nПолная длина пути к исполняемому файлу = %d символов. \n", (int) strlen(полный_путь_кфайлу));
        
        if ((наш_файл=fopen(полный_путь_кфайлу, "rb")) == NULL)
        {
            perror(argv[1]);
            perror(argv[2]);
            return 1;
        }
    }
    
    
    
    
    метод_как_текст = argv[3][0];
        
        // это прошлая домашняя работа - попытаюсь сравниь с более понятным вариантом кода (вариант №2)
    if (метод_как_текст != '2')    
    {            
        union 
        {
            unsigned char символ; // когда у нас сработает числовая комбинация, то этот символ будет равен 0b 0100 1111 = O 
                    // (большая заглавная О в английском алфавите = 79 в десятичном исчеслении в ASCII
            struct 
            {
                uint8_t бит_0 :1; // это самый младший бит в байте (нумерация наоборот) 
                uint8_t бит_1 :1; 
                uint8_t бит_2 :1; 
                uint8_t бит_3 :1; 
                uint8_t бит_4 :1; // это пустышка (4 старших бита
                uint8_t бит_5 :1; // это пустышка (4 старших бита
                uint8_t бит_6 :1; // это пустышка (4 старших бита
                uint8_t бит_7 :1; // это пустышка (4 старших бита
                
            } биты;
        } бит_символ;
        
        бит_символ.биты.бит_0 = 0; 
        бит_символ.биты.бит_1 = 0;
        бит_символ.биты.бит_2 = 0;
        бит_символ.биты.бит_3 = 0;
        бит_символ.биты.бит_4 = 0;
        бит_символ.биты.бит_5 = 0; 
        бит_символ.биты.бит_6 = 1;
        бит_символ.биты.бит_7 = 0; // в итоге должно получится 0b0100 0000 = @ как шестнадцатиричный = 0х40 и как десятичный = 64 


        // Определяет - есть ли внутри картинки zip архивы 
        fseek(наш_файл, 0L, SEEK_END);
        длина_файла = ftell(наш_файл);
        for (цикл = 1L; цикл <= длина_файла; цикл++) 
        {
            fseek(наш_файл, -цикл, SEEK_END); // считываем побайтно данные с КОНЦА файла
            символ = getc(наш_файл);
            // если ни один из символов не входит в ключ, то обновляет ключ
            if ((символ != 0x02) and (символ != 0x01) and (символ != 0x4b) and (символ != 0x50))
            {
                бит_символ.символ = '@';
            }
            else
            {
                switch (символ)
                {
                    case 0x02: // это у нас самый последний байт из 4, ставим самый младший бит (_0) 1
                        бит_символ.биты.бит_0 = 1;
                        break;
                    case 0x01: 
                        бит_символ.биты.бит_1 = 1;
                        break;
                    case 0x4b: 
                        бит_символ.биты.бит_2 = 1;
                        break;
                    case 0x50: // это у нас самый первый байт из 4-х если идти он начала файла, ставим ему 1 (бит_3)
                        бит_символ.биты.бит_3 = 1;
                }
                if (бит_символ.символ == 'O') // смотри параметры переменной
                {
                    printf("\n*=1) Вариант через биты. В вашем изображении есть скрытые файлы, то есть о является Rarjpeg-ом  архивом \n");   
                    штук++;
                    
                    // запускаем функцию по поиску и выводу названий файлов внутри картинки
                    fseek(наш_файл, (-1L+28L), SEEK_CUR); // считываем длину имени файла
                    символ = getc(наш_файл);
                    printf("Длина имени файла десятич=%d символов \nЕго название:  ", символ);
                    
                    fseek(наш_файл, (-1L+18L), SEEK_CUR); // здесь первый символ названия файла
                    for (int i=0; i < (int) символ; i++)
                    {
                        printf("%c",getc(наш_файл)); // автоматически смещается на 1 позицию к концу файла!
                    }
                    
                    printf("\n");
                    бит_символ.символ = '@';
                    скрытый_архив = true;
                }
            }
        }
        fclose(наш_файл); // закрывает открутый файл
        if (скрытый_архив == false)
        {
            puts("\n*=1) Вариант через биты. Ваш файл НЕ является Rarjpeg-ом  архивом \n");
        }
        
        printf("В файле найдено %i скрытиых/зашифрованных файлов \n", штук);
    }

















    // это новый вариант домашней работы. Отличия от вариант №1 практически нет, Второй вариант медленнее примерно на 1.0 -1.5%, что можно списать на погрешности замеров
    if (метод_как_текст == '2')    
    {
        // Определяет - есть ли внутри картинки zip архивы 
        fseek(наш_файл, 0L, SEEK_END);
        длина_файла = ftell(наш_файл);
        for (цикл = 1L; цикл <= длина_файла; цикл++) 
        {
            fseek(наш_файл, -цикл, SEEK_END); // считываем побайтно данные с КОНЦА файла
            символ = getc(наш_файл);
            
            // возможно что найдена искомая комбинация, проверяем
            if (символ == 0x02)
            {
                if (цикл+3 <= длина_файла)    // ((символ != 0x02) and (символ != 0x01) and (символ != 0x4b) and (символ != 0x50))
                {                    
                    fseek(наш_файл, -(цикл+1), SEEK_END);
                    if (0x01 == fgetc(наш_файл) )
                    {
                        fseek(наш_файл, -(цикл+2), SEEK_END);
                        if (0x4b == fgetc(наш_файл) ) 
                        {
                            fseek(наш_файл, -(цикл+3), SEEK_END);
                            if (0x50 == fgetc(наш_файл) ) 
                            {
                                printf("\n*=2 Вариант через символ. В вашем изображении есть скрытые файлы, то есть о является Rarjpeg-ом  архивом \n");   
                                // запускаем функцию по поиску и выводу названий файлов внутри картинки
                                fseek(наш_файл, (-1L+28L), SEEK_CUR); // считываем длину имени файла
                                символ = getc(наш_файл);
                                printf("Длина имени файла десятич=%d символов \nЕго название:  ", символ);
                                
                                fseek(наш_файл, (-1L+18L), SEEK_CUR); // здесь первый символ названия файла
                                for (int i=0; i < (int) символ; i++)
                                {
                                    printf("%c",getc(наш_файл)); // автоматически смещается на 1 позицию к концу файла!
                                }
                                
                                цикл +=3;
                                штук++;
                                printf("\n");
                                скрытый_архив = true; 
                           }
                       }
                    }
                }
            }
        }
        fclose(наш_файл); // закрывает открутый файл
        
        if (скрытый_архив == false)
        {
            puts("\n*=2 Вариант через символ. Ваш файл НЕ является Rarjpeg-ом  архивом \n");
        }
        
        printf("В файле найдено %i скрытиых/зашифрованных файлов \n", штук);
    }
    
    
    printf("При работе программа обработала байт = %lu \n\n", цикл);

    timespec_get(&время_стоп, TIME_UTC);    
    printf("Расчёт занял: %6.6f сек. \n", (время_стоп.tv_sec + (float)время_стоп.tv_nsec/1000000000.0) - (время_старт.tv_sec + (float)время_старт.tv_nsec/1000000000.0) );

	return 0;
    
}





static void help(void)
{ 
    puts("\n    *** Инструкция по работе с программой ***");
    puts("======================================");
    puts("При запуске программы нужно:\n  \
        \r1) В первом параметре указать путь к папке.");
    puts("2) Во втором параметре указать полное название файла для открытия.");
    puts("\tЕсли файл расположен в той же папке что и запускаемая программа, то укажите ключь  -here  ");
    puts("3) Метод работы кода (1 через битовые переменные (по умолчанию), 2 = через переменную как символ).");
    puts("В итоге, при запуске программы она должна иметь вид: ");
    puts("название программы    /home/postgres/Документы/дом_зад_otus_курсы__си_/дом_зад_курсы__си_/ДЗ_01/    zipjpeg.jpg  2");
    puts("   или ");
    puts("название программы    -here     zipjpeg.jpg  1");
    printf("*** Названия программы, каталогов и открываемого файла МОГУТ иметь русские символы, "
    "но названия внутренних файлов только на латиннице (распознование имен внутри архива на кириллице не реализовано!)\n");
    puts("======================================\n");
   
}