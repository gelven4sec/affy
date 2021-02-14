//
// Created by sven-eliasen on 1/1/2021.
//


#ifndef AFFY_DATASET_H
#define AFFY_DATASET_H

#include <stdio.h>

#define SIZE 246710


// movie dataframe
struct Movie{
    char* tconst;
    char* primaryTile;
    char** genres;
    double rating;
    char** nconsts;
    int nb_nconst;
    int nb_genres;
};

struct Movie * init_dataset(FILE* stream);

void free_dataset(struct Movie* dataset);

struct Movie* get_dataset();

#endif //AFFY_DATASET_H
