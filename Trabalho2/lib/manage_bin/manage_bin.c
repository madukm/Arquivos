/**
 * @ Author: Marcus Vinícius Medeiros Pará 11031663
 * @		 Maria Eduarda Kawakami Moreira 11218751
 * @ Create Time: 2020-05-08 18:31:38
 */

#include <stdio.h>
#include <stdlib.h>
#include "manage_bin.h"
#include "../manage_csv/manage_csv.h"

//Função utilizada para abrir os arquivos binários.
//path indica o caminho do arquivo a ser aberto
//cab receberá os dados armazenados no cabeçalho
//op indica o modo de abertura do arquivo. Pode ser 'r' ou 'w', para
//leitura ou escrita, respectivamente

//Em caso de leitura, o arquivo de cabeçalho recebe dados do arquivo binário.
//Em caso de escrita, o arquivo de cabeçalho é inicializado com valores zerados.

//Em caso de erro na abertura do arquivo para leitura, retorna-se NULL e é printada
//a mensagem ERROR_MSG
FILE* abrir_bin(char path[], Cabecalho** cab, char op) {
    FILE* fp = NULL;

    switch (op)
    {
    case 'w':
        fp = fopen(path, "w+b");
		if(fp == NULL){
			printf("Falha no processamento do arquivo.\n");
			exit(0);
		}
        escreve_char_bin(fp, '0');

		fseek(fp, 127, SEEK_CUR);
        *cab = criar_cabecalho();
        break;
    case 'r':
        fp = fopen(path, "r+b");
        if (fp == NULL) {
            printf("Falha no processamento do arquivo.\n");
            exit(0);
        }
        *cab = criar_cabecalho();
        le_char_bin(fp, &((*cab)->status));
        if ((*cab)->status == '0') {
            printf("Falha no processamento do arquivo.\n");
            free(*cab);
			fclose(fp);
            exit(0);
        }
        le_inteiro_bin(fp, &((*cab)->RRNproxRegistro));
        le_inteiro_bin(fp, &((*cab)->numeroRegistrosInseridos));
        le_inteiro_bin(fp, &((*cab)->numeroRegistrosRemovidos));
        le_inteiro_bin(fp, &((*cab)->numeroRegistrosAtualizados));
		if((*cab)->numeroRegistrosInseridos == 0){
//			printf("Registro Inexistente.\n");
//			exit(0);
		}
        fseek(fp, 128, SEEK_SET);
        break;
    default:
        break;
    }   

    return fp;
}

//Função utilizada para fechar um arquivo binário lido e dar free em cab alocado em abrir_bin.
//fp é o ponteiro do arquivo a ser fechado
//cab contém os dados do cabeçalho que será atualizado em caso de escrita (criado em abrir_bin)
//op indica o modo de abertura do arquivo. Pode ser 'r' ou 'w', para
//leitura ou escrita, respectivamente

//Em caso de leitura, o arquivo é simplesmente fechado.
//Em caso de escrita, os valores do registro de cabeçalho são atualizados no arquivo
void fecha_bin(FILE* fp, Cabecalho* cab, char op) {
    char null_ch = '$';

    switch (op)
    {
    case 'w':
        fseek(fp, 0, SEEK_SET);
        escreve_char_bin(fp, '1');
        escreve_inteiro_bin(fp, cab->RRNproxRegistro);
        escreve_inteiro_bin(fp, cab->numeroRegistrosInseridos);
        escreve_inteiro_bin(fp, cab->numeroRegistrosRemovidos);
        escreve_inteiro_bin(fp, cab->numeroRegistrosAtualizados);

        
        for (int i = 17; i <= 127 ; i++)
        {
            fwrite(&null_ch, sizeof(char), 1,fp);
        }
        break;
    case 'r':
        break;
    default:
        break;
    }
    free(cab);
    fclose(fp);
}

//Função utilizada para escrever um string de size bytes no arquivo 
//apontado por fp.
//fp indica o ponteiro do arquivo em que será feita a escrita
//str é o ponteiro da primeiro caracter a ser escrito
//size indica a quantidade de caracteres válidos escritos

//Normalmente a função escreve size caracteres no arquivo
//Em caso de falha na escrita (se fp for NULL), nada é feito.

