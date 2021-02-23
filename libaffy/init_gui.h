//
// Created by user0 on 2/21/21.
//

#ifndef AFFY_INIT_GUI_H
#define AFFY_INIT_GUI_H

#include "dataset.h"
#include <gtk/gtk.h>

GtkBuilder *builder_global;
MOVIE* dataset;
const char* apikey_global;

void init_gui(int argc, char **argv);

#endif //AFFY_INIT_GUI_H
