//
// Created by user0 on 2/21/21.
//

#include <gtk/gtk.h>
#include "init_gui.h"
#include "watchlist.h"
#include "config_file.h"

void on_main_window_destroy(){
    save_watchlist();
    free_dataset(dataset);
    if (watchlist_array != NULL) {free(watchlist_array);}
    gtk_main_quit();
    printf("\nExiting AFFY...\n");
}

void init_gui(int argc, char **argv){
    const char* apikey = NULL;
    gtk_init (&argc, &argv);
    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "../glade/main.glade", NULL);
    builder_global = builder;

    apikey = init_config();
    apikey_global = apikey;

    if (apikey == NULL) {
        GtkWidget* error_win = (GtkWidget*) gtk_builder_get_object(builder,"error_window");
        gtk_builder_connect_signals(builder, NULL);
        gtk_widget_show_all(error_win);
    } else {
        dataset = get_dataset();

        GtkWidget* win = (GtkWidget*) gtk_builder_get_object(builder,"main_window");
        gtk_builder_connect_signals(builder, NULL);

        gtk_widget_show_all(win);

        watchlist_array = watchlist(&watchlist_size);
    }

    gtk_main();
}