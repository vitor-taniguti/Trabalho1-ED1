#include "colisao.h"
#include "retangulo.h"
#include "circulo.h"
#include "linha.h"
#include "texto.h"
#include <string.h>
#include <math.h>

static const double EPS = 1e-9;

static double dist2(double x1, double y1, double x2, double y2){
    double dx = x1 - x2;
    double dy = y1 - y2;
    return dx*dx + dy*dy;
}

static double distanciaPontoSegmento2(double px, double py, double x1, double y1, double x2, double y2){
    double vx = x2 - x1;
    double vy = y2 - y1;
    double wx = px - x1;
    double wy = py - y1;
    double c1 = vx*wx + vy*wy;
    if (c1 <= 0.0) return dist2(px,py,x1,y1);
    double c2 = vx*vx + vy*vy;
    if (c2 <= c1) return dist2(px,py,x2,y2);
    double t = c1 / c2;
    double projx = x1 + t * vx;
    double projy = y1 + t * vy;
    return dist2(px,py,projx,projy);
}

static int orient(double ax, double ay, double bx, double by, double cx, double cy){
    double val = (bx - ax)*(cy - ay) - (by - ay)*(cx - ax);
    if (fabs(val) < EPS) return 0;
    return (val > 0) ? 2 : 1;
}

static int onSegment(double px, double py, double qx, double qy, double rx, double ry){
    return (qx <= fmax(px, rx) + EPS && qx + EPS >= fmin(px, rx) && qy <= fmax(py, ry) + EPS && qy + EPS >= fmin(py, ry));
}

static int segSegIntersec(double p1x, double p1y, double p2x, double p2y,double p3x, double p3y, double p4x, double p4y){
    int o1 = orient(p1x,p1y, p2x,p2y, p3x,p3y);
    int o2 = orient(p1x,p1y, p2x,p2y, p4x,p4y);
    int o3 = orient(p3x,p3y, p4x,p4y, p1x,p1y);
    int o4 = orient(p3x,p3y, p4x,p4y, p2x,p2y);
    if (o1 != o2 && o3 != o4) return 1;
    if (o1 == 0 && onSegment(p1x,p1y, p3x,p3y, p2x,p2y)) return 1;
    if (o2 == 0 && onSegment(p1x,p1y, p4x,p4y, p2x,p2y)) return 1;
    if (o3 == 0 && onSegment(p3x,p3y, p1x,p1y, p4x,p4y)) return 1;
    if (o4 == 0 && onSegment(p3x,p3y, p2x,p2y, p4x,p4y)) return 1;
    return 0;
}

static int pontoDentroRet(double px, double py, double rx, double ry, double rw, double rh){
    return (px + EPS >= rx && px <= rx + rw + EPS && py + EPS >= ry && py <= ry + rh + EPS);
}

int colideRetanguloRetangulo(forma atual, forma proximo, double *areaRound, double *areaTotal) {
    double ax = getXRetangulo(atual), ay = getYRetangulo(atual);
    double aw = getWRetangulo(atual), ah = getHRetangulo(atual);
    double bx = getXRetangulo(proximo), by = getYRetangulo(proximo);
    double bw = getWRetangulo(proximo), bh = getHRetangulo(proximo);
    double areaA = calcAreaRetangulo(atual);
    double areaB = calcAreaRetangulo(proximo);
    if (!(ax + aw < bx || bx + bw < ax || ay + ah < by || by + bh < ay)) {
        if (areaB > areaA) {
            if (areaRound) *areaRound += areaA;
            if (areaTotal) *areaTotal += areaA;
        }
        return 1;
    }
    return 0;
}

int colideCirculoCirculo(forma atual, forma proximo, double *areaRound, double *areaTotal) {
    double ax = getXCirculo(atual), ay = getYCirculo(atual), ar = getRCirculo(atual);
    double bx = getXCirculo(proximo), by = getYCirculo(proximo), br = getRCirculo(proximo);
    double d2 = dist2(ax,ay,bx,by);
    double rsum = ar + br;
    double areaA = calcAreaCirculo(ar);
    double areaB = calcAreaCirculo(br);
    if (d2 <= rsum*rsum + EPS) {
        if (areaB > areaA) {
            if (areaRound) *areaRound += areaA;
            if (areaTotal) *areaTotal += areaA;
        }
        return 1;
    }
    return 0;
}

