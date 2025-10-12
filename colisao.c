#include "colisao.h"
#include "retangulo.h"
#include "circulo.h"
#include "linha.h"
#include "texto.h"
#include <string.h>
#include <math.h>

void verificarColisao(iterador atual, iterador proximo, double *areaRound, double *areaTotal){
    forma formaAtual = getFormaFila(atual);
    forma formaProximo = getFormaFila(proximo);
    int tipoAtual = getTipoFila(atual);
    int tipoProximo = getTipoFila(proximo);
    int houveColisao = 0; 
    if (tipoAtual == 1 && tipoProximo == 1){
        houveColisao = (formaAtual, formaProximo);
    }
    if (tipoAtual == 2 && tipoProximo == 2){
        houveColisao = colideCirculoCirculo(formaAtual, formaProximo);
    }
    if (tipoAtual == 1 && tipoProximo == 2){
        houveColisao = colideRetanguloCirculo(formaAtual, formaProximo);
    }
    if (tipoAtual == 2 && tipoProximo == 1){
        houveColisao = colideRetanguloCirculo(formaAtual, formaProximo);
    }
    if (tipoAtual == 3 || tipoProximo == 3){
        houveColisao = colideLinha(formaAtual, formaProximo);
    }
    if (tipoAtual == 4 || tipoProximo == 4){
        houveColisao = colideTexto(formaAtual, formaProximo);
    }
    if (houveColisao)
}

int colideRetanguloRetangulo(forma atual, forma proximo) {
    double ax = getXRetangulo(atual), ay = getYRetangulo(atual);
    double aw = getWRetangulo(atual), ah = getHRetangulo(atual);
    double bx = getXRetangulo(proximo), by = getYRetangulo(proximo);
    double bw = getWRetangulo(proximo), bh = getHRetangulo(proximo);
    return !(ax + aw < bx || bx + bw < ax || ay + ah < by || by + bh < ay);
}

int colideCirculoCirculo(forma atual, forma proximo) {
    double dx = getXCirculo(atual) - getXCirculo(proximo);
    double dy = getYCirculo(atual) - getYCirculo(proximo);
    double distancia = sqrt(dx * dx + dy * dy);
    return distancia <= (getRCirculo(atual) + getRCirculo(proximo));
}

int colideRetanguloCirculo(forma atual, forma proximo) {
    double rx = getXRetangulo(atual), ry = getYRetangulo(atual);
    double rw = getWRetangulo(atual), rh = getHRetangulo(atual);
    double cx = getXCirculo(proximo), cy = getYCirculo(proximo), cr = getRCirculo(proximo);
    double maisProximoX = fmax(rx, fmin(cx, rx + rw));
    double maisProximoY = fmax(ry, fmin(cy, ry + rh));
    double dx = cx - maisProximoX;
    double dy = cy - maisProximoY;
    return (dx * dx + dy * dy) <= (cr * cr);
}

int colideTexto(forma atual, forma proximo) {
    double tx = getXTexto(atual);
    double ty = getYTexto(atual);
    double tw = strlen(getTxtoTexto(atual));
    double th = 20;
    return colideRetanguloRetangulo(atual, proximo);
}
