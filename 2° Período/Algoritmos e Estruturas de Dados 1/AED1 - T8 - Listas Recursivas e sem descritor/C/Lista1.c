#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"

typedef struct no* Lista;

Lista *criar(){
    Lista *l = (Lista*)malloc(sizeof(Lista));
    (*l) = NULL;
    return l;
}

void limpar(Lista *l){
    while (listaVazia(l) != 0)
        removerInicio(l);
    free(l);
    (*l) = NULL;
}

int inserirInicio(Lista * l, int it){
    if (l == NULL) return 2;
    No *no = (No*) malloc(sizeof(No));
    no->valor = it;
    no->prox = (*l);
    (*l) = no;
return 0;
}

int inserirFim(Lista *l, int it){
    if (l == NULL) return 2;
    No *novo = (No*)malloc(sizeof(No));
    novo->valor = it;
    novo->prox = NULL;
    if(listaVazia(l) == 0){
        return inserirInicio(l, it);
    }
    else{
        No *aux = (*l);
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = novo;
    }
    return 0;
}

int inserirPosicao(Lista *l, int it, int pos){
    if (l == NULL) return 2;
    if((listaVazia(l) == 0) || (pos == 0)){
        return inserirInicio(l, it);
    }
    No *aux = (*l);
    while((aux != NULL) && (pos > 0)){
        aux = aux->prox;
        pos--;
    }
    if(aux == NULL) return inserirFim(l, it);
    else{
        No *novo = (No*)malloc(sizeof(No));
        novo->valor = it;
        novo->prox = aux->prox;
        aux->prox = novo;
        return 0;
    }
}

int removerInicio(Lista *l){
    if (l == NULL) return 2;
    if (listaVazia(l) == 0) return 1; //(*l) == NULL
    No *noLista = (*l);
    (*l) = (*l)->prox;
    free(noLista);
    return 0;
}

int removerFim(Lista *l){
    if (l == NULL) return 2;
    if (listaVazia(l) == 0) return 1;
    No *varrer = (*l);
    No *varrer2 = NULL;
    while(varrer->prox != NULL){
        varrer2 = varrer;
        varrer = varrer->prox;
    }
    if(varrer == NULL){
        removerInicio(l);
    }
    else{
        varrer2->prox = NULL;
        free(varrer);
    }
    return 0;
}

int removerPosicao(Lista *l, int pos){
    if (l == NULL) return 2;
    if ((listaVazia(l) == 0) || (pos < 0)) return 1;
    if(pos == 1) return removerInicio(l);
    No *frente = (*l);
    No *tras = NULL;
    while(frente != NULL || pos > 0){
        tras = frente;
        frente = frente->prox;
        pos--;
    }
    tras->prox = frente->prox;
    free(frente);
    return 0;
}

int removerItem(Lista *l, int it){
    if (l == NULL) return 2;
    if (listaVazia(l) == 0) return 1;
    No *frente = *l;
    No *tras = NULL;
     while (frente != NULL && frente->valor != it) {
        tras = frente;
        frente = frente->prox;
    }
    if (frente == NULL) return 3;
    if(tras == NULL){
        (*l) = frente->prox;
    }
    else{
        tras->prox = frente->prox;
    }
    free(frente);
    return 0;
}

int buscarPosicao(Lista *l, int it, int *retorno){
    if (l == NULL) return 2;
    if (listaVazia(l) == 0) return 1;
    No *aux = (*l);
    int pos = 0;
    while(aux != NULL){
        if(aux->valor == it){
            *retorno = pos;
            return 0;
        }
        aux = aux->prox;
        pos++;
    }
    return 1;
}

int listaVazia(Lista *l){
    if((*l) == NULL) return 0;
    else return 1;
}

int listaCheia(Lista *l){
    return 1;
}

int tamanho(Lista *l){
    if(listaVazia(l) != 0) return 0;
    No *n = (*l);
    return 1 + tamanho(&(n->prox));
}

void mostrar(Lista *l){
    if (l != NULL) {
        if (listaVazia(l) != 0) {
            No *no = (*l);
            printf(" %d ",no->valor);
            mostrar(&(no->prox));
        }else printf("\n");
    }
}

//LETRA A
int ultimo(Lista *l, int *retorno){
    if(l == NULL) return 2;
    if(listaVazia(l) == 0) return 1;
    No *n = (*l);
    if(n->prox == NULL){
        *retorno = n->valor;
        return 0;
    }
    return ultimo(&(n->prox), retorno);
}
//LETRA B
int soma(Lista *l){
    if(l == NULL) return -1;
    if(listaVazia(l) == 0) return 0;
    No *no = (*l);
    return no->valor + soma(&(no->prox));
}

//LETRA C
void mostrarReversa(Lista *l){
    if(l != NULL){
        if(listaVazia(l) != 0){
            No *no = (*l);
            mostrarReversa(&(no->prox));
            printf(" %i ", no->valor);
        }
    }
}