int colideRetanguloCirculo(forma atual, forma proximo, int tipoAtual, double *areaRound, double *areaTotal) {
    double rx, ry, rw, rh, cx, cy, cr;
    if (tipoAtual == 1) {
        rx = getXRetangulo(atual);
        ry = getYRetangulo(atual);
        rw = getWRetangulo(atual);
        rh = getHRetangulo(atual);
        cx = getXCirculo(proximo);
        cy = getYCirculo(proximo);
        cr = getRCirculo(proximo);
    } else {
        rx = getXRetangulo(proximo);
        ry = getYRetangulo(proximo);
        rw = getWRetangulo(proximo);
        rh = getHRetangulo(proximo);
        cx = getXCirculo(atual);
        cy = getYCirculo(atual);
        cr = getRCirculo(atual);
    }
    double maisProxX = fmax(rx, fmin(cx, rx + rw));
    double maisProxY = fmax(ry, fmin(cy, ry + rh));
    double d2 = dist2(cx,cy, maisProxX,maisProxY);
    double areaA = (tipoAtual == 1) ? calcAreaRetangulo(atual) : calcAreaCirculo(getRCirculo(atual));
    double areaB = (tipoAtual == 1) ? calcAreaCirculo(getRCirculo(proximo)) : calcAreaRetangulo(proximo);
    if (d2 <= cr*cr + EPS) {
        if (areaB > areaA) {
            if (areaRound) *areaRound += areaA;
            if (areaTotal) *areaTotal += areaA;
        }
        return 1;
    }
    return 0;
}

static int segmentSegmentCollision(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4){
    return segSegIntersec(x1,y1,x2,y2, x3,y3,x4,y4);
}

static int segmentRectCollision(double sx1,double sy1,double sx2,double sy2,double rx,double ry,double rw,double rh){
    if (pontoDentroRet(sx1,sy1, rx,ry,rw,rh) || pontoDentroRet(sx2,sy2, rx,ry,rw,rh)) return 1;
    double rx1 = rx, ry1 = ry;
    double rx2 = rx + rw, ry2 = ry;
    double rx3 = rx + rw, ry3 = ry + rh;
    double rx4 = rx, ry4 = ry + rh;
    if (segmentSegmentCollision(sx1,sy1,sx2,sy2, rx1,ry1, rx2,ry2)) return 1;
    if (segmentSegmentCollision(sx1,sy1,sx2,sy2, rx2,ry2, rx3,ry3)) return 1;
    if (segmentSegmentCollision(sx1,sy1,sx2,sy2, rx3,ry3, rx4,ry4)) return 1;
    if (segmentSegmentCollision(sx1,sy1,sx2,sy2, rx4,ry4, rx1,ry1)) return 1;
    return 0;
}

static int segmentCircleCollision(double sx1,double sy1,double sx2,double sy2,double cx,double cy,double r){
    double d2 = distanciaPontoSegmento2(cx,cy, sx1,sy1,sx2,sy2);
    return d2 <= r*r + EPS;
}

int colideLinhaRetangulo(forma linhaF, forma retF, double *areaRound, double *areaTotal){
    double sx1 = getX1Linha(linhaF), sy1 = getY1Linha(linhaF);
    double sx2 = getX2Linha(linhaF), sy2 = getY2Linha(linhaF);
    double rx = getXRetangulo(retF), ry = getYRetangulo(retF);
    double rw = getWRetangulo(retF), rh = getHRetangulo(retF);
    double x1 = getX1Linha(linhaF);
    double y1 = getY1Linha(linhaF);
    double x2 = getX2Linha(linhaF);
    double y2 = getY2Linha(linhaF);
    double area = calcAreaLinha(x1, y1, x2, y2);
    int colide = segmentRectCollision(sx1,sy1,sx2,sy2, rx,ry,rw,rh);
    if (colide){
        double areaA = area;
        double areaB = calcAreaRetangulo(retF);
        if (areaB > areaA) {
            if (areaRound) *areaRound += areaA;
            if (areaTotal) *areaTotal += areaA;
        }
    }
    return colide;
}

