#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataset.h"


// clean this mess
char** init_bag_of_word(struct Movie* movie1, struct Movie* movie2, int* counter){
    *counter = movie1->nb_genres;
    int counter_nconsts = movie1->nb_nconst;
    char** list = malloc(sizeof(char *) * (*counter));

    for (int i = 0; i < *counter; i++) {
        list[i] = movie1->genres[i];
    }

    for (int i = 0; i < movie2->nb_genres; ++i){
        int counter2 = 0;
        char* str1 = movie2->genres[i];
        for (int j = 0; j < *counter; ++j) {
            char* str2 = movie1->genres[j];
            if (strcmp(str1, str2) == 0){
                counter2++;
                break;
            }
        }

        if (counter2 == 0){
            (*counter)++;
            list = realloc(list, sizeof(char *) * *counter);
            list[(*counter)-1] = movie2->genres[i];
        }
    }

    for (int i = 0; i < counter_nconsts; ++i) {
        (*counter)++;
        list = realloc(list, sizeof(char *) * (*counter));
        list[(*counter)-1] = movie1->nconsts[i];
    }


    for (int i = 0; i < movie2->nb_nconst; ++i){
        int counter2 = 0;
        char* str1 = movie2->nconsts[i];
        for (int j = 0; j < counter_nconsts; ++j) {
            char* str2 = movie1->nconsts[j];
            if (strcmp(str1, str2) == 0){
                counter2++;
                break;
            }
        }

        if (counter2 == 0){
            (*counter)++;
            list = realloc(list, sizeof(char *) * (*counter));
            list[(*counter)-1] = movie2->nconsts[i];
        }
    }
    return list;
}

double* get_cosine_similarity(struct Movie* movie1, struct Movie* movie2){
    int counter = 0;
    char** list = init_bag_of_word(movie1, movie2, &counter);


    for (int i = 0; i < counter; ++i) {
        printf("\n%s", list[i]);
    }

    free(list);
    return NULL;
}




// main
int main() {
    struct Movie *dataset; // the list of movies and their details
    double* cosine = NULL;


    // get the dataset from local file into a list of Movies (made be commit suicide)
    FILE* dataset_file = fopen("data.tsv", "r"); // dataset local .tsv file
    if (dataset_file == NULL){
        printf("\nCould not read dataset file.\nExit...");
        exit(EXIT_FAILURE);
    }
    dataset = init_dataset(dataset_file);
    fclose(dataset_file);

    /*for (int i = 0; i < 10; ++i) {
        printf("\n%d", dataset[i].nb_genres);
    }*/


    cosine = get_cosine_similarity(&dataset[0], &dataset[1]);


    free(cosine);
    free_dataset(dataset);
    //free(dataset); //cannot free because heap corruption (wtf) (maybe I forgot to free something inside idk)
    return 0;
}
