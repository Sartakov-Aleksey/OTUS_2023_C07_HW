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

find_package(CURL REQUIRED)	#Found PostgreSQL: /usr/lib/x86_64-linux-gnu/libpq.so (found version "16.0") 
include_directories(${CURL_INCLUDE_DIRS})

message(STATUS "Пакет/испол_модуль для CURL сборки: ${CURL_LIBRARIES}\n")



add_library(modul_json parson.c parson.h) 
target_include_directories(modul_json PUBLIC .)


add_executable(progr_HW_03 main.c curl.h) 	# указываем названием этого модуля и только латиницей




# ПЕРВОЕ имя должно быть именем из предыдущей строки(от main.c)
target_link_libraries(progr_HW_03 PUBLIC modul_json ${CURL_LIBRARIES}) 


# дополнительные параметры при компиляции 
add_compile_options(-Wall -Wextra -Wpedantic -std=c11) 
