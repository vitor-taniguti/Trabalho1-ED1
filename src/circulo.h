#ifndef CIRCULO_H
#define CIRCULO_H

/*
Módulo responsável por gerenciar a forma círculo, incluindo suas operações de set, get e calcular área.
A forma círculo tem como atributos um identificador único (id), uma coordenada X, uma coordenada Y, um raio, uma cor de borda e uma cor de preenchimento.
*/

typedef void *circulo;

/// @brief Cria um circulo com os atributos identificados
/// @param i Identificador unico do círculo
/// @param x Coordenada x do centro do círculo
/// @param y Coordenada y do centro do círculo 
/// @param r Raio do círculo
/// @param corb Cor da borda do círculo
/// @param corp Cor do preenchimento do círculo
/// @return Um ponteiro para o objeto 'circulo' criado
circulo criarCirculo(int i, double x, double y, double r, char *corb, char *corp);

/// @brief Pega o id do círculo
/// @param c Ponteiro para o círculo que o id será pego
/// @return Um inteiro do id do círculo
int getIdCirculo(circulo c);

/// @brief Pega a coordenada X do centro do círculo
/// @param c Ponteiro para o círculo que a coordenada será pega
/// @return Um double da coordenada X do círculo
double getXCirculo(circulo c);

/// @brief Pega a coordenada Y do centro do círculo
/// @param c Ponteiro para o círculo que a coordenada será pega
/// @return Um double da coordenada Y do círculo
double getYCirculo(circulo c);

/// @brief Pega o raio do círculo
/// @param c Ponteiro para o círculo que o raio será pego
/// @return Um double do rao do círculo
double getRCirculo(circulo c);

/// @brief Pega a cor da borda do círculo
/// @param c Ponteiro para o círculo que a cor será pega
/// @return Uma string da cor da borda do círculo
char* getCorBCirculo(circulo c);

/// @brief Pega a cor do prrenchimento do círculo
/// @param c Ponteiro para o círculo que a cor será pega
/// @return Uma string da cor do preenchimento do círculo
char* getCorPCirculo(circulo c);

/// @brief Calcula a área do círculo com raio r
/// @param c Ponteiro para o círculo que a área será calculada
/// @return Um double da área do círculo
double calcAreaCirculo(circulo c);

/// @brief Define o id do circulo
/// @param c Ponteiro para o círculo que o id será definido
/// @param id Id do círculo que será definido
void setIdCirculo (circulo c, int id);

/// @brief Define o valor da coordenada X do círculo
/// @param c Ponteiro para o círculo que a coordenada será definida
/// @param x Coordenada X do círculo que será definido
void setXCirculo(circulo c, double x);

/// @brief Define o valor da coordenada Y do círculo
/// @param c Ponteiro para o círculo que a coordenada será definida
/// @param y Coordenada Y do círculo que será definido
void setYCirculo(circulo c, double y);

/// @brief Define o valor do raio do círculo
/// @param c Ponteiro para o círculo que o raio será definido
/// @param r Raio do círculo que será definido
void setRCirculo(circulo c, double r);

/*As cores estarão escritas em hexadecimal de 6 bits mais o "#"*/

/// @brief Define a cor da borda do círculo
/// @param c Ponteiro para o círculo que a cor será definida
/// @param corb Cor de borda do círculo que será definido
void setCorBCirculo(circulo c, char *corb);

/// @brief Define a cor do preenchimento do círculo
/// @param c Ponteiro para o círculo que a cor será definida
/// @param corp Cor de preenchimento do círculo que será definido
void setCorPCirculo(circulo c, char *corp);

/// @brief Libera a memória alocada do círculo
/// @param c Ponteiro para o círculo que a memória será liberada
void liberarCirculo(circulo c);

#endif