//
// Created by user0 on 2/20/21.
//
#include <gtk/gtk.h>
#include "search_gui.h"
#include "request.h"
#include "parse_json.h"

void clean_grid(GtkGrid* grid){
    for (int i = 100; i > -1; --i) {
        gtk_grid_remove_row(GTK_GRID(grid), i);
    }
}

void on_search_entry_activate(GtkEntry* search_entry, GtkGrid* search_grid){
    const gchar* text;

    // if entry empty then do nothing
    if (gtk_entry_get_text_length(GTK_ENTRY(search_entry)) == 0) {return;}

    // get input from entry
    text = gtk_entry_get_text(GTK_ENTRY(search_entry));
    //g_print("%s\n", text); // DEBUG

    // empty the grid
    clean_grid(search_grid);

    // do search request to api
    RESULT_SEARCH result = search(text);

    // if null then error or not found, check STDOUT for the error msg
    if (result.titles == NULL){
        GtkWidget* not_found = gtk_label_new("No result"); // In case it's not found

        gtk_grid_insert_row(GTK_GRID(search_grid), 0);
        gtk_grid_attach(GTK_GRID(search_grid), not_found, 0, 0, 1, 1);
    } else {
        // iterate through result to print titles
        for (int i = 0; i < result.nb; ++i) {
            gtk_grid_insert_row(GTK_GRID(search_grid), i);
            GtkWidget* title = gtk_label_new(result.titles[i]);
            GtkWidget* year = gtk_label_new(result.years[i]);
            GtkWidget* id = gtk_label_new(result.ids[i]);
            gtk_grid_attach(GTK_GRID(search_grid), title, 0, i, 1, 1);
            gtk_grid_attach(GTK_GRID(search_grid), year, 1, i, 1, 1);
            gtk_grid_attach(GTK_GRID(search_grid), id, 2, i, 1, 1);

        }
    }

    // show result
    gtk_widget_show_all((GtkWidget *) search_grid);

    // free result
    free_search_result(result);
}
