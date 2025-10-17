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
        while (linha[i] != ' ' || linha[i] != '\n'){
            tipoForma[i] = linha[i];
            i++;
        }
        tipoForma[i] = '\0';
        processarLinhaFormas(linha, tipoForma, f, tt);
    }
    fclose(geo);
}

void processarLinhaFormas(char *linha, char *tipoForma, fila f, tipoTexto tt){
    int id;
    double x, x2, y, y2, r, w, h;
    char corb[max_cor], corp[max_cor], cor[max_cor], a;
    char font[max_fonte], size[max_fonte], weight[max_fonte];
    char txto[max_texto], type[3];
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