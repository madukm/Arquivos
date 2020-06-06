/**
 * @ Author: Marcus Vinícius Medeiros Pará 11031663
 * @		 Maria Eduarda Kawakami Moreira 11218751
 * @ Create Time: 2020-05-08 18:31:38
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funcionalidades.h"
#include "../manage_csv/manage_csv.h"
#include "../manage_bin/manage_bin.h"
#include "../binarioNaTela/binarioNaTela.h"

void exibe_registro(Registro* reg) {
	printf("Nasceu em ");
        if (reg->tamanhoCidadeBebe > 0) {
       		printf("%s", reg->cidadeBebe);
		}
		else printf("-");
		printf("/");
            
		if (reg->estadoBebe[0] != '\0') {
			printf("%.2s,", reg->estadoBebe);
		}
		else {
			printf("-,");
		}
        printf(" em ");
        if (reg->dataNascimento[0] != '\0') {
            printf("%.10s,", reg->dataNascimento);
		}
       	else {
            printf("-,");
        }
		printf(" um bebê de sexo ");
		switch (reg->sexoBebe)
		{
			case '0':
				printf("IGNORADO.");
                break;
            case '1':
                printf("MASCULINO.");
                break;
            case '2':
                printf("FEMININO.");
                break;
            default:
                printf("-.");
                break;
		}
		printf("\n");
}

/**
 * Permite a leitura de vários registros obtidos a partir de um arquivo de entrada no formato .csv,
 * e a gravação desses registros em um arquivo de dados de saída.
 * São passados como parâmetro o arquivo .csv (que contém os registros),
 * e o arquivo .bin no qual serão gravados os registros.
 * Após a gravação de todos os registros, é chamado a função binarioNaTela.
 */		
		
void funcionalidade1(char *path_1, char *path_2, Cabecalho *cab){
	FILE *csv_fp, *bin_fp;
	csv_fp = abrir_csv(path_1);
	bin_fp = abrir_bin(path_2, &cab, 'w');
	Registro reg;
	le_primeira_linha(csv_fp);
	while(le_registro(csv_fp, &reg) == 1)
		escreve_registro_bin(bin_fp, &reg, cab);
	fecha_bin(bin_fp, cab, 'w');
	fclose(csv_fp);
	binarioNaTela(path_2);
}

void funcionalidade2(char *path_1, Cabecalho *cab){
	
	FILE *bin_fp;

	bin_fp = abrir_bin(path_1, &cab, 'r');
	
	Registro reg;

	while (le_registro_bin(bin_fp, &reg) ) {
    	exibe_registro(&reg);
	}
	fecha_bin(bin_fp, cab, 'r');
}

void funcionalidade3(char *path_1,int m, char** args, Cabecalho *cab) {
	FILE* bin_fp;

	bin_fp = abrir_bin(path_1, &cab, 'r');
	Registro reg;

	int exists = 0;
	int removido;

	while((removido = busca_params_bin(bin_fp, &reg, m, args))) {
		exibe_registro(&reg);
		if(removido != -1)
			exists = 1;
	}
	if (!exists) printf("Registro Inexistente.\n");

	fecha_bin(bin_fp, cab, 'r');
	
}

void funcionalidade4(char* path_1, int RRN, Cabecalho* cab) {
	FILE* bin_fp;

	bin_fp = abrir_bin(path_1, &cab, 'r');
	Registro reg;
	
	if (busca_registro_RRN(bin_fp, &reg, RRN) == 1) exibe_registro(&reg);
	else printf("Registro Inexistente.\n");

}

/**
 * Permite a remoção lógica de registros, baseado na abordagem estática.
 * Armazena-se -1 no primeiro campo se o registro for removido.
 * São removidos n registros.
 * Se a solicitação de usuário não retornar nenhum registro, o programa continua.
 * Antes de terminar a execução, é chamado binarioNaTela.
 */
void funcionalidade5(char *path_1, Cabecalho *cab, int n){
	FILE* bin_fp;
	bin_fp = abrir_bin(path_1, &cab, 'r');
	
	fseek(bin_fp, 0, SEEK_SET);
	escreve_char_bin(bin_fp, '0'); // Marcando o arquivo como inconsistente.

	int i, j, m,  null = -1;
    char** args;
	
	Registro reg;
	
	for(i=0; i<n; i++)
	{
        scanf("%d", &m);
    	// Lendo os nomes e valores dos campos.
		args = (char**) malloc(2*m*sizeof(char*));
        for (j = 0; j < m; j++) {
            args[2*j] = (char*) malloc(30*sizeof(char));
            args[2*j + 1] = (char*) malloc(30*sizeof(char));
            scanf("%s", args[2*j]);
            scan_quote_string(args[2*j + 1]);
		}
		// Realizar a busca do começo.
		fseek(bin_fp, 128, SEEK_SET);
		while(busca_params_bin(bin_fp, &reg, m, args)){
			int prox = ftell(bin_fp); // Guarda o começo do próximo registro
			fseek(bin_fp, -128, SEEK_CUR); // Voltando para o começo do registro.
			escreve_inteiro_bin(bin_fp, null); //Remove logicamente para todos o registro encontrado.
			cab->numeroRegistrosRemovidos++;
			cab->numeroRegistrosInseridos--;
			fseek(bin_fp, prox, SEEK_SET); // Volta pro começo do próximo registro.
		}
		// Frees
		for (j = 0; j < m; j++)	{
    	 	free(args[2*j]);
 		 	free(args[2*j + 1]);
			args[2*j] = NULL;
			args[2*j+1] = NULL;
		}
		free(args);
	}

	fecha_bin(bin_fp, cab, 'w');
	binarioNaTela(path_1);
}

