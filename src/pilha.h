#ifndef PILHA_H
#define PILHA_H

#include <stdio.h>
#include "texto.h"

/*
Módulo responsável por gerenciar a estrutura de dado pilha, incluindo suas operações de criar, inserir, remover, get e liberar memória.
*/

typedef FILE *arquivo;
typedef void *pilha;
typedef void *forma;

/// @brief Cria uma nova pilha vazia
/// @return Ponteiro para a nova pilha criada
pilha criarPilha();

/// @brief Insere um elemento no topo da pilha
/// @param p Ponteiro para a pilha onde a forma será inserida
/// @param f Forma a ser inserida na pilha
/// @param tipoForma Tipo da forma a ser inserida na pilha
void inserirPilha(pilha p, forma f, int tipoForma);

/// @brief Remove o elemento no topo da pilha
/// @param p Ponteiro para a pilha onde a forma será removida
void removerPilha(pilha p);

/// @brief Pega o tipo do primeiro elemento da pilha
/// @param p Ponteiro para a pilha onde o tipo será pego
/// @return Um inteiro do tipo do primeiro elemento da pilha
int getTipoPrimeiroElementoPilha(pilha p);

/// @brief Pega o primeiro elemento da pilha (sem remover)
/// @param p Ponteiro para a pilha onde o elemento será pego
/// @return Ponteiro para o primeiro elemento ou NULL se estiver vazia
forma getPrimeiroElementoPilha(pilha p);

/// @brief Libera toda memória alocada da pilha e seus elementos
/// @param p Ponteiro para a pilha que será liberada
void liberarPilha(pilha p);

#endif