#ifndef _H_MANAGE_BIN
#define _H_MANAGE_BIN

#define MAX_CIDADE 105
#define SIZE_DATA 10


void escreve_cidade(FILE* fp, char cidade[105], int size);
void escreve_inteiro(FILE* fp, int number);
void escreve_data(FILE* fp, char data[10]);

#endif
