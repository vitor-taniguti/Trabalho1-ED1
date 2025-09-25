#ifndef TEXTO_H
#define TEXTO_H

/*
Módulo responsável por gerenciar a forma texto, incluindo suas operações de set, get e calcular área
*/

typedef void *texto;

/// @brief Cria um texto com os atributos identificados
/// @param i Identificador único da linha
/// @param x Coordenada x do texto
/// @param y Coordenada y do texto
/// @param corb String da cor de borda do texto
/// @param corp String da cor de preenchimento do texto
/// @param a Âncora do triângulo
/// @param txto String com o conteúdo do texto
/// @return Um ponteiro para objeto 'texto' criado
texto criarTexto(int i, double x, double y, char *corb, char *corp, char a, char *txto);

/// @brief Pega o id do texto
/// @param t Ponteiro para o texto que o id será pego
/// @return Um inteiro do id do texto
int getIdTexto(texto t);

/// @brief Pega a coordenada X do texto
/// @param t Ponteiro para o texto que a coordenada será pega
/// @return Um double da coordenada X do texto
double getXTexto(texto t);

/// @brief Pega a coordenada Y do texto
/// @param t Ponteiro para o texto que a coordenada será pega
/// @return Um double da coordenada Y do texto
double getYTexto(texto t);

/// @brief Pega a cor de borda do texto
/// @param t Ponteiro para o texto que a cor será pega
/// @return Uma string da cor de borda do texto
char* getCorBTexto(texto t);

/// @brief Pega a cor de preenchimento do texto
/// @param t Ponteiro para o texto que a cor será pega
/// @return Uma string da cor de preenchimento do texto
char* getCorPTexto(texto t);

/// @brief Pega a âncora do texto
/// @param t Ponteiro para o texto que a âncora será pega
/// @return Um caractere da âncora do texto
char getATexto(texto t);

/// @brief Pega o conteúdo do texto
/// @param t Ponteiro para o texto que o conteúdo será pego
/// @return Uma string do conteúdo do texto
char* getTxtoTexto(texto t);

/// @brief Define o id do texto
/// @param t Ponteiro para o texto que o id será definido
/// @param id Id do texto que será definido 
void setIdTexto(texto t, int id);

/// @brief Define a coordenada X do texto
/// @param t Ponteiro para o texto que a coordenada será definida
/// @param x Coordenada X do texto que será definido
void setXTexto(texto t, double x);

/// @brief Define a coordenada Y do texto
/// @param t Ponteiro para o texto que a coordenada será definida
/// @param y Coordenada Y do texto que será definido
void setYTexto(texto t, double y);

/*As cores estarão escritas em hexadecimal de 6 bits*/

/// @brief Define a cor de borda do texto
/// @param t Ponteiro para o texto que a cor será definida
/// @param corb Cor de borda do texto que será definido
void setCorBTexto(texto t, char *corb);

/// @brief Define a cor de preenchimento do texto
/// @param t Ponteiro para o texto que a cor será definida
/// @param corb Cor de preenchimento do texto que será definido
void setCorPTexto(texto t, char *corp);

/// @brief Define a âncora do texto
/// @param t Ponteiro para o texto que a âncora será definida
/// @param a Âncora do texto que será definido
void setATexto(texto t, char a);

/// @brief Define o conteúdo do texto
/// @param t Ponteiro para o texto que o conteúdo será definido
/// @param txto Conteúdo do texto que será definido
void setTxtoTexto(texto t, char *txto);

#endif