#ifndef DISPARADOR_H
#define DISPARADOR_H

#include <stdio.h>
#include "fila.h"

typedef void *disparador;
typedef FILE *arquivo;

/// @brief Cria e inicializa um disparador com os atributos especificados
/// @param f Ponteiro para a fila de elementos associada ao disparador
/// @param x Coordenada X do disparador
/// @param y Coordenada Y do disparador
/// @return Um ponteiro para o disparador criado
disparador criarDisparador(fila f, double x, double y, int id);

/// @brief Pega a fila de elementos associada ao disparador
/// @param d Ponteiro para o disparador que a fila será pega
/// @return Um ponteiro para a fila associada ao disparador
fila getFilaDisparador(disparador d);

/// @brief Pega a coordenada X do disparador
/// @param d Ponteiro para o disparador que a coordenada será pega
/// @return Um double da coordenada X do disparador
double getXDisparador(disparador d);

/// @brief Pega a coordenada Y do disparador
/// @param d Ponteiro para o disparador que a coordenada será pega
/// @return Um double da coordenada Y do disparador
double getYDisparador(disparador d);

/// @brief Dispara uma forma com as distancias especificadas
/// @param d Ponteiro para o disparador que será disparado
/// @param dx Deslocamento X da forma disparada em relação ao disparador
/// @param dy Deslocamento Y da forma disparada em relação ao disparador 
/// @param txt Ponteiro para o arquivo onde as informações serão registradas
void dispararDisparador(disparador d, double dx, double dy, arquivo *txt);

#endif