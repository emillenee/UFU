#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

#define MAX 100

typedef struct numero{
    int num;
}Numero;

typedef struct fila Fila;

Fila *criar();
void limpar(Fila *f);

int inserir(Fila *f, int it);
//int remover(Fila *f, int *it);
int remover(Fila *f);

int consultar(Fila *f, int *it);
int tamanho(Fila *f);

int filaVazia(Fila *f);
int filaCheia(Fila *f);

void mostrar(Fila *f);

#endif // FILA_H_INCLUDED