int colideLinhaCirculo(forma linhaF, forma circF, double *areaRound, double *areaTotal){
    double sx1 = getX1Linha(linhaF), sy1 = getY1Linha(linhaF);
    double sx2 = getX2Linha(linhaF), sy2 = getY2Linha(linhaF);
    double x1 = getX1Linha(linhaF);
    double y1 = getY1Linha(linhaF);
    double x2 = getX2Linha(linhaF);
    double y2 = getY2Linha(linhaF);
    double area = calcAreaLinha(x1, y1, x2, y2);
    int colide = segmentCircleCollision(sx1,sy1,sx2,sy2, getXCirculo(circF), getYCirculo(circF), getRCirculo(circF));
    if (colide){
        double areaA = area;
        double areaB = calcAreaCirculo(getRCirculo(circF));
        if (areaB > areaA) {
            if (areaRound) *areaRound += areaA;
            if (areaTotal) *areaTotal += areaA;
        }
    }
    return colide;
}

int colideLinhaLinha(forma l1, forma l2, double *areaRound, double *areaTotal){
    double a1x = getX1Linha(l1), a1y = getY1Linha(l1);
    double a2x = getX2Linha(l1), a2y = getY2Linha(l1);
    double b1x = getX1Linha(l2), b1y = getY1Linha(l2);
    double b2x = getX2Linha(l2), b2y = getY2Linha(l2);
    double x1 = getX1Linha(l1);
    double y1 = getY1Linha(l1);
    double x2 = getX2Linha(l1);
    double y2 = getY2Linha(l1);
    double area = calcAreaLinha(x1, y1, x2, y2);
    int colide = segmentSegmentCollision(a1x,a1y,a2x,a2y, b1x,b1y,b2x,b2y);
    if (colide){
        double areaA = area;
        double areaB = calcAreaLinha(getX1Linha(l2), getY1Linha(l2), getX2Linha(l2), getY2Linha(l2));
        if (areaB > areaA) {
            if (areaRound) *areaRound += areaA;
            if (areaTotal) *areaTotal += areaA;
        }
    }
    return colide;
}

int colideTextoTexto(forma t1, forma t2, double *areaRound, double *areaTotal){
    setX1X2Texto(t1, getATexto(t1));
    setX1X2Texto(t2, getATexto(t2));
    double sx1 = getX1Texto(t1), sy1 = getYtTexto(t1);
    double sx2 = getX2Texto(t1), sy2 = getYtTexto(t1);
    double tx1 = getX1Texto(t2), ty1 = getYtTexto(t2);
    double tx2 = getX2Texto(t2), ty2 = getYtTexto(t2);
    if (segmentSegmentCollision(sx1,sy1,sx2,sy2, tx1,ty1,tx2,ty2)){
        char *txto = getTxtoTexto(t1);
        double areaA = calcAreaTexto(txto);
        double areaB = calcAreaTexto(getTxtoTexto(t2));
        if (areaB > areaA) {
            if (areaRound) *areaRound += areaA;
            if (areaTotal) *areaTotal += areaA;
        }
        return 1;
    }
    return 0;
}

int colideTextoRetangulo(forma textoF, forma retF, double *areaRound, double *areaTotal){
    setX1X2Texto(textoF, getATexto(textoF));
    double sx1 = getX1Texto(textoF), sy1 = getYtTexto(textoF);
    double sx2 = getX2Texto(textoF), sy2 = getYtTexto(textoF);
    double rx = getXRetangulo(retF), ry = getYRetangulo(retF);
    double rw = getWRetangulo(retF), rh = getHRetangulo(retF);
    int colide = segmentRectCollision(sx1,sy1,sx2,sy2, rx,ry,rw,rh);
    if (colide){
        char *txto = getTxtoTexto(textoF);
        double areaA = calcAreaTexto(txto);
        double areaB = calcAreaRetangulo(retF);
        if (areaB > areaA) {
            if (areaRound) *areaRound += areaA;
            if (areaTotal) *areaTotal += areaA;
        }
    }
    return colide;
}

