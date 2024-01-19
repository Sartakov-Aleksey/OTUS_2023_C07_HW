cmake_minimum_required(VERSION 3.13)


# глобальное имя вашего проекта
project (lib_работа_смаке VERSION 1.10 LANGUAGES C)

message(STATUS "\n******************************** ")
message(STATUS " Начинаем компоновку и сборку программы версии = ${CMAKE_PROJECT_VERSION}\n")

Set (CMAKE_C_STANDAT 17)
Set (CMAKE_C_STANDART_REQUIRED True)



#add_subdirectory(каталог_program)

add_executable(progr_HW_01 main.c) 	# указываем названием этого модуля и только латиницей


# 			ПЕРВОЕ имя должно быть именем из предыдущей строки(от main.c)
# 			target_link_libraries(start_modul_HomeWork_01 modul_lib pq) # где pq это библиотека запросов для pq-fe.h

# дополнительные параметры при компиляции 
add_compile_options(-Wall -Wextra -Wpedantic -std=c11) 
