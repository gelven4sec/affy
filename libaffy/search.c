#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <json-c/json.h>

char result[1024];

// return user input title, only for cli version
char* read_input(){
    int counter = 0;
    char *input = malloc(sizeof(char) * 1024);
    int c;

    if (!input) {
        fprintf(stderr, "\nCould not allocate more memory");
        exit(EXIT_FAILURE);
    }

    // loop until user input enter
    while (1) {
        c = getchar();

        if (c == '\n') {
            input[counter] = '\0';
            return input;
        } else {
            input[counter] = c;
        }
        counter++;

        // if input is larger than 1024 bytes than stop and return nothing
        if (counter >= 1024) {
            fprintf(stderr, "\nExceed maximum input capacity");
            return "";
        }
    }
}

// takes request's argument to return usable url
char* get_url(char* apikey, char* title, unsigned int page){
    char* url = malloc(sizeof(char) * 1024);

    sprintf(url, "http://www.omdbapi.com/?s=%s&apikey=%s&page=%u", title, apikey, page);
    free(title);

    return url;
}

int search() {
    char* url;
    char* title;
    char* temp;

    //Replace movie
    printf("\nPlease, enter the title of the movie :" );
    title = read_input();
    temp = strchr(title, ' ');
    if (temp != NULL) {*temp = '+';} // cant let a space in http request

    url = get_url("cab5fef3", title, 1); // free title here

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
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));

        curl_easy_cleanup(curl);
    }
    free(url);


    return 0;

}