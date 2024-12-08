#ifndef ARVOREAVL_H
#define ARVOREAVL_H

#include "candidato.h"

typedef struct noAVL // Struct de um no de arvore AVL
{
    Candidato candidato;
    int fator;
    int altura;
    struct noAVL *esquerda;
    struct noAVL *direita;
} NoAVL;

typedef struct raizAVL // Struct de uma raiz de arvore AVL
{
    NoAVL *raiz;
} ArvoreAVL;

void criarArvoreAVL(ArvoreAVL *a);               // Cria uma arvore AVL
int arvoreVaziaAVL(ArvoreAVL *a);                // Verifica se a arvore AVL esta vazia
NoAVL *criarN_AVL(Candidato valor);              // Cria um no de arvore AVL
int alturaNo(NoAVL *n);                          // Retorna altura do no
int fatorBalanceamento(NoAVL *n);                // Calcula e retorna fator de balanceamento
void RotacaoLL(NoAVL **raiz);                    // Realiza rotacao direita-direita
void RotacaoRR(NoAVL **raiz);                    // Realiza rotacao esquerda-esquerda
void RotacaoLR(NoAVL **raiz);                    // Realiza rotacao direita-esquerda
void RotacaoRL(NoAVL **raiz);                    // Realiza rotacao direita-esquerda
NoAVL *insereAVL(NoAVL **raiz, Candidato valor); // Insere no na arvore AVl
void lerArquivoAVL(
    ArvoreAVL *a,
    const char *nomeArquivo); // Leitura de arquivo como arvore AVL
void buscarPorEstadoAVL(NoAVL *raiz,
                        const char *estado); // Busca por estado em arvore AVL
void buscarPorCidadeAVL(NoAVL *raiz, const char *estado,
                        const char *cidade); // Busca por cidade em arvore AVL
void buscarPorNumeroAVL(NoAVL *raiz, const char *estado, const char *cidade,
                        int numero);     // Busca por numero em arvore AVL
void imprimirCandidatoAVL(Candidato *c); // Imprime candidato de arvore AVL
void liberarArvoreAVL(NoAVL *raiz);      // Libera memoria de no de arvore AVL
void destruirArvoreAVL(ArvoreAVL *a);    // Destroi toda arvore AVL
void listarCandidatosGeneroCAVL(
    NoAVL *raiz, const char *estado, const char *cidade,
    const char *genero); // Imprimir todos candidatos de um determinado genero
                         // de uma cidade em arvore AVL
void listarCandidatosGeneroEAVL(
    NoAVL *raiz, const char *estado,
    const char *genero); // Imprimir todos candidatos de um determinado genero
                         // de um estado em arvore AVL
void listarCandidatosGeneroNAVL(
    NoAVL *raiz, const char *estado, const char *cidade, int num,
    const char
        *genero); // Imprimir todos os candidatos de um genero de um numero
void listarCandidatosPartidoCAVL(
    NoAVL *raiz, const char *estado, const char *cidade,
    const char *partido); // Imprimir todos candidatos de um determinado partido
                          // de uma cidade em arvore AVL
void listarCandidatosPartidoEAVL(
    NoAVL *raiz, const char *estado,
    const char *partido); // Imprimir todos candidatos de um determinado partido
                          // de um estado em arvore AVL
void listarCandidatosPartidoNAVL(
    NoAVL *raiz, const char *estado, const char *cidade, int num,
    const char
        *partido); // Imprimir todos candidatos de um partido de um numero
void listarCandidatosCorCAVL(
    NoAVL *raiz, char *estado, char *cidade, char *cor); // Imprimir todos candidatos de uma determinada cor de uma
                                                         // cidade em arvore AVL
void listarCandidatosCorEAVL(
    NoAVL *raiz, char *estado,
    char *cor); // Imprimir todos candidatos de uma determinada cor de um
                // estado em arvore AVL
void listarCandidatosCorNAVL(
    NoAVL *raiz, char *estado, char *cidade, int num,
    char *cor);                    // Imprimir todos candidatos de uma cor de um numero
NoAVL *balancearAVL(NoAVL **raiz); // Balanceia a arvore apos a insercao

#endif