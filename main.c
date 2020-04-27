#include <stdio.h>
#include <string.h>
#include "lib/manage_bin/manage_bin.h"

int main(int argc, char const *argv[])
{
    FILE* fp = fopen("./teste.bin", "w+b");


    fclose(fp);

    return 0;
}
