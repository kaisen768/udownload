#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "curl/curl.h"
#include "download.h"

size_t write_handle(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    return fwrite(ptr, size, nmemb, stream);
}

double processvalue;

int progress_handle(char *progress_data,
                     double t, /* dltotal */
                     double d, /* dlnow */
                     double ultotal,
                     double ulnow)
{
    processvalue = ulnow / ultotal * 100 / 110;
    return 0;
}

int download_file(char *url, char *output_filename)
{
    if (strncmp(url, "http", 4) != 0) {
        fprintf(stderr, "where the file is local.\n");
        return -2;
    }
    CURL *curl;
    CURLcode res = CURLE_OK;
    FILE *outfile;
    char *progress_data = "* ";

    curl = curl_easy_init();
    if(curl)
    {
        outfile = fopen(output_filename, "wb");

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, outfile);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_handle);
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, false);
        curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, progress_handle);
        curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, progress_data);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        fclose(outfile);
        /* always cleanup */
        curl_easy_cleanup(curl);
    }

    if(res != CURLE_OK){
        fprintf(stderr, "download Error.\n");
        return -1;
    }

    return 0;
}