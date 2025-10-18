#include "svg.h"
#include "circulo.h"
#include "retangulo.h"
#include "texto.h"
#include "linha.h"
#include "disparador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void abrirArquivoSvg(arquivo *saida, char *caminhoSaida){
    *saida = fopen(caminhoSaida, "w");
    if (*saida == NULL){
        printf("Falha na alocação de memória!");
        exit(1);
    }
}

void inicializarSVG(arquivo saida){
    fprintf(saida, "<svg xmlns:svg=\"http://www.w3.org/2000/svg\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
}

void inserirRetanguloSVG(arquivo saida, retangulo r){
    fprintf(saida, "<rect id=\"%d\" style=\"fill:%s;fill-opacity:0.5;stroke:%s\" height=\"%lf\" width=\"%lf\" y=\"%lf\" x=\"%lf\" />\n", getIdRetangulo(r), getCorPRetangulo(r), getCorBRetangulo(r), getHRetangulo(r), getWRetangulo(r), getYRetangulo(r), getXRetangulo(r));
}

void inserirCirculoSVG(arquivo saida, circulo c){
    fprintf(saida, "<circle id=\"%d\" style=\"fill:%s;fill-opacity:0.5;stroke:%s\" r=\"%lf\" cy=\"%lf\" cx=\"%lf\" />\n", getIdCirculo(c), getCorPCirculo(c), getCorBCirculo(c), getRCirculo(c), getYCirculo(c), getXCirculo(c));
}

void inserirLinhaSVG(arquivo saida, linha l){
    fprintf(saida, "<line id=\"%d\" x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" stroke-width=\"2\" />\n", getIdLinha(l), getX1Linha(l), getY1Linha(l), getX2Linha(l), getY2Linha(l), getCorLinha(l));
}

void inserirTextoSVG(arquivo saida, texto txt, tipoTexto tt){
    fprintf(saida, "<text id=\"%d\" style=\"font-size:%s;line-height:%s;fill:%s\" font-size=\"5\" y=\"%lf\" x=\"%lf\"> %s </text>\n", getIdTexto(txt), getSize(tt), getFamily(tt), getCorPTexto(txt), getYtTexto(txt), getXtTexto(txt), getTxtoTexto(txt));
}

void inserirAsteriscoSVG(arquivo saida, double x, double y){
    fprintf(saida, "<text x=\"%f\" y=\"%f\" font-size=\"20\" fill=\"red\">*</text>\n", x, y);
}

void inserirDimensoesDisparo(disparador d, double dx, double dy, arquivo saida) {
    double x = getXDisparador(d);
    double y = getYDisparador(d);
    double xFinal = x + dx;
    double yFinal = y + dy;
    fprintf(saida,"<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" ""stroke=\"purple\" stroke-width=\"1.5\" />\n",x, y, xFinal, yFinal);
    fprintf(saida,"<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" ""stroke=\"purple\" stroke-dasharray=\"3,3\" stroke-width=\"1\" />\n",xFinal, y, xFinal, yFinal); 
    fprintf(saida,"<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" ""stroke=\"purple\" stroke-dasharray=\"3,3\" stroke-width=\"1\" />\n",x, yFinal, xFinal, yFinal);
    fprintf(saida,"<text x=\"%lf\" y=\"%lf\" font-size=\"12\" fill=\"purple\" ""text-anchor=\"middle\">%.2lf</text>\n",(x + xFinal) / 2, y - 5, dx);
    fprintf(saida,"<text x=\"%lf\" y=\"%lf\" font-size=\"12\" fill=\"purple\" ""text-anchor=\"end\">%.2lf</text>\n",xFinal + 5, (y + yFinal) / 2, dy);
    fprintf(saida,"<text x=\"%lf\" y=\"%lf\" font-size=\"14\" fill=\"red\" ""text-anchor=\"middle\" dominant-baseline=\"middle\">*</text>\n",xFinal, yFinal);
}

void fecharSVG(arquivo saida) {
    fprintf(saida, "</svg>\n");
}