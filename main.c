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


// main
int main() {
    struct Movie *dataset; // the list of movies and their details
    int* result_list;

    // get the dataset from local file into a list of Movies (made be commit suicide)
    FILE* dataset_file = fopen("../dataset/data.tsv", "r"); // dataset local .tsv file
    if (dataset_file == NULL){
        printf("\nCould not read dataset file.\nExit...");
        exit(EXIT_FAILURE);
    }
    dataset = init_dataset(dataset_file);
    fclose(dataset_file);

    result_list = get_top_10("tt0120915", dataset); // slow as fuck

    // DEBUG
    for (int i = 0; i < 10; ++i) {
        printf("\n%d : %s", result_list[i], dataset[result_list[i]].primaryTile);
    }

    free(result_list);
    free_dataset(dataset);
    free(dataset);
    return 0;
}
