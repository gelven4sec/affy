cmake_minimum_required(VERSION 3.13)
project(affy C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lm -std=c99 -lcurl")

add_executable(affy main.c libaffy/dataset.c libaffy/dataset.h libaffy/cosine_similarity.c libaffy/cosine_similarity.h libaffy/get_top_10.c libaffy/get_top_10.h libaffy/create_profile.c libaffy/create_profile.h libaffy/search.c libaffy/search.h)
target_link_libraries(affy m curl)
