//
// Created by user0 on 2/20/21.
//
#include <gtk/gtk.h>
#include "search_gui.h"
#include "request.h"
#include "parse_json.h"

void clean_grid(GtkGrid* grid){
    for (int i = 10; i > -1; --i) {
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
    RESULT_SEARCH result = search(strdup(text)); // duplicate because i'm changing the string

    // if null then error or not found, check STDOUT for the error msg
    if (result.titles == NULL){
        GtkWidget* not_found = gtk_label_new("No result"); // In case it's not found

        gtk_grid_insert_row(GTK_GRID(search_grid), 0);
        gtk_grid_attach(GTK_GRID(search_grid), not_found, 0, 0, 1, 1);
    } else {
        // iterate through result to print titles
        for (int i = 0; i < result.nb; ++i) {
            char title_bold[255];
            // todo: check if in watchlist

            // add a row
            gtk_grid_insert_row(GTK_GRID(search_grid), i);

            // create widgets
            GtkWidget* title = gtk_label_new(result.titles[i]);
            sprintf(title_bold, "<b>%s</b>", result.titles[i]);
            gtk_label_set_markup(GTK_LABEL(title), title_bold);
            gtk_label_set_selectable(GTK_LABEL(title), TRUE);
            gtk_label_set_justify(GTK_LABEL(title), GTK_JUSTIFY_CENTER);

            GtkWidget* year = gtk_label_new(result.years[i]);
            GtkWidget* id = gtk_label_new(result.ids[i]);

            GtkWidget* btn_add = gtk_button_new_from_icon_name("gtk-add", GTK_ICON_SIZE_BUTTON);
            //g_signal_connect (btn_add, "clicked", G_CALLBACK (end_program), NULL);

            // insert widget
            gtk_grid_attach(GTK_GRID(search_grid), title, 0, i, 1, 1);
            gtk_grid_attach(GTK_GRID(search_grid), year, 1, i, 1, 1);
            gtk_grid_attach(GTK_GRID(search_grid), id, 2, i, 1, 1);
            gtk_grid_attach(GTK_GRID(search_grid), btn_add, 3, i, 1, 1);
        }
    }

    // show result
    gtk_widget_show_all((GtkWidget *) search_grid);

    // free result
    free_search_result(result);
}
