#include "trataArquivo.h"
#include <string.h>
#include <assert.h>

#define tam_caminho 250
#define tam_nome_arquivo 100
#define tam_msg 1000

void trataCaminho(char *caminho, int tamanhoMax, char *arg) {
    int tamanhoArg = strlen(arg);
    assert(tamanhoArg < tamanhoMax);
    if (arg[tamanhoArg - 1] == '/') {
        arg[tamanhoArg - 1] = '\0';
    }
    strcpy(caminho, arg);
}

void trataNomeArquivo(char *caminho, int tamanhoMax, char *arg) {
    int tamanhoArg = strlen(arg);
    assert((tamanhoArg + 4) < tamanhoMax);
    sprintf(caminho, "%s.txt", arg);
}

void combinacaoNomeArquivo(char *nomeGeo, char *nomeQry , char *caminhoSaida, int tamanho) {
    char geo[tam_nome_arquivo], qry[tam_nome_arquivo];
    char *caminhoSaidaInteiro[tam_nome_arquivo];
    strcpy(geo, nomeGeo);
    char *extensionGeo = strrchr(geo, '.');
    if (extensionGeo) *extensionGeo = '\0';
    if (nomeQry && strlen(nomeQry) > 0) {
        strcpy(qry, nomeQry);
        char *extensionQry = strrchr(qry, '.');
        if (extensionQry) *extensionQry = '\0';
        snprintf(caminhoSaida, tamanho, "%s-%s", geo, qry);
    } else { 
        snprintf(caminhoSaida, tamanho, "%s", geo);
    }
}