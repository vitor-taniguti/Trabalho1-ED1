#ifndef TEXTO_H
#define TEXTO_H

/*
Módulo responsável por gerenciar a forma texto, incluindo suas operações de set, get e calcular área
*/

typedef void *texto;
typedef void *tipoTexto;

/// @brief Cria um tipo de texto
/// @param family O dont-family do texto
/// @param weight O font-weight do texto
/// @param size O font=size do texto
/// @return Um ponteiro para o objeto 'tipoTexto' criado
tipoTexto criarTipoTexto(char *family, char *weight, char *size);

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
/// @return Um double da coordenada X da âncora do texto
double getXtTexto(texto t);

/// @brief Pega a coordenada Y do texto
/// @param t Ponteiro para o texto que a coordenada será pega
/// @return Um double da coordenada Y da âncora do texto
double getYtTexto(texto t);

/// @brief Pega a coordenada X1 do texto
/// @param t Ponteiro para o texto que a coordenada será pega
/// @return Um double da coordenada X1 do texto
double getX1Texto(texto t);

/// @brief Pega a coordenada X2 do texto
/// @param t Ponteiro para o texto que a coordenada será pega
/// @return Um double da coordenada X2 do texto
double getX2Texto(texto t);

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

/// @brief Pega a font-family do texto
/// @param tt Ponteiro para o tipo de texto que a font-family será pega
/// @return Uma string com o font-family do texto
char* getFamily(tipoTexto tt);

/// @brief Pega a font-weight do texto
/// @param tt Ponteiro para o tipo de texto que a font-weight será pega
/// @return Uma string com o font-weight do texto
char* getWeight(tipoTexto tt);

/// @brief Pega a font-size do texto
/// @param tt Ponteiro para o tipo de texto que a font-size será pega
/// @return Uma string com o font-size do texto
char* getSize(tipoTexto tt);

/// @brief Calcula a área do texto
/// @param t Ponteiro para o texto que a área será calculada
/// @return Um double da área do texto
double calcAreaTexto(texto t);

/// @brief Calcula os pontos de começo e de fim do texto para a colisão
/// @param t Ponteiro para o texto que as coordenas X1 e X2 serão definidas
/// @param a Âncora do texto
void setX1X2Texto(texto t, char a);

/// @brief Define o id do texto
/// @param t Ponteiro para o texto que o id será definido
/// @param id Id do texto que será definido 
void setIdTexto(texto t, int id);

/// @brief Define a coordenada X do texto
/// @param t Ponteiro para o texto que a coordenada será definida
/// @param x Coordenada X do texto que será definido
void setXtTexto(texto t, double x);

/// @brief Define a coordenada Y do texto
/// @param t Ponteiro para o texto que a coordenada será definida
/// @param y Coordenada Y do texto que será definido
void setYtTexto(texto t, double y);

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

/// @brief Define a font-family do texto
/// @param tt Ponteiro para o tipo de texto que o font-family será definido
/// @param family A nova font-family
void setFamily(tipoTexto tt, char *family);

/// @brief Define a font-weight do texto
/// @param tt Ponteiro para o tipo de texto que o font-weight será definido
/// @param weight A nova font-weight
void setWeight(tipoTexto tt, char *weight);

/// @brief Define a font-size do texto
/// @param tt Ponteiro para o tipo de texto que o font-size será definido
/// @param size A nova font-size
void setSize(tipoTexto tt, char *size);

/// @brief Libera a memória do tipo do texto
/// @param t Ponteiro para o tipo do texto que a momória será liberada
void liberarTipoTexto(tipoTexto t);

/// @brief Libera a memória do texto
/// @param t Ponteiro para o texto que a memória será liberada
void liberarTexto(texto t);

#endif