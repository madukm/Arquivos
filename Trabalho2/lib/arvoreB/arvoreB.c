#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvoreB.h"

#include "../manage_csv/manage_csv.h"
#include "../manage_bin/manage_bin.h"

// Cria header para arquivo da Arvore B
BT_header *criar_header_BT(){
	BT_header *cab = (BT_header *)malloc(sizeof(BT_header));
	if(cab != NULL){
		cab->status = '1';
		cab->noRaiz = -1;
		cab->nroNiveis = 0;
		cab->proxRRN = 0;
		cab->nroChaves = 0;
	}
	return cab;
}

//Inicializa uma página atribuindo -1 as chaves e aos ponteiros para os descendentes.
void inicializa_pagina(BT_page *page){
	if(page != NULL){
		int i;
		for(i=0; i<BT_ORDER-1; i++){
			page->keys[i].C = -1;
			page->keys[i].Pr = -1;
		}
		for(i=0; i<BT_ORDER; i++)
			page->P[i] = -1;
		page->n = 0;
	}
}

// Retorna o RRN do arquivo do registro de dados.
// Caso a chave não seja encontrada, retorna -1.
// RRN é o RRN da pagina que está sendo pesquisada. (RRN = nó raiz no início da recursão).
// chave é a chave a ser buscava.
// Found RRN é o RRN da página onde a chave se encontra (no arquivo de indices da arvore B)
// Found POS é a posição dentro da página(0 a 4).
int busca_BT(FILE *bt, int RRN, int chave, int *found_RRN, int *found_pos){
	int pos;
	BT_page page;
	inicializa_pagina(&page);
	
	//Chave não foi encontrada
	if(RRN == -1) return NOT_FOUND;
	
	//Ler pagina a partir de seu RRN.
	busca_pagina_RRN(bt, &page, RRN);	
	
	//Procurando pela chave nessa página.
	//Se achar, retorna o RRN do registro do arquivo de dados.
	for(pos = 0; pos<page.n; pos++){
		if(page.keys[pos].C == chave){
			*found_pos = pos;
			*found_RRN = RRN;
			return page.keys[pos].Pr; //RRN do registro do arquivo de dados.
		}
		if(chave < (page.keys[pos]).C)
			return busca_BT(bt, page.P[pos], chave, found_RRN, found_pos);
		
		if(pos == page.n-1)
			return busca_BT(bt, page.P[pos+1], chave, found_RRN, found_pos);
	
	}
	return -1;
}

// Insertion Sort para ordenar as chaves.
void insertionSort(BT_keys *chave, int RRN[]){
	int i, j, aux;
	for(i=0; i<BT_ORDER; i++){
		aux = chave[i].C;
		j = i-1;
		while(j>=0 && chave[j].C > aux){
			chave[j+1].C = chave[j].C;
			chave[j+1].Pr = chave[j].Pr;
			RRN[j+2] = RRN[j+1];
			j--;
		}
		chave[j+1].C = aux;
	}
}

//Split trata o overflow causado pela inserção de uma chave.

void split(BT_header *header, BT_keys *nova_chave, int filho_dir_nova, BT_page *page, BT_keys *chave_promo, int *filho_dir_promo, BT_page *new_page){
	//Auxiliares
	int i;
	BT_keys aux_keys[BT_ORDER];
	int aux_P[BT_ORDER+1];

	//Copiando as chaves e os ponteiros nos auxiliares para poder ordenar 
	for(i=0; i<BT_ORDER-1; i++){
		aux_keys[i].C = page->keys[i].C;
		aux_keys[i].Pr = page->keys[i].Pr;
	}	
	for(i=0; i<BT_ORDER; i++)
		aux_P[i] = page->P[i];

	aux_keys[5].C = nova_chave->C;
	aux_keys[5].Pr = nova_chave->Pr;
	aux_P[6] = filho_dir_nova;
	
	//Ordenando
	insertionSort(aux_keys, aux_P);
	
	//Passando as chaves para a página.
	for(i=0; i<BT_ORDER/2; i++){
		page->P[i] = aux_P[i];
		page->keys[i].C = aux_keys[i].C;
		page->keys[i].Pr = aux_keys[i].Pr;
	}
	page->P[BT_ORDER/2] = aux_P[BT_ORDER/2];
	page->n -= 1;

	//Definindo as chaves a serem promovidas e guardando o RRN da nova página.
	chave_promo->C = page->keys[BT_ORDER/2].C;
	chave_promo->Pr = page->keys[BT_ORDER/2].Pr;
	*filho_dir_promo = header->proxRRN;
	header->proxRRN++;
	
	//Passando as chaves para a nova página.
	for(i=0; i<BT_ORDER/2-1; i++){
		new_page->P[i] = aux_P[BT_ORDER/2+1+i];
		new_page->keys[i].C = aux_keys[BT_ORDER/2+1+i].C;
		new_page->keys[i].Pr = aux_keys[BT_ORDER/2+1+i].Pr;
	}
	new_page->P[BT_ORDER/2-1] = aux_P[BT_ORDER/2-1];
	
	//Atualizando n e nível.
	new_page->n = BT_ORDER/2 - 1;
	new_page->nivel = page->nivel;

	return;
}

		
//Retorna PROMOTION(overflow), NO_PROMOTION(página tem espaço), ERROR(chave já existe).

