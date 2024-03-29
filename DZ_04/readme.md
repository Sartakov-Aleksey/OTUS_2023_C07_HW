## I. Описание задания/задачи.

Написать программу, скачивающую с помощью libcurl и разбирающую с помощью произвольной сторонней
библиотеки для JSON в C текущие погодные данные со API wttr.in для заданного аргументом командной
строки города.

### Требования:
> * Выбрана библиотека для работы с JSON в C.
> * Создано консольное приложение, принимающее аргументом командной строки название города
(например, Moscow).
> * Приложение выводит на экран прогноз погоды на текущий день: текстовое описание погоды,
направление и скорость ветра, температура.
> * Приложение корректно обрабатывает ошибочно заданную локацию и сетевые ошибки
> * Код компилируется без предупреждений с ключами компилятора -Wall -Wextra -Wpedantic -std=c11.

<p> &nbsp; </p> 


## II. Как работает программа.

Программа использует на входе 2 ключа. 
> * Первый ключ = имя города для получения погоды. Можно на русском языке или латиницей. 
> * Второй ключ = имя локали  **ru** или **en**. Выдаёт описание текущей погоды на русском 
или на англиском языке. Так же выдаёт разные результаты погоды (с разными временем замеров).

Если при запуске программы пропустить один из ключей, то программа выдаст ошибку и краткую подсказку.


### Программа ориентирована на Debian, Ubuntu с русской локалью (ru_RU.UTF-8)

Названия файлов и папок могут быть на русском языке. Сама программа сохранена в файле с кодировкой UTF-8. 
При перекодировке программы в среде windows с utf-8 на Win-1251 корректная работа программы не гарантируется, так как  отсутствуют некоторые модули для работы программы с русской кодировкой. Возможно, что программа заработает в среде Windows, но фактические тесты в среде Windows не делались. 

<p> &nbsp; </p> 


## III. Что требует для того чтобы собрать программу.

Запустить файл запуск_сборки.sh из папки с домашней работой. Файл CMakeLists.txt уже настроен для генерации/создания исполняемого файла. 
Файл для запуска будет иметь название "progr_HW_04".
Исполняемый файл будет помещен в подпапку "_bin_архив" текущей папки.

<p> &nbsp; </p> 


## IV. Как запустить программу.

При запуске программы нужно: 
> * 1) В первом параметре указать город, к примеру Москва, Moscow; Нижний_Новгород или "Нижний Новгород"; Вологда или Vologda.
> * 2) Во втором параметре указать локаль для работы ru или en. Иногда результаты явно отличаются.

Если при запуске программы пропустить один из ключей, то программа выдаст краткую подсказку.

Пример: 

```
cd /home/postgres/Документы/дом_зад_otus_курсы__си_/дом_зад_курсы__си_23-08/build-Debug/bin/
./progr_HW_04 Влавивосток ru
или ./progr_HW_04 "Нижний Новгород" en
```

<p> &nbsp; </p> 

# V. Нюансы.

> Иногда, результаты запросов между двумя локалями несовпадают, иногда эти отличия очень заметные.

> Время замеров погоды практически всегда отличается. Причем в разных браузерах время и результаты запросов могут переворачиваться и то что было для версии **en** становится для версии **ru**.

<p> &nbsp; </p> 

### Примеры работы:

Сообщение об ошибке - нахватка ключей для работы:
![Ошибка соединения с сервером](https://github.com/Sartakov-Aleksey/OTUS_2023_C07_HW/blob/main/DZ_04/img/error.png)

<p> &nbsp; </p> 

Город Владивосток (ru + en):
![Попытка получить результаты из текстового поля](https://github.com/Sartakov-Aleksey/OTUS_2023_C07_HW/blob/main/DZ_04/img/Vladivostok.png)

<p> &nbsp; </p> 

Город Вологда (ru + en):
![Попытка получить результаты из текстового поля](https://github.com/Sartakov-Aleksey/OTUS_2023_C07_HW/blob/main/DZ_04/img/Vologda.png)

<p> &nbsp; </p> 

Город Нижний Новгород (ru + en):
![Попытка получить результаты из текстового поля](https://github.com/Sartakov-Aleksey/OTUS_2023_C07_HW/blob/main/DZ_04/img/Nizhnij_Novgorod.png)
<p> &nbsp; </p> 

Город Москва (ru + en):
![Попытка получить результаты из текстового поля](https://github.com/Sartakov-Aleksey/OTUS_2023_C07_HW/blob/main/DZ_04/img/Moscow.png)

<p> &nbsp; </p> 

😂 Дата 24 января 2024 г.

<p> &nbsp; </p> 
