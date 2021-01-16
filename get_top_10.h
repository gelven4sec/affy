//
// Created by sven-eliasen on 1/8/2021.
//

#ifndef AFFY_GET_TOP_10_H
#define AFFY_GET_TOP_10_H

#include "dataset.h"

int* get_top_10(char* tconst, struct Movie* dataset);

int* get_top_10_user(struct Movie user_profile, struct Movie* dataset, char** index_list, int nb);

int get_index(char* tconst, struct Movie* dataset);

#endif //AFFY_GET_TOP_10_H
