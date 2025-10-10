#ifndef CARREGADOR_H
#define CARREGADOR_H

#include "pilha.h"
#include "fila.h"
#include "disparador.h"
#include <stdio.h>

/*
Módulo responsável por gerenciar o carregamento de formas da pilha para o disparador.
*/

typedef void *carregador;

/// @brief Cria um novo carregador
/// @param id Identificador único do carregador
/// @return Ponteiro para o carregador criado
carregador criarCarregador(int id);

/// @brief Pega o carregador correspondente ao id fornecido
/// @param carregadores Fila com os disparadores que será percorrida
/// @param id Id do carregador que será procurado
/// @return Um ponteiro para o carregador com o id correspondente
carregador getCarregadorPorId(fila carregadores, int id);

/// @brief Pega a pilha associada ao carregador
/// @param c Carregador de onde a pilha será pega
/// @return Ponteiro para a pilha associada ao carregador
pilha getPilhaCarregador(carregador c);

/// @brief Carrega o carregador
/// @param c Carregador a ser carregado
/// @param f Fila de onde as formas irão sair
void carregarCarregador(carregador c, fila f);

/// @brief Libera a memória usada pelo carregador
/// @param c Ponteiro para o carregador
void liberarCarregador(carregador c);

#endif