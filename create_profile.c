//
// Created by user0 on 1/16/2021.
//

#include "create_profile.h"
#include <stdlib.h>
#include "dataset.h"
#include "get_top_10.h"
#include "cosine_similarity.h"

void init_genres(struct Movie movie, char** list, int* counter){
    for (int i = 0; i < movie.nb_genres; ++i) {
        if (check_duplicate(list, *counter, movie.genres[i]) == 1){
            list[(*counter)] = movie.genres[i];
            (*counter)++;
        }
    }
}

void init_nconsts(struct Movie movie, char** list, int* counter){
    for (int i = 0; i < movie.nb_nconst; ++i) {
        if (check_duplicate(list, *counter, movie.nconsts[i]) == 1){
            list[(*counter)] = movie.nconsts[i];
            (*counter)++;
        }
    }
}

struct Movie create_user_profile(char** list, int nb, struct Movie* dataset){
    int list_index[nb];
    int counter_nconst = 0;
    int counter_genres = 0;
    int size_nconst = 0;
    int size_genres = 0;
    char** list_genres;
    char** list_nconst;


    for (int i = 0; i < nb; ++i) {
        list_index[i] = get_index(list[i], dataset);
    }

    for (int i = 0; i < nb; ++i) {
        size_genres = size_genres + dataset[list_index[i]].nb_genres;
    }

    for (int i = 0; i < nb; ++i) {
        size_nconst = size_nconst + dataset[list_index[i]].nb_nconst;
    }

    list_genres = malloc(sizeof(char*) * size_genres);
    list_nconst = malloc(sizeof(char*) * size_nconst);

    for (int i = 0; i < nb; ++i) {
        init_genres(dataset[list_index[i]], list_genres, &counter_genres);
        init_nconsts(dataset[list_index[i]], list_nconst, &counter_nconst);
    }

    struct Movie user_profile = {
            "user-profile",
            "user-profile",
            list_genres,
            0.0,
            list_nconst,
            counter_nconst,
            counter_genres
    };

    return user_profile;
}