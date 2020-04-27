#ifndef _H_MANAGE_BIN
#define _H_MANAGE_BIN

#include "../manage_csv/manage_csv.h"

void escreve_cidade(FILE* fp, char cidade[MAX_CIDADE], int size);
void escreve_inteiro(FILE* fp, int number);
void escreve_data(FILE* fp, char data[SIZE_DATA]);
void escreve_sexo(FILE* fp, char sexo);
void escreve_estado(FILE* fp, char estado[SIZE_ESTADO]);

#endif
