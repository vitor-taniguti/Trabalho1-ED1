#include "fila.h"
#include "texto.h"
#include "svg.h"
#include <stdio.h>
#include <stdlib.h>

typedef void *forma;

typedef struct elemento{
    forma forma;
    int tipoForma;
    struct elemento *prox;
} Elemento;

typedef Elemento *pont;

typedef struct{
    int tamanho, tipo;
    pont topo;
    pont fim;
} Fila;

fila criarFila(){
    Fila *f = malloc(sizeof(Fila));
    if (f == NULL){
        printf("Falha na alocação de memória!");
        exit(1);
    }
    f->tamanho = 0;
    f->topo = NULL;
    f->fim = NULL;
    return ((Fila*)f);
}

int getTipoPrimeiroElementoFila(fila f){
    Fila *fila = ((Fila*)f);
    if (fila == NULL || fila->topo == NULL){
        return -1;
    }
    return fila->topo->tipoForma;
}

void inserirFila(fila f, forma forma, int tipoForma){
    Fila *fila = ((Fila*)f);
    Elemento *novoElemento = (Elemento*)malloc(sizeof(Elemento));
    if (novoElemento == NULL){
        printf("Falha na alocação de memória!");
        exit(1);
    }
    novoElemento->forma = forma;
    novoElemento->tipoForma = tipoForma;
    novoElemento->prox = NULL;
    if (fila->fim == NULL){  
        fila->topo = novoElemento;
        fila->fim = novoElemento;
    } else{
        fila->fim->prox = novoElemento;     
        fila->fim = novoElemento;
    }
    fila->tamanho++;
}

void removerFila(fila f){
    Fila *fila = ((Fila*)f);
    if (fila->topo == NULL){
        printf("A fila está vazia!");
        exit(1);
    }
    Elemento *elementoTopo = fila->topo;
    fila->topo = fila->topo->prox;
    if (fila->topo == NULL){
        fila->fim = NULL;
    }
    fila->tamanho--;
    free(elementoTopo);
}

forma getPrimeiroElementoFila(fila f){
    Fila *fila = ((Fila*)f);
    if (fila->topo == NULL){
        printf("A fila está vazia!");
        return NULL;
    }
    return fila->topo->forma;
}

iterador getPrimeiroFila(fila f){
    Fila *fila = ((Fila*)f);
    if (fila->topo == NULL){
        return NULL;
    }
    return fila->topo;
}

iterador getProximoFila(iterador i){
    Elemento *e = (Elemento*)i;
    if (e == NULL || e->prox == NULL){
        return NULL;
    }
    return e->prox;
}

iterador getUltimoFila(fila f){
    Fila *fila = ((Fila*)f);
    if (fila->topo == NULL){
        return NULL;
    }
    Elemento *e = fila->topo;
    while (e->prox != NULL){
        e = e->prox;
    }
    return e;
}

forma getFormaFila(iterador i){
    Elemento *e = (Elemento*)i;
    return e->forma;
}

int getTipoFormaFila(iterador i){
    Elemento *e = (Elemento*)i;
    return e->tipoForma;
}

void passarPelaFila(fila f, arquivo svg, tipoTexto tipoTexto){
    Fila *fila = ((Fila*)f);
    Elemento *elementoAtual = fila->topo;
    while (elementoAtual != NULL){
        selecionarAcaoFila(elementoAtual->forma, elementoAtual->tipoForma, svg, tipoTexto);
        Elemento *proximoElemento = elementoAtual->prox;
        elementoAtual = proximoElemento;
    }
}

void selecionarAcaoFila(forma forma, int tipoForma, arquivo svg, tipoTexto tipoTexto){
    switch (tipoForma){
        case 1:
            inserirRetanguloSVG(svg, forma);
            break;
        case 2:
            inserirCirculoSVG(svg, forma);
            break;
        case 3:
            inserirLinhaSVG(svg, forma);
            break;
        case 4:
            inserirTextoSVG(svg, forma, tipoTexto);
            break;
        default:
            break;
    }
}

void liberarFila(fila f){
    Fila *fila = ((Fila*)f);
    Elemento *elementoAtual = fila->topo;
    while (elementoAtual != NULL){
        Elemento *proximoElemento = elementoAtual->prox;
        free(elementoAtual);
        elementoAtual = proximoElemento;
    }
    fila->topo = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
    free(fila);
}