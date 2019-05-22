#ifndef FONTE_H
#define FONTE_H
#include <math.h>
#include <stdio.h>
#include "fontetype.h"

void skipComments(FILE *file_Imagem) {
    char buffer = fgetc(file_Imagem);

    do {
        if (buffer == '#')
            while (buffer != '\n')
                buffer = fgetc(file_Imagem);
        else
            ungetc(buffer, file_Imagem);
        buffer = fgetc(file_Imagem);
    } while (buffer == '#');
    ungetc(buffer, file_Imagem);
}

/* Abre e lê um arquivo de imagem */
FILE  *lerImagem(char filename[]){
    FILE *file;

    file = fopen(filename, "rw");

    if(! file){
        printf("\nO arquivo não foi lido corretamente!\n");
        printf("O formato de abertura é: \n");
        printf("./imagem -i Imagem.ppm -f ppm -o resultado.txt\n");
        exit(1);
    }

    return file;
}

/* Função para alocar imagens na memória*/

Imagem * buildImage(int width, int height){
    int i = 0;

    Imagem *imagem = malloc(sizeof(Imagem));

    if(!imagem){
        printf("\nNão foi possível alocar a imagem na memória!\n\n");
        exit(1);
    }

    imagem->width = width;
    imagem->height = height;

    imagem->pixels = (Pixel **)malloc(sizeof(Pixel*) * imagem->height);

    for(i = 0; i < height; i++)
        imagem->pixels[i] = (Pixel*)malloc(imagem->width * sizeof(Pixel));

    return imagem;
}

Imagem * getImagem(FILE *file){
	char header[3];
	int width, height, i, j, tamanhoMaximo;

	fscanf(file, "%s ", header);

	if(header[0] != 'P' && header[1]!= '3'){
		printf("\nTipo da imagem não suportado!\n\n");
		exit(1);
	}

  	skipComments(file);
	fscanf(file, "%d %d", &width, &height);

	fscanf(file, "%d", &tamanhoMaximo);
	
	Imagem *imagem = buildImage(width, height);

	for(i = 0; i < imagem->height; i++){
		for(j = 0; j < imagem->width; j++){
			skipComments(file);
			fscanf(file, "%i", &imagem->pixels[i][j].r);
			skipComments(file);
			fscanf(file, "%i", &imagem->pixels[i][j].g);
			skipComments(file);
			fscanf(file, "%i", &imagem->pixels[i][j].b);
			skipComments(file);
		}
	}

	fclose(file);

	return imagem;
}

/* Aplicação da escala de cinza */

Imagem *escalaCinza(Imagem *imagem){
    int i, j;

    printf("Criando a imagem em escala de cinza...");
        for(i = 0; i < imagem->height; i++){
            for(j = 0; j < imagem->width; j++){
                imagem->pixels[i][j].r = (int)(imagem->pixels[i][j].r*0.3 + imagem->pixels[i][j].g*0.59 +
                imagem->pixels[i][j].b*0.11);
                
                imagem->pixels[i][j].g = imagem->pixels[i][j].r;
                imagem->pixels[i][j].b = imagem->pixels[i][j].r;
            }
        }

    printf("...[OK]!\n");
    return imagem;    
}


Pixel * pixelReturn(Imagem *imagem, int width, int height){
   
    if( width >= imagem->width ) width = imagem->width - 1;
    if( height >= imagem->height ) height = imagem->height - 1;
    if( width < 0 ) width = 0;
    if( height < 0 ) height = 0;

    return &imagem->pixels[height][width];
}

Imagem * binario(Imagem *imagem){

	int i, j, t;
	Imagem *bin = buildImage(imagem->width, imagem->height);

printf("Aplicando Binarização...");

	 if(imagem->width == 1015 && imagem->height == 759) {
    		t = 50;
 	 }
	else if(imagem->width == 1198  && imagem->height == 770) {
    		t = 10;
  	}
	else {
    		t = 15;
	}

	for(i = 1; i < imagem->height-1; i++){
		for(j = 1; j < imagem->width-1; j++){
			if(imagem->pixels[i][j].r > t){
				bin->pixels[i][j].r = 255;			
				bin->pixels[i][j].g = 255;
				bin->pixels[i][j].b = 255;
			}else{
				bin->pixels[i][j].r = 0;				
				bin->pixels[i][j].g = 0;
				bin->pixels[i][j].b = 0;
			}  			
		}
	}

printf("...[OK]!\n");

	return bin;
		
}

/* Salvar as imagens */

int salvarImagem(char *file, Imagem *imagem, int arqu){
    int i = 0, j = 0;

    FILE * fileName = fopen(file, "w");

    if(!fileName)
        return -1;

    fprintf(fileName, "P3\n");
    fprintf(fileName, "%d %d\n", imagem->width, imagem->height);
    fprintf(fileName, "%d\n", arqu);

    for(i = 0; i < imagem->height; i++){
		for(j = 0; j < imagem->width; j++){
			if(imagem->pixels[i][j].r > 255) imagem->pixels[i][j].r = 255;
			if(imagem->pixels[i][j].g > 255) imagem->pixels[i][j].g = 255;
			if(imagem->pixels[i][j].b > 255) imagem->pixels[i][j].b = 255;
			fprintf(fileName, "%d\n", imagem->pixels[i][j].r);
			fprintf(fileName, "%d\n", imagem->pixels[i][j].g);
			fprintf(fileName, "%d\n", imagem->pixels[i][j].b);
		}
	}

    fclose(fileName);
}
#endif