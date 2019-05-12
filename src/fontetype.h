typedef struct  Pixels{
    int r, g, b;
}Pixel;

typedef struct Imagens{
    int width, height;
    int maxLength;
    Pixel **pixels;
}Imagem;