#include "retangulo.h"
#include "circulo.h"
#include "linha.h"
#include "texto.h"
#include "carregador.h"
#include "disparador.h"
#include "geo.h"
#include "qry.h"
#include "txt.h"
#include "svg.h"
#include "trataArquivo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH_LEN 250
#define FILE_NAME_LEN 100
#define MSG_LEN 1000

typedef FILE* arquivo;


int main(int argc, char *argv[]) {
    char dirEntrada[PATH_LEN] = ".";
    char dirSaida[PATH_LEN] = ".";
    char nomeArquivoGeo[FILE_NAME_LEN] = "";
    char nomeArquivoQry[FILE_NAME_LEN] = "";
    char fullPathGeo[PATH_LEN + FILE_NAME_LEN];
    char fullPathQry[PATH_LEN + FILE_NAME_LEN];
    char arquivoSaidaSvg[PATH_LEN + FILE_NAME_LEN];
    char arquivoSaidaTxt[PATH_LEN + FILE_NAME_LEN];
    char onlyQry[FILE_NAME_LEN] = "";
    int hasGeo = 0, hasSaida = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-e") == 0 && i + 1 < argc) {
            strcpy(dirEntrada, argv[++i]);
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            strcpy(dirSaida, argv[++i]);
            hasSaida = 1;
        } else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            strcpy(nomeArquivoGeo, argv[++i]);
            hasGeo = 1;
        } else if (strcmp(argv[i], "-q") == 0 && i + 1 < argc) {
            strcpy(nomeArquivoQry, argv[++i]);
            char *p = strrchr(argv[i], '/');
            strcpy(onlyQry, p ? p + 1 : argv[i]);
        } else {
            fprintf(stderr, "Parâmetro desconhecido ou inválido: %s\n", argv[i]);
            return EXIT_FAILURE;
        }
    }

    if (!hasGeo || !hasSaida) {
        fprintf(stderr, "Erro: parâmetros obrigatórios -f (geo) e -o (saida) não fornecidos.\n");
        return EXIT_FAILURE;
    }

    snprintf(fullPathGeo, sizeof(fullPathGeo), "%s/%s", dirEntrada, nomeArquivoGeo);

    if (strlen(nomeArquivoQry) > 0){
        snprintf(fullPathQry, sizeof(fullPathQry), "%s/%s", dirEntrada, nomeArquivoQry);
    }
    snprintf(arquivoSaidaSvg, sizeof(arquivoSaidaSvg), "%s/%s.svg", dirSaida, nomeArquivoGeo);
    snprintf(arquivoSaidaTxt, sizeof(arquivoSaidaTxt), "%s/%s.txt", dirSaida, onlyQry);

    arquivo geo = NULL;
    arquivo qry = NULL;
    arquivo txt = NULL;
    arquivo svg = NULL;

    abrirArquivoGeo(&geo, fullPathGeo);
    if (strlen(nomeArquivoQry) > 0){
        abrirArquivoQry(&qry, fullPathQry);
    }
    abrirArquivoTxt(&txt, arquivoSaidaTxt);
    abrirArquivoSvg(&svg, arquivoSaidaSvg);

    fila chao = criarFila();
    fila arena = criarFila();
    fila disparadores = criarFila();
    fila carregadores = criarFila();

    lerArquivoGeo(geo, chao);
    lerArquivoQry(qry, txt, svg, chao, arena, disparadores, carregadores);

    if (geo) fclose(geo);
    if (qry) fclose(qry);
    if (txt) fclose(txt);
    if (svg) fclose(svg);

    return 0;
}