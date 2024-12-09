#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Polinomio.h"

typedef struct nop Nop;

typedef struct polinomio{  
    int idem;
    struct no *inicio; 
}Polinomio;

typedef struct termo{
    long int coeficiente;
    long int grau;
}Termo;

typedef struct lista Lista; 

Lista *criar();

int inserirInicio(Lista *l, Polinomio *it);
int inserirFim(Lista *l, Polinomio *it);
int inserirPosicao(struct lista *l, struct polinomio *it,int pos);
int removerInicio(Lista *l);
int removerFim(Lista *l);
int removerPosicao(Lista *l,int pos);
int removerItem(struct lista *l,int it);
int buscarItemChave(Lista *l,int chave,struct polinomio *retorno);
int buscarPosicao(struct lista *l,int posicao,struct polinomio *retorno);
int listaVazia(Lista *l);
int listaCheia(Lista *l);
void limpar( Lista *l);
int tamanho(Lista *l);
void mostrar(Lista *l);


