#include <stdio.h>
#include <stdlib.h>
#include "conjuntos.h"

typedef struct conj {
    int *nums;
    int tamanho;
}Conj;

Conj* criar(){
    Conj *c = (Conj*) malloc (sizeof(Conj));
    c->nums = NULL;
    c->tamanho = 0;
    return c;
}

void removerIguais(Conj *c){
    for(int i = 0; i < c->tamanho; i++){
        for(int j = i+1; j < c->tamanho;){
            if(c->nums[j] == c->nums[i]){
                for(int k = j; k < c->tamanho - 1; k++){
                    c->nums[k] = c->nums[k+1];
                }
                c->tamanho--;
                c->nums = realloc (c->nums, c->tamanho * sizeof(int));
            }
            else{
                j++;
            }
        }
    }
}

void preencher(Conj *c, int t){
    c->tamanho = t;
    c->nums = (int*) malloc (t*sizeof(int));
    for(int i = 0; i < t; i++){
        scanf("%i", &c->nums[i]);
    }
    removerIguais(c);
}

void mostrar(Conj *c){
    if(c != NULL){
        for(int i = 0; i < c->tamanho; i++){
            printf("%i ", c->nums[i]);
        }
        printf("\n");
    }
}

void inserir(Conj *c, int n){
    c->nums = realloc (c->nums, (c->tamanho + 1) * sizeof(int));
    c->nums[c->tamanho] = n;
    c->tamanho += 1;
    removerIguais(c);
}

void remover(Conj *c, int n){
    for(int i = 0; i < c->tamanho; i++){
        for(int j = i+1; j < c->tamanho;){
            if(c->nums[j] == n){
                for(int k = j; k < c->tamanho - 1; k++){
                    c->nums[k] = c->nums[k+1];
                }
                c->tamanho--;
                c->nums = realloc (c->nums, c->tamanho * sizeof(int));
            }
            else{
                j++;
            }
        }
    }
}

Conj* uniao(Conj *c, Conj *c2){
    Conj *uniao;
    uniao = criar();
    uniao->tamanho = c->tamanho + c2->tamanho;
    uniao->nums = (int*) malloc(uniao->tamanho * sizeof(int));

    for(int i = 0; i < c->tamanho; i++){
        uniao->nums[i] = c->nums[i];
    }

    for(int i = c->tamanho; i < uniao->tamanho; i++){
        uniao->nums[i] = c2->nums[i - c->tamanho];
    }

    removerIguais(uniao);
    return uniao;
}

Conj* interseccao(Conj *c, Conj *c2){
    Conj *inter;
    inter = criar();
    inter->nums = (int*) malloc (inter->tamanho * sizeof(int));

    for(int i = 0; i < c->tamanho; i++){
        for(int j = 0; j < c2->tamanho; j++){
            if(c->nums[i] == c2->nums[j]){
                inter->nums = realloc (inter->nums, (inter->tamanho + 1) * sizeof(int));
                inter->nums[inter->tamanho] = c->nums[i];
                inter->tamanho += 1;
                break;
            }
        }
    }
    return inter;
}

Conj* diferenca(Conj *c, Conj *c2){
    Conj *difer;
    difer = criar();
    difer->nums = (int*) malloc (difer->tamanho * sizeof(int));

    for(int i = 0; i < c->tamanho; i++){
        int rep = 0; //repetição
        for(int j = 0; j < c2->tamanho; j++){
            if(c->nums[i] == c2->nums[j]){
                rep++;
            }
        }
        if(rep == 0){
            difer->nums = realloc (difer->nums, (difer->tamanho + 1) * sizeof(int));
            difer->nums[difer->tamanho] = c->nums[i];
            difer->tamanho += 1;
        }
    }
    return difer;
}
