## I. Цель/Задачи:

Сборка в UNIX. 

В процессе выполнения ДЗ вы получите опыт сборки программ для UNIX-подобных ОС. 

Необходимо скачать curl последней версии и собрать его в любой UNIX-подобной ОС с поддержкой лишь пяти протоколов: HTTP, HTTPS, IPFS, IPNS, TELNET.


## II. Требования:
> * Работа осуществляется в UNIX-подобной ОС (любой дистрибутив Linux, любая BSD-система, MacOS).
> * Скачан и распакован исходный код curl.
> * Сборка сконфигурирована с поддержкой лишь ишь пяти протоколов: HTTP, HTTPS, IPFS, IPNS, TELNET.
> * Осуществлена сборка (установку в систему осуществлять не требуется и не рекомендуется).
> * Собранный curl запущен с ключом --version для подтверждения корректности сборки.

<p> &nbsp; </p> 


## III. Что требует для того чтобы собрать программу.

> 1. Скачать исходники CURL можно по адресу: https://github.com/curl/curl/tree/master
> 2. Файл 'запуск_сборки.sh' поместить внутрь скачанного архива CURL в главную папку (папку самого вернхнего уровня/родительский каталог).
> 3. Перейти в папку с файлом 'запуск_сборки.sh'.
> 4. Запустить файл командой './запуск_сборки.sh'.
> 5. Исполняемый файл 'curl' будет помещен в подпапку "/_bin_архив/src/" текущей папки.
> 6. Перейти в указанную папку в терминале через команду 'cd нужная_папка'.
> 7. Запустить файл из указанной папки командой './curl --version'.


<p> &nbsp; </p> 


## IV. Примеры работы:

Скриншот СТАНДАРТНОЙ версии программы CURL:
![](https://github.com/Sartakov-Aleksey/OTUS_2023_C07_HW/blob/main/DZ_06/img/curl_full.png)

<p> &nbsp; </p> 

Скриншот РУЧНОЙ сборки, но без отключенных протоколов CURL:
![](https://github.com/Sartakov-Aleksey/OTUS_2023_C07_HW/blob/main/DZ_06/img/curl_handmake_full.png)

<p> &nbsp; </p> 

Итоговый результат программы CURL с отключенными протоколами (согласно ДЗ):
![](https://github.com/Sartakov-Aleksey/OTUS_2023_C07_HW/blob/main/DZ_06/img/curl_ok_dz.png)


<p> &nbsp; </p> 

😂 Дата 25 января 2024 г.

<p> &nbsp; </p> 
