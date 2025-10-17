#include "linha.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct lin{
    int i;
    double x1, y1, x2, y2;
    char *cor;
} lin;

linha criarLinha(int i, double x1, double y1, double x2, double y2, char *cor){
    lin *l = malloc(sizeof(lin));
    if (l == NULL){
        printf("Erro na alocação de memória da linha!");
    exit(1);
    } 
    l->i = i;
    l->x1 = x1;
    l->y1 = y1;
    l->x2 = x2;
    l->y2 = y2;
    l->cor = (char*)malloc(strlen(cor)+1);
    if(l->cor == NULL) {
        printf("Erro na alocação de memória para a cor.");
        exit(1);
    }
    strcpy(l->cor, cor);
    return ((lin*)l);
}

int getIdLinha(linha l){
    return ((lin*)l)->i;
}

double getX1Linha(linha l){
    return ((lin*)l)->x1;
}

double getY1Linha(linha l){
    return ((lin*)l)->y1;
}

double getX2Linha(linha l){
    return ((lin*)l)->x2;
}

double getY2Linha(linha l){
    return ((lin*)l)->y2;
}

char* getCorLinha(linha l){
    return ((lin*)l)->cor;
}

double calcAreaLinha(double x1, double y1, double x2, double y2){
    return 2*sqrt(pow(x1-x2, 2)+pow(y1-y2, 2));
}

char* calcCorComplementarLinha(char *cor){
    int r, g, b;
    char *comp = malloc(8*sizeof(char));
    if (cor[0] == '#')
        sscanf(cor + 1, "%2x%2x%2x", &r, &g, &b);
    else
        sscanf(cor, "%2x%2x%2x", &r, &g, &b);

    r = 255 - r;
    g = 255 - g;
    b = 255 - b;
    sprintf(comp, "#%02X%02X%02X", r, g, b);
    return comp;
}

void setIdLinha (linha l, int id){
    ((lin*)l)->i = id;
}

void setX1Linha(linha l, double x1){
    ((lin*)l)->x1 = x1;
}

void setY1Linha(linha l, double y1){
    ((lin*)l)->y1 = y1;
}

void setX2Linha(linha l, double x2){
    ((lin*)l)->x2 = x2;
}

void setY2Linha(linha l, double y2){
    ((lin*)l)->y2 = y2;
}

void setCorLinha(linha l, char *cor){
    lin *ll = (lin*)l;
    free(ll->cor);
    ll->cor = malloc(strlen(cor) + 1);
    if (ll->cor == NULL) {
        printf("Erro na alocação de memória para cor da linha!\n");
        exit(1);
    }
    strcpy(ll->cor, cor);
}

void liberarLinha(linha l){
    lin *ll = (lin*)l;
    free(ll->cor);
    free(ll);
}