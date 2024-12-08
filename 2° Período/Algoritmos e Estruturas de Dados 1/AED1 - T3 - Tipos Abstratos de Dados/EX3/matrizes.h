#ifndef MATRIZES_H_INCLUDED
#define MATRIZES_H_INCLUDED

typedef struct matriz Matriz;

Matriz* criar(int i, int j);

void destruir(Matriz *m);

void atribuir(Matriz *m, int i, int j, float n);

void acessar(Matriz *m, int i, int j);

int numLinhas(Matriz *m);

int numColunas(Matriz *m);

void preencherAleatorio(Matriz *m, float min, float max);

Matriz* somar(Matriz *m, Matriz *m2);

void mostrarM(Matriz *m);

#endif // MATRIZES_H_INCLUDED
