#ifndef LINHA_H
#define LINHA_H

/*
Módulo responsável por gerenciar a forma linha, incluindo suas operações de set, get e calcular área.
A forma linha tem como atributos um identificador único (id), uma coordenada X1, uma coordenada Y1, uma coordenada X2, uma coordenada Y2 e uma cor
*/

typedef void *linha;

/// @brief Cria uma linha com os atributos identificados
/// @param i Identificador único da linha
/// @param x1 Coordenada X da primeira extremidade da linha
/// @param y1 Coordenada Y da primeira extremidade da linha
/// @param x2 Coordenada X da segunda extremidade da linha
/// @param y2 Coordenada Y da segunda extremidade da linha
/// @param cor Cor da linha
/// @return Um ponteiro para o objeto 'linha' criado
linha criarLinha(int i, double x1, double y1, double x2, double y2, char *cor);

/// @brief Pega o id da linha
/// @param l Ponteiro para a linha que o id será pego
/// @return Um inteiro do id da linha
int getIdLinha(linha l);

/// @brief Pega a coordenada X da primeira extremidade da linha
/// @param l Ponteiro para a linha que a coordenada será pega
/// @return Um double da coordenada X da primeira extremidade da linha
double getX1Linha(linha l);

/// @brief Pega a coordenada Y da primeira extremidade da linha
/// @param l Ponteiro para a linha que a coordenada será pega
/// @return Um double da coordenada Y da primeira extremidade da linha
double getY1Linha(linha l);

/// @brief Pega a coordenada X da segunda extremidade da linha
/// @param l Ponteiro para a linha que a coordenada será pega
/// @return Um double da coordenada X da segunda extremidade da linha
double getX2Linha(linha l);

/// @brief Pega a coordenada Y da segunda extremidade da linha
/// @param l Ponteiro para a linha que a coordenada será pega
/// @return Um double da coordenada Y da segunda extremidade da linha
double getY2Linha(linha l);

/// @brief Pega a cor da linha
/// @param l Ponteiro para a linha que a cor será pega
/// @return Uma string da cor da linha
char* getCorLinha(linha l);

/// @brief Calcula a área da linha
/// @param l Ponteiro para a linha que a área será calculada
/// @return Um double da área da linha
double calcAreaLinha(linha l);

/// @brief Calcula a cor complementar do linha
/// @param cor String com a cor do linha
/// @return Uma string da cor complementar do linha
char* calcCorComplementarLinha(char *cor);

/// @brief Define o id da linha
/// @param l Ponteiro para a linha que o id será pego
/// @param id Id da linha que será definida
void setIdLinha(linha l, int id);

/// @brief Define a coordenada X da primeira extremidade da linha
/// @param l Ponteiro para a linha que a coordenada será definida
/// @param x1 Coordenda X da primeira extremidade da linha que será definida
void setX1Linha(linha l, double x1);

/// @brief Define a coordenada Y da primeira extremidade da linha
/// @param l Ponteiro para a linha que a coordenada será definida
/// @param y1 Coordenda Y da primeira extremidade da linha que será definida
void setY1Linha(linha l, double y1);

/// @brief Define a coordenada X da segunda extremidade da linha
/// @param l Ponteiro para a linha que a coordenada será definida
/// @param x2 Coordenada X da segunda extremidade da linha que será definida
void setX2Linha(linha l, double x2);

/// @brief Define a coordenada Y da segunda extremidade da linha
/// @param l Ponteiro para a linha que a coordenada será definida
/// @param y2 Coordenada Y da segunda extremidade da linha que será definida
void setY2Linha(linha l, double y2);

/*As cor está escrita em hexadecimal de 6 bits mais o "#"*/

/// @brief Define a cor da linha
/// @param l Ponteiro para a linha que a cor será definida
/// @param cor Cor da linha que será definida
void setCorLinha(linha l, char *cor);

/// @brief Libera a memória alocada da linha
/// @param l Ponteiro para a linha que a memória será liberada
void liberarLinha(linha l);

#endif