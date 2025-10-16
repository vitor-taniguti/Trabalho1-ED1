#include "disparador.h"
#include "carregador.h"
#include "retangulo.h"
#include "circulo.h"
#include "linha.h"
#include "texto.h"
#include "txt.h"
#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct disparador{
    forma forma;
    double x, y;
    int id, tipoForma;
    carregador carregadorE, carregadorD;
} Disparador;

disparador criarDisparador(int id, double x, double y){
    Disparador *disparador = (Disparador*)malloc(sizeof(Disparador));
    if (disparador == NULL){
        printf("Erro na alocação de memória!");
        exit(1);
    }
    disparador->forma = NULL;
    disparador->id = id;
    disparador->x = x;
    disparador->y = y;
    disparador->tipoForma = -1;
    return disparador;
}

disparador getDisparadorPorId(fila disparadores, int id){
    forma *atual = getPrimeiroElementoFila(disparadores); 
    while (atual != NULL){
        Disparador *disparador = (Disparador*) getPrimeiroFila(disparadores);
        if (getIdDisparador(disparador) == id){
            return disparador;
        }
        atual = getProximoFila(atual);
    }
    return NULL;
}

void setXDisparador(disparador d, double x){
    Disparador *disparador = ((Disparador*)d);
    disparador->x = x;
}

void setYDisparador(disparador d, double y){
    Disparador *disparador = ((Disparador*)d);
    disparador->y = y;
}

void setTipoEFormaDisparador(disparador d, forma f, int tipoForma){
    Disparador *disparador = (Disparador*)d;
    disparador->forma = f;
    disparador->tipoForma = tipoForma;
}

void setCarregadoresDisparador(disparador d, carregador cE, carregador cD){
    Disparador *disparador = (Disparador*)d;
    disparador->carregadorE = cE;
    disparador->carregadorD = cD;
}

int getIdDisparador(disparador d){
    return ((Disparador*)d)->id;
}

forma getFormaDisparador(disparador d){
    return ((Disparador*)d)->forma;
}

int getTipoFormaDisparador(disparador d){
    return ((Disparador*)d)->tipoForma;
}

carregador getCarregadorE(disparador d){
    return ((Disparador*)d)->carregadorE;
}

carregador getCarregadorD(disparador d){
    return ((Disparador*)d)->carregadorD;
}

void carregarDisparador(disparador d, char lado){
    Disparador *disparador = ((Disparador*)d);
    carregador cE = disparador->carregadorE;
    carregador cD = disparador->carregadorD;
    pilha pE = getPilhaCarregador(cE);
    pilha pD = getPilhaCarregador(cD);
    if (lado == 'd'){
        if (disparador->forma != NULL){
            inserirPilha(pD, disparador->forma, disparador->tipoForma);
        }
        if (getPrimeiroElementoPilha(pE) == NULL) {
            printf("Carregador esquerdo vazio!");
            return;
        }
        disparador->forma = getPrimeiroElementoPilha(pE);
        disparador->tipoForma = getTipoPrimeiroElementoPilha(pE);
        removerPilha(pE);
    } else{
        if (disparador->forma != NULL){
            inserirPilha(pE, disparador->forma, disparador->tipoForma);
        }
        if (getPrimeiroElementoPilha(pD) == NULL) {
            printf("Carregador direito vazio!");
            return;
        }
        disparador->forma = getPrimeiroElementoPilha(pD);
        disparador->tipoForma = getTipoPrimeiroElementoPilha(pD);
        removerPilha(pD);
    }
}

double getXDisparador(disparador d){
    return ((Disparador*)d)->x;
}

double getYDisparador(disparador d){
    return ((Disparador*)d)->y;
}

void dispararDisparador(disparador d, double dx, double dy, arquivo *txt, fila arena){
    Disparador *disparador = (Disparador*)d;
    if (disparador == NULL || disparador->forma == NULL){
        printf("Erro no disparador ou na forma!");
        exit(1);
    }
    forma f = disparador->forma;
    int tipo = disparador->tipoForma;
    double xD = disparador->x, yD = disparador->y;
    double novoX, novoY, novoX2, novoY2;
    novoX = xD + dx;
    novoY = yD + dy;
    switch (tipo){
    case 1:
        setXRetangulo(f, novoX);
        setYRetangulo(f, novoY);
        break;
    case 2:
        setXCirculo(f, novoX);
        setYCirculo(f, novoY);
        break;
    case 3:
        novoX2 = xD + dx + (getX2Linha(disparador->forma) - getX1Linha(disparador->forma));
        novoY2 = yD + dy + (getY2Linha(disparador->forma) - getY1Linha(disparador->forma));
        setX1Linha(f, novoX);
        setY1Linha(f, novoY);
        setX2Linha(f, novoX2);
        setY2Linha(f, novoY2);
        break;
    case 4:
        setXtTexto(f, novoX);
        setYtTexto(f, novoY);
        break;
    default:
        printf("Tipo de forma inválido!\n");
        break;
    }
    inserirFila(arena, f, tipo);
    disparador->forma = NULL;
    disparador->tipoForma = -1;
}