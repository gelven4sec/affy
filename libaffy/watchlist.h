//
// Created by user0 on 2/21/21.
//

#ifndef AFFY_WATCHLIST_H
#define AFFY_WATCHLIST_H

#include <stdio.h>

size_t watchlist_size;
char** watchlist_array;

void free_watchlist(char** list);

char** watchlist(size_t* counter);

#endif //AFFY_WATCHLIST_H
