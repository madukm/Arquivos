#ifndef _H_MANAGE_CSV
#define _H_MANAGE_CSV

struct _registro{
	char *cidadeMae;
	char *cidadeBebe;
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

//Funcionalidade 1:

//Funcionalidade 2:

#endif
