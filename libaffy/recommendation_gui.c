//
// Created by user0 on 2/22/21.
//

#include "recommendation_gui.h"
#include "search_gui.h"
#include "get_top_10.h"
#include "create_profile.h"
#include "watchlist.h"

void on_recommendation_btn_clicked(GtkButton* btn, GtkGrid* grid){
    MOVIE user_profile;
    int* result_list;

    // empty the grid
    clean_grid(grid);

    user_profile = create_user_profile(watchlist_array, watchlist_size, dataset);

    result_list = get_top_10_user(&user_profile, dataset, watchlist_array, watchlist_size);

    for (int i = 0; i < 10; ++i) {
        char title_bold[255];
        char rating_s[10];

        // add a row
        gtk_grid_insert_row(GTK_GRID(grid), i);

        // create widgets
        GtkWidget* title = gtk_label_new(dataset[result_list[i]].primaryTitle);
        sprintf(title_bold, "<b>%s</b>", dataset[result_list[i]].primaryTitle);
        gtk_label_set_markup(GTK_LABEL(title), title_bold);
        gtk_label_set_selectable(GTK_LABEL(title), TRUE);
        gtk_label_set_justify(GTK_LABEL(title), GTK_JUSTIFY_CENTER);

        sprintf(rating_s, "%lf", dataset[result_list[i]].rating);
        GtkWidget* rating = gtk_label_new(rating_s);
        GtkWidget* id = gtk_label_new(dataset[result_list[i]].tconst);
        gtk_label_set_selectable(GTK_LABEL(id), TRUE);

        // insert widget
        gtk_grid_attach(GTK_GRID(grid), title, 0, i, 1, 1);
        gtk_grid_attach(GTK_GRID(grid), rating, 1, i, 1, 1);
        gtk_grid_attach(GTK_GRID(grid), id, 2, i, 1, 1);
        //gtk_grid_attach(GTK_GRID(search_grid), btn_add, 3, i, 1, 1);
    }

    // show result
    gtk_widget_show_all((GtkWidget *) grid);

    // free result
    free(result_list);
}