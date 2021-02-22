//
// Created by sven-eliasen on 1/8/2021.
//

#ifndef AFFY_GET_TOP_10_H
#define AFFY_GET_TOP_10_H

#include "dataset.h"

int* get_top_10(char* tconst, MOVIE* dataset);

int* get_top_10_user(const MOVIE* user_profile, const MOVIE* dataset, const int* index_list, int nb);

int get_index(char* tconst, const MOVIE* dataset);

#endif //AFFY_GET_TOP_10_H
