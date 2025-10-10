#include "retangulo.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct ret{
    int i;
    double x, y, w, h;
    char *corb, *corp;
} ret;

retangulo criarRetangulo(int i, double x, double y, double w, double h, char *corb, char *corp){
    ret *r = malloc(sizeof(ret));
    if (r == NULL){
        printf("Erro na alocação de memória do retângulo!");
    exit(1);
    } 
    r->i = i;
    r->x = x;
    r->y = y;
    r->w = w;
    r->h = h;
    r->corb = (char*)malloc(strlen(corb)+1);
    if(r->corb == NULL) {
        printf("Erro na alocação de memória para a cor de borda.");
        exit(1);
    }
    strcpy(r->corb, corb);
    r->corp = (char*)malloc(strlen(corp)+1);
    if(r->corp == NULL) {
        printf("Erro na alocação de memória para a cor de preenchimento.");
        exit(1);
    }
    strcpy(r->corp, corp);
    return ((ret*)r);
}

int getIdRetangulo(retangulo r){
    return ((ret*)r)->i;
}

double getXRetangulo(retangulo r){
    return ((ret*)r)->x;
}

double getYRetangulo(retangulo r){
    return ((ret*)r)->y;
}

double getWRetangulo(retangulo r){
    return ((ret*)r)->w;
}

double getHRetangulo(retangulo r){
    return ((ret*)r)->h;
}

char* getCorBRetangulo(retangulo r){
    return ((ret*)r)->corb;
}

char* getCorPRetangulo(retangulo r){
    return ((ret*)r)->corp;
}

double calcAreaRetangulo(double w, double h){
    return w*h;
}

void setIdRetangulo(retangulo r, int id){
    ((ret*)r)->i = id;
}

void setXRetangulo(retangulo r, double x){
    ((ret*)r)->x = x;
}

void setYRetangulo(retangulo r, double y){
    ((ret*)r)->y = y;
}

void setWRetangulo(retangulo r, double largura){
    ((ret*)r)->w = largura;
}

void setHRetangulo(retangulo r, double altura){
    ((ret*)r)->h = altura;
}

void setCorBRetangulo(retangulo r, char *corb){
    ret *rr = (ret*)r;
    rr->corb = realloc(rr->corb, strlen(corb) + 1);
    if (rr->corb == NULL){
        printf("Erro na realocação de memória para cor de borda!\n");
        exit(1);
    }
    strcpy(rr->corb, corb);
}

void setCorPRetangulo(retangulo r, char *corp){
    ret *rr = (ret*)r;
    rr->corp = realloc(rr->corp, strlen(corp) + 1);
    if (rr->corp == NULL){
        printf("Erro na realocação de memória para cor de preenchimento!\n");
        exit(1);
    }
    strcpy(rr->corp, corp);
}

void liberarRetangulo(retangulo r){
    ret *rr = (ret*)r;
    free(rr->corb);
    free(rr->corp);
    free(rr);
}