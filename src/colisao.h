#ifndef COLISAO_H
#define COLISAO_H

/*
Módulo responsável por verificar a colisão entre formas adjacentes na fila da arena.
*/

#include "fila.h"

/// @brief Verifica se as formas da arenas foram esmagadas
/// @param atual Elemento atual sendo processado
/// @param proximo Proximo elemento do atual sendo processado
/// @return Um inteiro com o resultado da colisão (1 para verdadeiro, 0 para falso)
int verificarColisao(iterador atual, iterador proximo);

#endif