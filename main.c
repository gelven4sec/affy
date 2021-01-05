#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dataset.h"

int check_duplicate(char** list, int nb, char* str){
    for (int i = 0; i < nb; ++i) {
        if (strcmp(list[i], str) == 0) return 0;
    }
    return 1;
}

char** init_bag_words(struct Movie movie1, struct Movie movie2, int* counter, int* counter_genres){
    int size = movie1.nb_genres + movie1.nb_nconst + movie2.nb_genres + movie2.nb_nconst;
    char** list = malloc(sizeof(char *) * size);

    for (int i = 0; i < movie1.nb_genres; ++i) {
        list[i] = movie1.genres[i];
        (*counter)++;
        (*counter_genres)++;
    }

    for (int i = 0; i < movie2.nb_genres; ++i) {
        if (check_duplicate(movie1.genres, movie1.nb_genres, movie2.genres[i]) == 1){
            list[(*counter)] = movie2.genres[i];
            (*counter)++;
            (*counter_genres)++;
        }
    }

    for (int i = 0; i < movie1.nb_nconst; ++i) {
        list[(*counter)] = movie1.nconsts[i];
        (*counter)++;
    }

    for (int i = 0; i < movie2.nb_nconst; ++i) {
        if (check_duplicate(movie1.nconsts, movie1.nb_nconst, movie2.nconsts[i]) == 1){
            list[(*counter)] = movie2.nconsts[i];
            (*counter)++;
        }
    }

    return list;
}

// inverse document frequency
double idf_nconsts(char* word, struct Movie* dataset){
    int counter = 0;
    double result;

    for (int i = 0; i < 246711; ++i) {
        struct Movie movie = dataset[i];
        for (int j = 0; j < movie.nb_nconst; ++j) {
            if (strcmp(word, movie.nconsts[j]) == 0){
                counter++;
            }
        }
    }

    result = log10(246711.0/counter);

    return result;
}

double idf_genres(char* word, struct Movie* dataset){
    int counter = 0;
    double result;

    for (int i = 0; i < 246711; ++i) {
        struct Movie movie = dataset[i];
        for (int j = 0; j < movie.nb_genres; ++j) {
            if (strcmp(word, movie.genres[j]) == 0){
                counter++;
            }
        }
    }

    result = log10(246711.0/counter);

    return result;
}


double* init_list_idf(char** list, int counter, int counter_genres, struct Movie* dataset){
    double* list_idf = malloc(sizeof(double) * (counter));
    for (int i = 0; i < counter; ++i) {
        if (i < counter_genres){
            list_idf[i] = idf_genres(list[i], dataset);
        } else {
            list_idf[i] = idf_nconsts(list[i], dataset);
        }
    }

    return list_idf;
}

void init_vector(double* vector, struct Movie movie, int counter, int counter_genres, char** list, const double* list_idf){
    for (int i = 0; i < counter; ++i) {
        char* str1 = list[i];
        if (i < counter_genres){
            for (int j = 0; j < movie.nb_genres; j++){
                char* str2 = movie.genres[j];
                if (strcmp(str1, str2) == 0){
                    vector[i] = list_idf[i];
                    break;
                } else {
                    vector[i] = 0.0;
                }

            }
        } else {
            for (int j = 0; j < movie.nb_nconst; j++){
                char* str2 = movie.nconsts[j];
                if (strcmp(str1, str2) == 0){
                    vector[i] = list_idf[i];
                    break;
                } else {
                    vector[i] = 0.0;
                }

            }
        }

    }
}

// cos(x, y) = x * y / ( ||x|| * ||y|| )
double cosine_similarity(const double* x, const double* y, int counter){
    double result;
    double x_y = 0;
    double abs_x = 0;
    double abs_y = 0;

    for (int i = 0; i < counter; ++i) {
        x_y = x_y + (x[i] * y[i]);
    }

    // if x*y = 0 then cosine is 90° anyway
    if (x_y == 0.0){
        return 0.0;
    }

    for (int i = 0; i < counter; ++i) {
        abs_x = abs_x + ( x[i] * x[i] );
    }
    abs_x = sqrt(abs_x);

    for (int i = 0; i < counter; ++i) {
        abs_y = abs_y + ( y[i] * y[i] );
    }
    abs_y = sqrt(abs_y);

    result = x_y / (abs_x * abs_y);

    return result;
}


double get_cosine_similarity(struct Movie movie1, struct Movie movie2, struct Movie* dataset){
    int counter = 0;
    int counter_genres = 0;
    char** list = init_bag_words(movie1, movie2, &counter, &counter_genres);
    double* list_idf = init_list_idf(list, counter, counter_genres, dataset);
    double* vector1 = malloc(sizeof(double) * counter);
    double* vector2 = malloc(sizeof(double) * counter);
    double result;

    init_vector(vector1, movie1, counter, counter_genres, list, list_idf);
    init_vector(vector2, movie2, counter, counter_genres, list, list_idf);

    result = cosine_similarity(vector1, vector2, counter);

    free(vector1);
    free(vector2);
    free(list);
    free(list_idf);
    return result;
}


// main
int main() {
    struct Movie *dataset; // the list of movies and their details
    double* cosine = malloc(sizeof(double)*1000);



    // get the dataset from local file into a list of Movies (made be commit suicide)
    FILE* dataset_file = fopen("data.tsv", "r"); // dataset local .tsv file
    if (dataset_file == NULL){
        printf("\nCould not read dataset file.\nExit...");
        exit(EXIT_FAILURE);
    }
    dataset = init_dataset(dataset_file);
    fclose(dataset_file);

    printf("Begin !");
    for (int i = 0; i < 1000; ++i) {
        cosine[i] = get_cosine_similarity(dataset[1], dataset[i], dataset);
    }
    printf("\nFinished !");


    free(cosine);
    free_dataset(dataset);
    free(dataset); //cannot free because heap corruption (wtf) (maybe I forgot to free something inside idk or double free)
    return 0;
}
