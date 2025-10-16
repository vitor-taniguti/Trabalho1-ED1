#include "qry.h"
#include "disparador.h"
#include "carregador.h"
#include "txt.h"
#include "svg.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

void abrirArquivoQry(arquivo *qry, char *caminhoQry){
    *qry = fopen(caminhoQry, "r");
    if(*qry == NULL){
        printf("Erro na abertura do arquivo!\n");
        exit(1);
    }
}

void lerArquivoQry(arquivo qry, arquivo txt, arquivo svg, fila chao, fila arena, fila disparadores, fila carregadores, double *areaTotal){
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
        processarLinhaComandos(linha, comando, chao, arena, disparadores, carregadores, txt, svg, areaTotal);
    }
}

void processarLinhaComandos(char *linha, char *comando, fila chao, fila arena, fila disparadores, fila carregadores, arquivo txt, arquivo svg, double *areaTotal){
    int id, n, cE, cD;
    double x, y, x2, y2, dx, dy, ix, iy, areaTotal;
    char lado, com[5];
    if (strcmp(comando, "pd") == 0){
        sscanf(linha, "%3s %d %lf %lf", com, &id, &x, &y);
        pd(id, x, y, disparadores);
    } else if (strcmp(comando, "lc") == 0){
        sscanf(linha, "%3s %d %d", com, &id, &n);
        lc(id, n, chao, txt, carregadores);
    } else if (strcmp(comando, "atch") == 0){
        sscanf(linha, "%5s %d %d %d", com, &id, &cE, &cD);
        atch(id, cE, cD, carregadores, disparadores);
    } else if (strcmp(comando, "shft") == 0){
        sscanf(linha, "%5s %d %c %d", com, &id, &lado, &n);
        shft(id, lado, n, txt, disparadores);
    } else if (strcmp(comando, "dsp") == 0){
        sscanf(linha, "%4s %d %lf %lf %c", com, &id, &dx, &dy, &lado);
        dsp(id, dx, dy, lado, txt, svg, arena, disparadores);
    } else if (strcmp(comando, "rjd") == 0){
        sscanf(linha, "%4s %d %c %lf %lf %lf %lf", com, &id, &lado, &dx, &dy, &ix, &iy);
        rjd(id, lado, dx, dy, ix, iy, txt, arena, disparadores);
    } else if (strcmp(comando, "calc") == 0){
        calc(areaTotal, chao, arena, txt, svg);
    }
}

void pd(int id, double x, double y, fila disparadores){
    disparador d = getDisparadorPorId(disparadores, id); 
    if (d == NULL){
        d = criarDisparador(id, x, y);
        inserirFila(disparadores, criarDisparador(id, x, y), 0);
    } else{
        setXDisparador(d, x);
        setYDisparador(d, y);
    }
}

void lc(int id, int n, fila chao, arquivo txt, fila carregadores){
    carregador c = getCarregadorPorId(carregadores, id);
    if (c == NULL){
        c = criarCarregador(id);
        inserirFila(carregadores, c, 0);
    }
    for (int i = 0; i < n; i++){
        carregarCarregador(c, chao);
        printarDadosForma(txt, getPrimeiroElementoPilha(getPilhaCarregador(c)), getTipoPrimeiroElementoPilha(getPilhaCarregador(c)));
    }
}

void atch(int id, int cE, int cD, fila carregadores, fila disparadores){
    disparador d = getDisparadorPorId(disparadores, id);
    carregador c = getCarregadorE(d);
    carregador c2 = getCarregadorD(d);
    if (c != NULL){
        inserirFila(carregadores, c, 0);
    }
    if (c2 != NULL){
        inserirFila(carregadores, c2, 0);
    }
    c = getCarregadorPorId(carregadores, cE);
    c2 = getCarregadorPorId(carregadores, cD);
    setCarregadoresDisparador(d, c, c2);
}

void shft(int id, char lado, int n, arquivo txt, fila disparadores){
    disparador d = getDisparadorPorId(disparadores, id);
    for (int i = 0; i < n; i++){
        carregarDisparador(d, lado);
    }
    printarDadosForma(txt, getFormaDisparador(d), getTipoFormaDisparador(d));
}

void dsp(int id, double dx, double dy, char lado, arquivo txt, arquivo svg, fila arena, fila disparadores){
    disparador d = getDisparadorPorId(disparadores, id);
    printarDadosForma(txt, getFormaDisparador(d), getTipoFormaDisparador(d));
    dispararDisparador(d, dx, dy, txt, arena);
    printarPosicaoForma(txt, getUltimoFila(arena), getTipoUltimoFila(arena));
    if (lado == 'v'){
        inserirDimensoesDisparo(d, dx, dy, svg);
    }
}

void rjd(int id, char lado, double dx, double dy, double ix, double iy, arquivo txt, fila arena, fila disparadores){
    disparador d = getDisparadorPorId(disparadores, id);
    carregador c;
    if (lado == 'e'){
        c = getCarregadorD(d);
    } else{
        c = getCarregadorE(d);
    }
    int i = 0;
    while (getPrimeiroElementoPilha(getPilhaCarregador(c)) != NULL){
        shft(id, lado, 1, txt, disparadores);
        printarDadosForma(txt, getFormaDisparador(d), getTipoFormaDisparador(d));
        dispararDisparador(d, dx+i*ix, dy+i*iy, txt, arena);
        i++;
    }
}

