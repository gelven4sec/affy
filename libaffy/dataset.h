#ifndef AFFY_DATASET_H
#define AFFY_DATASET_H

#include <stdio.h>

#define SIZE 246710


// movie dataframe
struct Movie{
    char* tconst;
    char* primaryTitle;
    char** genres;
    double rating;
    char** nconsts;
    int nb_nconst;
    int nb_genres;
};
typedef struct Movie MOVIE;

MOVIE* init_dataset(FILE* stream);

void free_dataset(MOVIE* dataset);

MOVIE* get_dataset();

#endif //AFFY_DATASET_H