void escreve_str_bin(FILE* fp, char str[MAX_CIDADE], int size) {
    if (fp == NULL) return;
    
    char* ch = str;
    
	fwrite(ch, sizeof(char), size, fp);
}

//Função utilizada para escrever um inteiro no arquivo
//apontado por fp.
//fp indica o ponteiro do arquivo em que será feita a escrita.
//number é o inteiro que será escrito.

//Normalmente, a função escreve o inteiro number no arquivo.
//Em caso de falha na escrita (se fp for NULL), nada é feito.

void escreve_inteiro_bin(FILE* fp, int number) {
    if (fp == NULL) return;

    fwrite(&number, sizeof(int), 1, fp);
}

//Função para escrever uma string de SIZE_DATA caracteres representando
//uma data no formato AAAA-MM-DD.
//fp indica o ponteiro do arquivo em que será feita a escrita.
//data é o ponteiro da primeiro caracter a ser escrito

//Normalmente, a função escreve uma string de SIZE_DATA caracteres no arquivo.
//Em caso de falha na escrita (se fp for NULL), nada é feito.

void escreve_data_bin(FILE* fp, char data[SIZE_DATA]) {
    if (fp == NULL) return;
    if(data[0] == '\0'){
		char null_chr = '$';
		fwrite(&data[0], sizeof(char), 1, fp);
		for(int i=1; i<10; i++)
			fwrite(&null_chr, sizeof(char), 1, fp);
	}
	else
		fwrite(data, sizeof(char), SIZE_DATA, fp);
}

//Função utilizada para escrever um caracter no arquivo
//apontado por fp.
//fp indica o ponteiro do arquivo em que será feita a escrita.
//ch é o caracter que será escrito.

//Normalmente, a função escreve o caracter ch no arquivo.
//Em caso de falha na escrita (se fp for NULL), nada é feito.
void escreve_char_bin(FILE* fp, char ch) {
    if (fp == NULL) return;

    fwrite(&ch, sizeof(char), 1, fp);
}

//Função para escrever uma string de SIZE_ESTADO caracteres representando
//uma unidade federativa.
//fp indica o ponteiro do arquivo em que será feita a escrita.
//estado é o ponteiro da primeiro caracter a ser escrito.
//Em caso de falha na escrita (se fp for NULL), nada é feito.


void escreve_estado_bin(FILE* fp, char estado[SIZE_ESTADO]) {
    if (fp == NULL) return;
    if(estado[0] == '\0'){
		fwrite(&estado[0], sizeof(char), 1, fp);
		char null_chr = '$';
		fwrite(&null_chr, sizeof(char), 1, fp);
	}
	else
		fwrite(estado, sizeof(char), SIZE_ESTADO, fp);
}

//Função para escrever um registro no arquivo binário.
//fp indica o ponteiro do arquivo em que será feita a escrita.
//reg contem os dados que serão escritos.
//cab conterá os dados atualizados do cabeçalho ao final da função.

//Normalmente, a função escreve os dados de reg no arquivo e atualiza cab
//Em caso de falha na escrita (se fp for NULL), nada é feito.

void escreve_registro_bin(FILE* fp, Registro* reg, Cabecalho* cab) {
    if (fp == NULL) return;

    escreve_inteiro_bin(fp, reg->tamanhoCidadeMae);
    escreve_inteiro_bin(fp, reg->tamanhoCidadeBebe);

    escreve_str_bin(fp, reg->cidadeMae, reg->tamanhoCidadeMae);
    escreve_str_bin(fp, reg->cidadeBebe, reg->tamanhoCidadeBebe);
	
	for(int i=reg->tamanhoCidadeMae+reg->tamanhoCidadeBebe; i<97; i++)
		escreve_char_bin(fp, '$');

    escreve_inteiro_bin(fp, reg->idNascimento);
    escreve_inteiro_bin(fp, reg->idadeMae);

    escreve_data_bin(fp, reg->dataNascimento);

    escreve_char_bin(fp, reg->sexoBebe);

    escreve_estado_bin(fp, reg->estadoMae);
    escreve_estado_bin(fp, reg->estadoBebe);

    cab->numeroRegistrosInseridos += 1;
	cab->RRNproxRegistro += 1;
}

