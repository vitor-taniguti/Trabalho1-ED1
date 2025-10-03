#ifndef FILA_H
#define FILA_H

#include <stdio.h>
#include "texto.h"

/*
Módulo responsável por gerenciar a estrutura de dado fila, incluindo suas operações de criar, inserir, remover, get e liberar memória
*/

typedef FILE *arquivo;
typedef void *fila;
typedef void *forma;

/// @brief Cria uma nova fila vazia
/// @return Ponteiro para a nova fila criada
fila criarFila();

/// @brief Insere um elemento no final da fila
/// @param f Ponteiro para a fila onde a forma será inserida
/// @param forma Forma a ser inserida na fila
void inserirFila(fila f, forma forma);

/// @brief Remove o primeiro elemento da fila
/// @param f Ponteiro para a fila onde a forma será removida
void removerFila(fila f);

/// @brief Pega o primeiro elemento da fila (sem remover)
/// @param f Ponteiro para a fila onde o elemento será pego
/// @return Ponteiro para o primeiro elemento ou NULL se estiver vazia
forma getPrimeiroElementoFila(fila f);

/// @brief Percorre pela fila e aplica uma ação a cada elemento
/// @param f Ponteiro para a fila a ser percorrida
/// @param tipoFila Tipo de elemento na fila (1-Retângulo, 2-Círculo, 3-Linha, 4-Texto)
/// @param svg Ponteiro para o arquivo SVG onde os elementos serão inseridos
/// @param tipoTexto Tipo do texto a ser usado nos elementos tipo texto
void passarPelaFila(fila f, int tipoFila, arquivo svg, tipoTexto tipoTexto);

/// @brief Seleciona a ação a ser realizada para um elemento da fila
/// @param forma Ponteiro para a forma a ser processada
/// @param tipoFila Tipo de elemento na fila (1-Retângulo, 2-Círculo, 3-Linha, 4-Texto)
/// @param svg Ponteiro para o arquivo SVG onde os elementos serão inseridos
/// @param tipoTexto Tipo do texto a ser usado nos elementos tipo texto
void selecionarAcaoFila(forma forma, int tipoFila, arquivo svg, tipoTexto tipoTexto);

/// @brief Libera toda memória alocada da fila e seus elementos
/// @param f Ponteiro para a fila que será liberada
void liberarFila(fila f);

#endif