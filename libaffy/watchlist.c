//
// Created by user0 on 2/21/21.
//
#include "watchlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

void free_watchlist(char** list){
    for (int i = 0; list[i] != NULL; ++i) {
        free(list[i]);
    }
    free(list);
}

char** watchlist(size_t* counter) {
    FILE *file;
    unsigned long n;
    char** list;
    char id_tmp[1024];
    char* line = NULL;
    size_t line_size = 0;
    *counter = 0;

    //Check if file exist
    file = fopen("../dataset/watchlist.txt", "r");
    if (file == NULL) {
        return NULL;
    }

    fseek(file,0 ,SEEK_END);

    n = ftell(file);

    if (n == 0) {
        fclose(file);
        return NULL;

    } else {
        list = malloc(sizeof(char*) * (n/10)+1);

        fseek(file,0 ,SEEK_SET);

        while (fgets(id_tmp, 1024, file)){
            char* tmp = strdup(id_tmp);

            // remove new line character from string
            char* temp = strchr(tmp, '\n');
            *temp = '\0';

            list[*counter] = tmp;
            (*counter)++;

        }
        list[*counter] = NULL;
    }

    fclose(file);

    return list;
}



