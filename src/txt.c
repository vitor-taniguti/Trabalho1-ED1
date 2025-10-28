#include "txt.h"

void abrirArquivoTxt(arquivo *saida, char *caminhoTxt){
    *saida = fopen(caminhoTxt, "w");
    if (*saida == NULL){
        printf("Falha na alocação de memória!");
        exit(1);
    }
}

void printarDadosForma(arquivo txt, forma f, int tipoForma){
    switch (tipoForma){
        case 1:
            fprintf(txt, "Retângulo - Id: %d, X: %lf, Y: %lf, W: %lf, H: %lf, CorB: %s, CorP: %s\n", getIdRetangulo(f), getXRetangulo(f), getYRetangulo(f), getWRetangulo(f), getHRetangulo(f), getCorBRetangulo(f), getCorPRetangulo(f));
            break;
        case 2:
            fprintf(txt, "Círculo - Id: %d, X: %lf, Y: %lf, R: %lf, CorB: %s, CorP: %s\n", getIdCirculo(f), getXCirculo(f), getYCirculo(f), getRCirculo(f), getCorBCirculo(f), getCorPCirculo(f));
            break;
        case 3:
            fprintf(txt, "Linha - Id: %d, X1: %lf, Y1: %lf, X2: %lf, Y2: %lf, Cor: %s\n", getIdLinha(f), getX1Linha(f), getY1Linha(f), getX2Linha(f), getY2Linha(f), getCorLinha(f));
            break;
        case 4:
            fprintf(txt, "Texto - Id: %d, X: %lf, Y: %lf, CorB: %s, CorP: %s, Âncora: %c, Conteúdo: %s\n", getIdTexto(f), getXtTexto(f), getYtTexto(f), getCorBTexto(f), getCorPTexto(f), getATexto(f), getTxtoTexto(f));
            break;
        default:
            printf("Tipo de forma inválido!\n");
            break;
    }
}

void printarPosicaoForma(arquivo txt, forma f, int tipoForma){
    fprintf(txt, "Posição final - ");
    switch (tipoForma){
        case 1:
            fprintf(txt, "X: %lf, Y: %lf\n", getXRetangulo(f), getYRetangulo(f));
            break;
        case 2:
            fprintf(txt, "X: %lf, Y: %lf\n", getXCirculo(f), getYCirculo(f));
            break;
        case 3:
            fprintf(txt, "X1: %lf, Y1: %lf, X2: %lf, Y2: %lf\n", getX1Linha(f), getY1Linha(f), getX2Linha(f), getY2Linha(f));
            break;
        case 4:
            fprintf(txt, "X: %lf, Y: %lf\n", getXtTexto(f), getYtTexto(f));
            break;
        default:
            printf("Tipo de forma inválido!\n");
            break;
    }
}

void printarAreaEsmagada(arquivo txt, double areaRound, double areaTotal){
    fprintf(txt, "\nÁrea esmagada no round - %lf\nÁrea total esmagada - %lf\n\n", areaRound, areaTotal);
}

void printarVerificacao(arquivo txt, int caso){
    fprintf(txt, "Resultado da verificação - ");
    switch (caso){
        case 1:
            fprintf(txt, "Houve sobreposição e a área do i+1 é maior do que a área do i\n");
            break;
        case 2:
            fprintf(txt, "Houve sobreposição e a área do i+1 é menor do que a área do i\n");
            break;
        case 3:
            fprintf(txt, "Não houve colisão\n");
            break;
    }
}

void printarResultados(arquivo txt, double areaTotal, int instrucoes, int disparos, int esmagadas, int clonadas){
    fprintf(txt, "Resultados finais:\n\nPontuação final - %lf\nInstruções executadas - %d\nNúmero de disparos - %d\nFormas esmagadas - %d\nFormas clonadas - %d\n", areaTotal, instrucoes, disparos, esmagadas, clonadas);
}