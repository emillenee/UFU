#ifndef ARVOREBINARIA_H
#define ARVOREBINARIA_H

#include "candidato.h"

typedef struct no // Definicao da struct de no da arvore binaria
{
    Candidato candidato;
    struct no *esquerda;
    struct no *direita;
} No;

typedef struct raiz // Definicao da struct de raiz da arvore binaria
{
    No *raiz;
} Arvore;

void criarArvore(Arvore *a); // Cria uma arvore binaria
int arvoreVazia(Arvore *a);  // Verifica se a arvore binaria esta vazia
void lerArquivoABB(Arvore *a,
                   const char *nomeArquivo); // Le arquivo como arvore binaria
No *criarN(Candidato valor);                 // Cria um no de arvore binaria
No *inserirArvore(No *raiz,
                  Candidato valor);      // Insere um candidato em arvore binaria
void imprimirCandidatoABB(Candidato *c); // Imprime candidato de arvore binaria
void buscarPorEstadoABB(
    No *raiz, const char *estado); // Busca por estado em arvore binaria
void buscarPorCidadeABB(
    No *raiz, const char *estado,
    const char *cidade); // Busca por cidade em arvore binaria
void buscarPorNumeroABB(No *raiz, const char *estado, const char *cidade,
                        int numero); // Busca por numero em arvore binaria
void liberarArvoreABB(No *raiz);     // Libera a memoria dos nos da arvore
void destruirArvoreABB(Arvore *a);   // Destroi e libera uma arvore inteira
void listarCandidatosGeneroEABB(
    No *raiz, const char *estado,
    const char *genero); // Listar candidatos por genero quando pesquisar estado
void listarCandidatosGeneroCABB(
    No *raiz, const char *estado, const char *cidade,
    const char *genero); // Listar candidatos por genero quando pesquisar cidade
void listarCandidatosGeneroNABB(
    No *raiz, const char *estado, const char *cidade, int num,
    const char *genero); // Listar candidatos por genero quando pesquisar numero
void listarCandidatosPartidoEABB(
    No *raiz, const char *estado,
    const char
        *partido); // Listar candidatos por partido quando pesquisar estado
void listarCandidatosPartidoCABB(
    No *raiz, const char *estado, const char *cidade,
    const char
        *partido); // Listar candidatos por partido quando pesquisar cidade
void listarCandidatosPartidoNABB(
    No *raiz, const char *estado, const char *cidade, int num,
    const char
        *partido); // Listar candidatos por partido quando pesquisar numero
void listarCandidatosCorEABB(
    No *raiz, char *estado,
    char *cor); // Listar candidatos por cor quando pesquisar estado
void listarCandidatosCorCABB(
    No *raiz, char *estado, char *cidade,
    char *cor); // Listar candidatos por cor quando pesquisar cidade
void listarCandidatosCorNABB(
    No *raiz, char *estado, char *cidade, int num,
    char *cor); // Listar candidatos por cor quando pesquisar numero

#endif