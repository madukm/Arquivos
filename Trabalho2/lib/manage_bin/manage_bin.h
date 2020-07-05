/**
 * @ Author: Marcus Vinícius Medeiros Pará 11031663
 * @		 Maria Eduarda Kawakami Moreira 11218751
 * @ Create Time: 2020-05-08 18:31:38
 */

#ifndef _H_MANAGE_BIN
#define _H_MANAGE_BIN

#define ERROR_MSG "Falha no processamento do arquivo."

#include "../manage_csv/manage_csv.h"
#include "../arvoreB/arvoreB.h"

FILE* abrir_bin(char path[], Cabecalho** cab, char op);
void fecha_bin(FILE* fp, Cabecalho* cab, char op);

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
int busca_registro_RRN(FILE* fp, Registro* reg, int RRN);
int busca_params_bin(FILE* fp, Registro* reg, int n_params, char** params);

// ARQUIVO BINARIO ARVORE B
void le_pagina(FILE *fp, BT_page *page);
void busca_pagina_RRN(FILE *fp, BT_page *page, int RRN);
void le_header_BT(FILE *fp, BT_header *header);
void escreve_pagina_BT(FILE *fp, BT_page *page);
void escreve_header_BT(FILE *bt, BT_header *header);
	
#endif
