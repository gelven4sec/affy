//
// Created by AFFY developers on 1/8/2021.
//
// This is the main source file of the AFFY project.
// AFFY is a Content-Based recommender system for movies.
//
#include <stdio.h>
#include <stdlib.h>
#include "libaffy/init_gui.h"

// main
int main(int argc, char **argv) {
    /*MOVIE* dataset; // the list of movies and their details
    char** liked = create_liked();
    MOVIE user_profile;
    int* result_list;


    // get the dataset from local file into a list of Movies (made be commit suicide)
    dataset = get_dataset();

    user_profile = create_user_profile(liked, 3, dataset);

    result_list = get_top_10_user(&user_profile, dataset, liked, 3); // liked is freed here for now

    // DEBUG
    for (int i = 0; i < 10; ++i) {
        printf("\n%d : %s", result_list[i], dataset[result_list[i]].primaryTitle);
    }

    free(user_profile.genres);
    free(user_profile.nconsts);
    */

    init_gui(argc, argv);

    return 0;
}
