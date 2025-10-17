#include "texto.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct TipoTexto{
    char *fFamily;
    char *fWeight;
    char *fSize;
} TipoTexto;

typedef struct txt{
    int i;
    double xt, yt, x1, x2;
    char *corb, *corp, a, *txto;
    TipoTexto tipo;
} txt;

tipoTexto criarTipoTexto(){
    TipoTexto *tipo = (TipoTexto*)malloc(sizeof(TipoTexto));
    tipo->fFamily = NULL;
    tipo->fWeight = NULL;
    tipo->fSize = NULL;
    return tipo;
}

texto criarTexto(int i, double x, double y, char *corb, char *corp, char a, char *txto){
    txt *t = malloc(sizeof(txt));
    if (t == NULL){
        printf("Erro na alocação de memória da linha!");
    exit(1);
    } 
    t->i = i;
    t->xt = x;
    t->yt = y;
    t->corb = (char*)malloc(strlen(corb)+1);
    if(t->corb == NULL) {
        printf("Erro na alocação de memória para a cor de borda.");
        exit(1);
    }
    strcpy(t->corb, corb);
    t->corp = (char*)malloc(strlen(corp)+1);
    if(t->corp == NULL) {
        printf("Erro na alocação de memória para a cor de preenchimento.");
        exit(1);
    }
    strcpy(t->corp, corp);
    t->a = a;
    t->txto = (char*)malloc(strlen(txto)+1);
    if(t->txto == NULL) {
        printf("Erro na alocação de memória para o conteúdo.");
        exit(1);
    }
    strcpy(t->txto, txto);
    return ((txt*)t);
}

int getIdTexto(texto t){
    return ((txt*)t)->i;
}

double getXtTexto(texto t){
    return ((txt*)t)->xt;
}

double getYtTexto(texto t){
    return ((txt*)t)->yt;
}

double getX1Texto(texto t){
    return ((txt*)t)->x1;
}

double getX2Texto(texto t){
    return ((txt*)t)->x2;
}

char* getCorBTexto(texto t){
    return ((txt*)t)->corb;
}

char* getCorPTexto(texto t){
    return ((txt*)t)->corp;
}

char getATexto(texto t){
    return ((txt*)t)->a;
}

char* getTxtoTexto(texto t){
    return ((txt*)t)->txto;
}

char* getFamily(tipoTexto tt){
    return((TipoTexto*)tt)->fFamily;
}

char* getWeight(tipoTexto tt){
    return((TipoTexto*)tt)->fWeight;
}

char* getSize(tipoTexto tt){
    return((TipoTexto*)tt)->fSize;
}

double calcAreaTexto(char *txto){
    return 20*strlen(txto);
}

void setX1X2Texto(texto t, char a){
    txt *texto = (txt*)t;
    switch(a){
        case 'i':
            texto->x1 = texto->xt;
            texto->x2 = texto->xt + 10*strlen(texto->txto);
            break;
        case 'm':
            texto->x1 = texto->xt - 10*strlen(texto->txto);
            texto->x2 = texto->xt;
            break;
        case 'f':
            texto->x1 = texto->xt - 5*strlen(texto->txto);
            texto->x2 = texto->xt + 5*strlen(texto->txto);
    }
}

void setIdTexto(texto t, int id){
    ((txt*)t)->i = id;
}

void setXtTexto(texto t, double x){
    ((txt*)t)->xt = x;
}

void setYtTexto(texto t, double y){
    ((txt*)t)->yt = y;
}

void setCorBTexto(texto t, char *corb){
    txt *tt = (txt*)t;
    tt->corb = realloc(tt->corb, strlen(corb)+1);
    if(tt->corb == NULL){
        printf("Erro na realocação da memória para cor de borda!");
        exit(1);
    }
    strcpy(tt->corb, corb);
}

void setCorPTexto(texto t, char *corp){
    txt *tt = (txt*)t;
    tt->corp = realloc(tt->corp, strlen(corp)+1);
    if(tt->corp == NULL){
        printf("Erro na realocação da memória para cor de preenchimento!");
        exit(1);
    }
    strcpy(tt->corp, corp);
}

void setATexto(texto t, char a){
    ((txt*)t)->a = a;
}

void setTxtoTexto(texto t, char *txto){
    txt *tt = (txt*)t;
    tt->txto = realloc(tt->txto, strlen(txto)+1);
    if(tt->txto == NULL){
        printf("Erro na realocação da memória para o conteúdo do texto!");
        exit(1);
    } 
    strcpy(tt->txto, txto);
}

void setFamily(tipoTexto tt, char *family){
    TipoTexto *tipo = (TipoTexto*)tt;
    tipo->fFamily = realloc(tipo->fFamily, strlen(family)+1);
    if (tipo->fFamily == NULL){
        printf("Erro na realocação da memória para a font-family do texto!");
        exit(1);
    }
    strcpy(tipo->fFamily, family);
}

void setWeight(tipoTexto tt, char *weight){
    TipoTexto *tipo = (TipoTexto*)tt;
    tipo->fWeight = realloc(tipo->fWeight, strlen(weight)+1);
    if (tipo->fWeight == NULL){
        printf("Erro na realocação da memória para a font-weight do texto!");
        exit(1);
    }
    strcpy(tipo->fWeight, weight);
}

void setSize(tipoTexto tt, char *size){
    TipoTexto *tipo = (TipoTexto*)tt;
    tipo->fSize = realloc(tipo->fSize, strlen(size)+1);
    if (tipo->fSize == NULL){
        printf("Erro na realocação da memória para a font-size do texto!");
        exit(1);
    }
    strcpy(tipo->fSize, size);
}

void liberarTipoTexto(tipoTexto t){
    TipoTexto *tt = (TipoTexto*)t;
    free(tt->fFamily);
    free(tt->fWeight);
    free(tt->fSize);
    free(tt);
}

void liberarTexto(texto t){
    if (!t) return;
    txt *tt = (txt*)t;
    if (tt->corb) free(tt->corb);
    if (tt->corp) free(tt->corp);
    if (tt->txto) free(tt->txto);
    liberarTipoTexto(&(tt->tipo));
    free(tt);
}
