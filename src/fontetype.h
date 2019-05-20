#ifndef FONTE_TYPE_H
#define FONTE_TYPE_H

typedef struct  Pixels{
    int r, g, b;
}Pixel;

typedef struct Imagens{
    int width, height;
    int maxLength;
    Pixel **pixels;
}Imagem;

#endif