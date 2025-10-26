#ifndef TRATAARQUIVO_H
#define TRATAARQUIVO_H

/// @brief Manipula o caminho do arquivo fornecido
/// @param caminho O caminho do arquivo a ser preenchido
/// @param tamanhoMax O tamanho máximo do arquivo 
/// @param arg O caminho do arquivo de origem que será manipulado
void trataCaminho(char *caminho, int tamanhoMax, char *arg);

/// @brief Adiciona a extensão ".txt" ao nome do arquivo fornecido
/// @param caminho O caminho final do arquivo com final ".txt"
/// @param tamanhoMax O tamanho máximo do arquivo
/// @param arg O nome do arquivo a ser formatado
void trataNomeArquivo(char *caminho, int tamanhoMax, char *arg);

/// @brief Combina os arquivos de entrada para gerar um caminho de saida
/// @param nomeGeo Nome do arquivo .geo
/// @param nomeQry Nome do arquivo .qry
/// @param caminhoSaida O caminho de saída combinado
/// @param tamanho O tamanho máximo do caminho de saída
void combinacaoNomeArquivo(char *nomeGeo, char *nomeQry, char *caminhoSaida, int tamanho);

#endif