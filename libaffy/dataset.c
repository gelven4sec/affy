/*
 * Filename : dataset.c
 *
 * Made by : Léa LAROZE and Joakim PETTERSEN
 *
 * Created : 20/12/2020
 *
 * Description : Load dataset and return list of movies.
*/

#include "dataset.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// read dataset file and return pointer to list
MOVIE* get_dataset(){
    MOVIE* dataset;

    // dataset local .tsv file
    FILE* dataset_file = fopen("../dataset/data.tsv", "r");

    if (dataset_file == NULL){
        printf("\nCould not read dataset file.\nExit...");
        exit(EXIT_FAILURE);
    }

    dataset = init_dataset(dataset_file);
    fclose(dataset_file);

    return dataset;
}

// return the fields per lines
char** get_fields(char* line){
    char* tok;

    // 5 because we know there are 5 fields
    char** list = malloc(sizeof(char *) * 5);
    int counter = 0;

    // split string with much pain and over-head
    for (tok = strtok(line, "\t"); tok && *tok; tok = strtok(NULL, "\t\n")){
        char* token = strdup(tok);
        list[counter] = token;
        counter++;
        if (counter >= 5){
            break;
        }
    }

    return list;
}

// convert averageRating from dataset into a double
double rating_float(char* rating_s){
    double rating;
    rating = atof(rating_s);
    free(rating_s);
    return rating;
}

// count words
int nb_nconsts(const char* line){
    int count = 0;

    // get number of separator
    for (int i = 0; line[i] != '\0'; ++i) {
        if (',' == line[i])
            ++count;
    }
    // nb separator+1 = number of fields
    return count+1;
}

// return the crews per lines
char** get_words(char* line, int* counter){
    char* tok;
    int words = nb_nconsts(line);
    char** list = malloc(sizeof(char *) * words);
    *counter = 0;

    // split string with much pain and over-head
    for (tok = strtok(line, ","); tok && *tok; tok = strtok(NULL, ",\n")){
        char* token = strdup(tok);
        list[*counter] = token;
        (*counter)++;
        if (*counter >= words){
            break;
        }
    }

    free(line);
    return list;
}

// return movie structure for dataset
MOVIE get_movie(char* line){
    int nb_nconsts;
    int nb_genres;
    char** list = get_fields(line);

    MOVIE movie = {
            list[0],
            list[1],
            get_words(list[2], &nb_genres),
            rating_float(list[3]),
            get_words(list[4], &nb_nconsts),
            nb_nconsts,
            nb_genres
    };

    free(list);
    return movie;
}

// return full dataset
MOVIE* init_dataset(FILE* stream){
    MOVIE* dataset;
    char line[1024];
    int counter = 0;

    dataset = malloc(sizeof(MOVIE)*SIZE);
    if (dataset == NULL) {
        printf("\nFailed to allocate memory to dataset.");
        exit(EXIT_FAILURE);
    }

    // iterate though file lines
    while (fgets(line, 1024, stream)){
        dataset[counter] = get_movie(line);
        counter++;
    }

    return dataset;
}

void free_nconsts(const MOVIE* movie){
    for (int i = 0; i < movie->nb_nconst; i++){
        free(movie->nconsts[i]);
    }
    free(movie->nconsts);
}

void free_genres(const MOVIE* movie){
    for (int i = 0; i < movie->nb_genres; i++){
        free(movie->genres[i]);
    }
    free(movie->genres);
}

// free dataset
void free_dataset(MOVIE* dataset){
    for (int i = 0; i < SIZE; i++){
        free(dataset[i].tconst);
        free(dataset[i].primaryTitle);
        free_genres(&dataset[i]);
        free_nconsts(&dataset[i]);
    }
    free(dataset);
}