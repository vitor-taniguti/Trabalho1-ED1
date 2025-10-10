#include "qry.h"
#include "disparador.h"
#include "carregador.h"
#include "txt.h"
#include "svg.h"
#include <stdio.h>
#include <string.h>

void abrirArquivoQry(arquivo *qry, char *caminhoQry){
    *qry = fopen(caminhoQry, "r");
    if(*qry == NULL){
        printf("Erro na abertura do arquivo!\n");
        exit(1);
    }
}

void lerArquivoQry(arquivo qry, arquivo txt, arquivo svg, fila chao, fila arena, fila disparadores, fila carregadores){
    if (qry == NULL){
        printf("Arquivo não foi aberto!");
        return;
    }
    char linha[256], comando[5];
    while (fgets(linha, sizeof(linha), qry)){
        int i = 0;
        while (linha[i] != ' '){
            comando[i] = linha[i];
            i++;
        }
        comando[i] = '\0';
        processarLinhaComandos(linha, comando, chao, arena, disparadores, carregadores, txt, svg);
    }
}

void processarLinhaComandos(char *linha, char *comando, fila chao, fila arena, fila disparadores, fila carregadores, arquivo txt, arquivo svg){
    int id, n, cE, cD;
    double x, y, x2, y2, dx, dy, ix, iy;
    char lado, com[5];
    disparador d;
    carregador c, c2;
    if (strcmp(comando, "pd") == 0){
        sscanf(linha, "%3s %d %lf %lf", com, &id, &x, &y);
        d = getDisparadorPorId(disparadores, id); 
        if (d == NULL){
            inserirFila(disparadores, criarDisparador(id, x, y), 0);
        } else{
            setXDisparador(d, x);
            setYDisparador(d, y);
        }
    } else if (strcmp(comando, "lc") == 0){
        sscanf(linha, "%3s %d %d", com, &id, &n);
        c = getCarregadorPorId(carregadores, id);
        if (c == NULL){
            c = criarCarregador(id);
            inserirFila(carregadores, c, 0);
        }
        for (int i = 0; i < n; i++){
            carregarCarregador(c, chao);
            printarDadosForma(&txt, getPrimeiroElementoPilha(getPilhaCarregador(c)), getTipoPrimeiroElementoPilha(getPilhaCarregador(c)));
        }
    } else if (strcmp(comando, "atch") == 0){
        sscanf(linha, "%5s %d %d %d", com, id, &cE, &cD);
        d = getDisparadorPorId(disparadores, id);
        c = getCarregadorPorId(carregadores, cE);
        c2 = getCarregadorPorId(carregadores, cD);
        setCarregadoresDisparador(d, c, c2);
    } else if (strcmp(comando, "shft") == 0){
        sscanf(linha, "%5s %d %c %d", com, id, lado, n);
        d = getDisparadorPorId(disparadores, id);
        for (int i = 0; i < n; i++){
            carregarDisparador(d, lado);
        }
        printarDadosForma(&txt, getFormaDisparador(d), getTipoFormaDisparador(d));
    } else if (strcmp(comando, "dsp") == 0){
        sscanf(linha, "");
    } else if (strcmp(comando, "") == 0){
        sscanf(linha, "");
    } else if (strcmp(comando, "") == 0){
        sscanf(linha, "");
    }
}