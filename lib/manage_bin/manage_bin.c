#include <stdio.h>
#include "manage_bin.h"
//#include "../manage_csv/manage_csv.h"

void escreve_cidade_bin(FILE* fp, char cidade[MAX_CIDADE], int size) {
    if (fp == NULL) return;
    
    char* ch = cidade;
    char null_ch = '$';

    fwrite(ch, sizeof(char), size, fp);
    for (int i = size; i < MAX_CIDADE ; i++)
    {
        fwrite(&null_ch, sizeof(char), 1,fp);
    }
}

void escreve_inteiro_bin(FILE* fp, int number) {
    if (fp == NULL) return;

    fwrite(&number, sizeof(int), 1, fp);
}

void escreve_data_bin(FILE* fp, char data[SIZE_DATA]) {
    if (fp == NULL) return;

    fwrite(data, sizeof(char), SIZE_DATA, fp);
}

void escreve_sexo_bin(FILE* fp, char sexo) {
    if (fp == NULL) return;

    fwrite(&sexo, sizeof(char), 1, fp);
}

void escreve_estado_bin(FILE* fp, char estado[SIZE_ESTADO]) {
    if (fp == NULL) return;

    fwrite(estado, sizeof(char), SIZE_ESTADO, fp);
}

void escreve_registro_bin(FILE* fp, Registro* reg) {
    if (fp == NULL) return;

    escreve_inteiro_bin(fp, reg->tamanhoCidadeMae);
    escreve_inteiro_bin(fp, reg->tamanhoCidadeBebe);

    escreve_cidade_bin(fp, reg->cidadeMae, reg->tamanhoCidadeMae);
    escreve_cidade_bin(fp, reg->cidadeBebe, reg->tamanhoCidadeBebe);
    
    escreve_inteiro_bin(fp, reg->idNascimento);
    escreve_inteiro_bin(fp, reg->idadeMae);

    escreve_data_bin(fp, reg->dataNascimento);

    escreve_sexo_bin(fp, reg->sexoBebe);

    escreve_estado_bin(fp, reg->estadoMae);
    escreve_estado_bin(fp, reg->estadoBebe);
}

void le_inteiro_bin(FILE* fp, int* number) {
    if (fp == NULL) return;

    fread(number, sizeof(int), 1, fp);
}

void le_cidade_bin(FILE* fp, char cidade[MAX_CIDADE], int size) {
    if (fp == NULL) return;

    fread(cidade, sizeof(char), MAX_CIDADE, fp);
    cidade[size] = '\0';
}

void le_data_bin(FILE* fp, char data[SIZE_DATA]) {
    if (fp == NULL) return;

    fread(data, sizeof(char), SIZE_DATA, fp);
}

void le_sexo_bin(FILE* fp, char* sexo) {
    if (fp == NULL) return;

    fread(sexo, sizeof(char), 1, fp);
}