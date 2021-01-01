cmake_minimum_required(VERSION 3.19)
project(affy C)

set(CMAKE_C_STANDARD 99)

add_executable(affy main.c dataset.c dataset.h)