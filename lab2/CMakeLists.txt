cmake_minimum_required(VERSION 3.23)
set(PROJECT_NAME main.cpp)				 # имя проекта		 
project("${PROJECT_NAME}")

set(CMAKE_CXX_STANDARD 17)

add_executable("${PROJECT_NAME}" lab2.cpp)