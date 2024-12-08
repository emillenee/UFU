#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

typedef struct no{
    int valor;
    struct no* prox;
}No;

typedef struct no* Lista;

Lista *criar();
void limpar(Lista *l);

int inserirInicio(Lista * l, int it);
int inserirFim(Lista *l, int i);
int inserirPosicao(Lista *l, int it, int pos);

int removerInicio(Lista *l);
int removerFim(Lista *l);
int removerPosicao(Lista *l, int pos);
int removerItem(Lista *l, int it);

int buscarPosicao(Lista *l, int it, int *retorno);

int listaVazia(Lista *l);
int listaCheia(Lista *l);

int tamanho(Lista *l);
void mostrar(Lista *l);

int ultimo(Lista *l, int *retorno);
int soma(Lista *l);
void mostrarReversa(Lista *l);
void removerRecorrencias(Lista *l, int it);

#endif // LISTA_H_INCLUDED
