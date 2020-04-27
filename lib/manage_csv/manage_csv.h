#ifndef _H_MANAGE_CSV
#define _H_MANAGE_CSV

#include "../binarioNaTela/binarioNaTela.h"

struct _registro{
	char cidadeMae[105];
	char cidadeBebe[105];
	int idNascimento;
	int idadeMae;
	char dataNascimento[10];
	char sexoBebe;
	char estadoMae[2];
	char estadoBebe[2];
};

typedef struct _registro Registro;

struct _cabecalho{
	int stats;
	Registro *lidos;
};

typedef struct _cabecalho Cabecalho;

//Funções auxiliares
void 

//Funcionalidade 1:

//Funcionalidade 2:

#endif
