#ifndef RETANGULO_H
#define RETANGULO_H

/*
Módulo responsável por gerenciar a forma retângulo, incluindo suas operações de set, get e calcular área
*/

typedef void *retangulo;

/// @brief Cria um retângulo com os atributos identificados
/// @param id Identificador unico do retângulo
/// @param x Coordenada x do centro do retângulo
/// @param y Coordenada y do centro do retângulo 
/// @param w Largura do retângulo
/// @param h Altura do retângulo
/// @param corb Cor da borda do retângulo
/// @param corp Cor do preenchimento do retângulo
/// @return Um ponteiro para o objeto 'retangulo' criado
retangulo criarRetangulo(int id, double x, double y, double w, double h, char *corB, char *corP);

/// @brief Pega o id do retângulo
/// @param r Ponteiro para o retângulo que o id será pego
/// @return Um inteiro do id do retângulo
int getIdRetangulo(retangulo r);

/// @brief Pega a coordenada X do centro do retângulo
/// @param r Ponteiro para o retângulo que a coordenada será pega
/// @return Um double da coordenada X do retângulo
double getXRetangulo(retangulo r);

/// @brief Pega a coordenada Y do centro do retângulo
/// @param r Ponteiro para o retângulo que a coordenada será pega
/// @return Um double da coordenada Y do retângulo
double getYRetangulo(retangulo r);

/// @brief Pega a largura do retângulo
/// @param r Ponteiro para o retângulo que a largura será pega
/// @return Um double da largura do retângulo
double getWRetangulo(retangulo r);

/// @brief Pega a altura do retângulo
/// @param r Ponteiro para o retângulo que a altura será pega
/// @return Um double da altura do retângulo
double getHRetangulo(retangulo r);

/// @brief Pega a cor da borda do retângulo
/// @param r Ponteiro para o retângulo que a cor será pega
/// @return Uma string da cor da borda do retângulo
char* getCorBRetangulo(retangulo r);

/// @brief Pega a cor do prrenchimento do retângulo
/// @param r Ponteiro para o retângulo que a cor será pega
/// @return Uma string da cor do preenchimento do retângulo
char* getCorPRetangulo(retangulo r);

/// @brief Calcula a área do retângulo
/// @param r Ponteiro para o retângulo que a área será calculada
/// @return Um double da área do retângulo
double calcAreaRetangulo(double w, double h);

/// @brief Define o id do retângulo
/// @param r Ponteiro para o retângulo que o id será definido
/// @param id Id do retângulo que será definido
void setIdRetangulo (retangulo r, int id);

/// @brief Define o valor da coordenada X do retângulo
/// @param r Ponteiro para o retângulo que a coordenada será definida
/// @param x Coordenada X do retângulo que será definido
void setXRetangulo(retangulo r, double x);

/// @brief Define o valor da coordenda Y do retângulo
/// @param r Ponteiro para o retângulo que a largura será definida
/// @param y Coordenada Y do retângulo que será definido
void setYRetangulo(retangulo r, double y);

/// @brief Define a largura do retângulo
/// @param r Ponteiro para o retângulo que a largura será definida
/// @param w Largura do retângulo que será definido
void setWRetangulo(retangulo r, double w);

/// @brief Define a altura do retângulo
/// @param r Ponteiro para o retângulo que a altura será definida
/// @param h Altura do retângulo que será definido
void setHRetangulo(retangulo r, double h);

/*As cores estarão escritas em hexadecimal de 6 bits*/

/// @brief Define a cor da borda do retângulo
/// @param r Ponteiro para o retângulo que a cor será definida
/// @param corb String da cor de borda do retângulo
void setCorBRetangulo(retangulo r, char *corb);

/// @brief Define a cor do preenchimento do retângulo
/// @param r Ponteiro para o retângulo que a cor será definida
/// @param corp String da cor de preenchimento do retângulo 
void setCorPRetangulo(retangulo r, char *corp);

/// @brief Libera a memória alocada do retângulo
/// @param r Ponteiro para o retângulo que a memória será liberada
void liberarRetangulo(retangulo r);

#endif