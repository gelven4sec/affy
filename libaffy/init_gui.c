/*
 * Filename : init_gui.c
 *
 * Made by : Léa LAROZE and Joakim PETTERSEN
 *
 * Created : 07/01/2021
 *
 * Description : Principle function to call gui interface.
*/

#include <gtk/gtk.h>
#include "init_gui.h"
#include "watchlist.h"
#include "config_file.h"

void on_main_window_destroy(){

    // save watchlist into file from memory
    save_watchlist();

    free_dataset(dataset);

    // can be null if no watchlist file
    if (watchlist_array != NULL) {free(watchlist_array);}

    // exit gtk main loop
    gtk_main_quit();

    printf("\nExiting AFFY...\n");
}

void init_gui(int argc, char **argv){
    const char* apikey = NULL;

    gtk_init(&argc, &argv);
    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "../glade/main.glade", NULL);

    // need builder to access widgets from anywhere
    builder_global = builder;

    // get apikey from config file
    apikey = init_config();

    // make apikey accessible from anywhere
    apikey_global = apikey;

    if (apikey == NULL) {

        // if error with config file, show error dialog
        GtkWidget* error_win = (GtkWidget*) gtk_builder_get_object(builder,"error_window");
        gtk_builder_connect_signals(builder, NULL);
        gtk_widget_show_all(error_win);

    } else {

        // load movie dataset file into memory
        dataset = get_dataset();

        GtkWidget* win = (GtkWidget*) gtk_builder_get_object(builder,"main_window");
        gtk_builder_connect_signals(builder, NULL);

        gtk_widget_show_all(win);

        // load watchlist file into memory
        watchlist_array = watchlist(&watchlist_size);
    }

    gtk_main();
}