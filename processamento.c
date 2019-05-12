#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/fonte.h"
#include "src/fontetype.h"


int main(int argc, char const *argv[])
{
    char *arg = argv[2];
    char *imagem = "imagens/";
    char Nome[25];
    Nome[0] = '\0';

    /*Concatenar as strings*/
    strcat(Nome, imagem);
    strcat(Nome, arg);

    FILE *file1 = lerImagem(Nome);
    Imagem *imagem1 = getImage(file1);

    // FILE *file2 = readFile(Nome);
    // Imagem *imagem2 = getImage(file2);

    /*Retorno de dimensões das imagens*/
    printf ("<==================Dimensões da imagem==================>\n");
	printf("Largura: %d\n", (*imagem1).width);
	printf("Altura: %d\n\n", (*imagem1).height);


    Imagem * GS = escalaCinza(imagem);
    salvarImagem("processamento/EscalaCinza", GS, 255);

    return 0;
}
