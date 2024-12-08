#ifndef BUSCABINARIA_H
#define BUSCABINARIA_H

#include "candidato.h"

void lerArquivoVetor(
    Candidato *c,
    const char *nomeArquivo); // Le o arquivo e armazena como vetor
int contarLinhas(
    const char *nomeArquivo); // Conta a quantidade de linhas do arquivo
void shellEstados(Candidato *c,
                  int linhas); // Ordena por estados utilizando ShellSort
void buscaBinariaEstado(Candidato *c, int linhas, int *inf, int *sup,
                        char *chave); // Busca candidatos por estado
void shellCidades(Candidato *c, int inf,
                  int sup); // Ordena por cidades utilizando ShellSort
void buscaBinariaCidade(Candidato *c, int *inf, int *sup,
                        char *cidade); // Busca candidatos por cidade
void shellNumeros(Candidato *c, int inf,
                  int sup); // Ordena por numero utilizando ShellSort
void buscaBinariaNumero(Candidato *c, int *inf, int *sup,
                        int num);   // Busca candidatos por numero
void imprimeCandidato(Candidato c); // Imprime candidato
void imprimeIntervalo(Candidato *c, int inf,
                      int sup); // Imprime um intervalo do vetor
void listagemGenero(Candidato *c, int inf, int sup,
                    char *genero); // Imprime os candidatos de determinado
                                   // genero em um intervalo
void listagemPartido(Candidato *c, int inf, int sup,
                     char *sigla); // Imprime os candidatos de determinado
                                   // partido em um intervalo
void listagemCor(
    Candidato *c, int inf, int sup,
    char *cor); // Imprime os candidatos de determinada cor em um intervalo

#endif