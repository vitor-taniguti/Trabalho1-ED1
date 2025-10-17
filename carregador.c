#include "carregador.h"
#include "disparador.h"
#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct carregador{
    int id;
    pilha p;
} Carregador;

carregador criarCarregador(int id){
    Carregador *c = malloc(sizeof(Carregador));
    if (c == NULL) {
        printf("Erro na alocação de memória!");
        exit(1);
    }
    c->id = id;
    c->p = criarPilha();
    return (Carregador*)c;
}

carregador getCarregadorPorId(fila carregadores, int id){
    forma *atual = getPrimeiroElementoFila(carregadores); 
    while (atual != NULL){
        Carregador *carregador = (Carregador*) getPrimeiroFila(carregadores);
        if (getIdDisparador(carregador) == id){
            return carregador;
        }
        atual = getProximoFila(atual);
    }
    return NULL;
}

pilha getPilhaCarregador(carregador c){
    return ((Carregador*)c)->p;
}

void carregarCarregador(carregador c, fila f){
    Carregador *carregador = (Carregador*)c;
    pilha pilha = carregador->p;
    forma form = getPrimeiroElementoFila(f);
    int tipoForma = getTipoPrimeiroElementoFila(f);
    inserirPilha(pilha, form, tipoForma);
    removerFila(f);
}

void liberarCarregador(carregador c){
    free(c);
}