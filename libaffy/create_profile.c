/*
 * Filename : create_profile.c
 *
 * Made by : Léa LAROZE and Joakim PETTERSEN
 *
 * Created : 24/13/5252
 *
 * Description : Create user profile structure.
*/

#include "create_profile.h"
#include <stdlib.h>
#include "dataset.h"
#include "cosine_similarity.h"

void init_genres(MOVIE movie, char** list, int* counter){
    for (int i = 0; i < movie.nb_genres; ++i) {
        if (check_duplicate(list, *counter, movie.genres[i]) == 1){
            list[(*counter)] = movie.genres[i];
            (*counter)++;
        }
    }
}

void init_nconsts(MOVIE movie, char** list, int* counter){
    for (int i = 0; i < movie.nb_nconst; ++i) {
        if (check_duplicate(list, *counter, movie.nconsts[i]) == 1){
            list[(*counter)] = movie.nconsts[i];
            (*counter)++;
        }
    }
}

MOVIE create_user_profile(const int* list_index, int nb, MOVIE* dataset){
    int counter_nconst = 0;
    int counter_genres = 0;
    int size_nconst = 0;
    int size_genres = 0;
    char** list_genres;
    char** list_nconst;

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

    MOVIE user_profile = {
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