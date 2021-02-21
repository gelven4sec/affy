cmake_minimum_required(VERSION 3.13)
project(affy C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -rdynamic")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

add_executable(affy main.c libaffy/dataset.c libaffy/dataset.h libaffy/cosine_similarity.c libaffy/cosine_similarity.h libaffy/get_top_10.c libaffy/get_top_10.h libaffy/create_profile.c libaffy/create_profile.h libaffy/request.c libaffy/request.h libaffy/parse_json.c libaffy/parse_json.h libaffy/search_gui.c libaffy/search_gui.h libaffy/watchlist.c libaffy/watchlist.h libaffy/init_gui.c libaffy/init_gui.h)
target_link_libraries(affy m curl json-c ${GTK3_LIBRARIES})
