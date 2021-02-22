//
// Created by user0 on 2/21/21.
//
#include "watchlist.h"
#include "init_gui.h"
#include "get_top_10.h"
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

void free_watchlist_char(char** list){
    for (int i = 0; i < watchlist_size; ++i) {
        free(list[i]);
    }
    free(watchlist_array);
}

int* get_watchlist_indexes(char** list){
    int* list_index = malloc(sizeof(int) * watchlist_size);

    for (int i = 0; i < watchlist_size; ++i) {
        list_index[i] = get_index(list[i], dataset);
    }

    // don't need anymore
    free_watchlist_char(list);

    return list_index;
}

int* watchlist(size_t* counter) {
    FILE *file;
    unsigned long n;
    char** list;
    char id_tmp[1024];
    *counter = 0;

    //Check if file exist
    file = fopen("../dataset/watchlist.txt", "r");
    if (file == NULL) {
        return NULL;
    }

    // get file size
    fseek(file,0 ,SEEK_END);
    n = ftell(file);

    // file empty or not well filled, len(id+'\n') == 10
    if (n == 0 || n%10 != 0) {
        fclose(file);
        return NULL;

    } else {
        list = malloc(sizeof(char*) * (n/10));

        fseek(file,0 ,SEEK_SET);

        while (fgets(id_tmp, 1024, file)){
            char* tmp = strdup(id_tmp);

            // remove new line character from string
            char* temp = strchr(tmp, '\n');
            *temp = '\0';

            list[*counter] = tmp;
            (*counter)++;

        }
    }

    fclose(file);

    return get_watchlist_indexes(list); // list free here
}

void clean_watchlist_grid(GtkGrid* grid){
    for (int i = watchlist_size; i > -1; --i) {
        gtk_grid_remove_row(GTK_GRID(grid), i);
    }
}

void fill_watchlist_grid(){
    GtkWidget* watchlist_grid = (GtkWidget*) gtk_builder_get_object (builder_global,"watchlist_grid");

    // empty the grid
    clean_watchlist_grid(GTK_GRID(watchlist_grid));

    // if no file or corrupt
    if (watchlist_array == NULL){
        GtkWidget* not_found = gtk_label_new("List empty... (You've never seen a movie ?)"); // In case it's not found

        gtk_grid_insert_row(GTK_GRID(watchlist_grid), 0);
        gtk_grid_attach(GTK_GRID(watchlist_grid), not_found, 0, 0, 1, 1);
    }

    for (int i = 0; i < watchlist_size; ++i) {
        char title_bold[255];

        // add a row
        gtk_grid_insert_row(GTK_GRID(watchlist_grid), i);

        // create widgets
        GtkWidget* title = gtk_label_new(dataset[watchlist_array[i]].primaryTitle);
        sprintf(title_bold, "<b>%s</b>", dataset[watchlist_array[i]].primaryTitle);
        gtk_label_set_markup(GTK_LABEL(title), title_bold);
        gtk_label_set_selectable(GTK_LABEL(title), TRUE);
        gtk_label_set_justify(GTK_LABEL(title), GTK_JUSTIFY_CENTER);

        GtkWidget* id = gtk_label_new(dataset[watchlist_array[i]].tconst);

        GtkWidget* btn_add = gtk_button_new_from_icon_name("gtk-delete", GTK_ICON_SIZE_BUTTON);
        //g_signal_connect (btn_add, "clicked", G_CALLBACK (on_btn_add_clicked), id); //todo: delete movie from watchlist

        // insert widget
        gtk_grid_attach(GTK_GRID(watchlist_grid), title, 0, i, 2, 1);
        gtk_grid_attach(GTK_GRID(watchlist_grid), id, 2, i, 1, 1);
        gtk_grid_attach(GTK_GRID(watchlist_grid), btn_add, 3, i, 1, 1);
    }

    gtk_widget_show_all((GtkWidget *) watchlist_grid);
}

