//
// Created by user0 on 2/21/21.
//

#include "watchlist.h"
#include<stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "parse_json.h"



void watchlist()
{
    FILE *file;
    int n;
    char **list;

    //Check if file exist
    if (file = fopen("watchlist.txt", "r"))
    {
        fclose(file);
        printf("File exists");
    }
    else
    {
        printf("File doesn't exist");
    }

    //Check if file is empty
    file = fopen("watchlist.txt","r");
    if (file ==NULL)
    {
        printf("Error cannot open file");
        exit(1);
    }
    fseek(file,0,SEEK_END);
    n=ftell(file);
    if (n==0){
        printf("\nFile is empty");
    } else {
        printf("\nFile isn't empty. \n");

        file = fopen("watchlist.txt", "r");


        /* fopen() return NULL if last operation was unsuccessful */
        if(file == NULL)
        {
            /* Unable to open file hence exit */
            printf("Unable to open file.\n");
            printf("Please check whether file exists.\n");
            exit(EXIT_FAILURE);
        }


        /* File open success */
        printf("File opened successfully\n\n");

        do
        {
            /* Read single character from file */
            list = fgetc(file);

            /* Print character read on console */
            putchar(list);

        } while(list != EOF); /* Repeat this if last read character is not EOF */


        /* Done with this file, close file to release resource */
        fclose(file);
    }

    void insert(GtkGrid* watchlist){

    // if null then error or not found, check STDOUT for the error msg
    if (list == NULL){
        GtkWidget* not_found = gtk_label_new("No result"); // In case it's not found

        gtk_grid_insert_row(GTK_GRID(watchlist), 0);
        gtk_grid_attach(GTK_GRID(watchlist), not_found, 0, 0, 1, 1);
    } else {
        // iterate through result to print id
        for (int i = 0; i < list; ++i) {
            char title_bold[255];

            // add a row
            gtk_grid_insert_row(GTK_GRID(watchlist), i);

            // create widgets
            gtk_label_set_selectable(GTK_LABEL(list), TRUE);//??
            GtkWidget* id = gtk_label_new(list);

            // insert widget
            gtk_grid_attach(GTK_GRID(list), list, 2, i, 1, 1);

        }
    }

    // show result
    gtk_widget_show_all((GtkWidget *) watchlist);
    }
}



