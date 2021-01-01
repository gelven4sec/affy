//
// Created by user0 on 1/1/2021.
//


#ifndef AFFY_DATASET_H
#define AFFY_DATASET_H

#include <stdio.h>

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

char** get_fields(char* line);

double rating_float(char* rating_s);

int nb_nconsts(const char* line);

char** get_words(char* line, int* counter);

struct Movie get_movie(char* line);

struct Movie * init_dataset(FILE* stream);

void free_nconsts(struct Movie* movie);

void free_genres(struct Movie* movie);

void free_dataset(struct Movie* dataset);

//void print_dataset_10(struct Movie* dataset);

struct Movie getter_movie(struct Movie* dataset, int row);

#endif //AFFY_DATASET_H
