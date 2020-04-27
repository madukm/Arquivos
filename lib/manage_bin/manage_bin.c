#include <stdio.h>
#include "manage_bin.h"
//#include "../manage_csv/manage_csv.h"

void escreve_cidade(FILE* fp, char cidade[105], int size) {
    if (fp == NULL) return;
    
    char* ch = cidade;
    char null_ch = '$';

    fwrite(ch, sizeof(char), size, fp);
    for (int i = size; i < 105; i++)
    {
        fwrite(&null_ch, sizeof(char), 1,fp);
    }
}