int colideTextoCirculo(forma textoF, forma circF, double *areaRound, double *areaTotal){
    setX1X2Texto(textoF, getATexto(textoF));
    double sx1 = getX1Texto(textoF), sy1 = getYtTexto(textoF);
    double sx2 = getX2Texto(textoF), sy2 = getYtTexto(textoF);
    double cx = getXCirculo(circF), cy = getYCirculo(circF), cr = getRCirculo(circF);
    int colide = segmentCircleCollision(sx1,sy1,sx2,sy2, cx,cy,cr);
    if (colide){
        double comprimento = fabs(sx2 - sx1);
        double areaA = comprimento * 1.0;
        double areaB = calcAreaCirculo(getRCirculo(circF));
        if (areaB > areaA) {
            if (areaRound) *areaRound += areaA;
            if (areaTotal) *areaTotal += areaA;
        }
    }
    return colide;
}

int colideTextoLinha(forma textoF, forma linhaF, double *areaRound, double *areaTotal){
    setX1X2Texto(textoF, getATexto(textoF));
    double sx1 = getX1Texto(textoF), sy1 = getYtTexto(textoF);
    double sx2 = getX2Texto(textoF), sy2 = getYtTexto(textoF);
    double lx1 = getX1Linha(linhaF), ly1 = getY1Linha(linhaF);
    double lx2 = getX2Linha(linhaF), ly2 = getY2Linha(linhaF);
    int colide = segmentSegmentCollision(sx1,sy1,sx2,sy2, lx1,ly1,lx2,ly2);
    if (colide){
        double comprimento = fabs(sx2 - sx1);
        double areaA = comprimento * 1.0;
        double areaB = calcAreaLinha(getX1Linha(linhaF), getY1Linha(linhaF), getX2Linha(linhaF), getY2Linha(linhaF));
        if (areaB > areaA) {
            if (areaRound) *areaRound += areaA;
            if (areaTotal) *areaTotal += areaA;
        }
    }
    return colide;
}

int verificarColisao(iterador atual, iterador proximo, double *areaRound, double *areaTotal) {
    forma fA = getFormaFila(atual);
    forma fB = getFormaFila(proximo);
    int tA = getTipoFormaFila(atual);
    int tB = getTipoFormaFila(proximo);
    if (tA == 1 && tB == 1) return colideRetanguloRetangulo(fA,fB, areaRound, areaTotal);
    if (tA == 2 && tB == 2) return colideCirculoCirculo(fA,fB, areaRound, areaTotal);
    if ((tA == 1 && tB == 2) || (tA == 2 && tB == 1)) {
        if (tA == 1) return colideRetanguloCirculo(fA,fB, 1, areaRound, areaTotal);
        else return colideRetanguloCirculo(fA,fB, 2, areaRound, areaTotal);
    }
    if (tA == 3 && tB == 1) return colideLinhaRetangulo(fA, fB, areaRound, areaTotal);
    if (tA == 3 && tB == 2) return colideLinhaCirculo(fA, fB, areaRound, areaTotal);
    if (tA == 3 && tB == 3) return colideLinhaLinha(fA, fB, areaRound, areaTotal);
    if (tA == 3 && tB == 4) return colideTextoLinha(fB, fA, areaRound, areaTotal);
    if (tA == 4 && tB == 3) return colideTextoLinha(fA, fB, areaRound, areaTotal);
    if (tA == 4 && tB == 4) return colideTextoTexto(fA, fB, areaRound, areaTotal);
    if (tA == 4 && tB == 1) return colideTextoRetangulo(fA, fB, areaRound, areaTotal);
    if (tA == 4 && tB == 2) return colideTextoCirculo(fA, fB, areaRound, areaTotal);
    if (tA == 1 && tB == 4) return colideTextoRetangulo(fB, fA, areaRound, areaTotal);
    if (tA == 2 && tB == 4) return colideTextoCirculo(fB, fA, areaRound, areaTotal);
    return 0;
}
