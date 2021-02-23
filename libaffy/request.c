#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "parse_json.h"

char result[4096] = "";

// takes request's argument to return usable url
char* get_url(const char* apikey, char* title, unsigned int page){
    char* url = malloc(sizeof(char) * 1024);

    sprintf(url, "http://www.omdbapi.com/?s=%s&apikey=%s&page=%u&type=movie", title, apikey, page);
    free(title);

    return url;

}

static size_t write_result(void *ptr, size_t size, size_t nmemb, void *stream){
    strcat(result, ptr);

    return size*nmemb;
}

RESULT_SEARCH search(char* title, const char* apikey) {
    char* url;
    char* temp;

    while ((temp = strchr(title, ' ')) != NULL){
        *temp = '+';
    }

    url = get_url(apikey, title, 1); // free title here

    strcpy(result, "");

    CURL *curl;
    char result_curl;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        //set network option, provide the URL to use in the request

        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        //Set http option, follow HTTP 3xx redirects set long parameter to 1

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_result);
        //Write output to result

        result_curl = curl_easy_perform(curl);
        //Perform the entire request in a blocking manner


        if (result_curl != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result_curl));

        curl_easy_cleanup(curl);
    }
    free(url);

    //printf("\n%s", result);
    RESULT_SEARCH output = get_title_list(result);

    return output;
}