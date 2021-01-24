#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

//Function replace movie by title

void string_replace(char* source, char* substring, char* with){
    char* substring_source = strstr(source, substring);
    if (substring_source == NULL){
        return;
    }

    memmove(
            substring_source + strlen(with),
            substring_source + strlen(substring),
            strlen(substring_source)- strlen(substring)+1
            );

    memcpy(substring_source,with, strlen(with));
}


//Function replace numb by the number

void page_numb(char* source, char* substring, char* with){

    char string[225];
    int value = 1;
    sprintf(string, "%d", value);

    char* substring_source = strstr(source, substring);
    if (substring_source == NULL){
        return;
    }

    memmove(
            substring_source + strlen(with),
            substring_source + strlen(substring),
            strlen(substring_source)- strlen(substring)+1
    );

    memcpy(substring_source,with, strlen(with));
}

int search() {

    char url[255]= "http://www.omdbapi.com/?s=movie&apikey=cab5fef3&page=numb";
    char title[20] = {0};
    char numb[20]={0};

    //Replace movie
    printf("Please, enter the title of the movie :" );
    scanf("%s",title);

    //Replace page number
    printf("Please, enter the page number :" );
    scanf("%s",numb);

    //printf("%s\n",url); for testing
    string_replace(url,"movie",title);
    page_numb(url,"numb",numb);
    //printf("%s\n",url); for testing

    CURL *curl;
    char result;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        //set network option, provide the URL to use in the request

        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        //Set http option, follow HTTP 3xx redirects set long parameter to 1

        result = curl_easy_perform(curl);
        //Perform the entire request in a blocking manner


        if (result != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(result));

        /* always cleanup */

        curl_easy_cleanup(curl);
    }



    return 0;

}