//Função para ler um inteiro de um arquivo.
//fp é o ponteiro do arquivo a ser lido.
//number é o endereço de memória onde o inteiro será armazenado

//Normalmente, a função lê um inteiro do arquivo e retorna o 
//número de inteiros lidos com sucesso.

//Se fp for NULL, nada é feito.

int le_inteiro_bin(FILE* fp, int* number) {
    if (fp == NULL) return 0;

    return fread(number, sizeof(int), 1, fp);
}

//Função para ler uma string do arquivo apontado por fp.
//fp é o ponteiro do arquivo a ser lido.
//str é o endereço de memória onde o primeiro caracter será armazenado.
//size indica a quantidade de caracteres a serem lidos.

//Normalmente, a função lê size caracteres do arquivo e adiciona um caracter
//nulo ('\0') no final da string, mesmo se a string for vazia, e retorna o
//número de strings lidas com sucesso.

//Se fp for NULL, nada é feito.

int le_str_bin(FILE* fp, char str[MAX_CIDADE], int size) {
    if (fp == NULL) return 0;

    int leu = fread(str, sizeof(char), size, fp);
    str[size] = '\0';
    return leu;
}

//Função para ler uma string de SIZE_DATA caracteres do arquivo apontado por fp.
//fp é o ponteiro do arquivo a ser lido.
//data é o endereço de memória onde o primeiro caracter será armazenado.


//Normalmente, a função lê SIZE_DATA caracteres do arquivo e retorna o número
//de strings lidas com sucesso.

//Se fp for NULL, nada é feito.

int le_data_bin(FILE* fp, char data[SIZE_DATA]) {
    if (fp == NULL) return 0;

    return fread(data, sizeof(char), SIZE_DATA, fp);
}

//Função para ler um caracter de um arquivo.
//fp é o ponteiro do arquivo a ser lido.
//ch é o endereço de memória onde o caracter será armazenado

//Normalmente, a função lê um caracter do arquivo e retorna o 
//número de caracteres lidos com sucesso.

//Se fp for NULL, nada é feito.

int le_char_bin(FILE* fp, char* ch) {
    if (fp == NULL) return 0;

    return fread(ch, sizeof(char), 1, fp);
}

//Função para ler uma string de SIZE_ESTADO caracteres do arquivo apontado por fp.
//fp é o ponteiro do arquivo a ser lido.
//estado é o endereço de memória onde o primeiro caracter será armazenado.


//Normalmente, a função lê SIZE_ESTADO caracteres do arquivo e retorna o número
//de strings lidas com sucesso.

//Se fp for NULL, nada é feito.

int le_estado_bin(FILE* fp, char estado[SIZE_ESTADO]) {
    if (fp == NULL) return 0;

    return fread(estado, sizeof(char), SIZE_ESTADO, fp);
}

//Função para ler os dados de um registro no arquivo apontado por fp
//e armazená-los em reg.
//fp é o ponteiro do arquivo a ser lido.
//reg é o endereço de memória onde o registro será armazenado

//Normalmente, a função lê um registro do arquivo e retorna o 
//número de registros lidos com sucesso.
//Se o arquivo for removido, ele retorna -1.

//Se fp for NULL, nada é feito.

int le_registro_bin(FILE* fp, Registro* reg) {
    if (fp == NULL) return 0;

    int leu = 0;
    leu = le_inteiro_bin(fp, &(reg->tamanhoCidadeMae));
    if(reg->tamanhoCidadeMae == -1){
		fseek(fp, 124, SEEK_CUR); //ir para o proximo registro
		return -1;
	}
	if (!leu){
		fseek(fp, 124, SEEK_CUR);
		return 0;
	}

    leu = le_inteiro_bin(fp, &(reg->tamanhoCidadeBebe));
    if (!leu) {
		fseek(fp, 120, SEEK_CUR);
		return 0;
	}

    le_str_bin(fp, reg->cidadeMae, reg->tamanhoCidadeMae);
    le_str_bin(fp, reg->cidadeBebe, reg->tamanhoCidadeBebe);
    fseek(fp, 105 - (reg->tamanhoCidadeMae) - (reg->tamanhoCidadeBebe) - 8, SEEK_CUR);
    
    le_inteiro_bin(fp, &(reg->idNascimento));
    le_inteiro_bin(fp, &(reg->idadeMae));

    le_data_bin(fp, reg->dataNascimento);

    le_char_bin(fp, &(reg->sexoBebe));

    le_estado_bin(fp, reg->estadoMae);
    le_estado_bin(fp, reg->estadoBebe);
    return 1;
    
}

