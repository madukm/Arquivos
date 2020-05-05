#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "manage_csv.h"


//-----Cabecalho-----
Cabecalho *criar_cabecalho(){
	Cabecalho *cab;
	cab = (Cabecalho *)malloc(sizeof(Cabecalho));
	if(cab != NULL){
		cab->status = 1;
		cab->RRNproxRegistro = 0;
		cab->numeroRegistrosInseridos = 0;
		cab->numeroRegistrosRemovidos = 0;
		cab->numeroRegistrosAtualizados = 0;
	}
	return cab;
}


//Função que lê cada string de um registro num arquivo .csv com sepação por vírgula. 
char *le_string(FILE *file, int tamanho){
	if(file == NULL){
		printf("Falha de carregamento no arquivo.\n");
		return NULL;
	}
	char *str;
	str = (char *)malloc((tamanho+1) * sizeof(char));
	fscanf(file, "%[^,^\n]s", str);
	fseek(file, 1, SEEK_CUR); //pula a vírgula no arquivo
	return str;
}

//Função que lê um inteiro de um registro num arquivo .csv
int le_int(FILE *file){
	if(file == NULL){
		printf("Falha de carregamento no arquivo.\n");
		return -1;
	}
	int n;
	fscanf(file, "%d", &n);
	fseek(file, 1, SEEK_CUR); //pula a vírgula no arquivo
	return n;
}

//Função que lê um char de um registro num arquivo .csv
char le_char(FILE *file){
	if(file == NULL) return -1;
	char c;
	fscanf(file, "%c", &c);
	fseek(file, 1, SEEK_CUR);//pula a vírgula no arquivo
	return c;
}

//A função lê a string com o nome da cidade e modifica o parametro size_cidade que representa o tamanho dessa string.
char *le_cidade(FILE *file, int *size_cidade){
	char *str; 
	str = le_string(file, 50);
	if(str == NULL) return str;
	*size_cidade = strlen(str);
	str = realloc(str, (*size_cidade)+1);
	return str;
}

char *le_data(FILE *file){
	return le_string(file, SIZE_DATA);
}

char le_sexo(FILE *file){
	return le_char(file);
}

char *le_estado(FILE *file){
	return le_string(file, SIZE_ESTADO);
}

//Função que lê a primeira linha do arquivo que contêm os nomes dos campos dos registros.
void le_primeira_linha(FILE *file){
	char *str = (char *)malloc(90*sizeof(int));
	fscanf(file, "%s", str);
	fseek(file, 1, SEEK_CUR);
	free(str);	
}

//Função que lê uma linha do arquivo csv e coloca os campos num registro.
Registro *le_registro(FILE *file){
	Registro *reg = (Registro *)malloc(sizeof(Registro));
	if(reg == NULL) return reg;
	int *size_cidadeMae, *size_cidadeBebe;
	char *aux;
	size_cidadeMae = (int *)malloc(sizeof(int));
	size_cidadeBebe = (int *)malloc(sizeof(int));

	aux = le_cidade(file, size_cidadeMae);
	strcpy(reg->cidadeMae, aux);
	free(aux);
	
	aux = le_cidade(file, size_cidadeBebe);
	strcpy(reg->cidadeBebe, aux);
	free(aux);
	
	reg->tamanhoCidadeMae = *size_cidadeMae;
	reg->tamanhoCidadeBebe = *size_cidadeBebe;
	free(size_cidadeMae);
	free(size_cidadeBebe);

	reg->idNascimento = le_int(file);
	
	reg->idadeMae = le_int(file);
	
	aux = le_data(file); 
	strcpy(reg->dataNascimento, aux);
	free(aux);
	
	reg->sexoBebe = le_sexo(file);
	
	aux = le_estado(file);
	strcpy(reg->estadoMae, aux);
	free(aux);
	
	aux = le_estado(file);
	strcpy(reg->estadoBebe, aux);
	free(aux);
	
	return reg;
}

//Função para debug que printa os campos de um registro.
void print_registro(Registro *r){
	printf("tam = %d cidadeMae = %s\n", r->tamanhoCidadeMae, r->cidadeMae);
	printf("tam = %d cidadeBebe = %s\n", r->tamanhoCidadeBebe, r->cidadeBebe);
	printf("idNascimento = %d\n", r->idNascimento);
	printf("idadeMae = %d\n", r->idadeMae);
	printf("dataNascimento = %s\n", r->dataNascimento);
	printf("sexo = %c\n", r->sexoBebe);
	printf("estadoMae = %s\n", r->estadoMae);
	printf("estadoBebe = %s\n\n", r->estadoBebe);
}
