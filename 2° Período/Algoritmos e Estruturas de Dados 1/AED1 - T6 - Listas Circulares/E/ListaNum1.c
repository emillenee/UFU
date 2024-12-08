#include <stdio.h>
#include <stdlib.h>
#include "ListaNum.h"

typedef struct no{
    Num valor;
    struct no *prox;
}No;

typedef struct lista {
    No *final;
}Lista;

Lista *criar(){
    Lista *l =(Lista*)malloc(sizeof(Lista));
    l->final = NULL;
    return l;
}

void limpar(Lista *l){
    while (listaVazia(l) != 0)
    removerInicio(l);
    free(l);
    l = NULL;
}

int listaVazia(Lista *l) {
    if (l == NULL) return 2;
    if (l->final == NULL){
        return 0;
    } else {
        return 1;
    }
}


int listaCheia(Lista *l){
    return 1;
}

int tamanho(Lista *l) {
    if (l == NULL) return -1;
    if (listaVazia(l) == 0) return 0;
        No *varrer = l->final->prox;
        int cont = 0;
    do {
        cont++;
        varrer = varrer->prox;
    } while (varrer != l->final->prox);
    return cont;
}

void mostrar(Lista *l) {
    if (l != NULL) {
    printf("[");
    if (listaVazia(l) != 0) {
        No *noLista = l->final->prox;
        do {
            printf(" %d, ",noLista->valor.n);
            noLista = noLista->prox;
        } while (noLista != l->final->prox);
    }
    printf("]\n");
    }
}

int inserirFim(Lista *l, Num it) {
    if (l == NULL) return 2;
    No *no = (No *)malloc(sizeof(No));
    no->valor = it;
    if (listaVazia(l) == 0) {
        l->final = no;
        no->prox = no;
    }else {
        no->prox = l->final->prox;
        l->final->prox = no;
        l->final = no;
    }
    return 0;
}

int removerInicio(Lista *l) {
    if (l == NULL) return 2;
    if (listaVazia(l) == 0) return 1;
    if (l->final->prox == l->final) {
        free(l->final);
        l->final = NULL;
        return 0;
    }
    No *temp = l->final->prox;
    l->final->prox = temp->prox;
    free(temp);
    return 0;
}

int numeros(Lista *l, Lista *par, Lista *impar){
    if (l == NULL || par == NULL || impar == NULL) return 1;
    if (listaVazia(l) == 0) return 2;
    No *varrer = l->final->prox;
    for(int i = 0; i < (tamanho(l)); i++){
        if((varrer->valor.n%2) == 0){
            inserirFim(par, varrer->valor);
            varrer = varrer->prox;
        }
        else{
            inserirFim(impar, varrer->valor);
            varrer = varrer->prox;
        }
    }
    return 0;
}