int insere_BT(FILE *bt, int RRN, BT_keys chave, BT_keys *chave_promo, int *rrn_promo){
	
	int pos;
	BT_keys p_b_chave; //chave promovida do nível inferior para ser inserida em page
	int p_b_RRN; //RRN promovido do nível inferior para ser inserido em page
	BT_page page, new_page;
	int return_value;
	
	BT_header header;

	inicializa_pagina(&page);
	inicializa_pagina(&new_page);

	if(RRN == -1){ //chegou num nó folha (construção a partir das folhas) 
		//Não há espaço no nó, chave deve ser promovida.
		chave_promo->C = chave.C;
		chave_promo->Pr = chave.Pr;
		*rrn_promo = -1;
		return PROMOTION;
	}
	
	//Se a página não é um nó folha, a função é chamada recursivamente até que encontre
	//a chave ou chegue ao nó folha.
	int found_RRN; //Não vai ser usada nessa função.
	//Chave já existe.
	if(busca_BT(bt, RRN, chave.C, &found_RRN, &pos) != -1){
		return ERROR;
	}
	
	//Se chave não existe, encontrar em que descendente ela terá que ser inserida.
	int new_RRN;
	if(chave.C < page.keys[0].C){
		new_RRN = page.P[0];
	}else if(chave.C < page.keys[1].C){
		new_RRN = page.P[1];
	}else if(chave.C < page.keys[2].C){
		new_RRN = page.P[2];
	}else if(chave.C < page.keys[3].C){
		new_RRN = page.P[3];
	}else if(chave.C < page.keys[4].C){
		new_RRN = page.P[4];
	}else{
		new_RRN = page.P[5];
	}
	
	return_value = insere_BT(bt, new_RRN, chave, &p_b_chave, &p_b_RRN); 
	
	if(return_value == NO_PROMOTION || return_value == ERROR){
		return return_value;
	}else if(page.n < BT_ORDER-1){//Inserção sem particionamento
		page.keys[page.n].C = chave.C;
		page.keys[page.n].Pr = chave.Pr;
		insertionSort(page.keys, page.P);	
		return NO_PROMOTION;
	}else{//inserção sem particionamento, indicando chave promovida
		le_header_BT(bt, &header);
		split(&header, &p_b_chave, p_b_RRN, &page, chave_promo, rrn_promo, &new_page); 
		
		//Atualiza page
		fseek(bt, RRN*SIZE_PAGE + SIZE_HEADER, SEEK_SET);
		escreve_pagina_BT(bt, &page);
		
		//Escreve new_page
		fseek(bt, (*rrn_promo)*SIZE_PAGE + SIZE_HEADER, SEEK_SET);
		escreve_pagina_BT(bt, &new_page);
		header.nroChaves += 1;
		header.proxRRN += 1;
		
		return PROMOTION;
	}
}

//Rotina inicializadora e de tratamento da raiz.
//A chave de busca é o idNascimento.
void driver_BT(char *b_tree, FILE *fp){
	FILE *bt;
	BT_header *header;
   	Registro reg;
	
	if((bt = fopen(b_tree, "rb+")) == NULL){
		//Se o arquivo não existe, então cria-se o arquivo e um header.
		//A primeira chave vira o noRaiz.
		bt = fopen(b_tree, "wb+");
		header = criar_header_BT();
		fseek(fp, 128, SEEK_SET);
   		if(le_registro_bin(fp, &reg) < 1){ //Se não houver registros.
		 	// printf(ERROR_MSG);
			escreve_header_BT(bt, header);	
			free(header);
			fclose(bt);
			return;
		}
	
		BT_page root;
		inicializa_pagina(&root);
		
		root.keys[0].C = reg.idNascimento;
		root.keys[0].Pr = 0; //RRN = 0 no arquivo fp.
		header->noRaiz = header->proxRRN++;	
	}

	else{//Se o arquivo já existe, lemos header.
		header = (BT_header *)malloc(sizeof(BT_header));
		le_header_BT(bt, header);
	}
	
	fseek(fp, 128, SEEK_SET);
	
	BT_keys chave = {-1, -1};
	int RRN_fp;
	int filho_promo;
   	BT_keys	chave_promo;

	//Enquanto existir uma chave
	while(1){
		RRN_fp = (ftell(fp)-SIZE_HEADER)/SIZE_REGISTRO; //RRN do registro a ser lido.
		if(le_registro_bin(fp, &reg) < 1) break; //Acabaram os registros.
		
		chave.C = reg.idNascimento;
		chave.Pr = RRN_fp;
		
		if(insere_BT(bt, header->noRaiz, chave, &chave_promo, &filho_promo) == PROMOTION){
			BT_page new_root;
			inicializa_pagina(&new_root);
			//Chaves
			new_root.keys[0].C = chave_promo.C;
			new_root.keys[0].Pr = chave_promo.Pr;
			//Filhos
			new_root.P[0] = header->noRaiz;
			new_root.P[1] = filho_promo;
			
			header->noRaiz = header->proxRRN;
			header->proxRRN += 1;
			header->nroNiveis += 1;
		
		}
	}
	
	escreve_header_BT(bt, header);	

	free(header);
	fclose(bt);

}

