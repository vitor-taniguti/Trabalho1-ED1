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

#define PATH_LEN 512
#define FILE_NAME_LEN 256

typedef FILE* arquivo;

int main(int argc, char *argv[]) {
    char dirEntrada[PATH_LEN] = ".";
    char dirSaida[PATH_LEN] = ".";
    char nomeArquivoGeo[FILE_NAME_LEN] = "";
    char nomeArquivoQry[FILE_NAME_LEN] = "";
    int hasGeo = 0, hasSaida = 0, hasQry = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-e") == 0 && i + 1 < argc) {
            trataCaminho(dirEntrada, PATH_LEN, argv[++i]);
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            trataCaminho(dirSaida, PATH_LEN, argv[++i]);
            hasSaida = 1;
        } else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            strcpy(nomeArquivoGeo, argv[++i]);
            hasGeo = 1;
        } else if (strcmp(argv[i], "-q") == 0 && i + 1 < argc) {
            strcpy(nomeArquivoQry, argv[++i]);
            hasQry = 1;
        } else {
            fprintf(stderr, "Parâmetro desconhecido ou inválido: %s\n", argv[i]);
            return EXIT_FAILURE;
        }
    }

    if (!hasGeo || !hasSaida) {
        fprintf(stderr, "Erro: parâmetros obrigatórios -f (geo) e -o (saida) não fornecidos.\n");
        return EXIT_FAILURE;
    }

    char fullPathGeo[PATH_LEN + FILE_NAME_LEN];
    snprintf(fullPathGeo, sizeof(fullPathGeo), "%s/%s", dirEntrada, nomeArquivoGeo);

    char fullPathQry[PATH_LEN + FILE_NAME_LEN];
    if (hasQry) {
        snprintf(fullPathQry, sizeof(fullPathQry), "%s/%s", dirEntrada, nomeArquivoQry);
    }

    char baseNomeGeo[FILE_NAME_LEN];
    char baseNomeCombinado[FILE_NAME_LEN];
    
    combinacaoNomeArquivo(nomeArquivoGeo, NULL, baseNomeGeo, sizeof(baseNomeGeo));

    char arquivoSaidaSvgGeo[PATH_LEN + FILE_NAME_LEN];
    snprintf(arquivoSaidaSvgGeo, sizeof(arquivoSaidaSvgGeo), "%s/%s.svg", dirSaida, baseNomeGeo);

    char arquivoSaidaSvgQry[PATH_LEN + FILE_NAME_LEN];
    char arquivoSaidaTxt[PATH_LEN + FILE_NAME_LEN];

    if (hasQry) {
        combinacaoNomeArquivo(nomeArquivoGeo, nomeArquivoQry, baseNomeCombinado, sizeof(baseNomeCombinado));
        snprintf(arquivoSaidaSvgQry, sizeof(arquivoSaidaSvgQry), "%s/%s.svg", dirSaida, baseNomeCombinado);
        snprintf(arquivoSaidaTxt, sizeof(arquivoSaidaTxt), "%s/%s.txt", dirSaida, baseNomeCombinado);
    }

    arquivo geo = NULL;
    arquivo qry = NULL;
    arquivo txt = NULL;
    arquivo svgGeo = NULL;
    arquivo svgQry = NULL;

    abrirArquivoGeo(&geo, fullPathGeo);
    if (hasQry) {
        abrirArquivoQry(&qry, fullPathQry);
        abrirArquivoTxt(&txt, arquivoSaidaTxt);
        abrirArquivoSvg(&svgQry, arquivoSaidaSvgQry);
        inicializarSVG(svgQry);
    }
    abrirArquivoSvg(&svgGeo, arquivoSaidaSvgGeo);
    inicializarSVG(svgGeo);

    fila chao = criarFila();
    fila arena = criarFila();
    fila disparadores = criarFila();
    fila carregadores = criarFila();

    tipoTexto tt = criarTipoTexto("Arial, sans-serif", "normal", "12px");

    lerArquivoGeo(geo, chao, tt);

    passarPelaFila(chao, svgGeo, tt);
    fecharSVG(svgGeo);

    if (hasQry) {
        lerArquivoQry(qry, txt, svgQry, chao, arena, disparadores, carregadores);
        passarPelaFila(chao, svgQry, tt);
        fecharSVG(svgQry);
    }

    liberarFila(chao);
    liberarFila(arena);
    liberarFila(disparadores);
    liberarFila(carregadores);
    liberarTipoTexto(tt);

    if (geo) fclose(geo);
    if (qry) fclose(qry);
    if (txt) fclose(txt);
    if (svgGeo) fclose(svgGeo);
    if (svgQry) fclose(svgQry);

    return 0;
}