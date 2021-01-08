#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dataset.h"
#include "cosine_similarity.h"

int get_index(char* tconst, struct Movie* dataset){
    for (int i = 1; i < SIZE; ++i) {
        if (strcmp(tconst, dataset[i].tconst) == 0) return i;
    }
    return 0;
}

int* array_index(){
    int* list = malloc(sizeof(int) * SIZE);
    for (int i = 0; i < SIZE; ++i) {
        list[i] = i;
    }
    return list;
}

int check_array(int* list, int index){
    int count = 0;
    for (int i = 0; i < 10; ++i) {
        if (list[i] == index) count++;
    }
    return count;
}

int* bubble_sort(double* list_cosine){
    int inner, outer;
    double temp_double;
    int* list = malloc(sizeof(int) * 10);
    int* list_index = array_index();

    for(outer=0;outer<SIZE-1;outer++){
        for(inner=outer+1;inner<SIZE;inner++){
            if(list_cosine[outer] < list_cosine[inner]){

                temp_double = list_cosine[outer];
                list_cosine[outer] = list_cosine[inner];
                list_cosine[inner] = temp_double;

                if (check_array(list_index, inner) == 0) {
                    list_index[outer] = inner;
                }

            }
        }
        if ((outer % 10000) == 0) printf("\n%d/246710", outer);
    }

    for (int i = 0; i < 10; ++i) {
        list[i] = list_index[i];
    }

    free(list_index);
    return list;
}

int* get_top_10(char* tconst, struct Movie* dataset){
    int index = get_index(tconst, dataset);
    double* list = malloc(sizeof(double) * SIZE);
    int* result_list;

    if (index == 0){
        printf("\nInput movie id not in dataset.\nExit...");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < SIZE; ++i) {
        list[i] = get_cosine_similarity(dataset[index], dataset[i]);
    }

    result_list = bubble_sort(list);

    free(list);
    return result_list;
}

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

    result_list = get_top_10("tt4154796", dataset);

    // DEBUG
    for (int i = 0; i < 10; ++i) {
        printf("\n%d : %s", result_list[i], dataset[result_list[i]].primaryTile);
    }

    free(result_list);
    free_dataset(dataset);
    free(dataset);
    return 0;
}
