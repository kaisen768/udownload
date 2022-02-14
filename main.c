#include <stdio.h>
#include "download.h"

int main(int argc, const char *argv[])
{
    download_file("http://fw.cuav.net/air-link/update.json", "test.json");

    return 0;
}
