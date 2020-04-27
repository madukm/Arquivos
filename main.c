#include <stdio.h>
#include <string.h>
#include "lib/manage_bin/manage_bin.h"

int main(int argc, char const *argv[])
{
    int tam_cidade;
    char cidade[105];

    FILE* fp = fopen("./teste.bin", "w+b");

    scanf("%[^\n]105s", cidade);
    printf("%s\n", cidade);

    escreve_cidade(fp,cidade, strlen(cidade));

    fclose(fp);

    return 0;
}
