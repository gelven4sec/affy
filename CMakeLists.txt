cmake_minimum_required(VERSION 3.13)
project(affy C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lm")

add_executable(affy main.c dataset.c dataset.h cosine_similarity.c cosine_similarity.h)