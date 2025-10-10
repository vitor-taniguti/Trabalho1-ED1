#include "svg.h"
#include "circulo.h"
#include "retangulo.h"
#include "texto.h"
#include "linha.h"
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
    fprintf(saida, "<text id=\"%d\" style=\"font-size:%s;line-height:%s;fill:%s\" font-size=\"5\" y=\"%lf\" x=\"%lf\"> %s </text>\n", getIdTexto(txt), getSize(tt), getFamily(tt), getYtTexto(txt), getXtTexto(txt), getTxtoTexto(txt));
}

void fecharSVG(arquivo saida) {
    fprintf(saida, "</svg>\n");
}