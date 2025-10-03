#ifndef SVG_H
#define SVG_H

#include <stdio.h>
#include <stdlib.h>
#include "retangulo.h"
#include "circulo.h"
#include "linha.h"
#include "texto.h"

typedef FILE *arquivo;
typedef void *forma;

/// @brief Cria o arquivo de saída SVG (.svg)
/// @param saida Ponteiro duplo para o endereço do arquivo
/// @param caminhoSaida Ponteiro com o nome do arquivo de saída criado
void abrirArquivoSaida(arquivo *saida, char *caminhoSaida);

/// @brief Adiciona a tag inicial do arquivo SVG
/// @param saida Ponteiro para o arquivo de saída
void inicializarSVG(arquivo saida);

/// @brief Adiciona a tag rect do arquivo SVG
/// @param saida Ponteiro para o arquivo de saída
/// @param r Forma do retângulo
void inserirRetanguloSVG(arquivo saida, retangulo r);

/// @brief Adciona a tag circle do arquivo SVG
/// @param saida Ponteiro para o arquivo de saída
/// @param c Forma do círculo
void inserirCirculoSVG(arquivo saida, circulo c);

/// @brief Adiciona a tag line do arquivo SVG
/// @param saida Ponteiro para o arquivo de saída
/// @param l Forma da linha
void inserirLinhaSVG(arquivo saida, linha l);

/// @brief Adiciona a tag text do arquivo SVG
/// @param saida Ponteiro para o arquivo de saída
/// @param txt Forma do texto
/// @param tt Atributos estéticos do texto
void inserirTextoSVG(arquivo saida, texto txt, tipoTexto tt);

/// @brief Adiciona a tag final do arquivo SVG
/// @param saida Ponteiro para o arquivo de saída
void fecharSVG(arquivo saida);

#endif