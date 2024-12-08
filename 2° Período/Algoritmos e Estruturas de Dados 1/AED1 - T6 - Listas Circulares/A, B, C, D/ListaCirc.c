#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista.h"

typedef struct no {
    Aluno valor;
    struct no *prox;
}No;

typedef struct lista {
    No *final;
}ListaCircular;

Lista *criar() {
    Lista *l =(Lista*)malloc(sizeof(Lista));
    l->final = NULL;
    return l;
}

void limpar(Lista *l) {
    while (listaVazia(l) != 0)
    removerInicio(l);
    free(l);
    l = NULL;
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
            printf(" {%d, ",noLista->valor.mat);
            printf("%s, ",noLista->valor.nome);
            printf("%.2f} ",noLista->valor.n1);
            noLista = noLista->prox;
        } while (noLista != l->final->prox);
    }
    printf("]\n");
    }
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

int inserirInicio(Lista *l, Aluno it) {
    if (l == NULL) return 2;
    No *no = (No *)malloc(sizeof(No));
    no->valor = it;
    if (listaVazia(l) == 0) {
        l->final = no;
        no->prox = no;
    }else {
        no->prox = l->final->prox;
        l->final->prox = no;
    }
    return 0;
}

int inserirFim(Lista *l, Aluno it) {
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

int inserirPosicao(Lista *l, Aluno it, int pos){
    if (l == NULL) return 2;
    int tam = tamanho(l);
    if (pos < 0 || pos > tam) return 1;

    if (pos == 0) {
        return inserirInicio(l, it);
    } else if (pos == tam) {
        return inserirFim(l, it);
    } else {
        No *novo = (No *)malloc(sizeof(No));
        novo->valor = it;

        No *varrer = l->final->prox;
        for (int i = 0; i < pos - 1; i++) {
            varrer = varrer->prox;
        }
        novo->prox = varrer->prox;
        varrer->prox = novo;
        return 0;
    }
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

int removerFim(Lista *l) {
    if (l == NULL) return 2;
    if (listaVazia(l) == 0) return 1;
    if (l->final->prox == l->final) {
        free(l->final);
        l->final = NULL;
        return 0;
    }
    No *aux = l->final->prox, *noFinal = l->final;
    while (aux->prox != l->final) {
        aux = aux->prox;
    }
    aux->prox = noFinal->prox;
    free(noFinal);
    l->final = aux;
    return 0;
}

int removerPosicao(Lista *l,int pos){
    if (l == NULL) return 2;
    if (listaVazia(l) == 0) return 1;
    No *varrer = l->final->prox;
    No *varrer2 = l->final;
    for(int i = 0; i < pos; i++){
        varrer2 = varrer;
        varrer = varrer->prox;
    }
    varrer2->prox = varrer->prox;
    free(varrer);
    return 0;
}

int removerItem(Lista *l, Aluno it){
    if (l == NULL) return 1;
    if (listaVazia(l) == 0) return 2;

    No *varrer = l->final->prox;
    No *varrer2 = l->final;
    do {
        if (varrer->valor.mat == it.mat){
            if (varrer == l->final) {
                l->final = varrer2;
            }
            varrer2->prox = varrer->prox;
            free(varrer);
            return 0;
        }
        varrer2 = varrer;
        varrer = varrer->prox;
    } while (varrer != l->final->prox);
    return 1;
}

int buscarItemChave(Lista *l, int chave, Aluno *it) {
    if (l == NULL) return 2;
    if (listaVazia(l) == 0) return 1;
    No *no = l->final->prox;
    while ((no->prox != l->final->prox)&&((no->valor).mat != chave))
        no = no->prox;
    if ((no->valor).mat != chave )
        return 1;
    else {
        *it = no->valor;
        return 0;
    }
}

int buscarPosicao(Lista *l, int pos, int *retorno){
    if (l == NULL) return 2;
    if (listaVazia(l) == 0) return 1;
    No *no = l->final->prox;
    int cont = 0;
    while (cont < pos && no != l->final) {
        no = no->prox;
        cont++;
    }
    if (cont != pos) return 1;
    *retorno = cont;
    return 0;
}

int removerCentral(Lista *l){
    int tam = tamanho(l);
    if (tam == 1){
        return removerInicio(l);
    }
    int meio = ((tam+1)/2)-1;
    return removerPosicao(l, meio);
}

int removerPrimeiro(Lista *l, Aluno it){
    if (l == NULL) return 1;
    if (listaVazia(l) == 0) return 2;

    No *varrer = l->final->prox;
    No *varrer2 = l->final;
    do {
        if (varrer->valor.mat == it.mat){
            varrer2->prox = varrer->prox;
            free(varrer);
            return 0;
        }
        varrer2 = varrer;
        varrer = varrer->prox;
    } while (varrer != l->final->prox);
    return 1;
}

Lista *interseccao (Lista *l, Lista *l2){
    if(l==NULL || l2==NULL) return NULL;
    if(listaVazia(l) == 0 || listaVazia(l2) == 0) return NULL;
    Lista *l3 = criar();
    No *novo = l->final->prox;
    for(int i = 0; i < tamanho(l); i++){
        No *novo2 = l2->final->prox;
        for(int j = 0; j < tamanho(l2); j++){
            if(novo->valor.mat == novo2->valor.mat){
                inserirFim(l3, novo->valor);
            }
            novo2 = novo2->prox;
        }
        novo = novo->prox;
    }
    return l3;
}
