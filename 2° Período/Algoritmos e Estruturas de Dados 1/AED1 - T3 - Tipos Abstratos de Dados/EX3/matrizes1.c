#include <stdio.h>
#include <stdlib.h>
#include "matrizes.h"

typedef struct matriz {
    int linhas;
    int colunas;
    float **dados;
}Matriz;

Matriz* criar(int l, int c){
    Matriz *m = (Matriz*) malloc (sizeof(Matriz));
    if(m == NULL){
        printf("Erro ao alocar a matriz.\n");
        return NULL;
    }

    m->linhas = l;
    m->colunas = c;

    m->dados = (float**) malloc (l * sizeof(float*));

    for(int i = 0; i < l; i++){
        m->dados[i] = (float*) malloc (c * sizeof(float*));
    }

    return m;
}

void destruir(Matriz *m){
    for(int i = 0; i < m->linhas; i++){
        free(m->dados[i]);
    }

    free(m->dados);
    free(m);
}

void atribuir(Matriz *m, int i, int j, float n){
    if(m == NULL){
        printf("--- Matriz nao existe! ---\n");
        return;
    }

    if(i < 0 || i >= m->linhas || j < 0 || j >= m->colunas){
        printf("--- Dimensoes nao compativeis com a matriz! ---");
        return;
    }
    m->dados[i][j] = n;
}

void acessar(Matriz *m, int i, int j){
    printf("%.1f\n", m->dados[i][j]);
}

int numLinhas(Matriz *m){
    return m->linhas;
}

int numColunas(Matriz *m){
    return m->colunas;
}

void mostrarM(Matriz *m){
    for(int i = 0; i < m->linhas; i++){
        for(int j = 0; j < m->colunas; j++){
            printf("%.1f ", m->dados[i][j]);
        }
        printf("\n");
    }
}

Matriz* somar(Matriz *m, Matriz *m2){
    int l, c;
    if(m->linhas > m2->linhas){
        l = m->linhas;
    }
    else{
        l = m2->linhas;
    }

    if(m->colunas > m2->colunas){
        c = m->colunas;
    }
    else{
        c = m2->colunas;
    }

    Matriz *soma;
    soma = criar(l, c);

    for(int i = 0; i < l; i++){
        for(int j = 0; j < c; j++){
            soma->dados[i][j] = m->dados[i][j] + m2->dados[i][j];
        }
    }
    return soma;
}

void preencherAleatorio(Matriz *m, float min, float max){
    for(int i = 0; i < m->linhas; i++){
        for(int j = 0; j < m->colunas; j++){
            float escala = rand() / (float) RAND_MAX;
            m->dados[i][j] = min + escala * (max - min);
        }
    }
}
