/*
 * Filename : search_gui.c
 *
 * Made by : Léa LAROZE and Joakim PETTERSEN
 *
 * Created : 14/53/2021
 *
 * Description : Search engine with OMDb's api as back-end.
*/

#include <gtk/gtk.h>
#include "search_gui.h"
#include "request.h"
#include "parse_json.h"
#include "init_gui.h"
#include "watchlist.h"
#include "get_top_10.h"

// add movie to watchlist
void on_btn_add_clicked(GtkButton* btn, GtkLabel* id){
    char* movie_id;
    int index;

    gtk_widget_hide(GTK_WIDGET(btn));
    movie_id = gtk_label_get_text(id);

    index = get_index(movie_id, dataset);

    watchlist_size++;
    watchlist_array = realloc(watchlist_array, watchlist_size);

    watchlist_array[watchlist_size-1] = index;

}

// reset grid
void clean_grid(GtkGrid* grid){
    for (int i = 10; i > -1; --i) {
        gtk_grid_remove_row(GTK_GRID(grid), i);
    }
}

int check_in_array(char* id){
    int index = get_index(id, dataset);

    // if 0, then not in dataset, then pop it
    if (index == 0) { return 1;}

    for (int i = 0; i < watchlist_size; ++i) {
        if (index == watchlist_array[i]){return 1;}
    }

    return 0;
}

void on_search_entry_activate(GtkEntry* search_entry, GtkGrid* search_grid){
    const gchar* text;

    // if entry empty then do nothing
    if (gtk_entry_get_text_length(GTK_ENTRY(search_entry)) == 0) {return;}

    // get input from entry
    text = gtk_entry_get_text(GTK_ENTRY(search_entry));

    // empty the grid
    clean_grid(search_grid);

    // do search request to api
    RESULT_SEARCH result = search(strdup(text), apikey_global); // duplicate because i'm changing the string

    // if null then error or not found, check STDOUT for the error msg
    if (result.titles == NULL){
        GtkWidget* not_found = gtk_label_new("No result"); // In case it's not found

        gtk_grid_insert_row(GTK_GRID(search_grid), 0);
        gtk_grid_attach(GTK_GRID(search_grid), not_found, 0, 0, 1, 1);
    } else {
        // iterate through result to print titles
        for (int i = 0; i < result.nb; ++i) {
            char title_bold[255];

            if (check_in_array(result.ids[i])) {continue;}

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
            gtk_label_set_selectable(GTK_LABEL(id), TRUE);

            GtkWidget* btn_add = gtk_button_new_from_icon_name("gtk-add", GTK_ICON_SIZE_BUTTON);
            g_signal_connect (btn_add, "clicked", G_CALLBACK (on_btn_add_clicked), id);

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
