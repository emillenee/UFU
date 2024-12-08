#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

typedef struct no{
    int valor;
    struct no* prox;
}No;

typedef struct no* Lista;

Lista *criar();
void limpar(Lista *l);

int adicionar(Lista *l, int it);
int removerInicio(Lista *l);

void mostrar(Lista *l);

int transforma(Lista *l, int t);

void somar(Lista *l);

#endif // LISTA_H_INCLUDED
