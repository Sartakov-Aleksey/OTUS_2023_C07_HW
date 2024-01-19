cmake_minimum_required(VERSION 3.13)


# глобальное имя вашего проекта
project (uskorenie_mmvb_analiz VERSION 1.0 LANGUAGES C)

message(STATUS "\n******************************** ")
message(STATUS "имя проекта: ${PROJECT_NAME}") # Русские буквы - не принимает! не скомпилирует!!!!
message(STATUS " Начинаем компоновку и сборку программы версии = ${CMAKE_PROJECT_VERSION}\n")


Set (CMAKE_C_STANDAT 17)
Set (CMAKE_C_STANDART_REQUIRED True)


message(STATUS "Начинаем компоновку и сборку программы версии = ${CMAKE_PROJECT_VERSION}")
message(STATUS "Корневой каталог для сборки: ${CMAKE_BINARY_DIR}")



find_package(PostgreSQL)
	# Found PostgreSQL: /usr/lib/x86_64-linux-gnu/libpq.so (found version "16.0") 
message(STATUS "Пакет/испол_модуль для PostgreSQL для сборки: ${PostgreSQL_LIBRARIES}\n")


# Добавляем заголовочный файл библиотеки  <libpq-fe.h> он же потом указывает на исполняемый модуль для
   # сборки: /usr/lib/x86_64-linux-gnu/libpq.so, но его указываем позже ОТДЕЛЬНО в блоке = target_link_libraries(...)
include_directories(/usr/include/postgresql) # include <libpq-fe.h> OK


add_executable(progr_HW_15 main.c) 	# указываем названием этого модуля и только латиницей

# ПЕРВОЕ имя должно быть именем из предыдущей строки(от main.c)
target_link_libraries(progr_HW_15 ${PostgreSQL_LIBRARIES}) 


# дополнительные параметры при компиляции 
add_compile_options(-Wall -Wextra -Wpedantic -std=c11) 
