#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaPoli.h"
#include "Polinomio.h"


typedef struct polinomio Polinomio;

typedef struct no {
    Termo valor; 
    struct no *prox;
}No;

Polinomio *policriar() {
    Polinomio *l = ( Polinomio*)malloc(sizeof( Polinomio));
    l->inicio = NULL;
    return l;
}


int polilistaVazia( Polinomio *l){
    if (l == NULL)
        return 2;
    if (l->inicio == NULL)
        return 0;
    return 1;
}

int polilistaCheia( Polinomio *l){
    if (l == NULL) return 2;
    else return 1;
}

int polilistaCheia2( Polinomio *l){
    return 0;
}


int poliinserirInicio( Polinomio *l,  Termo it){
    if (l == NULL) return 2;
    if (polilistaCheia(l)== 0) return 1;
    No *n = (No*)malloc(sizeof(No));
    n->valor = it;
    n->prox = l->inicio;
    l->inicio = n;
    return 0;
}

int poliinserirFim( Polinomio *l, Termo it){
    if (l == NULL) return 2;
    if (polilistaVazia(l) == 0) return poliinserirInicio(l,it);
    No *n = l->inicio;
    while (n->prox != NULL)
    n = n->prox;
    No *n1 = (No*)malloc(sizeof(No));
    n1->valor = it;
    n->prox = n1;
    n1->prox = NULL;
    return 0;
}

int poliinserirPosicao( struct polinomio *l,struct termo it,int pos){
    if (l == NULL) return 2;
    if (pos < 0) return 3;
    if ((polilistaVazia(l) == 0)||(pos == 0))
        return poliinserirInicio(l,it);
    No *n = l->inicio;
    int p = 1;
    while ((n->prox != NULL)&&(p != pos)) {
        p++;
        n = n->prox;
    }
    No *n1 = (No*)malloc(sizeof(No));
    n1->valor = it;
    n1->prox = n->prox;
    n->prox = n1;
    return 0;
}

int poliremoverInicio( Polinomio *l){
    if (l == NULL) return 2;
    if (polilistaVazia(l) == 0) return 1;
    No *n = l->inicio;
    l->inicio = n->prox;
    free(n);
    return 0;
}

int poliremoverFim( Polinomio *l){
    if (l == NULL) return 2;
    if (polilistaVazia(l) == 0) return 1;
    No *noAuxiliar = NULL;
    No *noLista = l->inicio;
    while (noLista->prox != NULL) {
        noAuxiliar = noLista;
        noLista = noLista->prox;
    }
    if (noAuxiliar == NULL) l->inicio = NULL;
    else noAuxiliar->prox = NULL;
    free(noLista);
    return 0;
}

int poliremoverPosicao( Polinomio *l,int pos){
    if (l == NULL) return 2;
    if (polilistaVazia(l) == 0) return 1;
    if (pos == 0) return poliremoverInicio(l);
    No *n = l->inicio;
    for (int i = 1; i < pos; i++){
        n = n->prox;
    } 
    No *n2 = n->prox;
    n->prox = n->prox->prox;
    free(n2);
}


int poliRemoverTermo(Polinomio *p, Termo it){
    No *no = p->inicio;
    No *ant = NULL;
    while (no != NULL && no->valor.grau < it.grau){
        ant = no;
        no = no->prox;
    }
    if (no != NULL && no->valor.grau == it.grau){
        if (ant == NULL){
            p->inicio = no->prox;
        } else {
            ant->prox = no->prox;
        }
        free(no);
        return 0;
    }
    return -1;
}

int poliremoverItem( Polinomio *l, Termo it){
    if (l == NULL) return 2;
    if (polilistaVazia(l) == 0) return 1;
    No *n = l->inicio;
    int cont = 0;
    if (n->valor.grau == it.grau) return poliremoverInicio(l);

    while(n->prox!= NULL){
        n = n->prox;
        cont ++;
        if (n->valor.grau == it.grau){
            poliremoverPosicao(l, cont);
            cont --;
            return 0;
        }
    }
    return -1;
}


int polibuscarItemChave( Polinomio *l, int chave, Termo *retorno){
    if (l == NULL) return 2;
    No *noLista = l->inicio;
    while ((noLista != NULL)) {
    if ((noLista->valor).grau == chave) {
        *retorno = noLista->valor;
        return 0;
    }
    noLista = noLista->prox;
    }
    return 1;
}
int polibuscarPosicao( struct polinomio *l, int posicao, struct termo *retorno){
    if(l == NULL) return 2;
    if(polilistaVazia(l)== 0) return 1;
    int i = 0;
    No *n = l->inicio;
    for( i=1; i<posicao && n->prox; i++){
        n = n->prox;
    }
    if (i<posicao) return 3;
    *retorno = n->valor;
    return 0;
}

