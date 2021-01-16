//
// Created by sven-eliasen on 1/8/2021.
//
// This is the main source file of the AFFY project.
// AFFY is a Content-Based recommender system for movies.
//
#include <stdio.h>
#include <stdlib.h>
#include "dataset.h"
#include "get_top_10.h"
#include "cosine_similarity.h"

void add_genres(struct Movie movie, char** final_list, int* list_weight, int* counter, int* counter_genres){
    for (int i = 0; i < movie.nb_genres; ++i) {
        if (*counter != 0 && check_duplicate(final_list, *counter, movie.genres[i]) == 1){

            final_list = (char**)realloc(final_list, sizeof(char*)*(*counter) + 1);
            if (final_list == NULL) {
                printf("\nFailed to reallocate !");
                exit(EXIT_FAILURE);
            }

            list_weight = (int*)realloc(list_weight, sizeof(int)*(*counter) + 1);
            if (list_weight == NULL) {
                printf("\nFailed to reallocate !");
                exit(EXIT_FAILURE);
            }

            final_list[*counter] = movie.genres[i];
            (*counter)++;
            (*counter_genres)++;
        } else if (*counter != 0 && check_duplicate(final_list, *counter, movie.genres[i]) != 1){
            int index = check_duplicate(final_list, *counter, movie.genres[i]);
            list_weight[index] = list_weight[index] + 1;
        }
    }

}

void add_nconsts(struct Movie movie, char** final_list, int* list_weight, int* counter){
    for (int i = 0; i < movie.nb_nconst; ++i) {
        if (*counter != 0 && check_duplicate(final_list, *counter, movie.nconsts[i]) == 1){

            final_list = (char**)realloc(final_list, sizeof(char*)*(*counter) + 1);
            if (final_list == NULL) {
                printf("\nFailed to reallocate !");
                exit(EXIT_FAILURE);
            }

            list_weight = (int*)realloc(list_weight, sizeof(int)*(*counter) + 1);
            if (list_weight == NULL) {
                printf("\nFailed to reallocate !");
                exit(EXIT_FAILURE);
            }

            final_list[*counter] = movie.nconsts[i];
            (*counter)++;
        } else if (*counter != 0 && check_duplicate(final_list, *counter, movie.nconsts[i]) != 1){
            int index = check_duplicate(final_list, *counter, movie.nconsts[i]);
            list_weight[index] = list_weight[index] + 5;
        }
    }

}

void init_bag_words_user(struct Movie* dataset, const int* list_index, int nb, char** final_list, int* list_weight, int* counter, int* counter_genres){
    printf("\nDEBUG 3");
    for (int i = 0; i < nb; ++i) {
        add_genres(dataset[list_index[i]], final_list, list_weight, counter, counter_genres);
        add_nconsts(dataset[list_index[i]], final_list, list_weight, counter);
        printf("\nDEBUG 4:%d", *counter);
    }

}

int get_user_recommendation(char** list, int nb, struct Movie* dataset){
    int list_index[nb];
    int counter = 0;
    int counter_genres = 0;
    char** list_words = NULL;
    int* list_weight = NULL;

    for (int i = 0; i < nb; ++i) {
        list_index[i] = get_index(list[i], dataset);
    }
    free(list);
    printf("\nDEBUG 1");
    init_bag_words_user(dataset, list_index, nb, list_words, list_weight, &counter, &counter_genres);
    printf("\nDEBUG 2");

    printf("\nDEBUG Counter %d", counter);

    for (int i = 0; i < counter; ++i) {
        printf("\nDEBUG %s", list_words[i]);
    }

    free(list_words);
    free(list_weight);

    return 0;
}

char** create_liked(){
    char** list = malloc(sizeof(char*) * 3);
    list[0] = "tt0105236";
    list[1] = "tt0110912";
    list[2] = "tt1130884";

    return list;
}

// main
int main() {
    struct Movie *dataset; // the list of movies and their details
    char** liked = create_liked();

    // get the dataset from local file into a list of Movies (made be commit suicide)
    FILE* dataset_file = fopen("../dataset/data.tsv", "r"); // dataset local .tsv file
    if (dataset_file == NULL){
        printf("\nCould not read dataset file.\nExit...");
        exit(EXIT_FAILURE);
    }
    dataset = init_dataset(dataset_file);
    fclose(dataset_file);

    get_user_recommendation(liked, 3, dataset);

    //result_list = get_top_10("tt0120915", dataset);

    // DEBUG
    /*for (int i = 0; i < 10; ++i) {
        printf("\n%d : %s", result_list[i], dataset[result_list[i]].primaryTile);
    }*/

    //free(result_list);
    free_dataset(dataset);
    free(dataset);
    return 0;
}
