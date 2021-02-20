//
// Created by user0 on 2/20/21.
//
#include <gtk/gtk.h>
#include "search_gui.h"

void on_search_entry_activate(GtkEntry* search_entry, GtkGrid* search_grid){
    const gchar* text;

    // if entry empty then do nothing
    if (gtk_entry_get_text_length(GTK_ENTRY(search_entry)) == 0) {return;}

    // get input from entry
    text = gtk_entry_get_text(GTK_ENTRY(search_entry));
    //g_print("%s\nDEBUG", text); // DEBUG



    //gtk_box_pack_start(GTK_BOX(search_container), )

}
