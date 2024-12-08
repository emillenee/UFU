#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"

typedef struct lista {
    int total;
    int tamanho;
    Aluno *valores;
}Lista;

Lista *criar(){
    Lista *l = (Lista*)malloc(sizeof(Lista));
    if(l != NULL){
        l->total = 0;
        l->valores = NULL;
    }
    return l;
}

void limpar(Lista *l){
    if(l != NULL){
        l->total = 0;
    }
}

void destruir(Lista *l){
    if(l != NULL){
        free(l->valores);
        free(l);
    }
}

int inserirInicio(Lista *l, Aluno it){
    if(l == NULL) return 2;
    Aluno *temp = (Aluno*)realloc(l->valores, (l->total+1) * sizeof(Aluno));
    if(temp == NULL) return 1;
    l->valores = temp;

    for(int i = l->total; i>0; i--){
        l->valores[i] = l->valores[i-1];
    }
    l->valores[0] = it;
    l->total++;
    return 0;
}

int inserirFim(Lista *l, Aluno it) {
    if (l == NULL) return 2;
    Aluno *temp = (Aluno*)realloc(l->valores, (l->total+1) * sizeof(Aluno));
    if(temp == NULL) return 1;
    l->valores = temp;
    l->valores[l->total] = it;
    l->total++;
    return 0;
}

int inserirPosicao(Lista *l, Aluno it, int pos){
    if(l == NULL) return 2;
    if(pos <= 0 || pos >= l->total) return 3;
    Aluno *temp = (Aluno*)realloc(l->valores, (l->total+1) * sizeof(Aluno));
    if(temp == NULL) return 1;
    l->valores = temp;
    for(int i = l->total; i>=pos; i--){
        l->valores[i] = l->valores[i-1];
    }
    l->valores[pos-1] = it;
    l->total++;
    return 0;
}

int removerInicio(Lista *l){
    if(l == NULL) return 2;
    if(listaVazia(l) == 0) return 1;
    for(int i = 0; i<l->total-1; i++){
        l->valores[i] = l->valores[i+1];
    }
    Aluno *temp = (Aluno*)realloc(l->valores, (l->total-1) * sizeof(Aluno));
    if(temp == NULL) return 1;
    l->valores = temp;
    l->total--;
    return 0;
}

int removerFim(Lista *l){
    if(l == NULL) return 2;
    if(listaVazia(l) == 0) return 1;
    Aluno *temp = (Aluno*)realloc(l->valores, (l->total-1) * sizeof(Aluno));
    if(temp == NULL) return 1;
    l->valores = temp;
    l->total--;
    return 0;
}

int removerPosicao(Lista *l,int pos){
    if(l == NULL) return 2;
    if(listaVazia(l) == 0) return 1;
    if(pos <= 0 || pos > l->total) return 3;

    for(int i = pos-1; i < l->total-1; i++){
        l->valores[i] = l->valores[i+1];
    }

    Aluno *temp = (Aluno*)realloc(l->valores, (l->total-1) * sizeof(Aluno));
    if(temp == NULL) return 1;
    l->valores = temp;
    l->total--;
    return 0;
}

int removerItem(Lista *l, int chave){
    if(l == NULL) return 2;
    if(listaVazia(l) == 0) return 1;
    for(int i = 0; i < l->total; i++){
        if(l->valores[i].mat == chave){
            removerPosicao(l, i+1);
            i--;
        }
    }
    return 0;
}

int buscarItemChave(Lista *l, int chave, Aluno *retorno){
    if(l == NULL) return 2;
    if(listaVazia(l) == 0) return 1;
    for(int i = 0; i<l->total; i++){
        if(l->valores[i].mat == chave){
            *retorno = l->valores[i];
            return 0;
        }
    }
    return -1;
}

int buscarPosicao(Lista *l, int pos, Aluno *retorno){
    if(l == NULL) return 2;
    if(listaVazia(l) == 0) return 1;
    if(pos <= 0 || pos > l->tamanho) return 3;
    *retorno = l->valores[pos-1];
    return 0;
}

int listaVazia(Lista *l){
    if(l == NULL) return 2;
    if(l->total == 0) return 0;
    else return 1;
}

int listaCheia(Lista *l){
    if(l == NULL) return 2;
    if(l->total == l->tamanho) return 0;
    else return 1;
}

int tamanho(Lista *l){
    if(l == NULL) return 2;
    return (l->total);
}

void mostrar(Lista *l){
    if(l != NULL){
        printf("[");
        for(int i = 0; i<l->total; i++){
            printf(" {%d, ",l->valores[i].mat);
            printf("%s, ",l->valores[i].nome);
            printf("%.2f} ",l->valores[i].n1);
        }
        printf("]\n");
    }
}

int contemItem(Lista *l, int chave){
    if(l == NULL) return 2;
    if(listaVazia(l) == 0) return 3;
    for(int i = 0; i < l->total; i++){
        if(l->valores[i].mat == chave){
            return 0;
        }
    }
    return 1;
}

int reversa(Lista *l, Lista *r){
    if(l == NULL) return 2;
    if(listaVazia(l) == 0) return 3;
    r->total = l->total;
    r->valores = (Aluno*)realloc(r->valores, (r->total) * sizeof(Aluno));
    int j = 0;
    for(int i = l->total-1; i >= 0; i--){
        r->valores[j] = l->valores[i];
        j++;
    }
    return 0;
}

int contaItem(Lista *l, int chave){
    if(l == NULL) return -1;
    int cont = 0;
    for(int i = 0; i < l->total; i++){
        if(l->valores[i].mat == chave){
            cont++;
        }
    }
    return cont;
}
