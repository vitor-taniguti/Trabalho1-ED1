#ifndef TXT_H
#define TXT_H

#include <stdio.h>
#include <stdlib.h>
#include "retangulo.h"
#include "circulo.h"
#include "linha.h"
#include "texto.h"
#include "fila.h"

typedef FILE* arquivo;
typedef void* Forma;

/// @brief Abre um arquivo de texto para gravação
/// @param txt Ponteiri duplo para o endereço do arquivo
/// @param caminhoTxt Ponteiro para o caminho onde será salvo o arquivo de texto
void abrirArquivoTxt(arquivo *txt, char *caminhoTxt);

/// @brief Imprime os dados da forma
/// @param txt Ponteiro para o arquivo de saída
/// @param f Ponteiro para a forma carregada
/// @param tipoForma Tipo da forma que os dados serão printados (1-Retângulo, 2-Círculo, 3-Linha, 4-Texto)
void printarDadosForma(arquivo txt, forma f, int tipoForma);

/// @brief Imprime a posição da forma
/// @param txt Ponteiro para o arquivo de saída
/// @param f Ponteiro para a forma carregada
/// @param tipoForma Tipo da forma que os dados serão printados (1-Retângulo, 2-Círculo, 3-Linha, 4-Texto)
void printarPosicaoForma(arquivo txt, forma f, int tipoForma);

/// @brief Imprime a área esmagada no disparo
/// @param txt Ponteiro para o arquivo de saída
/// @param areaRound Área esmagada no round
/// @param areaTotal Área esmagada total (no jogo inteiro)
void printarAreaEsmagada(arquivo txt, double areaRound, double areaTotal);

/// @brief Imprime o resultado da verificação se a área foi esmagada
/// @param txt Ponteiro pra o arquivo de saída
/// @param caso Caso da verificação
void printarVerificacao(arquivo txt, int caso);

/// @brief Imprime os resultados finais do jogo
/// @param txt Ponteiro para o arquivo de saída
/// @param areaTotal Área total esmagada 
/// @param instrucoes Número de instruções feitas
/// @param disparos Número de disparos feitos
/// @param esmagadas Número de formas esmagadas
/// @param clonadas Número de formas clonadas
void printarResultados(arquivo txt, double areaTotal, int instrucoes, int disparos, int esmagadas, int clonadas);

#endif