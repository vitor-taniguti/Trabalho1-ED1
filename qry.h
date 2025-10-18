#ifndef QRY_H
#define QRY_H

#include "disparador.h"
#include "carregador.h"
#include "txt.h"
#include "svg.h"
#include <stdio.h>

/*
Módulo responsável por ler o arquivo qry e executar os comandos correspondentes
*/

/// @brief Abre o arquivo para leitura
/// @param qry Ponteiro para o arquivo que será aberto
/// @param caminhoQry Caminho para o arquivo que será aberto
void abrirArquivoQry(arquivo *qry, char *caminhoQry);

/// @brief Lê e processa as linhas de um arquivo de entrada
/// @param qry Ponteiro para o arquivo de entrada
/// @param chao Fila do chão 
/// @param arena Fila da arena
/// @param txt Arquivo com extensao .txt que será usado
/// @param svg Aquivo com extensao .svg que será usado
/// @param disparadores Fila onde estão armazenados os disparadores
/// @param carregadores Fila onde estão armazenados os carregadores
void lerArquivoQry(arquivo qry, arquivo txt, arquivo svg, fila chao, fila arena, fila disparadores, fila carregadores);

#endif