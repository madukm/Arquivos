#ifndef _H_MANAGE_BIN
#define _H_MANAGE_BIN

#include "../manage_csv/manage_csv.h"

FILE* abrir_bin(char path[], Cabecalho** cab, char op);
void fecha__bin(FILE* fp, Cabecalho* cab, char op);


void escreve_str_bin(FILE* fp, char str[MAX_CIDADE], int size);
void escreve_inteiro_bin(FILE* fp, int number);
void escreve_data_bin(FILE* fp, char data[SIZE_DATA]);
void escreve_char_bin(FILE* fp, char ch);
void escreve_estado_bin(FILE* fp, char estado[SIZE_ESTADO]);

void escreve_registro_bin(FILE* fp, Registro* reg, Cabecalho* cab);

int le_str_bin(FILE* fp, char str[MAX_CIDADE], int size);
int le_inteiro_bin(FILE* fp, int* number);
int le_data_bin(FILE* fp, char data[SIZE_DATA]);
int le_char_bin(FILE* fp, char* ch);
int le_estado_bin(FILE* fp, char estado[SIZE_ESTADO]);

int le_registro_bin(FILE* fp, Registro* reg);



#endif
