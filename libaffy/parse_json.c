/*
 * Filename : parse_json.c
 *
 * Made by : Léa LAROZE and Joakim PETTERSEN
 *
 * Created : 02/24/2021
 *
 * Description : Parse json content and return usable data.
*/

#include <stdio.h>
#include <string.h>
#include <json-c/json.h>
#include "parse_json.h"

void free_search_result(RESULT_SEARCH result){
    // if null then nothing was found then dont need to free
    if (result.titles != NULL){
        // free titles
        for (int i = 0; i < result.nb; ++i) {
            free(result.titles[i]);
        }
        free(result.titles);

        // free years
        for (int i = 0; i < result.nb; ++i) {
            free(result.years[i]);
        }
        free(result.years);

        // free ids
        for (int i = 0; i < result.nb; ++i) {
            free(result.ids[i]);
        }
        free(result.ids);
    }
}

// OMDb provide a Response field to prevent failed query
int check_response(const struct json_object* parsed_result){
    struct json_object* response;
    struct json_object* error;

    json_object_object_get_ex(parsed_result, "Response", &response);
    json_object_object_get_ex(parsed_result, "Error", &error);
    //printf("\n%s", json_object_get_string(response));

    if (strcmp(json_object_get_string(response), "False") == 0){
        printf("\nError: %s", json_object_get_string(error));
        return 1;
    }
    return 0;
}

// Parse every structure of result
RESULT_SEARCH get_title_list(char* result){
    struct json_object* parsed_result;
    struct json_object* search;
    struct json_object* movie;
    struct json_object* movie_title;
    struct json_object* movie_year;
    struct json_object* movie_id;
    char** titles;
    char** years;
    char** ids;
    RESULT_SEARCH output;

    size_t n_movie;

    parsed_result = json_tokener_parse(result);

    // Response is the field containing a bool if the request has success
    // if no film found then false
    if (check_response(parsed_result)){
        output.titles = NULL;
        return output; // return RESULT_SEARCH with titles NULL when film not found
    }

    json_object_object_get_ex(parsed_result, "Search", &search);
    n_movie = json_object_array_length(search);

    titles = malloc(sizeof(char*) * n_movie);
    years = malloc(sizeof(char*) * n_movie);
    ids = malloc(sizeof(char*) * n_movie);

    for (int i = 0; i < n_movie; ++i) {
        movie = json_object_array_get_idx(search, i);
        json_object_object_get_ex(movie, "Title", &movie_title);
        json_object_object_get_ex(movie, "Year", &movie_year);
        json_object_object_get_ex(movie, "imdbID", &movie_id);

        titles[i] = strdup(json_object_get_string(movie_title));
        years[i] = strdup(json_object_get_string(movie_year));
        ids[i] = strdup(json_object_get_string(movie_id));
    }

    output.titles = titles;
    output.years = years;
    output.ids = ids;
    output.nb = n_movie;

    return output;
}

// parsed json string from buffer and return apikey
const char* get_apikey(char* buffer){
    struct json_object* parsed_result;
    struct json_object* apikey_obj;
    const char* apikey;

    parsed_result = json_tokener_parse(buffer);

    // stop if no valid json file
    if (parsed_result == NULL){
        return NULL;
    }

    // get apikey object from json structure
    json_object_object_get_ex(parsed_result, "apikey", &apikey_obj);
    apikey = json_object_get_string(apikey_obj);

    return apikey;
}