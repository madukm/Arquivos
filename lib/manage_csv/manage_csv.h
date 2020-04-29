#ifndef _H_MANAGE_CSV
#define _H_MANAGE_CSV

#define MAX_CIDADE 105
#define SIZE_DATA 10
#define SIZE_ESTADO 2

#include "../binarioNaTela/binarioNaTela.h"


struct _registro{
	int tamanhoCidadeMae;
	int tamanhoCidadeBebe;
	char cidadeMae[MAX_CIDADE + 1];
	char cidadeBebe[MAX_CIDADE + 1];
	int idNascimento;
	int idadeMae;
	char dataNascimento[SIZE_DATA];
	char sexoBebe;
	char estadoMae[SIZE_ESTADO];
	char estadoBebe[SIZE_ESTADO];
};

typedef struct _registro Registro;

struct _cabecalho{
	int stats;
	Registro *lidos;
};

typedef struct _cabecalho Cabecalho;

//Funções auxiliares

//Funcionalidade 1:

//Funcionalidade 2:

#endif