/**
 * Permite a inserção de registros, baseado na abordagem estática.
 * São inseridos n registros no final do arquivo.
 * Ao final de de todas as modificações, é chamado binarioNaTela.
 */
void funcionalidade6(char *path_1, Cabecalho *cab, int n)
{	
	FILE *bin_fp;
	bin_fp = abrir_bin(path_1, &cab, 'r'); 
	int i;
	Registro reg;

	for(i=0; i<n; i++)
	{
		scan_quote_string(reg.cidadeMae);
		scan_quote_string(reg.cidadeBebe);
		scanf("%d", &reg.idNascimento);
		if(scanf("%d", &reg.idadeMae) == 0)
		{
			scanf("%*s"); // O NULO ainda não foi lido, então ignoraremos ele.
			reg.idadeMae = -1;
		}
		scan_quote_string(reg.dataNascimento);
		scan_quote_char(&reg.sexoBebe);	
		scan_quote_string(reg.estadoMae);
		scan_quote_string(reg.estadoBebe);
		reg.tamanhoCidadeMae = strlen(reg.cidadeMae);
		reg.tamanhoCidadeBebe = strlen(reg.cidadeBebe);
		fseek(bin_fp, 0, SEEK_END); // Sempre inserre no final do arquivo.
		escreve_registro_bin(bin_fp, &reg, cab);
	}

	fecha_bin(bin_fp, cab, 'w');
	binarioNaTela(path_1);
}

void funcionalidade7(char *path_1, Cabecalho *cab, int n)
{
	FILE *bin_fp;
	bin_fp = abrir_bin(path_1, &cab, 'r'); 
	
	int i, j, m, RRN, numero, checkError = 0;
	char sexo, nomeCampo[40], valorCampo[50];
	
	Registro r;

	for(i=0; i<n; i++)
	{
		scanf("%d", &RRN);
		scanf("%d", &m);
		
		for(j=0; j<m; j++)
		{	
			scanf("%s", nomeCampo);
			fseek(bin_fp, 128*(RRN+1), SEEK_SET); // Vai pro byte offset do registro.
			
			if(SEEK_SET == SEEK_END) checkError = 1; // Se o RRN não for válido.
			else{
				if(le_registro_bin(bin_fp, &r) != 1) // Se o registro estiver removido.
					checkError = 1;
			}
			
			if(checkError == 1) break; 
			
			fseek(bin_fp, -128, SEEK_CUR);
			
			if(strcmp(nomeCampo, "cidadeMae") == 0)
			{	
				scan_quote_string(valorCampo);
				escreve_inteiro_bin(bin_fp, strlen(valorCampo));
				fseek(bin_fp, 4, SEEK_CUR);
				escreve_str_bin(bin_fp, valorCampo, strlen(valorCampo));
				
			}else if(strcmp(nomeCampo, "cidadeBebe") == 0)
			{
				scan_quote_string(valorCampo);
				fseek(bin_fp, 4, SEEK_CUR);
				escreve_inteiro_bin(bin_fp, strlen(valorCampo));
				fseek(bin_fp, r.tamanhoCidadeMae, SEEK_CUR);
				escreve_str_bin(bin_fp, valorCampo, strlen(valorCampo));
			
			}else if(strcmp(nomeCampo, "idNascimento") == 0)
			{
				fseek(bin_fp, 105, SEEK_CUR);
				scanf("%d", &numero);
				escreve_inteiro_bin(bin_fp, numero);
			
			}else if(strcmp(nomeCampo, "idadeMae") == 0)
			{
				fseek(bin_fp, 109, SEEK_CUR);
				if(scanf("%d", &numero) == 0){
					numero = -1;
					scanf("%*s");
				}
				escreve_inteiro_bin(bin_fp, numero);
			
			}else if(strcmp(nomeCampo, "dataNascimento") == 0)
			{
				fseek(bin_fp, 113, SEEK_CUR);
				scan_quote_string(valorCampo);
				escreve_data_bin(bin_fp, valorCampo);
			
			}else if(strcmp(nomeCampo, "sexoBebe") == 0)
			{
				fseek(bin_fp, 123, SEEK_CUR);
				scan_quote_char(&sexo);
				escreve_char_bin(bin_fp, sexo);
			
			}else if(strcmp(nomeCampo, "estadoMae") == 0)
			{
				fseek(bin_fp, 124, SEEK_CUR);
				scan_quote_string(valorCampo);
				escreve_estado_bin(bin_fp, valorCampo);
			
			}else if(strcmp(nomeCampo, "estadoBebe") == 0)
			{
				fseek(bin_fp, 126, SEEK_CUR);
				scan_quote_string(valorCampo);
				escreve_estado_bin(bin_fp, valorCampo);
			}
		}
		// Se o registro não puder ser lido ou estiver removido, então ignoramos todos os campos em relação a ele.
		// E passamos para o próximo.
		if(checkError == 1)
		{
			for(j=0; j<m; j++)
				scanf("%*s");
		}
		// Senão, o registro foi atualizado com sucesso.
		else cab->numeroRegistrosAtualizados++;
	}

	fecha_bin(bin_fp, cab, 'w');
	binarioNaTela(path_1);

}
