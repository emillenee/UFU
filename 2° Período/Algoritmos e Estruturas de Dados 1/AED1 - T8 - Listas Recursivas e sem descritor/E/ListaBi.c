#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Lista.h"

typedef struct no* Lista;

Lista *criar(){
    Lista *l = (Lista*)malloc(sizeof(Lista));
    (*l) = NULL;
    return l;
}

void limpar(Lista *l){
    while ((*l) == NULL)
        removerInicio(l);
    free(l);
    (*l) = NULL;
}

int adicionar(Lista *l, int it){
    if (l == NULL) return 1;
    No *novo = (No*) malloc(sizeof(No));
    novo->valor = it;
    novo->prox = (*l);
    (*l) = novo;
    return 0;
}

int removerInicio(Lista *l){
    if ((l == NULL) || (*l) == NULL) return 1;
    No *temp = (*l);
    (*l) = (*l)->prox;
    free(temp);
    return 0;
}

void mostrar(Lista *l){
    if(l != NULL){
        if((*l) != NULL){
            No *no = (*l);
            printf(" %i ", no->valor);
            mostrar(&(no->prox));
        }else printf("\n");
    }
}
/*
int transforma(Lista *l, int t){
    if(l == NULL || (*l) == NULL){
        return 0;
    }
    else{
        No *no = (*l);
        if(no->valor == 1){
            int soma = pow(2, t);
            return soma + transforma(&(no->prox), t-1);
        }
        else{
            return transforma(&(no->prox), t-1);
        }
    }
}
*/

int transforma(Lista *l, int t){
    if(l == NULL || (*l) == NULL){
        return 0;
    }
    else{
        No *no = (*l);
        int soma = no->valor * pow(2, t);
        return soma + transforma(&(no->prox), t-1);
    }
}
