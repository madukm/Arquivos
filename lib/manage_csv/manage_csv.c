#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "manage_csv.h"

/**
 * manage_csv lida com a leitura do arquivo .csv e com os registros, incluindo os casos de erro.
 */

//Criação do cabeçalho
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


/**
 * Função para abrir o arquivo .csv
 * Caso não seja possível abrir, manda uma mensagem de erro e encerra o programa.
 */
FILE *abrir_csv(char path1[]){
	FILE *arq;
	arq = fopen(path1, "r");
	if(arq == NULL){
		printf("Falha no carregamento do arquivo.\n");
		exit(0);
	}
	return arq;
}

/**
 * Função que lê cada string de um registro num arquivo .csv com sepação por vírgula.
 * Recebe o tamanho da string a ser lida.
 * O fseek é dado a fim de pular a vírgula no arquivo.
 */ 
char *le_string(FILE *file, int tamanho){
	char *str;
	str = (char *)malloc((tamanho+1) * sizeof(char));
	str[0] = '\0';
	fscanf(file, "%[^,^\n]s", str);
	fseek(file, 1, SEEK_CUR); //pula a vírgula no arquivo
	return str;
}

/**
 * Função que lê um inteiro de um registro num arquivo .csv.
 * Se o valor for nulo, armazena-se o valor -1.
 * O fscanf retorna o número de campos convertidos e atribuídos com êxito.
 * Portanto se o valor de retorno for igual a zero, o valor lido é nulo.
 * O fseek é dado a fim de pular a vírgula no arquivo.
 */
int le_int(FILE *file){
	int n;
	if(fscanf(file, "%d", &n) <= 0)
		n = -1;
	fseek(file, 1, SEEK_CUR);
	return n;
}

/**
 * Função que lê um char de um registro num arquivo .csv
 * Se o char for nulo, a vírgula será lida ao invés do valor.
 * Nesse caso, atribuímos '0' ao char e não é necessário fazer o fseek.
 * Se o char não for nulo, damos fseek para pular a vírgula.
 */
char le_char(FILE *file){
	if(file == NULL) return -1;
	char c;
	fscanf(file, "%c", &c);
	if (c != ',') {
		fseek(file, 1, SEEK_CUR);
	}
	else {
		c = '0';
	}
	return c;

}

/**
 * A função lê a string com o nome da cidade.
 * Por esse campo ser de tamanho variável fazemos um realloc para o tamanho exato da string lida.
 * Modificamos o parâmetro size_cidade para conter o tamanho da cidade, que será usado no campo tamanhoCidade no registro.
 */
 char *le_cidade(FILE *file, int *size_cidade){
	char *str; 
	str = le_string(file, 50);
	if(str == NULL) return str;
	*size_cidade = strlen(str);
	str = realloc(str, (*size_cidade)+1);
	return str;
}

//A função lê a data de nascimento no formato DD/MM/AAAA.
char *le_data(FILE *file){
	return le_string(file, SIZE_DATA);
}

//A função lê o char correspondente ao sexo.
char le_sexo(FILE *file){
	return le_char(file);
}

//A função lê o estado no formato EE.
char *le_estado(FILE *file){
	return le_string(file, SIZE_ESTADO);
}

/**
 * A função lê o ID do registro.
 * Note que o ID nunca é nulo, portanto usaremos para determinar o final do arquivo.
 * int *retorno_fscanf recebe o retorno do fscanf feito para ler o ID.
 * Quando o retorno for <= 0 chegamos ao final do arquivo.
 * Fazemos o fseek para pular a vírgula no arquivo.
 */
int le_id(FILE *file, int *retorno_fscanf){
	int n;
	*retorno_fscanf = fscanf(file, "%d", &n);
	fseek(file, 1, SEEK_CUR); //pula a vírgula no arquivo
	return n;
}

//Função que lê e ignora a primeira linha do arquivo que contêm os nomes dos campos dos registros.
//Damos o fseek para pular o \n.
void le_primeira_linha(FILE *file){
	fscanf(file, "%*s");
	fseek(file, 1, SEEK_CUR);
}

/**
 * Função que lê uma linha do arquivo .csv que corresponde ao registro e adiciona os dados ao parâmetro Registro.
 * Utiliza a função le_id para conferir se o arquivo chegou ao final. Nesse caso retorna 0.
 * Caso o registro seja lido com sucesso retorna-se 1.
 */
int le_registro(FILE *file, Registro *reg){
	int size_cidadeMae, size_cidadeBebe, retorno_fscanf;
	char *aux;
	
	aux = le_cidade(file, &size_cidadeMae);
	strcpy(reg->cidadeMae, aux);
	free(aux);

	aux = le_cidade(file, &size_cidadeBebe);
	strcpy(reg->cidadeBebe, aux);
	free(aux);

	
	reg->tamanhoCidadeMae = size_cidadeMae;
	reg->tamanhoCidadeBebe = size_cidadeBebe;

	reg->idNascimento = le_id(file, &retorno_fscanf);
	if(retorno_fscanf <= 0)
		return 0;

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

	return 1;
}

//Função para debug que printa os campos de um registro.
void print_registro(Registro *r){
	printf("tam = %d cidadeMae = %s\n", r->tamanhoCidadeMae, r->cidadeMae);
	printf("tam = %d cidadeBebe = %s\n", r->tamanhoCidadeBebe, r->cidadeBebe);
	printf("idNascimento = %d\n", r->idNascimento);
	printf("idadeMae = %d\n", r->idadeMae);
	printf("dataNascimento = %s\n", r->dataNascimento);
	printf("sexo = %c\n", r->sexoBebe);
	printf("estadoMae = %.2s\n", r->estadoMae);
	printf("estadoBebe = %.2s\n\n", r->estadoBebe);
}

