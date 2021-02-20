//
// Created by sven-eliasen on 1/8/2021.
//
// This is the main source file of the AFFY project.
// AFFY is a Content-Based recommender system for movies.
//
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "libaffy/dataset.h"
#include "libaffy/get_top_10.h"
#include "libaffy/create_profile.h"
#include "libaffy/parse_json.h"
#include "libaffy/request.h"

// GLOBAL VAR (not proud of, but gtk oblige)
char apikey_global[9];
MOVIE* dataset_global;

// DEBUG
char** create_liked(){
    char** list = malloc(sizeof(char*) * 3);
    list[0] = "tt0105236";
    list[1] = "tt0110912";
    list[2] = "tt1130884";

    return list;
}

void on_search_entry_activate(GtkEntry* search_entry, GtkBox* search_container){
    const gchar* text;

    // if entry empty then do nothing
    if (gtk_entry_get_text_length(GTK_ENTRY(search_entry)) == 0) {return;}

    // get input from entry
    text = gtk_entry_get_text(GTK_ENTRY(search_entry));
    g_print("%s", text);

    //gtk_box_pack_start(GTK_BOX(search_container), )

}

// main
int main(int argc, char **argv) {
    /*MOVIE* dataset; // the list of movies and their details
    char** liked = create_liked();
    MOVIE user_profile;
    int* result_list;


    // get the dataset from local file into a list of Movies (made be commit suicide)
    dataset = get_dataset();

    user_profile = create_user_profile(liked, 3, dataset);

    result_list = get_top_10_user(&user_profile, dataset, liked, 3); // liked is freed here for now

    // DEBUG
    for (int i = 0; i < 10; ++i) {
        printf("\n%d : %s", result_list[i], dataset[result_list[i]].primaryTile);
    }

    free(user_profile.genres);
    free(user_profile.nconsts);
    free(result_list);
    free_dataset(dataset);
    free(dataset);

    RESULT_SEARCH output;
    output = search();

    for (int i = 0; i < output.nb; ++i) {
        printf("\n%d\t%s\t%s\t%s", i, output.titles[i], output.years[i], output.ids[i]);
    }*/

    gtk_init (&argc, &argv);

    GtkBuilder *builder = gtk_builder_new ();

    gtk_builder_add_from_file (builder, "../glade/main.glade", NULL);
    GtkWidget* win = (GtkWidget*) gtk_builder_get_object (builder,"main_window");
    gtk_builder_connect_signals(builder, NULL);


    gtk_widget_show_all (win);
    gtk_main ();

    return 0;
}
