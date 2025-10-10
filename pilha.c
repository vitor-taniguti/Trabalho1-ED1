#include "pilha.h"
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
    int tamanho;
    pont topo;
} Pilha;


pilha criarPilha(){
    Pilha *p = malloc(sizeof(Pilha));
    if (p == NULL){
        printf("Falha na alocação de memória!");
        exit(1);
    }
    p->topo = NULL;
    p->tamanho = 0;
    return ((Pilha*)p);
}

void inserirPilha(pilha p, forma f, int tipoForma){
    Pilha *pilha = ((Pilha*)p);
    Elemento *novoElemento = (Elemento*)malloc(sizeof(Elemento));
    if (novoElemento == NULL){
        printf("Falha na alocação de memória!");
        exit(1);
    }
    novoElemento->forma = f;
    novoElemento->tipoForma = tipoForma;
    novoElemento->prox = pilha->topo;
    pilha->topo = novoElemento;
    pilha->tamanho++;
}

void removerPilha(pilha p){
    Pilha *pilha = ((Pilha*)p);
    if (pilha->topo == NULL){
        printf("A pilha está vazia!");
        exit(1);
    }
    Elemento *elementoTopo = pilha->topo;
    pilha->topo = pilha->topo->prox;
    free(elementoTopo->forma);
    free(elementoTopo);
    pilha->tamanho--;
}

int getTipoPrimeiroElementoPilha(pilha p){
    Pilha *pilha = (Pilha*)p;
    if (pilha == NULL || pilha->topo == NULL){
        printf("A pilha está vazia!");
        return -1;
    }
    return pilha->topo->tipoForma;
}

void passarPelaPilha(pilha p, int tipoPilha, arquivo svg, tipoTexto tipoTexto){
    Pilha *pilha = ((Pilha*)p);
    Elemento *elementoAtual = pilha->topo;
    while (elementoAtual != NULL){
        selecionarAcaoPilha(elementoAtual->forma, tipoPilha, svg, tipoTexto);
        Elemento *proximoElemento = elementoAtual->prox;
        elementoAtual = proximoElemento;
    }
}

void selecionarAcaoPilha(forma f, int tipoPilha, arquivo svg, tipoTexto tipoTexto){
    switch (tipoPilha){
        case 1:
            inserirRetanguloSVG(svg, f);
            break;
        case 2:
            inserirCirculoSVG(svg, f);
            break;
        case 3:
            inserirLinhaSVG(svg, f);
            break;
        case 4:
            inserirTextoSVG(svg, f, tipoTexto);
            break;
        default:
            break;
    }
}

void liberarPilha(pilha p){
    Pilha *pilha = ((Pilha*)p);
    Elemento *elementoAtual = pilha->topo;
    while (elementoAtual != NULL){
        Elemento *proximoElemento = elementoAtual->prox;
        free(elementoAtual);
        elementoAtual = proximoElemento;
    }
    pilha->topo = NULL;
    pilha->tamanho = 0;
    free(pilha);
}