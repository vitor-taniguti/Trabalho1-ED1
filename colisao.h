#ifndef COLISAO_H
#define COLISAO_H

#include "fila.h"

/// @brief Verifica se as formas da arenas foram esmagadas
/// @param atual Elemento atual sendo processado
/// @param proximo Proximo elemento do atual sendo processado
/// @param areaRound Área esmagada no round
/// @param areaTotal Área esmagada total (no jogo inteiro)
/// @return Um inteiro com o resultado da colisão (1 para verdadeiro, 0 para falso)
int verificarColisao(iterador atual, iterador proximo, double *areaRound, double *areaTotal);

#endif