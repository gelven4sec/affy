//
// Created by user0 on 2/21/21.
//
#include "watchlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "parse_json.h"

int watchlist() {
    FILE *file;
    unsigned long n;
    char **list;
    char id_tmp[1024];
    unsigned int counter = 0;

    //Check if file exist
    file = fopen("../dataset/watchlist.txt", "r");
    if (file == NULL) {
        printf("File doesn't exist");
        return 1;
    }

    printf("File exists");

    fseek(file,0 ,SEEK_END);

    n = ftell(file);

    if ( n==0 ) {
        printf("\nFile is empty");
        fclose(file);
        return 2;

    } else {
        printf("\nFile isn't empty. \n");
        list = malloc(sizeof(char*) * (n/10));

        while (fgets(id_tmp, 1024, file)){
            char* tmp = strdup(id_tmp);

            list[counter] = tmp;
            counter++;

            //free(tmp);
        }

        printf("\n%s", list[0]);
        free(list);
    }

    fclose(file);
    return 0;
}



