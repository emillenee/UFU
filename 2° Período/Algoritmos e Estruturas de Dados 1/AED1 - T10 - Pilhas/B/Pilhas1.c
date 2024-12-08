#include <stdio.h>
#include <stdlib.h>
#include "Pilhas.h"

typedef struct no{
    Numero valor;
    struct no *prox;
}No;

typedef struct pilha{
    No *topo;
}Pilha;

Pilha *criar(){
    Pilha *p = (Pilha *)malloc(sizeof(Pilha));
    p->topo = NULL;
    return p;
}

void limpar(Pilha *p){
    if(p == NULL) return;
    Numero n;
    while(pilhaVazia(p) != 0)
        pop(p, &n);
    free(p);
    p = NULL;
}

int push(Pilha *p, Numero it){
    if(p == NULL) return 2;
    No *novo = (No*)malloc(sizeof(No));
    novo->valor = it;
    novo->prox = p->topo;
    p->topo = novo;
    return 0;
}

int pop(Pilha *p, Numero *it){
    if(p == NULL) return 2;
    if(pilhaVazia(p) == 0) return 1;
    No *temp = p->topo;
    *it = temp->valor;
    p->topo = temp->prox;
    free(temp);
    return 0;
}

int consultar(Pilha *p, Numero *it){
    if (p == NULL) return 2;
    if (pilhaVazia(p) == 0) return 1;
    No *temp = p->topo;
    *it = temp->valor;
    return 0;
}

int tamanho(Pilha *p) {
    if (p == NULL) return -1;
    int ct = 0;
    No *no = p->topo;
    while (no != NULL) {
    ct++;
    no = no->prox;
    }
    return ct;
}

int pilhaVazia(Pilha *p) {
    if (p == NULL) return 2;
    if (p->topo == NULL)
    return 0;
    else
    return 1;
}

int pilhaCheia(Pilha *p) {
    return 1;
}

void mostrar(Pilha *p) {
    if (p != NULL) {
        printf("[");
        No *no = p->topo;
        while (no != NULL) {
            printf(" %d, ",no->valor.num);
            no = no->prox;
        }
    printf("]\n");
    }
}

//LETRA B

int iguais(Pilha *p1, Pilha *p2){
    if((p1 == NULL) || (p2 == NULL)) return -1;
    if(tamanho(p1) != tamanho(p2)) return 1;
    while(pilhaVazia(p1) != 0){
        Numero cP1, cP2;
        pop(p1, &cP1);
        pop(p2, &cP2);
        if(cP1.num != cP2.num)
            return 1;
    }
    return 0;
}