void calc(double *areaTotal, fila chao, fila arena, arquivo txt, arquivo svg){
    iterador atual = getPrimeiroFila(arena);
    iterador proximo = getProximoFila(atual);
    double areaRound = 0;
    while (proximo != NULL){
        int houveColisao = 0;
        double areaAtual = areaRound;
        forma fA = getFormaFila(atual); 
        forma fP = getFormaFila(proximo);
        int tA = getTipoFormaFila(atual);
        int tP = getTipoFormaFila(proximo);
        char *corP, *corB;
        houveColisao = verificarColisao(atual, proximo, &areaRound, areaTotal);
        if (houveColisao){    
            if (areaAtual != areaRound){
                double x, y;
                getXYForma(fA, tA, &x, &y);
                inserirAsteriscoSVG(svg, x, y);
                removerFila(arena);
                inserirFila(chao, getPrimeiroElementoFila(arena), getTipoPrimeiroElementoFila(arena));
                removerFila(arena);
            } else{
                setCorBForma(fP, tP, getCorPForma(fA, tA, corP));
                inserirFila(chao, fA, tA);
                removerFila(arena);
                inserirFila(chao, fP, tP);
                removerFila(arena);
                clonarForma(fA, tA, chao);
            }
        } else{
            inserirFila(chao, fA, tA);
            removerFila(arena);
            inserirFila(chao, fP, tP);
            removerFila(arena);
        }
        atual = proximo;
        proximo = getProximoFila(proximo);
    }
    printarAreaEsmagada(txt, areaRound, *areaTotal);
}

void getXYForma(forma f, int tipoForma, double *x, double *y){
    switch (tipoForma){
        case 1:
            *x = getXRetangulo(f);
            *y = getYRetangulo(f);
            break;
        case 2:
            *x = getXCirculo(f);
            *y = getYCirculo(f);
            break;
        case 3:
            double x1 = getX1Linha(f);
            double y1 = getY1Linha(f);
            double x2 = getX2Linha(f);
            double y2 = getY2Linha(f);
            double d1 = sqrt(pow(x1, 2) + pow(y1, 2));
            double d2 = sqrt(pow(x2, 2) + pow(y2, 2));
            if (d1 < d2){
                *x = x1;
                *y = y1;
            } else if (d2 < d1){
                *x = x2;
                *y = y2;
            } else{
                if (y1 < y2){
                    *x = x1;
                    *y = y1;
                } else{
                    *x = x2;
                    *y = y2;
                }
            }
            break;
        case 4:
            *x = getXtTexto(f);
            *y = getYtTexto(f);
            break;
    }
}

char* getCorPForma(forma f, int tipoForma, char *corP){
    switch (tipoForma){
        case 1:
            strcpy(getCorPRetangulo(f), corP);
            break;
        case 2:
            strcpy(getCorPCirculo(f), corP);
            break;
        case 3:
            strcpy(getCorLinha(f), corP);
            break;
        case 4:
            strcpy(getCorPTexto(f), corP);
            break;
    }
    return corP;
}

char* getCorBForma(forma f, int tipoForma, char *corB){
    switch (tipoForma){
        case 1:
            strcpy(getCorBRetangulo(f), corB);
            break;
        case 2:
            strcpy(getCorBCirculo(f), corB);
            break;
        case 3:
            strcpy(getCorLinha(f), corB);
            break;
        case 4:
            strcpy(getCorBTexto(f), corB);
            break;
    }
    return corB;
}

void setCorPForma(forma f, int tipoForma, char *corP){
    switch (tipoForma){
        case 1:
            setCorPRetangulo(f, corP);
            break;
        case 2:
            setCorPCirculo(f, corP);
            break;
        case 3:
            setCorLinha(f, corP);
            break;
        case 4:
            setCorPTexto(f, corP);
            break;
    }
}

void setCorBForma(forma f, int tipoForma, char *corB){
    switch (tipoForma){
        case 1:
            setCorBRetangulo(f, corB);
            break;
        case 2:
            setCorBCirculo(f, corB);
            break;
        case 3:
            setCorLinha(f, corB);
            break;
        case 4:
            setCorBTexto(f, corB);
            break;
    }
}

void clonarForma(forma f, int tipoForma, fila chao){
    forma formaNova;
    int id;
    double x, y, w, h, r, x2, y2;
    char *corP, *corB, a, *txto;
    switch (tipoForma){
        case 1:
            id = getIdRetangulo(f) + 1;
            x = getXRetangulo(f);
            y = getYRetangulo(f);
            w = getWRetangulo(f);
            h = getHRetangulo(f);
            corP = getCorBRetangulo(f);
            corB = getCorPRetangulo(f);
            formaNova = criarRetangulo(id, x, y, w, h, corB, corP);
            break;
        case 2:
            id = getIdCirculo(f) + 1;
            x = getXCirculo(f);
            y = getYCirculo(f);
            r = getRCirculo(f);
            corP = getCorBCirculo(f);
            corB = getCorPCirculo(f);
            formaNova = criarCirculo(id, x, y, r, corB, corP);
            break;
        case 3:
            id = getIdLinha(f) + 1;
            x = getX1Linha(f);
            y = getY1Linha(f);
            x2 = getX2Linha(f);
            y2 = getY2Linha(f);
            corP = calcCorComplementarLinha(f);
            formaNova = criarLinha(id, x, y, x2, y2, corP);
            break;
        case 4:
            id = getIdTexto(f) + 1;
            x = getXtTexto(f);
            y = getYtTexto(f);
            a = getATexto(f);
            corP = getCorBTexto(f);
            corB = getCorPTexto(f);
            txto = getTxtoTexto(f);
            formaNova = criarTexto(id, x, y, corB, corP, a, txto);
            break;
    }
    inserirFila(chao, formaNova, tipoForma);
}

int getMaiorId(fila chao){
    
}