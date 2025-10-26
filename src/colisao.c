#include "colisao.h"
#include "retangulo.h"
#include "circulo.h"
#include "linha.h"
#include "texto.h"
#include <string.h>
#include <math.h>

int intersectaSegmentos(double a1x, double a1y, double a2x, double a2y, double b1x, double b1y, double b2x, double b2y) {
    double den = (a1x - a2x) * (b1y - b2y) - (a1y - a2y) * (b1x - b2x);
    if (den == 0) {
        return 0;
    }
    double t = ((a1x - b1x) * (b1y - b2y) - (a1y - b1y) * (b1x - b2x)) / den;
    double u = -((a1x - a2x) * (a1y - b1y) - (a1y - a2y) * (a1x - b1x)) / den;
    if (t >= 0 && t <= 1 && u >= 0 && u <= 1) {
        return 1;
    }
    return 0;
}

int alg_RetanguloLinha(double rx, double ry, double rw, double rh, double l1x, double l1y, double l2x, double l2y) {
    int p1_dentro = (l1x >= rx && l1x <= rx + rw && l1y >= ry && l1y <= ry + rh);
    int p2_dentro = (l2x >= rx && l2x <= rx + rw && l2y >= ry && l2y <= ry + rh);
    if (p1_dentro || p2_dentro) {
        return 1;
    }
    double r_x2 = rx + rw;
    double r_y2 = ry + rh;
    if (intersectaSegmentos(l1x, l1y, l2x, l2y, rx, ry, r_x2, ry)) return 1;
    if (intersectaSegmentos(l1x, l1y, l2x, l2y, rx, r_y2, r_x2, r_y2)) return 1;
    if (intersectaSegmentos(l1x, l1y, l2x, l2y, rx, ry, rx, r_y2)) return 1;
    if (intersectaSegmentos(l1x, l1y, l2x, l2y, r_x2, ry, r_x2, r_y2)) return 1;
    return 0;
}

int alg_CirculoLinha(double cx, double cy, double cr, double l1x, double l1y, double l2x, double l2y) {
    double distSq1 = pow(l1x - cx, 2) + pow(l1y - cy, 2);
    double distSq2 = pow(l2x - cx, 2) + pow(l2y - cy, 2);
    if (distSq1 <= pow(cr, 2) || distSq2 <= pow(cr, 2)) {
        return 1;
    }
    double lenSq = pow(l2x - l1x, 2) + pow(l2y - l1y, 2);
    if (lenSq == 0) {
        return 0;
    }
    double t = fmax(0, fmin(1, ((cx - l1x) * (l2x - l1x) + (cy - l1y) * (l2y - l1y)) / lenSq));
    double pontoProxX = l1x + t * (l2x - l1x);
    double pontoProxY = l1y + t * (l2y - l1y);
    double distSqPonto = pow(pontoProxX - cx, 2) + pow(pontoProxY - cy, 2);
    return distSqPonto <= pow(cr, 2);
}

int verificarColisao(iterador atual, iterador proximo, double *areaRound, double *areaTotal){
    forma fA = getFormaFila(atual);
    forma fP = getFormaFila(proximo);
    int tA = getTipoFormaFila(atual);
    int tP = getTipoFormaFila(proximo);
    double x1A, y1A, x2A, y2A;
    double x1P, y1P, x2P, y2P;
    calcularHitBox(fA, tA, &x1A, &y1A, &x2A, &y2A);
    calcularHitBox(fP, tP, &x1P, &y1P, &x2P, &y2P);
    if (x1A > x2P || x1P > x2A || y1A > y2P || y1P > y2A) return 0;
    if (tA == 1 && tP == 1) return colideRetanguloRetangulo(fA, fP);
    else if (tA == 1 && tP == 2) return colideRetanguloCirculo(fA, fP);
    else if (tA == 1 && tP == 3) return colideRetanguloLinha(fA, fP);
    else if (tA == 1 && tP == 4) return colideRetanguloTexto(fA, fP);
    else if (tA == 2 && tP == 1) return colideCirculoRetangulo(fA, fP);
    else if (tA == 2 && tP == 2) return colideCirculoCirculo(fA, fP);
    else if (tA == 2 && tP == 3) return colideCirculoLinha(fA, fP);
    else if (tA == 2 && tP == 4) return colideCirculoTexto(fA, fP);
    else if (tA == 3 && tP == 1) return colideLinhaRetangulo(fA, fP);
    else if (tA == 3 && tP == 2) return colideLinhaCirculo(fA, fP);
    else if (tA == 3 && tP == 3) return colideLinhaLinha(fA, fP);
    else if (tA == 3 && tP == 4) return colideLinhaTexto(fA, fP);
    else if (tA == 4 && tP == 1) return colideTextoRetangulo(fA, fP);
    else if (tA == 4 && tP == 2) return colideTextoCirculo(fA, fP);
    else if (tA == 4 && tP == 3) return colideTextoLinha(fA, fP);
    else if (tA == 4 && tP == 4) return colideTextoTexto(fA, fP);
    return 0;
}

