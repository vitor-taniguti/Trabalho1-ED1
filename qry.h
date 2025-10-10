#ifndef QRY_H
#define QRY_H

#include "disparador.h"
#include "carregador.h"
#include "txt.h"
#include "svg.h"
#include <stdio.h>

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

/// @brief Processa uma linha do arquivo e executa os comandos correspondentes
/// @param linha Linha a ser processada
/// @param comando Comando a ser executado
/// @param chao Fila do chão 
/// @param arena Fila da arena
/// @param disparadores Fila onde estão armazenados os disparadores
/// @param carregadores Fila onde estão armazenados os carregadores
/// @param txt Arquivo com extensao .txt que será usado
/// @param svg Aquivo com extensao .svg que será usado
void processarLinhaComandos(char *linha, char *comando, fila chao, fila arena, fila disparadores, fila carregadores, arquivo txt, arquivo svg);

#endif