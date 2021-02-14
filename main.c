//
// Created by sven-eliasen on 1/8/2021.
//
// This is the main source file of the AFFY project.
// AFFY is a Content-Based recommender system for movies.
//
#include <stdio.h>
#include <stdlib.h>
#include "libaffy/dataset.h"
#include "libaffy/get_top_10.h"
#include "libaffy/create_profile.h"
#include "libaffy/request.h"

char** create_liked(){
    char** list = malloc(sizeof(char*) * 3);
    list[0] = "tt0105236";
    list[1] = "tt0110912";
    list[2] = "tt1130884";

    return list;
}

// main
int main() {
    /*struct Movie *dataset; // the list of movies and their details
    char** liked = create_liked();
    struct Movie user_profile;
    int* result_list;

    // get the dataset from local file into a list of Movies (made be commit suicide)
    dataset = get_dataset();

    user_profile = create_user_profile(liked, 3, dataset);

    result_list = get_top_10_user(user_profile, dataset, liked, 3); // liked is freed here for now

    // DEBUG
    for (int i = 0; i < 10; ++i) {
        printf("\n%d : %s", result_list[i], dataset[result_list[i]].primaryTile);
    }

    free(user_profile.genres);
    free(user_profile.nconsts);
    free(result_list);
    free_dataset(dataset);
    free(dataset);*/

    search();

    return 0;
}
