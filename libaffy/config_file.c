//
// Created by user0 on 2/23/21.
//

#include <stdio.h>
#include "config_file.h"
#include "parse_json.h"

const char* init_config(){
    unsigned long n;
    char buffer[1024];
    const char* apikey;

    FILE* config_file = fopen("../dataset/config.json", "r");

    if (config_file == NULL) {return NULL;}

    // get file size
    fseek(config_file,0 ,SEEK_END);
    n = ftell(config_file);

    // file empty
    if (n == 0) {
        fclose(config_file);
        return NULL;

    }

    fseek(config_file, 0, SEEK_SET);

    fread(buffer, 1024, 1, config_file);
    fclose(config_file);

    apikey = get_apikey(buffer);

    return apikey;
}