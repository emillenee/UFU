#include <stdio.h>
#include <stdlib.h>
#include "ListaPoli.h"
#include "Polinomio.h"


typedef struct nop {
    Polinomio *valor; 
    struct nop *prox;
}Nop;


typedef struct lista {
    struct nop *inicio; 
}Lista;

Lista *criar() {
    Lista *l = (Lista*)malloc(sizeof(Lista));
    l->inicio = NULL;
    return l;
}

int listaVazia(Lista *l) {
    if (l == NULL)
    return 2;
    if (l->inicio == NULL)
    return 0;
    return 1;
}

int listaCheia(Lista *l){
    if (l == NULL) return 2;
    //if (l->total) return 0;
    else return 1;
}

int listaCheia2(Lista *l){
    return 0;
}


int inserirInicio(Lista *l,  Polinomio *it){
    if (l == NULL) return 2;
    if (listaCheia(l)== 0) return 1;
    Nop *n = (Nop*)malloc(sizeof(Nop));
    n->valor = it;
    n->prox = l->inicio;
    l->inicio = n;
    n->valor->idem = tamanho(l);
    return 0;
}

int inserirFim(Lista *l, Polinomio *it){
    if (l == NULL) return 2;
    Polinomio *cpy = geraCopia(it);
    if (listaVazia(l) == 0) return inserirInicio(l,cpy);
    Nop *n = l->inicio;
    while (n->prox != NULL)
        n = n->prox;
    Nop *n1 = (Nop*)malloc(sizeof(Nop));
    n1->valor = cpy;
    n->prox = n1;
    n1->prox = NULL;
    n1->valor->idem = tamanho(l);
    return 0;
}

int inserirPosicao(struct lista *l, struct polinomio *it,int pos){
    if (l == NULL) return 2;
    if (pos < 0) return 3;
    if ((listaVazia(l) == 0)||(pos == 0))
    return inserirInicio(l,it);
    Nop *n = l->inicio;
    int p = 1;
    while ((n->prox != NULL)&&(p != pos)) {
    p++;
    n = n->prox;
    }
    Nop *n1 = (Nop*)malloc(sizeof(Nop));
    n1->valor = it;
    n1->prox = n->prox;
    n->prox = n1;
    return 0;
}

int removerInicio(Lista *l){
    if (l == NULL) return 2;
    if (listaVazia(l) == 0) return 1;
    Nop *n = l->inicio;
    l->inicio = n->prox;
    free(n);
    return 0;
}

int removerFim(Lista *l){
    if (l == NULL) return 2;
    if (listaVazia(l) == 0) return 1;
    Nop *noAuxiliar = NULL;
    Nop *noLista = l->inicio;
    while (noLista->prox != NULL) {
        noAuxiliar = noLista;
        noLista = noLista->prox;
    }
    if (noAuxiliar == NULL) l->inicio = NULL;
    else noAuxiliar->prox = NULL;
    free(noLista);
    return 0;
}
int removerPosicao(Lista *l,int pos){
    if (l == NULL) return 2;
    if (listaVazia(l) == 0) return 1;
    Nop *n = l->inicio;
    if (pos == 0) removerInicio(l);
    if (pos >= tamanho(l)) removerFim(l);
    for (int i = 1; i < pos; i++){
        n = n->prox;
    } 
    Nop *n2 = n->prox;
    n->prox = n->prox->prox;
    free(n2);

}
int removerItem(struct lista *l, int it){
    if (l == NULL) return 2;
    if (listaVazia(l) == 0) return 1;
    Nop *n = l->inicio;
    int cont = 1;
    if (n->valor->idem == it) removerInicio(l); 
    while(n->prox!= NULL){
        n = n->prox;
        cont ++;
        if (n->valor->idem == it){
            removerPosicao(l, cont);
            cont --;
        }
    }
    return 0;
}

int buscarItemChave(Lista *l, int chave, Polinomio *retorno){
    if (l == NULL) return 2;
    Nop *noLista = l->inicio;
    while ((noLista != NULL)) {
        if (noLista->valor->idem == chave) {
            retorno->idem = noLista->valor->idem;
            retorno->inicio = noLista->valor->inicio;
            return 0;
        }
        noLista = noLista->prox;
    }
    return 1;
}

int buscarPosicao(struct lista *l, int posicao, struct polinomio *retorno){
    if(l == NULL) return 2;
    if(listaVazia(l)== 0) return 1;
    int i = 0;
    Nop *n = l->inicio;
    for( i=1; i<posicao && n->prox; i++){
        n = n->prox;
    }
    if (i<posicao) return 3;
    retorno->idem = n->valor->idem;
    retorno->inicio = n->valor->inicio;
    return 0;
}

int ContemItem(Lista *l,  Polinomio *it){
    if(l == NULL) return 2;
    if(listaVazia(l) == 0) return 3;
    Nop *n = l->inicio;
    while(n != NULL){
        if(n->valor->idem == it->idem){
            return 0;
        }
        n = n->prox;
    }
}


int removern(Lista *l, int n){
    if(l==NULL) return 2;
    if(listaVazia(l)== 0) return 1;
    int i=0;
    while (listaVazia(l)!= 0 && i<n) {
        removerInicio(l);
        i++;
    }
    return 0;
}

int tamanho(Lista *l){
    if(l == NULL) return 2;
    int cont = 0;
    Nop *n = l->inicio;
    while(n != NULL){
        cont++;
        n = n->prox;
    }
    return cont;
}

void mostrar(Lista *l){
    if (l != NULL) {
        Nop *noLista = l->inicio;
        while (noLista != NULL) {
            printf(" Polinomio %d: \n",noLista->valor->idem);
            polimostrar(noLista->valor);
            noLista = noLista->prox;
        }
        printf("\n");
   }
}

void limpar(Lista *l) {
    while (listaVazia(l) != 0)
    removerInicio(l);
    free(l);
}

