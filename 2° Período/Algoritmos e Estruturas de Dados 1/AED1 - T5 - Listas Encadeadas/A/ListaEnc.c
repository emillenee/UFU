#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"

typedef struct no{
    Aluno valor;
    struct no *prox;
}No;

typedef struct lista{
    No *inicio;
}Lista;

Lista *criar(){
    Lista *l = (Lista*)malloc(sizeof(Lista));
    l->inicio = NULL;
    return l;
}

void limpar(Lista *l){
    No *atual = l->inicio;
    No *proximo;

    while(atual != NULL){
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    l->inicio = NULL;
}

/*
void limpar(Lista *l){
    while(listaVazia(l) != 0){
        removerInicio(l);
    }
}
*/

int inserirInicio(Lista *l,Aluno it){
    if(l == NULL) return 1;
    if(listaCheia(l) == 0) return 2;
    No *novo = (No*)malloc(sizeof(No));
    novo->valor = it;
    novo->prox = l->inicio;
    l->inicio = novo;
    return 0;
}

int inserirFim(Lista *l,Aluno it){
    if(l == NULL) return 1;
    if(listaCheia(l) == 0) return 2;
    if(listaVazia(l) == 0){
        return inserirInicio(l, it);
    }
    No *varrer = l->inicio;
    while(varrer->prox != NULL){
        varrer = varrer->prox;
    }
    No *novo = (No*)malloc(sizeof(No));
    novo->valor = it;
    novo->prox = NULL;
    varrer->prox = novo;
    return 0;
}

int inserirPosicao(Lista *l,Aluno it,int pos){
    if(l == NULL) return 1;
    if(listaCheia(l) == 0) return 2;
    if(pos == 1 || listaVazia(l) == 0){
        return inserirInicio(l, it);
    }
    int p = 1;
    No *varrer = l->inicio;
    while((varrer->prox != NULL) && (p != pos)){
        p++;
        varrer = varrer->prox;
    }
    No *novo = (No*)malloc(sizeof(No));
    novo->valor = it;
    novo->prox = varrer->prox;
    varrer->prox = novo;
    return 0;
}

int removerInicio(Lista *l){
    if(l == NULL) return 1;
    if(listaVazia(l) == 0) return 2;
    No *varrer = l->inicio;
    l->inicio = varrer->prox;
    free(varrer);
    return 0;
}

int removerFim(Lista *l){
    if(l == NULL) return 1;
    if(listaVazia(l) == 0) return 2;
    No *varrer = l->inicio;
    No *varrer2 = NULL;
    while(varrer->prox != NULL){
        varrer2 = varrer;
        varrer = varrer->prox;
    }
    if(varrer2 == NULL) l->inicio = NULL;
    else varrer2->prox = NULL;
    return 0;
}

int removerPosicao(Lista *l,int pos){
    if(l == NULL) return 1;
    if(listaVazia(l) == 0) return 2;
    if(pos == 1){
        removerInicio(l);
    }
    int p = 1;
    No *varrer = l->inicio;
    No *varrer2 = NULL;
    while((varrer != NULL) && (p != pos)){
        p++;
        varrer2 = varrer;
        varrer = varrer->prox;
    }
    if(varrer == NULL) return 3;
    varrer2->prox = varrer->prox;
    free(varrer);
    return 0;
}

int removerItem(Lista *l, Aluno it){
    if(l == NULL) return 1;
    if(listaVazia(l) == 0) return 2;
    No *varrer = l->inicio;
    No *varrer2 = NULL;
    while(varrer != NULL && varrer->valor.mat != it.mat){
        varrer2 = varrer;
        varrer = varrer->prox;
    }
    if(varrer == NULL) return 3;
    if(varrer2 == NULL) l->inicio = varrer->prox;
    else varrer2->prox = varrer->prox;
    free(varrer);
    return 0;
}

int buscarItemChave(Lista *l,int chave,Aluno *retorno){
    if(l == NULL) return 1;
    No *varrer = l->inicio;
    while(varrer != NULL){
        if((varrer->valor.mat == chave)){
            *retorno = varrer->valor;
            return 0;
        }
        varrer = varrer->prox;
    }
    return 1;
}

int buscarPosicao(Lista *l,int pos, Aluno *retorno){
    if(l == NULL) return 1;
    if(listaVazia(l) == 0) return 2;
    int cont;
    No *varrer = l->inicio;
    while(varrer != NULL && cont < pos){
        cont++;
        varrer = varrer->prox;
    }
    if(varrer == NULL) return 3;
    *retorno = varrer->valor;
    return 0;
}

int listaVazia(Lista *l){
    if(l == NULL) return 1;
    if(l->inicio == NULL) return 0;
    return 1;
}

int listaCheia(Lista *l){
    if(l == NULL) return 2;
    No *n = (No*)malloc(sizeof(No));
    if(n == NULL) return 0;
    else{
        free(n);
        return 1;
    }
}

int tamanho(Lista *l){
    if(l == NULL) return -1;
    int cont = 0;
    No *varrer = l->inicio;
    while(varrer != NULL){
        cont++;
        varrer = varrer->prox;
    }
    return cont;
}

void mostrar(Lista *l){
    if(l != NULL){
        printf("[");
        No *varrer = l->inicio;
        while (varrer != NULL){
            printf(" {%d, ", varrer->valor.mat);
            printf("%s, ", varrer->valor.nome);
            printf("%.2f} ", varrer->valor.n1);
            varrer = varrer->prox;
        }
        printf("]\n");
    }
}
