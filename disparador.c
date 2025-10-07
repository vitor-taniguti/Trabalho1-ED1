#include "disparador.h"
#include "fila.h"
#include "retangulo.h"
#include "circulo.h"
#include "linha.h"
#include "texto.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct disparador{
    fila f;
    double x, y;
    int id, tipoForma;
} Disparador;

typedef struct elemento{
    forma forma;
    int tipoForma;
    struct elemento *prox;
} Elemento;

typedef Elemento *pont;

typedef struct{
    int tamanho;
    pont topo;
    pont fim;
} Fila;

disparador criarDisparador(fila f, double x, double y, int id){
    Disparador *disparador = (Disparador*)malloc(sizeof(Disparador));
    if (disparador == NULL){
        printf("Erro na alocação de memória!");
        exit(1);
    }
    Fila *fila = ((Fila*)f);
    if (fila == NULL){
        printf("Erro na alocação de memória!");
        exit(1);
    }
    disparador->f = fila;
    disparador->x = x;
    disparador->y = y;
    disparador->id = id;
    return disparador;
}

fila getFilaDisparador(disparador d){
    Disparador *disparador = ((Disparador*)d);
    return disparador->f;
}

double getXDisparador(disparador d){
    return ((Disparador*)d)->x;
}

double getYDisparador(disparador d){
    return ((Disparador*)d)->y;
}

void dispararDisparador(disparador d, double dx, double dy, arquivo *txt){
    Disparador *disparador = (Disparador*)d;
    if (disparador == NULL || disparador->f == NULL){
        printf("Erro no disparador ou na fila!");
        exit(1);
    }
    Fila *fila = (Fila*)disparador->f;
    forma f = getPrimeiroElementoFila(fila);
    double x, y, x2, y2;
    double xD = disparador->x, yD = disparador->y;
    double novoX, novoY, novoX2, novoY2;
    switch (fila->topo->tipoForma){
    case 1:
        x = getXRetangulo(f);
        y = getYRetangulo(f);
        novoX = x + xD + dx;
        novoY = y + yD + dy;
        printInformacoesRetangulo(txt, getIdRetangulo(f), getXRetangulo(f), getYRetangulo(f), getHRetangulo(f), getWRetangulo(f), getCorBRetangulo(f), getCorPRetangulo(f));
        setXRetangulo(f, novoX);
        setYRetangulo(f, novoY);
        break;

    case 2:
        x = getXCirculo(f);
        y = getYCirculo(f);
        novoX = x + xD + dx;
        novoY = y + yD + dy;
        printInformacoesCirculo(txt, getIdCirculo(f), getXCirculo(f), getYCirculo(f), getRCirculo(f), getCorBCirculo(f), getCorPCirculo(f));
        setXCirculo(f, novoX);
        setYCirculo(f, novoY);
        break;

    case 3:
        x = getX1Linha(f);
        y = getY1Linha(f);
        x2 = getX2Linha(f);
        y2 = getY2Linha(f);
        novoX = x + xD + dx;
        novoY = y + yD + dy;
        novoX2 = x2 + xD + dx;
        novoY2 = y2 + yD + dy;
        printInformacoesLinha(txt, getIdLinha(f), getX1Linha(f), getY1Linha(f), getX2Linha(f), getY2Linha(f), getCorLinha(f));
        setX1Linha(f, novoX);
        setY1Linha(f, novoY);
        setX2Linha(f, novoX2);
        setY2Linha(f, novoY2);
        break;

    case 4:
        x = getXtTexto(f);
        y = getYtTexto(f);
        novoX = x + xD + dx;
        novoY = y + yD + dy;
        printInformacoesTexto(txt, getIdTexto(f), getXTexto(f), getYTexto(f), getCorbTexto(f), getCorpTexto(f), getATexto(f), getTxtoTexto(f));
        setXtTexto(f, novoX);
        setYtTexto(f, novoY);
        break;

    default:
        printf("Tipo de forma inválido!\n");
        break;
    }
}