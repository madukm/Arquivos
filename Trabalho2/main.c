/**
 * @ Author: Marcus Vinícius Medeiros Pará 11031663
 * @		 Maria Eduarda Kawakami Moreira 11218751
 * @ Create Time: 2020-05-08 18:31:38
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lib/manage_bin/manage_bin.h"
#include "lib/manage_csv/manage_csv.h"
#include "lib/binarioNaTela/binarioNaTela.h"
#include "lib/funcionalidades/funcionalidades.h"

int main(int argc, char const *argv[])
{
    Cabecalho* cab = NULL;
    int input_op;
    char path_1[100];
    char path_2[100];

    scanf("%d%s", &input_op, path_1);
    switch (input_op)
    {
    case 1:
        scanf("%s", path_2);
		funcionalidade1(path_1, path_2, cab);
		break;
    case 2:
        funcionalidade2(path_1, cab);
        break;
    case 3:{
        int m;
        char** args;
        scanf("%d", &m);
        args = (char**) malloc(2*m*sizeof(char*));
        for (int i = 0; i < m; i++) {
            args[2*i] = (char*) malloc(30*sizeof(char));
            args[2*i + 1] = (char*) malloc(30*sizeof(char));

            scanf("%s", args[2*i]);
            scan_quote_string(args[2*i + 1]);
        }
        funcionalidade3(path_1,m, args, cab);
        for (int i = 0; i < m; i++) {
            free(args[2*i]);
            free(args[2*i + 1]);

            args[2*i] = NULL;
            args[2*i + 1] = NULL;
        }
        break;
    }
    default:
        break;
    }
    
    return 0;
}
