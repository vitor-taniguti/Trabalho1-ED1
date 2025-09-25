#include "texto.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct txt{
    int i;
    double x, y;
    char *corb, *corp, a, *txto;
} txt;

texto criarTexto(int i, double x, double y, char *corb, char *corp, char a, char *txto){
    txt *t = malloc(sizeof(txt));
    if (t == NULL){
        printf("Erro na alocação de memória da linha!");
    exit(1);
    } 
    t->i = i;
    t->x = x;
    t->y = y;
    t->corb = (char*)malloc(strlen(corb)+1);
    if(t->corb == NULL) {
        printf("Erro na alocação de memória para a cor de borda.");
        exit(1);
    }
    strcpy(t->corb, corb);
    t->corp = (char*)malloc(strlen(corb)+1);
    if(t->corb == NULL) {
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

double getXTexto(texto t){
    return ((txt*)t)->x;
}

double getYTexto(texto t){
    return ((txt*)t)->y;
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

void setIdTexto(texto t, int id){
    ((txt*)t)->i = id;
}

void setXTexto(texto t, double x){
    ((txt*)t)->x = x;
}

void setYTexto(texto t, double y){
    ((txt*)t)->y = y;
}

void setCorBTexto(texto t, char *corb){
    ((txt*)t)->corb = corb;
}

void setCorPTexto(texto t, char *corp){
    ((txt*)t)->corp = corp;
}

void setATexto(texto t, char a){
    ((txt*)t)->a = a;
}

void setTxtoTexto(texto t, char *txto){
    ((txt*)t)->txto = txto;
}