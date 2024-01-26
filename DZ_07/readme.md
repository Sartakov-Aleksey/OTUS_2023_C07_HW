## I. Задание.

Найти и исправить утечки памяти в программе из приложенного архива. 
Для запуска valgrind следует использовать следующие команды в каталоге с распакованным архивом:

```
cd test/package
make valgrind
```

### Цель задания
Получить навык поиска утечек памяти с помощью valgrind

### Критерии успеха
1. Найдена как минимум одна утечка памяти, создан patch, исправляющий утечку.
2. Бонусные баллы за дополнительные найденные и исправленные утечки.
3. Далее успешность определяется ревью кода.

### Требования:
> * Создано консольное приложение, принимающее аргументом командной строки входной файл.
> * Приложение корректно обрабатывает ошибки доступа к файлу.
> * Приложение корректно подсчитывает и выводит на экран информацию о том, сколько раз в файле
встречается каждое слово, которое есть в файле.
> * Код компилируется без предупреждений с ключами компилятора -Wall -Wextra -Wpedantic -std=c11.

<p> &nbsp; </p> 


## II. Как делался поиск утечки памяти.

> * Запустил valgrind. Rjvfylf **"cd /obmen/_git_OTUS_2023-C01/OTUS_2023_C07_HW/DZ_07/clib/test/package/"** и **"make valgrind"**. 
> * Резульаты скопировал в текстовой файл. Получилось чуть более 1500 строк записей.
> * В папке с проектом запустил поиск слова "malloc". Получил 35 файлов с этой функцией.
> * В папке с проектом запустил поиск слова "calloc". Получил 0 файлов.
> * Искал совпадение в результате работы программы valgrind с ошибкой "definitely" и списком файлов, имеющих функцию "mallcoc". Получил всего 3 файла: "/src/common/clib-package.c", "/deps/strdup/strdup.c", "/deps/http-get/http-get.c".
> * Искал возврат функции из запроса malloc и в конечной функции (куда приходил ответ) искал функцию free(...) по данному запросу.
> * Чаще всего в коде перед вызовом функции, использующую mallco стояла очистка указателя "free((char*) переменная)". Там где не было очистки ни до ни после, делал очистку выделенной памяти по указателю.
> * Риски минимальные, т.к после этого вызывалась сразу новая функция по выделению памяти и назначению в неё результатов работы.
> * В коде ниже - есть пометки "???". Эти блоки кода оставлены на потом, если с первой попытки проблема не была устранена.


```
файл:strdup.c  		стр 17:    char *buf = malloc(len);
файл:http-get.c  	стр 22:    res->data = malloc(realsize + 1);
файл:http-get.c  	стр 46:    http_get_response_t *res = malloc(sizeof(http_get_response_t));
.
файл: clib-package.c   очень много функций:
 нет malloc -> nstall_packages (clib-package.c:370)		 = clib_package_new_from_slug(slug, verbose);
 нет malloc -> install_packages (clib-package.c:374)		 = clib_package_install(pkg, dir, verbose);
 ......
 ЕСТЬ malloc (http-get.c   стр 46)	clib_package_new_from_slug_with_package_name (clib-package.c:660) 
 					= http_get_shared(json_url, clib_package_curl_share);
 ......
 нет malloc -> clib_package_new_from_slug (clib-package.c:796)	 = clib_package_new_from_slug_with_package_name(slug, verbose, name);
 ??? fetch_package_file_thread (clib-package.c:999)		 = int *status = malloc(sizeof(int));
 нет malloc -> clib_package_install (clib-package.c:1383)	 = hash_set(visited_packages, strdup(pkg->name), "t");
 нет malloc -> clib_package_install (clib-package.c:1579)	 = clib_package_install_dependencies(pkg, dir, verbose); 
 ??? clib_package_install_dependencies (clib-package.c:1615)     = install_packages(pkg->dependencies, dir, verbose);
```

<p> &nbsp; </p> 


## III. Что требует для того чтобы собрать программу.

Если уже был запущен скрипт по сборке, то потребуется повторно зайти в папку в терминале через cd ... и заново ввести команду, иначе сделанные исправления в файле не применятся.

Сами исправления (патч) расположен в папке "img".

<p> &nbsp; </p> 


## IV. Примеры работы:

Первоначальные ошибки, выданные valgrind:
![Первоначальные ошибки, выданные valgrind](https://github.com/Sartakov-Aleksey/OTUS_2023_C07_HW/blob/main/DZ_07/img/all_error.png)

<p> &nbsp; </p> 

Ошибки, выданные valgrind после правки кода (частичного устранения недочётов):
![После частичного удаления недочётов](https://github.com/Sartakov-Aleksey/OTUS_2023_C07_HW/blob/main/DZ_07/img/delete_error.png)

<p> &nbsp; </p> 

😂 Дата 26 января 2024 г.

<p> &nbsp; </p> 
