#ifndef _H_ARVORE_B
#define _H_ARVORE_B

#define BT_ORDER 6
#define SIZE_HEADER 72
#define SIZE_PAGE 72

#define NOT_FOUND -1
#define NO_PROMOTION 0
#define PROMOTION 1
#define ERROR -1

struct _BT_header{
	char status;
	int noRaiz;
	int nroNiveis;
	int proxRRN;
	int nroChaves;
};

struct _BT_keys{
	int C;
	int Pr;
};

struct _BT_page{
	int nivel;
	int n;
	struct _BT_keys keys[BT_ORDER-1];
	int P[BT_ORDER]; //RRN dos registros da árvore B
};

typedef struct _BT_header BT_header;
typedef struct _BT_page BT_page;
typedef struct _BT_keys BT_keys;

BT_header *criar_header_BT(void);
void inicializa_pagina(BT_page *page);
int busca_BT(FILE *fp, int RRN, int chave, int *found_RRN, int *found_pos);
void insertionSort(BT_keys *keys, int *P, BT_keys new_key, int new_P, int n);
void split(BT_header *header, BT_keys *nova_chave, int filho_dir_nova, BT_page *page, BT_keys *chave_promo, int *filho_dir_promo, BT_page *new_page);
int insere_BT_rec(FILE *fp, BT_header *header, int RRN, BT_keys chave, BT_keys *chave_promo, int *rrn_promo);	
int insere_BT(FILE *bt, BT_keys chave, BT_header *header);
void driver_BT(char *b_tree, FILE *fp);

#endif
