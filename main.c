#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataset.h"


// main
int main() {
    struct Movie *dataset; // the list of movies and their details


    // get the dataset from local file into a list of Movies (made be commit suicide)
    FILE* dataset_file = fopen("data.tsv", "r"); // dataset local .tsv file
    if (dataset_file == NULL){
        printf("\nCould not read dataset file. Exit...");
        exit(EXIT_FAILURE);
    }
    dataset = init_dataset(dataset_file);
    fclose(dataset_file);




    free_dataset(dataset);
    //free(dataset); //cannot free because heap corruption (wtf) (maybe I forgot to free something inside idk)
    return 0;
}
