#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionalidades.h"
#include "../manage_csv/manage_csv.h"
#include "../manage_bin/manage_bin.h"
#include "../binarioNaTela/binarioNaTela.h"


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
    	printf("Nasceu em ");
        if (reg.tamanhoCidadeBebe > 0) {
       		printf("%s", reg.cidadeBebe);
		}
		else printf("-");
		printf("/");
            
		if (reg.estadoBebe[0] != '\0') {
			printf("%.2s,", reg.estadoBebe);
		}
		else {
			printf("-,");
		}
        printf(" em ");
        if (reg.dataNascimento[0] != '\0') {
            printf("%.10s,", reg.dataNascimento);
		}
       	else {
            printf("-,");
        }
		printf(" um bebê de sexo ");
		switch (reg.sexoBebe)
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
	fecha_bin(bin_fp, cab, 'r');
}       
