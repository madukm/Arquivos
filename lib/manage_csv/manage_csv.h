#ifndef _H_MANAGE_CSV
#define _H_MANAGE_CSV

#include "../binarioNaTela/binarioNaTela.h"

#define SIZE_DATA 10
#define MAX_CIDADE 105
#define SIZE_ESTADO 2
#define SIZE_REGISTRO 128

struct _registro{
	int tamanhoCidadeMae;
    int tamanhoCidadeBebe;
    char cidadeMae[MAX_CIDADE + 1];
    char cidadeBebe[MAX_CIDADE + 1];
    int idNascimento;
	int idadeMae;
    char dataNascimento[SIZE_DATA+1];
    char sexoBebe;
    char estadoMae[SIZE_ESTADO+1];
	char estadoBebe[SIZE_ESTADO+1];
 };
 
typedef struct _registro Registro;
 
struct _cabecalho{
	char status;
    int RRNproxRegistro;
    int numeroRegistrosInseridos;
    int numeroRegistrosRemovidos;
    int numeroRegistrosAtualizados;
};
 
typedef struct _cabecalho Cabecalho;


char *read_string(FILE *file, int tamanho);
int read_int(FILE *file);

char *le_cidade(FILE *file, int *size_cidade);
char *le_data(FILE *file);
char le_sexo(FILE *file);
char *le_estado(FILE *file);
void le_primeira_linha(FILE *file);
Registro *le_registro(FILE *file);

#endif
