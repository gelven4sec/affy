#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dataset.h"
#include "cosine_similarity.h"


// main
int main() {
    struct Movie *dataset; // the list of movies and their details
    double cosine;

    // get the dataset from local file into a list of Movies (made be commit suicide)
    FILE* dataset_file = fopen("data.tsv", "r"); // dataset local .tsv file
    if (dataset_file == NULL){
        printf("\nCould not read dataset file.\nExit...");
        exit(EXIT_FAILURE);
    }
    dataset = init_dataset(dataset_file);
    fclose(dataset_file);

    cosine = get_cosine_similarity(dataset[435], dataset[51246]);
    printf("\nCosine similarity: %lf", cosine);

    free_dataset(dataset);
    free(dataset);
    return 0;
}
