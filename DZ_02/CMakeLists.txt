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


add_executable(progr_HW_02 main.c) 	# указываем названием этого модуля и только латиницей


# дополнительные параметры при компиляции 
add_compile_options(-Wall -Wextra -Wpedantic -std=c11) 
