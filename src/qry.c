#include "qry.h"
#include "disparador.h"
#include "carregador.h"
#include "txt.h"
#include "svg.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

double calcAreaForma(forma f, int tipoForma){
    switch (tipoForma){
        case 1:
            return calcAreaRetangulo(f);
            break;
        case 2:
           return calcAreaCirculo(f);
           break;
        case 3:
            return calcAreaLinha(f);
            break;
        case 4:
            return calcAreaTexto(f);
            break;
    }
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

char* getCorPForma(forma f, int tipoForma){
    switch (tipoForma){
        case 1:
            return getCorPRetangulo(f);
            break;
        case 2:
            return getCorPCirculo(f);
            break;
        case 3:
            return calcCorComplementarLinha(getCorLinha(f));
            break;
        case 4:
            return getCorPTexto(f);
            break;
        default:
            return NULL;
            break;
    }
}

char* getCorBForma(forma f, int tipoForma){
    switch (tipoForma){
        case 1:
            return getCorBRetangulo(f);
            break;
        case 2:
            return getCorBCirculo(f);
            break;
        case 3:
            return getCorLinha(f);
            break;
        case 4:
            return getCorBTexto(f);
            break;
        default:
            return NULL;
            break;
    }
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
    int id = getMaiorId(chao) + 1;
    double x, y, w, h, r, x2, y2;
    char *corP, *corB, a, *txto;
    switch (tipoForma){
        case 1:
            x = getXRetangulo(f);
            y = getYRetangulo(f);
            w = getWRetangulo(f);
            h = getHRetangulo(f);
            corP = getCorBRetangulo(f);
            corB = getCorPRetangulo(f);
            formaNova = criarRetangulo(id, x, y, w, h, corB, corP);
            break;
        case 2:
            x = getXCirculo(f);
            y = getYCirculo(f);
            r = getRCirculo(f);
            corP = getCorBCirculo(f);
            corB = getCorPCirculo(f);
            formaNova = criarCirculo(id, x, y, r, corB, corP);
            break;
        case 3:
            x = getX1Linha(f);
            y = getY1Linha(f);
            x2 = getX2Linha(f);
            y2 = getY2Linha(f);
            corP = calcCorComplementarLinha(f);
            formaNova = criarLinha(id, x, y, x2, y2, corP);
            break;
        case 4:
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
    iterador atual = getPrimeiroFila(chao);
    int maior = 0;
    while (atual != NULL) {
        int id = getIdForma(getFormaFila(atual), getTipoFormaFila(atual));
        if (id > maior){
            maior = id;
        }
        atual = getProximoFila(atual);
    }
    return maior;
}

int getIdForma(forma f, int tipoForma){
    switch (tipoForma){
        case 1:
            return getIdRetangulo(f);
            break;
        case 2:
            return getIdCirculo(f);
            break;
        case 3:
            return getIdLinha(f);
            break;
        case 4:
            return getIdTexto(f);
            break;
    }
    return 0;
}

void abrirArquivoQry(arquivo *qry, char *caminhoQry){
    *qry = fopen(caminhoQry, "r");
    if(*qry == NULL){
        printf("Erro na abertura do arquivo!\n");
        exit(1);
    }
}

void lerArquivoQry(arquivo qry, arquivo txt, arquivo svg, fila chao, fila arena, fila disparadores, fila carregadores){
    double areaTotal = 0;
    int instrucoes = 0, disparos = 0, esmagadas = 0, clonadas = 0; 
    if (qry == NULL){
        printf("Arquivo não foi aberto!");
        return;
    }
    char linha[256], comando[5];
    while (fgets(linha, sizeof(linha), qry)){
        int i = 0;
        while (linha[i] != ' ' && linha[i] != '\n' && linha[i] != '\0'){
            comando[i] = linha[i];
            i++;
        }
        comando[i] = '\0';
        processarLinhaComandos(linha, comando, chao, arena, disparadores, carregadores, txt, svg, &areaTotal, &instrucoes, &disparos, &esmagadas, &clonadas);
    }
    printarResultados(txt, areaTotal, instrucoes, disparos, esmagadas, clonadas);
}

void processarLinhaComandos(char *linha, char *comando, fila chao, fila arena, fila disparadores, fila carregadores, arquivo txt, arquivo svg, double *areaTotal, int* instrucoes, int *disparos, int *esmagadas, int *clonadas){
    int id, n, cE, cD;
    double x, y, dx, dy, ix, iy;
    char lado, com[5];
    fprintf(txt, "[*] %s\n", linha);
    if (strcmp(comando, "pd") == 0){
        sscanf(linha, "%3s %d %lf %lf", com, &id, &x, &y); 
        pd(id, x, y, disparadores);
    } else if (strcmp(comando, "lc") == 0){
        sscanf(linha, "%3s %d %d", com, &id, &n);
        lc(id, n, chao, txt, carregadores);
        fprintf(txt, "\n");
    } else if (strcmp(comando, "atch") == 0){
        sscanf(linha, "%5s %d %d %d", com, &id, &cE, &cD);
        atch(id, cE, cD, carregadores, disparadores);
    } else if (strcmp(comando, "shft") == 0){
        sscanf(linha, "%5s %d %c %d", com, &id, &lado, &n);
        shft(id, lado, n, txt, disparadores);
        fprintf(txt, "\n");
    } else if (strcmp(comando, "dsp") == 0){
        sscanf(linha, "%4s %d %lf %lf %c", com, &id, &dx, &dy, &lado);
        dsp(id, dx, dy, lado, txt, svg, arena, disparadores, disparos);
        fprintf(txt, "\n");
    } else if (strcmp(comando, "rjd") == 0){
        sscanf(linha, "%4s %d %c %lf %lf %lf %lf", com, &id, &lado, &dx, &dy, &ix, &iy);
        rjd(id, lado, dx, dy, ix, iy, txt, svg, arena, disparadores, disparos);
    } else if (strcmp(comando, "calc") == 0){
        calc(areaTotal, chao, arena, txt, svg, esmagadas, clonadas);
    }
    (*instrucoes)++;
}

void pd(int id, double x, double y, fila disparadores){
    disparador d = getDisparadorPorId(disparadores, id); 
    if (d == NULL){
        d = criarDisparador(id, x, y);
        inserirFila(disparadores, d, 5);
    } else{
        setXDisparador(d, x);
        setYDisparador(d, y);
    }
}

void lc(int id, int n, fila chao, arquivo txt, fila carregadores){
    fprintf(txt, "Formas carregadas:\n\n");
    carregador c = getCarregadorPorId(carregadores, id);
    if (c == NULL){
        c = criarCarregador(id);
        inserirFila(carregadores, c, 6);
    }
    for (int i = 0; i < n; i++){
        carregarCarregador(c, chao);
        printarDadosForma(txt, getPrimeiroElementoPilha(getPilhaCarregador(c)), getTipoPrimeiroElementoPilha(getPilhaCarregador(c)));
    }
}

void atch(int id, int cE, int cD, fila carregadores, fila disparadores){
    disparador d = getDisparadorPorId(disparadores, id);
    carregador c = getCarregadorPorId(carregadores, cE);
    carregador c2 = getCarregadorPorId(carregadores, cD);
    if (c == NULL){
        c = criarCarregador(cE);
        inserirFila(carregadores, c, 6);
    }
    if (c2 == NULL){
        c2 = criarCarregador(cD);
        inserirFila(carregadores, c2, 6);
    }
    setCarregadoresDisparador(d, c, c2);
}

void shft(int id, char lado, int n, arquivo txt, fila disparadores){
    fprintf(txt, "Forma no ponto de disparo - ");
    disparador d = getDisparadorPorId(disparadores, id);
    for (int i = 0; i < n; i++){
        carregarDisparador(d, lado);
    }
    printarDadosForma(txt, getFormaDisparador(d), getTipoFormaDisparador(d));
}

void dsp(int id, double dx, double dy, char lado, arquivo txt, arquivo svg, fila arena, fila disparadores, int *disparos){
    fprintf(txt, "Forma disparada - ");
    disparador d = getDisparadorPorId(disparadores, id);
    printarDadosForma(txt, getFormaDisparador(d), getTipoFormaDisparador(d));
    dispararDisparador(d, dx, dy, arena);
    iterador atual = getPrimeiroFila(arena);
    if (atual != NULL){ 
        iterador proximo = getProximoFila(atual);
        while (proximo != NULL){
            atual = proximo;
            proximo = getProximoFila(atual);
        }
    }
    printarPosicaoForma(txt, getFormaFila(atual), getTipoFormaFila(atual));
    if (lado == 'v'){
        inserirDimensoesDisparo(d, dx, dy, svg);
    }
    (*disparos)++;
}

void rjd(int id, char lado, double dx, double dy, double ix, double iy, arquivo txt, arquivo svg, fila arena, fila disparadores, int *disparos){
    fprintf(txt, "Formas disparadas na rajada:\n\n");
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
        dsp(id, dx+i*ix, dy+i*iy, lado, txt, svg, arena, disparadores, disparos);
        fprintf(txt, "\n");
        i++;
    }
}

void calc(double *areaTotal, fila chao, fila arena, arquivo txt, arquivo svg, int *esmagadas, int *clonadas){
    fprintf(txt, "Fim da rodada! Fazendo verificações\n\n");
    double areaRound = 0;
    iterador atual = getPrimeiroFila(arena);
    while (atual != NULL && getProximoFila(atual) != NULL){
        iterador proximo = getProximoFila(atual);
        int houveColisao = 0;
        forma fA = getFormaFila(atual); 
        forma fP = getFormaFila(proximo);
        int tA = getTipoFormaFila(atual);
        int tP = getTipoFormaFila(proximo);
        double aA = calcAreaForma(fA, tA);
        double aP = calcAreaForma(fP, tP);
        houveColisao = verificarColisao(atual, proximo);
        if (houveColisao){ 
            if (aP > aA){
                double x, y;
                getXYForma(fA, tA, &x, &y);
                inserirAsteriscoSVG(svg, x, y);
                removerFila(arena);
                switch (tA){
                    case 1:
                        liberarRetangulo(fA);
                        break;
                    case 2:
                        liberarCirculo(fA);
                        break;
                    case 3:
                        liberarLinha(fA);
                        break;
                    case 4:
                        liberarTexto(fA);
                        break;
                }
                inserirFila(chao, fP, tP);
                removerFila(arena);
                printarVerificacao(txt, 1);
                (*areaTotal) += aA;
                areaRound += aA;
                (*esmagadas)++;
            } else{
                setCorBForma(fP, tP, getCorPForma(fA, tA));
                inserirFila(chao, fA, tA);
                removerFila(arena);
                inserirFila(chao, fP, tP);
                removerFila(arena);
                clonarForma(fA, tA, chao);
                printarVerificacao(txt, 2);
                (*clonadas)++;
            }
        } else{
            inserirFila(chao, fA, tA);
            removerFila(arena);
            inserirFila(chao, fP, tP);
            removerFila(arena);
            printarVerificacao(txt, 3);
        }
        atual = getPrimeiroFila(arena);
    }
    if (atual != NULL){
        inserirFila(chao, getFormaFila(atual), getTipoFormaFila(atual));
        removerFila(arena);
    }
    printarAreaEsmagada(txt, areaRound, *areaTotal);
}