#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

void criarArvore(Arvore *a){
    a->raiz = NULL;
}

int arvoreVazia(Arvore *a){
    return (a->raiz == NULL);
}

int contarLinhas(const char *nomeArquivo){
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo");
        return -1;
    }

    int linhas = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), arquivo)) {
        linhas++;
    }

    fclose(arquivo);
    return linhas;
}

void lerArquivoABB(Arvore *a, const char *nomeArquivo){
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), arquivo)) {
        CodigoP cep;
        sscanf(buffer, "%9[^;];%2[^;];%49[^;];%99[^\n]", cep.cep, cep.estado, cep.cidade, cep.rua);
        a->raiz = inserirArvore(a->raiz, cep);
    }

    fclose(arquivo);
}

//Função que cria um novo nó
No* criarN(CodigoP valor){
    No *novo = (No*)malloc(sizeof(No));
    if(novo){
        novo->valor = valor;
        novo->esquerdo = NULL;
        novo->direito = NULL;
    }
    return novo;
}

No* inserirArvore(No *raiz, CodigoP valor) {
    if (raiz == NULL) {
        return criarN(valor);
    }

    if (strcmp(valor.cep, raiz->valor.cep) < 0) {
        raiz->esquerdo = inserirArvore(raiz->esquerdo, valor);
    } else if (strcmp(valor.cep, raiz->valor.cep) > 0) {
        raiz->direito = inserirArvore(raiz->direito, valor);
    }
    return raiz;
}

No* removeArvore(No *raiz, CodigoP valor) {
    if (raiz == NULL) {
        return NULL;
    }

    if (strcmp(valor.cep, raiz->valor.cep) < 0) {
        raiz->esquerdo = removeArvore(raiz->esquerdo, valor);
    } else if (strcmp(valor.cep, raiz->valor.cep) > 0) {
        raiz->direito = removeArvore(raiz->direito, valor);
    } else {
        // Caso 1: Nó sem filhos
        if (raiz->esquerdo == NULL && raiz->direito == NULL) {
            free(raiz);
            return NULL;
        }
        // Caso 2: Nó com um filho
        else if (raiz->esquerdo == NULL) {
            No *temp = raiz->direito;
            free(raiz);
            return temp;
        } else if (raiz->direito == NULL) {
            No *temp = raiz->esquerdo;
            free(raiz);
            return temp;
        }
        // Caso 3: Nó com dois filhos
        else {
            No *temp = menorArvore(raiz->direito);
            raiz->valor = temp->valor;
            raiz->direito = removeArvore(raiz->direito, temp->valor);
        }
    }
    return raiz;
}

void pesquisar(No *raiz, CodigoP *cep){
    if(raiz == NULL){
        printf("Erro: Registro nao esta na arvore\n");
        return;
    }
    if(strcmp(cep->cep, raiz->valor.cep) < 0){
        pesquisar(raiz->esquerdo, cep);
        return;
    }else if(strcmp(cep->cep, raiz->valor.cep) > 0){
        pesquisar(raiz->direito, cep);
    }else{
        *cep = raiz->valor;
    }
}

//Funções de percurso
void percorrerCentral(No *raiz){
    if(raiz != NULL){
        percorrerCentral(raiz->esquerdo);
        imprimirCodigoP(&raiz->valor);
        percorrerCentral(raiz->direito);
    }
}

void percorrerPreFixado(No *raiz){
    if(raiz != NULL){
        imprimirCodigoP(&raiz->valor);
        percorrerPreFixado(raiz->esquerdo);
        percorrerPreFixado(raiz->direito);
    }
}

void percorrerPosFixado(No *raiz){
    if(raiz != NULL){
        percorrerPosFixado(raiz->esquerdo);
        percorrerPosFixado(raiz->direito);
        imprimirCodigoP(&raiz->valor);
    }
}

int alturaArvore(No *raiz){
    if(raiz == NULL){
        return -1;
    }else{
        int alturaEsquerda = alturaArvore(raiz->esquerdo);
        int alturaDireita = alturaArvore(raiz->direito);
        if(alturaEsquerda > alturaDireita){
            return alturaEsquerda + 1;
        }else{
            return alturaDireita + 1;
        }
    }
}

No* menorArvore(No *raiz){
    if (raiz == NULL){
        return NULL;
    }
    No *novo = raiz;
    while (novo->esquerdo != NULL){
        novo = novo->esquerdo;
    }
    return novo;
}

No* maiorArvore(No *raiz){
    if (raiz == NULL){
        return NULL;
    }
    No *novo = raiz;
    while (novo->direito != NULL){
        novo = novo->direito;
    }
    return novo;
}


//Funções de imprimir
void imprimirCodigoP(CodigoP *p){
    if(p != NULL){
        printf("==========\n");
        printf("CEP: %s\n", p->cep);
        printf("Estado: %s\n", p->estado);
        printf("Cidade: %s\n", p->cidade);
        printf("Rua: %s\n", p->rua);
    }
}