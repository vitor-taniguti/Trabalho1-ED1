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
            printInformacoesRetangulo(txt, getIdRetangulo(f), getXRetangulo(f), getYRetangulo(f), getHRetangulo(f), getWRetangulo(f), getCorBRetangulo(f), getCorPRetangulo(f));
            break;
        case 2:
            printInformacoesCirculo(txt, getIdCirculo(f), getXCirculo(f), getYCirculo(f), getRCirculo(f), getCorBCirculo(f), getCorPCirculo(f));
            break;
        case 3:
            printInformacoesLinha(txt, getIdLinha(f), getX1Linha(f), getY1Linha(f), getX2Linha(f), getY2Linha(f), getCorLinha(f));
            break;
        case 4:
            printInformacoesTexto(txt, getIdTexto(f), getXTexto(f), getYTexto(f), getCorbTexto(f), getCorpTexto(f), getATexto(f), getTxtoTexto(f));
            break;
        default:
            printf("Tipo de forma inválido!\n");
            break;
    }
}