int poliContemItem( Polinomio *l, Termo it){
    if(l == NULL) return 2;
    if(polilistaVazia(l) == 0) return 3;
    No *n = l->inicio;
    while(n != NULL){
        if(n->valor.grau == it.grau){
            return 0;
        }
        n = n->prox;
    }
}

int politamanho( Polinomio *l){
    if(l == NULL) return 2;
    int cont = 0;
    No *n = l->inicio;
    while(n != NULL){
        cont++;
        n = n->prox;
    }
    return cont;
}

void polimostrar( Polinomio *l){
    if (l != NULL) {
    printf("[ ");
    No *noLista = l->inicio;
    auxmostrar(noLista,0);
    printf("]\n");
   }
}
int auxmostrar(No *l,int verif){
    if(l == NULL) return 0;
    auxmostrar(l->prox, 1);
    printf("%ld",l->valor.coeficiente);
    printf("X^");
    printf("%ld ",l->valor.grau);
    
    if (verif != 0)printf("+ ");
    return 0;
}

void polilimpar( Polinomio *l) {
    while (polilistaVazia(l) != 0)
    poliremoverInicio(l);
}


int poliCalcular(struct polinomio *p, int x, long int *retorno){
    if(p == NULL) return -1;
    if(p->inicio == NULL) return -1;
    struct no *n = p->inicio;
    *retorno = 0;
    while (n!=NULL){
        *retorno = *retorno + pow(x, (n->valor).grau) * (n->valor).coeficiente;
        n = n->prox;
    } 
        return 0;
}

int poliInserirTermo(Polinomio *p, Termo it){
    No *no = p->inicio;
    No *ant = NULL;
    while (no != NULL && no->valor.grau < it.grau){
        ant = no;
        no = no->prox;
    }
    No *novo = malloc(sizeof(No));
    novo->valor = it;
    novo->prox = no;
    if (ant == NULL){
        p->inicio = novo;
    } else {
        ant->prox = novo;
    }
    return 0;
}


int poliIncrementa(Polinomio *p, Termo it){
    No *no = p->inicio;
    while (no->valor.grau != it.grau){
        no = no->prox;
    }
    no = no->prox;
    while(no != NULL){
        no->valor.grau++;
        no = no->prox;
    }
    return 0;
}


Polinomio *geraCopia(Polinomio *p){
    Polinomio *copia = policriar();
    No *no = p->inicio;
    Termo cpy;
    while (no != NULL){
        cpy = no->valor;
        poliInserirTermo(copia, cpy);
        no = no->prox;
    }
    return copia;
}


//Versão que busca grau primeiro e vê se os polinomios o possuem
Polinomio* somaPolinomios(Polinomio *p1, Polinomio *p2){
    int i;
    Polinomio *soma = policriar();
    No *n1 = p1->inicio;
    No *n2 = p2->inicio;
    No *maior, *menor;


    while (n1 != NULL || n2 != NULL){
        if(n1 != NULL && n2 != NULL){
            if(n1->valor.grau > n2->valor.grau){
                menor = n2;	
            }else{
                menor = n1;
            } 
        } else if(n1 != NULL){
            menor = n1;
        } else menor = n2;
        
        i = menor->valor.grau;
        
        //loop que percorre todos os graus até o tamanho max
        Termo t1, t2; //Para armazenar os valores(se existirem) dos termos de ambos os poli com aquele grau
        t1.coeficiente = 0;
        t2.coeficiente = 0;
        long int coeficienteSoma = 0;

        if (polibuscarItemChave(p1, i, &t1) == 0) {
            coeficienteSoma += t1.coeficiente; //se o poli 1 tiver aquele grau então o seu coeficiente é somado
        }
        if (polibuscarItemChave(p2, i, &t2) == 0) {
            coeficienteSoma += t2.coeficiente; //mesma coisa soq com o poli 2
        }
        //se a soma dos t1 e t2 for diferente de 0, então cria um novo termo que vai ser add no poli soma
        if (coeficienteSoma != 0) {
            Termo novo;
            novo.grau = i; //grau atual
            novo.coeficiente = coeficienteSoma;
            if(polibuscarItemChave(soma, novo.grau, &t1) != 0){
                poliInserirTermo(soma, novo);
            }
            if(menor == n1){
                n1 = n1->prox;
            }else n2 = n2->prox;
        }
      
    }
    return soma;

}