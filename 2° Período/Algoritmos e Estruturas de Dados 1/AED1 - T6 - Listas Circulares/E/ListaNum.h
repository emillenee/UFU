#ifndef LISTANUM_H_INCLUDED
#define LISTANUM_H_INCLUDED

typedef struct num{
    int n;
}Num;

typedef struct lista Lista;

Lista *criar();

void limpar(Lista *l);

int listaVazia(Lista *l);
int listaCheia(Lista *l);
int tamanho(Lista *l);
void mostrar(Lista *l);

int inserirFim(Lista *l, Num it);
int removerInicio(Lista *l);

int numeros(Lista *l, Lista *par, Lista *impar);

#endif // LISTANUM_H_INCLUDED
