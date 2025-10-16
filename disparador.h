#ifndef DISPARADOR_H
#define DISPARADOR_H

#include <stdio.h>
#include "carregador.h"

/*
Módulo responsável por gerenciar os disparadores, suas funções get e set e associar carregadores.
*/

typedef void *carregador;
typedef void *disparador;
typedef FILE *arquivo;

/// @brief Cria e inicializa um disparador com os atributos especificados
/// @param id Identificador único do disparador
/// @param x Coordenada X do disparador
/// @param y Coordenada Y do disparador
/// @return Um ponteiro para o disparador criado
disparador criarDisparador(int id, double x, double y);

/// @brief Pega o disparador correspondente ao id fornecido
/// @param disparadores Fila com os disparadores que será percorrida
/// @param id Id do disparador que será procurado
/// @return Um ponteiro para o disparador com o id correspondente
disparador getDisparadorPorId(fila disparadores, int id);

/// @brief Define a coordenada X do disparador
/// @param d Ponteiro para o disparador que a coordenada será definida
/// @param x Coordenada X do disparador
void setXDisparador(disparador d, double x);

/// @brief Define a coordenada X do disparador
/// @param d Ponteiro para o disparador que a coordenada será definida
/// @param y Coordenada X do disparador
void setYDisparador(disparador d, double y);

/// @brief Define a forma e tipo da forma do disparador
/// @param d Ponteiro para o disparador que será definido
/// @param f Forma que será definida
/// @param tipoForma Tipo da forma que será definida
void setTipoEFormaDisparador(disparador d, forma f, int tipoForma);

/// @brief Define os dois carregadores associados ao disparador
/// @param d Ponteiro para o disparador
/// @param c1 Carregador esquerdo que será associado
/// @param c2 Carregador direito que será associado
void setCarregadoresDisparador(disparador d, carregador cE, carregador cD);

/// @brief Pega o Id do disparador
/// @param d Ponteiro para o disparador que o Id será pego
/// @return Um inteiro do Id do disparador
int getIdDisparador(disparador d);

/// @brief Pega a forma do disparador
/// @param d Ponteiro para o disparador que a forma será pega
/// @return Um ponteiro para a forma do disparador
forma getFormaDisparador(disparador d);

/// @brief Pega o tipo da forma do disparador
/// @param d Ponteiro para o disparador que o tipo da forma será pego
/// @return Um inteiro do tipo da forma do disparador
int getTipoFormaDisparador(disparador d);

/// @brief Pega o carregador esquerdo associado a um disparador
/// @param d Ponteiro para o disparador
/// @return Um ponteiro para o carregador esquerdo do disparador
carregador getCarregadorE(disparador d);

/// @brief Pega o carregador direito associado a um disparador
/// @param d Ponteiro para o disparador
/// @return Um ponteiro para o carregador direito do disparador
carregador getCarregadorD(disparador d);

/// @brief Carrega o disparador com um dos carregadores
/// @param d Ponteiro para o disparador
/// @param lado Lado do carregador que carregará o disparador
void carregarDisparador(disparador d, char lado);

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
/// @param arena Fila para onde serão disparadas as formas
void dispararDisparador(disparador d, double dx, double dy, arquivo *txt, fila arena);

#endif