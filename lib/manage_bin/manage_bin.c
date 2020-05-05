#include <stdio.h>
#include "manage_bin.h"
#include "../manage_csv/manage_csv.h"

FILE* abrir_bin(char path[], Cabecalho** cab, char op) {
    FILE* fp = NULL;

    switch (op)
    {
    case 'w':
        fp = fopen(path, "w+b");
        escreve_char_bin(fp, '0');
        fseek(fp, SEEK_CUR, 127);
        *cab = criar_cabecalho();
        break;
    case 'r':
        fp = fopen(path, "rb");
        le_char_bin(fp, &((*cab)->status));
        le_inteiro_bin(fp, &((*cab)->RRNproxRegistro));
        le_inteiro_bin(fp, &((*cab)->numeroRegistrosInseridos));
        le_inteiro_bin(fp, &((*cab)->numeroRegistrosRemovidos));
        le_inteiro_bin(fp, &((*cab)->numeroRegistrosAtualizados));
        break;
    default:
        break;
    }   

    return fp;
}

void fecha__bin(FILE* fp, Cabecalho* cab, char op) {
    char null_ch = '$';

    switch (op)
    {
    case 'w':{}
        rewind(fp);
        escreve_char_bin(fp, '1');
        escreve_inteiro_bin(fp, cab->RRNproxRegistro);
        escreve_inteiro_bin(fp, cab->numeroRegistrosInseridos);
        escreve_inteiro_bin(fp, cab->numeroRegistrosRemovidos);
        escreve_inteiro_bin(fp, cab->numeroRegistrosAtualizados);

        
        for (int i = 17; i <= 127 ; i++)
        {
            fwrite(&null_ch, sizeof(char), 1,fp);
        }
        
        break;
    case 'r':
        break;
    default:
        break;
    }
    fclose(fp);
}

void escreve_str_bin(FILE* fp, char str[MAX_CIDADE], int size) {
    if (fp == NULL) return;
    
    char* ch = str;
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

void escreve_char_bin(FILE* fp, char ch) {
    if (fp == NULL) return;

    fwrite(&ch, sizeof(char), 1, fp);
}

void escreve_estado_bin(FILE* fp, char estado[SIZE_ESTADO]) {
    if (fp == NULL) return;

    fwrite(estado, sizeof(char), SIZE_ESTADO, fp);
}

void escreve_registro_bin(FILE* fp, Registro* reg, Cabecalho* cab) {
    if (fp == NULL) return;

    escreve_inteiro_bin(fp, reg->tamanhoCidadeMae);
    escreve_inteiro_bin(fp, reg->tamanhoCidadeBebe);

    escreve_str_bin(fp, reg->cidadeMae, reg->tamanhoCidadeMae);
    escreve_str_bin(fp, reg->cidadeBebe, reg->tamanhoCidadeBebe);
    
    escreve_inteiro_bin(fp, reg->idNascimento);
    escreve_inteiro_bin(fp, reg->idadeMae);

    escreve_data_bin(fp, reg->dataNascimento);

    escreve_char_bin(fp, reg->sexoBebe);

    escreve_estado_bin(fp, reg->estadoMae);
    escreve_estado_bin(fp, reg->estadoBebe);

    cab->numeroRegistrosInseridos += 1;
}

void le_inteiro_bin(FILE* fp, int* number) {
    if (fp == NULL) return;

    fread(number, sizeof(int), 1, fp);
}

void le_str_bin(FILE* fp, char str[MAX_CIDADE], int size) {
    if (fp == NULL) return;

    fread(str, sizeof(char), MAX_CIDADE, fp);
    str[size] = '\0';
}

void le_data_bin(FILE* fp, char data[SIZE_DATA]) {
    if (fp == NULL) return;

    fread(data, sizeof(char), SIZE_DATA, fp);
}

void le_char_bin(FILE* fp, char* ch) {
    if (fp == NULL) return;

    fread(ch, sizeof(char), 1, fp);
}

void le_estado_bin(FILE* fp, char estado[SIZE_ESTADO]) {
    if (fp == NULL) return;

    fread(estado, sizeof(char), SIZE_ESTADO, fp);
}

void le_registro_bin(FILE* fp, Registro* reg) {
    if (fp == NULL) return;

    le_inteiro_bin(fp, &(reg->tamanhoCidadeMae));
    le_inteiro_bin(fp, &(reg->tamanhoCidadeBebe));

    le_str_bin(fp, reg->cidadeMae, reg->tamanhoCidadeMae);
    le_str_bin(fp, reg->cidadeBebe, reg->tamanhoCidadeBebe);
    
    le_inteiro_bin(fp, &(reg->idNascimento));
    le_inteiro_bin(fp, &(reg->idadeMae));

    le_data_bin(fp, reg->dataNascimento);

    le_char_bin(fp, &(reg->sexoBebe));

    le_estado_bin(fp, reg->estadoMae);
    le_estado_bin(fp, reg->estadoBebe);

}