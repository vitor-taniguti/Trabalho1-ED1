#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geo.h"
#include "retangulo.h"
#include "circulo.h"
#include "linha.h"
#include "texto.h"
#include "fila.h"
#include "disparador.h"

#define max_fonte 64
#define max_cor 8
#define max_texto 1024

void abrirArquivoGeo(arquivo *geo, char *caminhoGeo){
    *geo = fopen(caminhoGeo, "r");
    if(*geo == NULL){
        printf("Erro na abertura do arquivo!\n");
        exit(1);
    }
}

void lerArquivoGeo(arquivo geo, fila f, tipoTexto tt){
    if (geo == NULL){
        printf("Arquivo não foi aberto!");
        return;
    }
    char linha[256], tipoForma[3];
    while (fgets(linha, sizeof(linha), geo)){
        int i = 0;
        while (linha[i] != ' ' && linha[i] != '\n' && linha[i] != '\0'){
            tipoForma[i] = linha[i];
            i++;
        }
        tipoForma[i] = '\0';
        processarLinhaFormas(linha, tipoForma, f, tt);
    }
}

void processarLinhaFormas(char *linha, char *tipoForma, fila f, tipoTexto tt){
    char corb[max_cor] = {0}, corp[max_cor] = {0}, cor[max_cor] = {0};
    char font[max_fonte] = {0}, size[max_fonte] = {0}, weight[max_fonte] = {0};
    char txto[max_texto] = {0}, type[3] = {0};
    double x=0, x2=0, y=0, y2=0, r=0, w=0, h=0;
    int id=0;
    char a = '\0';
    if (strcmp(tipoForma, "r") == 0){
        sscanf(linha, "%2s %d %lf %lf %lf %lf %7s %7s", type, &id, &x, &y, &w, &h, corb, corp); 
        inserirFila(f, criarRetangulo(id, x, y, w, h, corb, corp), 1);
    }  else if (strcmp(tipoForma, "c") == 0){
        sscanf(linha, "%2s %d %lf %lf %lf %7s %7s", type, &id, &x, &y, &r, corp, corb);
        inserirFila(f, criarCirculo(id, x, y, r, corb, corp), 2);
    } else if (strcmp(tipoForma, "l") == 0){
        sscanf(linha, "%2s %d %lf %lf %lf %lf %7s", type, &id, &x, &y, &x2, &y2, cor);
        inserirFila(f, criarLinha(id, x, y, x2, y2, cor), 3);
    } else if (strcmp(tipoForma, "t") == 0) {
        sscanf(linha, "%2s %d %lf %lf %7s %7s %1s %1023[^\n]", type, &id, &x, &y, corb, corp, &a, txto);
        inserirFila(f, criarTexto(id, x, y, corb, corp, a, txto), 4);
    } else if (strcmp(tipoForma, "ts") == 0){
        sscanf(linha, "%2s %255s %1s %255s", type, font, weight, size);
        setFamily(tt, font);
        setWeight(tt, weight);
        setSize(tt, size);
    } else{
        printf("A forma solicitada não está no registro: %s\n", linha);
    }
}