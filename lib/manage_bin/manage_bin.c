#include <stdio.h>
#include "manage_bin.h"
//#include "../manage_csv/manage_csv.h"

void escreve_cidade(FILE* fp, char cidade[MAX_CIDADE], int size) {
    if (fp == NULL) return;
    
    char* ch = cidade;
    char null_ch = '$';

    fwrite(ch, sizeof(char), size, fp);
    for (int i = size; i < MAX_CIDADE ; i++)
    {
        fwrite(&null_ch, sizeof(char), 1,fp);
    }
}

void escreve_inteiro(FILE* fp, int number) {
    if (fp == NULL) return;

    fwrite(&number, sizeof(int), 1, fp);
}

void escreve_data(FILE* fp, char data[SIZE_DATA]) {
    if (fp == NULL) return;

    fwrite(data, sizeof(char), SIZE_DATA, fp);
}

void escreve_sexo(FILE* fp, char sexo) {
    if (fp == NULL) return;

    fwrite(&sexo, sizeof(char), 1, fp);
}

void escreve_estado(FILE* fp, char estado[SIZE_ESTADO]) {
    if (fp == NULL) return;

    fwrite(estado, sizeof(char), SIZE_ESTADO, fp);
}

void escreve_registro(FILE* fp, Registro* reg) {
    if (fp == NULL) return;

    escreve_inteiro(fp, reg->tamanhoCidadeMae);
    escreve_inteiro(fp, reg->tamanhoCidadeBebe);

    escreve_cidade(fp, reg->cidadeMae, reg->tamanhoCidadeMae);
    escreve_cidade(fp, reg->cidadeBebe, reg->tamanhoCidadeBebe);
    
    escreve_inteiro(fp, reg->idNascimento);
    escreve_inteiro(fp, reg->idadeMae);

    escreve_data(fp, reg->dataNascimento);

    escreve_sexo(fp, reg->sexoBebe);

    escreve_estado(fp, reg->estadoMae);
    escreve_estado(fp, reg->estadoBebe);
}