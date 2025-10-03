#include "disparador.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct disparador{
    fila f;
    double x, y;
} Disparador;

disparador criarDisparador(fila f, double x, double y){
    Disparador *disparador = (Disparador*)malloc(sizeof(Disparador));
    disparador->f = f;
    disparador->x = x;
    disparador->y = y;
    return disparador;
}

fila getFilaDisparador(disparador d){
    Disparador *disparador = ((Disparador*)d);
    return disparador->f;
}

double getXDisparador(disparador d){
    return ((Disparador*)d)->x;
}