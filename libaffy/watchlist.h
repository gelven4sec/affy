//
// Created by user0 on 2/21/21.
//

#ifndef AFFY_WATCHLIST_H
#define AFFY_WATCHLIST_H

#include <stdio.h>

size_t watchlist_size;
int* watchlist_array;

int* watchlist(size_t* counter);

void fill_watchlist_grid();

void save_watchlist();

#endif //AFFY_WATCHLIST_H
