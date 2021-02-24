/*
 * Filename : main.c
 *
 * Made by : Léa LAROZE and Joakim PETTERSEN
 *
 * Created : 12/12/2020
 *
 * Description : This is the main source file of the AFFY
 *               project, calling the principle function.
*/

#include <stdio.h>
#include "config_file.h"
#include "parse_json.h"

// load file and return apikey string
const char* init_config(){
    unsigned long n;
    char buffer[1024];
    const char* apikey;

    FILE* config_file = fopen("../dataset/config.json", "r");

    // if no config file then stop
    if (config_file == NULL) {return NULL;}

    // get file size
    fseek(config_file,0 ,SEEK_END);
    n = ftell(config_file);

    // file empty
    if (n == 0) {
        fclose(config_file);
        return NULL;
    }

    // reset cursor
    fseek(config_file, 0, SEEK_SET);

    // load file into string memory
    fread(buffer, 1024, 1, config_file);
    fclose(config_file);

    // parse json file and return apikey string
    apikey = get_apikey(buffer);

    return apikey;
}