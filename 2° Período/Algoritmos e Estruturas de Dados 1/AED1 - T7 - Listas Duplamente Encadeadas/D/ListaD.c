#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"

typedef struct no{
    Aluno valor;
    struct no *prox;
    struct no *ant;
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
    while (listaVazia(l) != 0)
        removerInicio(l);
    free(l);
    l = NULL;
}

int listaVazia(Lista *l){
    if(l == NULL) return 2;
    if(l->inicio == NULL)
        return 0;
    else
        return 1;
}

int listaCheia(Lista *l){
    return 1;
}

int tamanho(Lista *l){
    if(l == NULL) return -1;
    No *no = l->inicio;
    int cont = 0;
    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

void mostrar(Lista *l){
    if(l != NULL){
        printf("[");
        No *n = l->inicio;
        while(n != NULL){
            printf(" {%d, ", n->valor.mat);
            printf("%s, ", n->valor.nome);
            printf("%.2f} ", n->valor.n1);
            n = n->prox;
        }
        printf("]\n");
    }
}

int inserirInicio(Lista *l,Aluno it){
    if(l == NULL) return 2;
    No *novo = (No*)malloc(sizeof(No));
    novo->valor = it;
    novo->prox = l->inicio;
    novo->ant = NULL;
    if(l->inicio != NULL)
        l->inicio->ant = novo;
    l->inicio = novo;
    return 0;
}

int inserirFim(Lista *l,Aluno it){
    if(l == NULL) return 2;
    if(listaVazia(l) == 0)
        return inserirInicio(l, it);
    No *aux = l->inicio;
    while(aux->prox != NULL)
        aux = aux->prox;
    No *novo = (No*)malloc(sizeof(No));
    novo->valor = it;
    novo->prox = NULL;
    novo->ant = aux;
    aux->prox = novo;
    return 0;
}

int inserirPosicao(Lista *l,Aluno it,int pos){
    if(l == NULL) return 1;
    if((listaVazia(l) == 0) || (pos == 0))
        return inserirInicio(l, it);
    No *aux = l->inicio;
    while((aux != NULL) && (pos > 0)){
        aux = aux->prox;
        pos--;
    }
    if(aux == NULL) return inserirFim(l, it);
    else{
    No *novo = (No*)malloc(sizeof(No));
    novo->valor = it;
    novo->prox = aux;
    novo->ant = aux->ant;
    aux->ant = novo;
    novo->ant->prox = novo;
    }
    return 0;
}

int removerInicio(Lista *l){
    if (l == NULL) return 2;
    if (listaVazia(l) == 0)
        return 1;
    No *noLista = l->inicio;
    l->inicio = noLista->prox;
    if (l->inicio != NULL)
        l->inicio->ant = NULL;
    free(noLista);
    return 0;
}

int removerFim(Lista *l){
    if (l == NULL) return 2;
    if (listaVazia(l) == 0)
        return 1;
    No *noLista = l->inicio;
    while (noLista->prox != NULL)
        noLista = noLista->prox;
    if (noLista->ant == NULL)
        l->inicio = NULL;
    else
        noLista->ant->prox = NULL;
    free(noLista);
    return 0;
}

int removerPosicao(Lista *l,int pos){
    if(l == NULL) return -1;
    if(listaVazia(l) == 0) return -2;
    No *n = l->inicio;
    int i = 0;
    while(n != NULL && i < pos){
        n = n->prox;
        i++;
    }
    if(n == NULL) return -3;
    if(n->ant == NULL) return removerInicio(l);
    if(n->prox == NULL) return removerFim(l);
    n->ant->prox = n->prox;
    n->prox->ant = n->ant;
    free(n);
    return 0;
}

int removerItem(Lista *l,int it){
    if(l == NULL) return 1;
    if(listaVazia(l) == 0) return 2;
    No *n = l->inicio;
    int pos = 0;
    while(n != NULL){
        if(n->valor.mat == it){
            removerPosicao(l, pos);
            return 0; // stop after removing the first student
        }
        n = n->prox;
        pos++;
    }
    return 3;
}

int buscarItemChave(Lista *l,int chave,Aluno *retorno){
    if(l == NULL) return -1;
    if(listaVazia(l) == 0) return -1;
    No *n = l->inicio;
    while(n != NULL){
        if(n->valor.mat == chave){
            if(retorno != NULL)
                *retorno = n->valor;
            return 0;
        }
        n = n->prox;
    }
    return -1;
}

int buscarPosicao(Lista *l,int posicao,Aluno *retorno){
    if(l == NULL) return -1;
    if(listaVazia(l) == 0) return -2;
    No *n = l->inicio;
    int i = 0;
    while(n != NULL && i < posicao){
        n = n->prox;
        i++;
    }
    if(n == NULL) return -3;
    *retorno = n->valor;
    return 0;
}

int buscarMaior(Lista *l, Aluno *retorno){
    if(l == NULL) return 1;
    if(listaVazia(l) == 0) return 2;
    *retorno = l->inicio->valor;
    No *n = l->inicio;
    while(n != NULL){
        if(n->valor.n1 > retorno->n1){
            *retorno = n->valor;
        }
        n = n->prox;
    }
    return 0;
}

int limparSem(Lista *l){
    while (listaVazia(l) != 0)
        removerInicio(l);
    return 0;
}

int trocar(Lista *l, int a, int b){
    if(l == NULL) return 1;
    if(listaVazia(l) == 0) return 2;
    if(a < 0 || b < 0) return 3;
    No *aux = l->inicio;
    No *aux2 = l->inicio;
    int i = 0, j = 0;
    while(i < a && aux != NULL){
        aux = aux->prox;
        i++;
    }
    while(j < b && aux2 != NULL){
        aux2 = aux2->prox;
        j++;
    }
    if(aux == NULL || aux2 == NULL) return 4;
    Aluno temp = aux->valor;
    aux->valor = aux2->valor;
    aux2->valor = temp;
    return 0;
}

int iguais(Lista *l, Lista *l2){
    if(l == NULL || l2 == NULL) return -1;
    if(tamanho(l) != tamanho(l2)) return 1;
    No *n = l->inicio;
    while(n != NULL){
        Aluno a;
        if(buscarItemChave(l2, n->valor.mat, &a) != 0) return 1;
        n = n->prox;
    }
    return 0;
}

int remDuplicados(Lista *l){
    if(l == NULL) return 1;
    if(listaVazia(l) == 0) return 2;
    No *atual = l->inicio;
    int pos = 0;
    while (atual != NULL){
        No *varrer = atual->prox;
        int posV = pos + 1;
        while(varrer != NULL){
            if(atual->valor.mat == varrer->valor.mat){
                removerPosicao(l, posV);
            }else{
                posV++;
            }
            varrer = varrer->prox;
        }
        atual = atual->prox;
        pos++;
    }
    return 0;
}
