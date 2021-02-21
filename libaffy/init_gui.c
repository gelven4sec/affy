//
// Created by user0 on 2/21/21.
//

#include <gtk/gtk.h>
#include "init_gui.h"
#include "watchlist.h"

void init_gui(int argc, char **argv){
    gtk_init (&argc, &argv);

    GtkBuilder *builder = gtk_builder_new ();
    builder_global = builder;

    gtk_builder_add_from_file (builder, "../glade/main.glade", NULL);
    GtkWidget* win = (GtkWidget*) gtk_builder_get_object (builder,"main_window");
    gtk_builder_connect_signals(builder, NULL);

    gtk_widget_show_all (win);


    watchlist_array = watchlist(&watchlist_size);

    for (int i = 0; watchlist_array[i] != NULL; ++i) {
        printf("%s", watchlist_array[i]);
    }

    free_watchlist(watchlist_array);

    gtk_main ();
}