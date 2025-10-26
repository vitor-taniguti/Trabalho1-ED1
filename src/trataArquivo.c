#include "trataArquivo.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>

#define tam_caminho 250
#define tam_nome_arquivo 100
#define tam_msg 1000

void trataCaminho(char *caminho, int tamanhoMax, char *arg) {
    int tamanhoArg = strlen(arg);
    assert(tamanhoArg < tamanhoMax);
    strcpy(caminho, arg);
    if (tamanhoArg > 0 && caminho[tamanhoArg - 1] == '/') {
        caminho[tamanhoArg - 1] = '\0';
    }
}

void trataNomeArquivo(char *caminho, int tamanhoMax, char *arg) {
    snprintf(caminho, tamanhoMax, "%s.txt", arg);
}

void combinacaoNomeArquivo(char *nomeGeo, char *nomeQry , char *caminhoSaida, int tamanho) {
    char geo[tam_nome_arquivo], qry[tam_nome_arquivo];
    const char *pGeo = strrchr(nomeGeo, '/');
    pGeo = pGeo ? pGeo + 1 : nomeGeo;
    strcpy(geo, pGeo);
    char *extensionGeo = strrchr(geo, '.');
    if (extensionGeo) *extensionGeo = '\0';
    if (nomeQry && strlen(nomeQry) > 0) {
        const char *pQry = strrchr(nomeQry, '/');
        pQry = pQry ? pQry + 1 : nomeQry;
        strcpy(qry, pQry);
        char *extensionQry = strrchr(qry, '.');
        if (extensionQry) *extensionQry = '\0';
        snprintf(caminhoSaida, tamanho, "%s-%s", geo, qry);
    } else { 
        snprintf(caminhoSaida, tamanho, "%s", geo);
    }
}