#include <stdio.h>
#include <string.h>
#include "lib/manage_bin/manage_bin.h"
#include "lib/manage_csv/manage_csv.h"

int main(int argc, char const *argv[])
{
    Cabecalho* cab = NULL;
    Registro reg;
    // char op = 'r';
    int input_op;
    char path_1[100];
    char path_2[100];
    FILE* bin_fp;

    scanf("%d%s", &input_op, path_1);
    switch (input_op)
    {
    case 1:
        scanf("%s", path_2);

        break;
    case 2:
        bin_fp = abrir_bin(path_1, &cab, 'r');
        
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
        fecha__bin(bin_fp, cab, 'r');
        break;
    default:
        break;
    }
    
    return 0;
}
