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
typedef void *iterador;

/// @brief Cria uma nova fila vazia
/// @return Ponteiro para a nova fila criada
fila criarFila();

/// @brief Retorna o tipo da primeira forma da fila (1-Retângulo, 2-Círculo, 3-Linha, 4-Texto)
/// @param f Ponteiro para a fila
/// @return Tipo da primeira forma da fila
int getTipoPrimeiroElementoFila(fila f);

/// @brief Insere um elemento no final da fila
/// @param f Ponteiro para a fila onde a forma será inserida
/// @param forma Forma a ser inserida na fila
/// @param tipoForma Tipo da forma a ser inserida na fila (1-Retângulo, 2-Círculo, 3-Linha, 4-Texto)
void inserirFila(fila f, forma forma, int tipoForma);

/// @brief Remove o primeiro elemento da fila
/// @param f Ponteiro para a fila onde a forma será removida
void removerFila(fila f);

/// @brief Pega o a forma do primeiro elemento da fila (sem remover)
/// @param f Ponteiro para a fila onde o elemento será pego
/// @return Ponteiro para a forma do primeiro elemento ou NULL se estiver vazia
forma getPrimeiroElementoFila(fila f);

/// @brief Pega o priemeiro elemento da fila (sem remover)
/// @param f Ponteiro para a fila onde o elemento será pego
/// @return Ponteiro para o primeiro elemento ou NULL se estiver vazia
iterador getPrimeiroFila(fila f);

/// @brief  Pega o proximo elemento da fila (sem remover)
/// @param i Elemento que o próximo elemento será pego
iterador getProximoFila(iterador i);

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