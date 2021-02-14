//
// Created by sven-eliasen on 1/5/2021.
//

#ifndef AFFY_COSINE_SIMILARITY_H
#define AFFY_COSINE_SIMILARITY_H

#include "dataset.h"

double get_cosine_similarity(MOVIE movie1, MOVIE movie2);

int check_duplicate(char** list, int nb, char* str);

#endif //AFFY_COSINE_SIMILARITY_H
