#ifndef GEO_H
#define GEO_H

#include <stdio.h>
#include "disparador.h"

typedef FILE* arquivo;
typedef void* fila;

/// @brief Abre o arquivo para leitura
/// @param geo Ponteiro para o arquivo que será aberto
/// @param caminhoGeo Caminho para o arquivo que será aberto
void abrirArquivo(arquivo *geo, char *caminhoGeo);

/// @brief Lê e processa as linhas de um arquivop de entrada
/// @param geo Ponteiro para o arquivo de entrada
/// @param d Ponteiro para o disparador 
/// @param tt Estilo do texto
void lerArquivo(arquivo geo, disparador d, tipoTexto tt);

/// @brief Processa uma linha do arquivo e cria objetods com base no tipo especificado
/// @param linha Linha que será processada
/// @param tipoForma Tipo de forma representado pela linha
/// @param f Fila que as formas serão inseridas
/// @param tt Estilo do texto
void processarLinhaFormas(char *linha, char *tipoForma, fila f, tipoTexto tt);

#endif