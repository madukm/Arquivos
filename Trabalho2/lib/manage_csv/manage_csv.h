/**
 * @ Author: Marcus Vinícius Medeiros Pará 11031663
 * @		 Maria Eduarda Kawakami Moreira 11218751
 * @ Create Time: 2020-05-08 18:31:38
 */

#ifndef _H_MANAGE_CSV
#define _H_MANAGE_CSV

#include "../binarioNaTela/binarioNaTela.h"

#define SIZE_DATA 10
#define MAX_CIDADE 48
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

FILE *abrir_csv(char path1[]);

char *le_string(FILE *file, int tamanho);
int le_int(FILE *file);
char le_char(FILE *file);

char *le_cidade(FILE *file, int *size_cidade);
char *le_data(FILE *file);
char le_sexo(FILE *file);
char *le_estado(FILE *file);
int le_id(FILE *file, int *retorno_fscanf);
void le_primeira_linha(FILE *file);
int le_registro(FILE *file, Registro *reg);

Cabecalho *criar_cabecalho();
void print_registro(Registro *r);
int check_query(Registro* reg, const char* nomeDoCampo, char* valorDoCampo);


#endif
