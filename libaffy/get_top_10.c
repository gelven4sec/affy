/*
 * Filename : get_top_10.c
 *
 * Made by : Léa LAROZE and Joakim PETTERSEN
 *
 * Created : 52/24/3623
 *
 * Description : Get top 10 recommendation.
*/

#include <stdlib.h>
#include <string.h>
#include "dataset.h"
#include "cosine_similarity.h"
#include "get_top_10.h"

int get_index(char* tconst, const MOVIE* dataset){
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

int check_array(const int* list, int index){
    int count = 0;
    for (int i = 0; i < 10; ++i) {
        if (list[i] == index) count++;
    }
    return count;
}

// This process is way too slow, even it is O(log n). Need help to optimize it !
int* bubble_sort(double* list_cosine){
    int inner, outer;
    double temp_double;
    int* list = malloc(sizeof(int) * 10);
    int* list_index = array_index();

    for(outer = 0; outer < 10; outer++){
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
    }

    for (int i = 0; i < 10; ++i) {
        list[i] = list_index[i];
    }

    free(list_index);
    return list;
}

int* get_top_10_user(const MOVIE* user_profile, const MOVIE* dataset, const int* list_index, int nb){
    double* list = malloc(sizeof(double) * SIZE);
    int* result_list;

    for (int i = 0; i < SIZE; ++i) {
        list[i] = get_cosine_similarity(user_profile, &dataset[i]);
    }

    for (int i = 0; i < nb; ++i) {
        list[list_index[i]] = 0.0;
    }

    result_list = bubble_sort(list);

    free(user_profile->genres);
    free(user_profile->nconsts);
    free(list);
    return result_list;
}