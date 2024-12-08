#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Filas.h"

typedef struct no{
    Paciente p;
    struct no *prox;
}No;

typedef struct fila{
    No *inicio;
    No *fim;
    int qtd;
}Fila;

Fila *criar(){
    Fila *f = (Fila*)malloc(sizeof(Fila));
    f->qtd = 0;
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

void limpar(Fila *f){
    if(f == NULL ) return;
    while(filaVazia(f) != 0)
        atender(f);
    free(f);
    f = NULL;
}

int inserirP(Fila *f, char *nome){
    if(f == NULL) return 2;
    No *novo = (No*)malloc(sizeof(No));
    strcpy(novo->p.nome, nome);
    novo->prox = NULL;
    if(filaVazia(f) == 0){
        f->inicio = novo;
    }
    else{
        f->fim->prox = novo;
    }
    f->fim = novo;
    f->qtd++;
    return 0;
}

int atender(Fila *f){
    if(f == NULL) return 2;
    if(filaVazia(f) == 0) return 1;
    No *temp = f->inicio;
    f->inicio = temp->prox;
    free(temp);
    if(f->inicio == NULL)
        f->fim = NULL;
    f->qtd--;
    return 0;
}

void mostrar(Fila *f){
    if(f != NULL){
        printf("[");
        No *no = f->inicio;
        while(no != NULL){
            printf(" %s, ", no->p.nome);
            no = no->prox;
        }
        printf("]\n");
    }
}

int filaVazia(Fila *f){
    if(f == NULL) return 2;
    if(f->qtd == 0)
        return 0;
    else
        return 1;
}
