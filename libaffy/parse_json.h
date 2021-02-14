//
// Created by user0 on 2/14/21.
//

#ifndef AFFY_PARSE_JSON_H
#define AFFY_PARSE_JSON_H

struct Result{
    char** titles;
    char** years;
    char** ids;
    size_t nb;
};
typedef struct Result RESULT_SEARCH;

struct ResultTitle{
    char* test; //todo: determine what information to take
};

RESULT_SEARCH get_title_list(char* result);

#endif //AFFY_PARSE_JSON_H