// Função que realiza busca pelos valores dos campos no arquivo binário em fp, e
// o coloca em 'reg'.
// A função retorna 1 se encontrar o registro. Caso contrário, retorna 0.
// Se encontrar um registro logicamente removido, ele apenas o ignora e continua a busca.
// n_params indica quantos pares chave-valor são passados em params.
// params é um array de strings com pares chave-valor.
int busca_params_bin(FILE* fp, Registro* reg, int n_params, char** params) {
    Registro registro_lido;
	int removido;
    while ((removido = le_registro_bin(fp, &registro_lido)) != 0) {
        if(removido == -1) continue;
		int is_target = 1;
    	for (int i = 0; i < n_params; i++) {
            char* nomeDoCampo = params[2*i];
            char* valorDoCampo = params[2*i + 1];
            is_target *= check_query(&registro_lido, nomeDoCampo, valorDoCampo);

        }
        if (is_target) {
            *reg = registro_lido;
            return 1;
        }
	}
    
    return 0;
}

int busca_registro_RRN(FILE* fp, Registro* reg, int RRN) {
    fseek(fp, RRN*SIZE_REGISTRO, SEEK_CUR);
    return le_registro_bin(fp, reg);
}

// ARQUIVO BINARIO ARVORE B
// Le pagina do arquivo binario e guarda em BT_page.
void le_pagina(FILE *fp, BT_page *page){
	if(fp == NULL) return;
	
	int i;

    le_inteiro_bin(fp, &(page->nivel));
	
	le_inteiro_bin(fp, &(page->n));
	
	for(i=0; i<BT_ORDER-1; i++){
		le_inteiro_bin(fp, &(page->keys[i].C));
		le_inteiro_bin(fp, &(page->keys[i].Pr));
	}

	for(i=0; i<BT_ORDER; i++)
		le_inteiro_bin(fp, &(page->P[i]));
	
	return;	
}

//Busca a pagina a partir do RRN
void busca_pagina_RRN(FILE *bt, BT_page *page, int RRN){
	fseek(bt, RRN*SIZE_PAGE + SIZE_HEADER, SEEK_SET);
	le_pagina(bt, page);
	return;
}

void le_header_BT(FILE *bt, BT_header *header){
	if(bt == NULL) return;
	
	fseek(bt, 0, SEEK_SET);

    le_char_bin(bt, &(header->status));
	// le_inteiro_bin(bt, &(header->status));
	le_inteiro_bin(bt, &(header->noRaiz));
	le_inteiro_bin(bt, &(header->nroNiveis));
	le_inteiro_bin(bt, &(header->proxRRN));
	le_inteiro_bin(bt, &(header->nroChaves));
	
	return;
}

void escreve_header_BT(FILE *bt, BT_header *header){
	if(bt == NULL) return;
	fseek(bt, 0, SEEK_SET);
	escreve_char_bin(bt, header->status);
	escreve_inteiro_bin(bt, header->noRaiz);
	escreve_inteiro_bin(bt, header->nroNiveis);
	escreve_inteiro_bin(bt, header->proxRRN);
	escreve_inteiro_bin(bt, header->nroChaves);
    for (int i = 0; i < 55; i++) {
        escreve_char_bin(bt, '$');
    }
	return;
}

void escreve_pagina_BT(FILE *fp, BT_page *page){
	if(fp == NULL) return;

	escreve_inteiro_bin(fp, page->nivel);
	escreve_inteiro_bin(fp, page->n);
	
	for(int i=0; i<BT_ORDER-1; i++){
		escreve_inteiro_bin(fp, page->keys[i].C);
		escreve_inteiro_bin(fp, page->keys[i].Pr);
	}
	for(int i=0; i<BT_ORDER; i++)
		escreve_inteiro_bin(fp, page->P[i]);
	
}
