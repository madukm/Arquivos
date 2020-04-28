#ifndef _H_MANAGE_BIN
#define _H_MANAGE_BIN

#include "../manage_csv/manage_csv.h"

void escreve_cidade_bin(FILE* fp, char cidade[MAX_CIDADE], int size);
void escreve_inteiro_bin(FILE* fp, int number);
void escreve_data_bin(FILE* fp, char data[SIZE_DATA]);
void escreve_sexo_bin(FILE* fp, char sexo);
void escreve_estado_bin(FILE* fp, char estado[SIZE_ESTADO]);

void escreve_registro_bin(FILE* fp, Registro* reg);

void le_cidade_bin(FILE* fp, char cidade[MAX_CIDADE], int size);
void le_inteiro_bin(FILE* fp, int* number);
void le_data_bin(FILE* fp, char data[SIZE_DATA]);
void le_sexo_bin(FILE* fp, char* sexo);
void le_estado_bin(FILE* fp, char* estado[SIZE_ESTADO]);

void le_registro_bin(FILE* fp, Registro* reg);



#endif