void calcularHitBox(forma f, int tipoForma, double *x1, double *y1, double *x2, double *y2){
    switch (tipoForma){
        case 1:
            *x1 = getXRetangulo(f);
            *y1 = getYRetangulo(f);
            *x2 = *x1 + getWRetangulo(f);
            *y2 = *y1 + getHRetangulo(f);
            break;
        case 2:
        {
            double raio = getRCirculo(f);
            double x = getXCirculo(f);
            double y = getYCirculo(f);
            *x1 = x - raio;
            *y1 = y - raio;
            *x2 = x + raio;
            *y2 = y + raio;
            break;
        }
        case 3:
        {
            double xA = getX1Linha(f);
            double xB = getX2Linha(f);
            double yA = getY1Linha(f);
            double yB = getY2Linha(f);
            *x1 = fmin(xA, xB);
            *y1 = fmin(yA, yB);
            *x2 = fmax(xA, xB);
            *y2 = fmax(yA, yB);
            break;
        }
        case 4:
        {
            setX1X2Texto(f, getATexto(f)); 
            
            double xA = getX1Texto(f);
            double xB = getX2Texto(f);
            double yA = getYtTexto(f);
            double yB = getYtTexto(f);

            *x1 = fmin(xA, xB);
            *y1 = fmin(yA, yB);
            *x2 = fmax(xA, xB);
            *y2 = fmax(yA, yB);
            break;
        }
    }
}

int colideRetanguloRetangulo(forma fA, forma fP){
    return 1;
}

int colideRetanguloCirculo(forma fA, forma fP){
    double rx = getXRetangulo(fA);
    double ry = getYRetangulo(fA);
    double rw = getWRetangulo(fA);
    double rh = getHRetangulo(fA);
    double cx = getXCirculo(fP);
    double cy = getYCirculo(fP);
    double cr = getRCirculo(fP);
    double testX = fmax(rx, fmin(cx, rx + rw));
    double testY = fmax(ry, fmin(cy, ry + rh));
    double distSq = pow(cx - testX, 2) + pow(cy - testY, 2);
    return distSq <= pow(cr, 2);
}

int colideRetanguloLinha(forma fA, forma fP){
    return alg_RetanguloLinha(
        getXRetangulo(fA), getYRetangulo(fA), getWRetangulo(fA), getHRetangulo(fA),
        getX1Linha(fP), getY1Linha(fP), getX2Linha(fP), getY2Linha(fP)
    );
}

int colideRetanguloTexto(forma fA, forma fP){
    setX1X2Texto(fP, getATexto(fP));
    return alg_RetanguloLinha(
        getXRetangulo(fA), getYRetangulo(fA), getWRetangulo(fA), getHRetangulo(fA),
        getX1Texto(fP), getYtTexto(fP), getX2Texto(fP), getYtTexto(fP)
    );
}

int colideCirculoRetangulo(forma fA, forma fP){
    return colideRetanguloCirculo(fP, fA);
}

int colideCirculoCirculo(forma fA, forma fP){
    double xA = getXCirculo(fA);
    double yA = getYCirculo(fA);
    double rA = getRCirculo(fA);
    double xP = getXCirculo(fP);
    double yP = getYCirculo(fP);
    double rP = getRCirculo(fP);
    double distSq = pow(xA - xP, 2) + pow(yA - yP, 2);
    double somaRaiosSq = pow(rA + rP, 2);
    return distSq <= somaRaiosSq;
}

int colideCirculoLinha(forma fA, forma fP){
    return alg_CirculoLinha(
        getXCirculo(fA), getYCirculo(fA), getRCirculo(fA),
        getX1Linha(fP), getY1Linha(fP), getX2Linha(fP), getY2Linha(fP)
    );
}

int colideCirculoTexto(forma fA, forma fP){
    setX1X2Texto(fP, getATexto(fP));
    return alg_CirculoLinha(
        getXCirculo(fA), getYCirculo(fA), getRCirculo(fA),
        getX1Texto(fP), getYtTexto(fP), getX2Texto(fP), getYtTexto(fP)
    );
}

int colideLinhaRetangulo(forma fA, forma fP){
    return colideRetanguloLinha(fP, fA);
}

int colideLinhaCirculo(forma fA, forma fP){
    return colideCirculoLinha(fP, fA);
}

int colideLinhaLinha(forma fA, forma fP){
    return intersectaSegmentos(
        getX1Linha(fA), getY1Linha(fA), getX2Linha(fA), getY2Linha(fA),
        getX1Linha(fP), getY1Linha(fP), getX2Linha(fP), getY2Linha(fP)
    );
}

int colideLinhaTexto(forma fA, forma fP){
    setX1X2Texto(fP, getATexto(fP));
    return intersectaSegmentos(
        getX1Linha(fA), getY1Linha(fA), getX2Linha(fA), getY2Linha(fA),
        getX1Texto(fP), getYtTexto(fP), getX2Texto(fP), getYtTexto(fP)
    );
}

int colideTextoRetangulo(forma fA, forma fP){
    return colideRetanguloTexto(fP, fA);
}

int colideTextoCirculo(forma fA, forma fP){
    return colideCirculoTexto(fP, fA);
}

int colideTextoLinha(forma fA, forma fP){
    return colideLinhaTexto(fP, fA);
}

int colideTextoTexto(forma fA, forma fP){
    return 1;
}