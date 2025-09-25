#include "circulo.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define pi 3.14159265358979323846

typedef struct circ{
    int i;
    double x, y, r;
    char *corb, *corp;
} circ;

circulo criarCirculo(int i, double x, double y, double r, char *corb, char *corp){
    circ *c = malloc(sizeof(circ));
    if (c == NULL){
        printf("Erro na alocação de memória do círculo!");
        exit(1);
    } 
    c->i = i;
    c->x = x;
    c->y = y;
    c->r = r;
    c->corb = (char*)malloc(strlen(corb)+1);
    if(c->corb == NULL) {
        printf("Erro na alocação de memória para a cor de borda.");
        exit(1);
    }
    strcpy(c->corb, corb);
    c->corp = (char*)malloc(strlen(corp)+1);
    if(c->corp == NULL) {
        printf("Erro na alocação de memória para a cor de preenchimento.");
        exit(1);
    }
    strcpy(c->corp, corp);
    return ((circ*)c);
}

int getIdCirculo(circulo c){
    return ((circ*)c)->i;
}

double getXCirculo(circulo c){
    return ((circ*)c)->x;
}

double getYCirculo(circulo c){
    return ((circ*)c)->y;
}

double getRCirculo(circulo c){
    return ((circ*)c)->r;
}

double calcAreaCirculo(double r){
    return pi*pow(r, 2);
}

char* getCorBCirculo(circulo c){
    return ((circ*)c)->corb;
}

char* getCorPCirculo(circulo c){
    return ((circ*)c)->corp;
}

void setIdCirculo(circulo c, int id){
    return ((circ*)c)->i = id;
}

void setXCirculo(circulo c, double x){
    ((circ*)c)->x = x;
}

void setYCirculo(circulo c, double y){
    ((circ*)c)->y = y;
}

void setRCirculo(circulo c, double raio){
    ((circ*)c)->r = raio;
}

void setCorBCirculo(circulo c, char *corb){
    strcpy(((circ*)c)->corb, corb);
}

void setCorPCirculo(circulo c, char *corp){
    strcpy(((circ*)c)->corp, corp);
}