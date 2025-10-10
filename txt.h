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

/// @brief Imprime um comando no arquivo de texto
/// @param txt Ponteiro duplo para o arquivo de saída
/// @param comando String contendo o comando a ser registrado
void printarLinhaComando(arquivo *txt, char *comando);

/// @brief Imprime os dados das formas carregadas no carregador no arquivo de texto
/// @param txt Ponteiro duplo para o arquivo de saída
/// @param f Ponteiro para a forma carregada
/// @param tipoForma Tipo da forma que os dados serão printados (1-Retângulo, 2-Círculo, 3-Linha, 4-Texto)
void printarDadosForma(arquivo *txt, forma f, int tipoForma);

/// @brief Imprime os dados da forma que está no ponto de disparo
/// @param txt Ponteiro duplo para o arquivo de saída
/// @param f Ponteiro para a fila do disparador
void printarDadosFormaPontoDisparo(arquivo *txt, fila f);

/// @brief Imprime os dados do disparo efetuado
/// @param txt Ponteiro duplo para o arquivo de saída
void printarDadosDisparo(arquivo *txt);

#endif