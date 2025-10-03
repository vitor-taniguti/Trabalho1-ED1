#ifndef PILHA_H
#define PILHA_H

#include <stdio.h>
#include "texto.h"

/*
Módulo responsável por gerenciar a estrutura de dado pilha, incluindo suas operações de criar, inserir, remover, get e liberar memória
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
void inserirPilha(pilha p, forma f);

/// @brief Remove o elemento no topo da pilha
/// @param p Ponteiro para a pilha onde a forma será removida
void removerPilha(pilha p);

/// @brief Pega o primeiro elemento da pilha
/// @param p Ponteiro para a pilha onde o elemento será pego
/// @return Ponteiro para o primeiro elemento ou NULL se estiver vazia
forma getPrimeiroElementoPilha(pilha p);

/// @brief Percorre pela pilha e aplica uma ação à cada elemento
/// @param p Ponteiro para a pilha a ser percorrida
/// @param tipoPilha Tipo de elemento na pilha (1-Retângulo, 2-Círculo, 3-Linha, 4-Texto)
/// @param sgv Ponteiro para o arquivo SVG onde os elementos serão inseridos
/// @param tipoTexto Tipo do texto a ser usado nos elementos tipo texto
void passarPelaPilha(pilha p, int tipoPilha, arquivo svg, tipoTexto tipoTexto);

/// @brief Seleciona a ação a ser realizada para um elemento da pilha
/// @param f Ponteiro para a forma para ser processada
/// @param tipoPilha Tipo de elemento na pilha (1-Retângulo, 2-Círculo, 3-Linha, 4-Texto)
/// @param sgv Ponteiro para o arquivo SVG onde os elementos serão inseridos
/// @param tipoTexto Tipo do texto a ser usado nos elementos tipo texto
void selecionarAcaoPilha(forma f, int tipoPilha, arquivo svg, tipoTexto tipoTexto);

/// @brief Libera toda memória alocada da pilha e seus elementos
/// @param p Ponteiro para a pilha que será liberada
void liberarPilha(pilha p);

#endif