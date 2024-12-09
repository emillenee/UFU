#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct no No;

typedef struct termo Termo;

typedef struct polinomio Polinomio;

Polinomio *policriar();
int poliinserirInicio(struct polinomio *l,  struct termo it);
int poliinserirFim(Polinomio *l,  Termo it);
int poliinserirPosicao(struct polinomio *l,struct termo it, int pos);
int poliremoverInicio(Polinomio *l);
int poliremoverFim(Polinomio *l);
int poliremoverPosicao(Polinomio *l,int pos);
int poliremoverItem(Polinomio *l, Termo it);
int polibuscarItemChave(Polinomio *l,int chave,  Termo *retorno);
int polibuscarPosicao(struct polinomio *l,int posicao,struct termo *retorno);
int PolinomioVazio(Polinomio *l);
int politamanho(Polinomio *l);
void polimostrar(Polinomio *l);
int auxmostrar(No *l, int verif);

void polilimpar(Polinomio *p);

int poliCalcular(struct polinomio *p, int x, long int *retorno);
int poliIncrementa(Polinomio *p, Termo it);
int poliInserirTermo(Polinomio *p, Termo it);
int poliRemoverTermo(Polinomio *p, Termo it);
Polinomio* geraCopia(Polinomio *p);
Polinomio* somaPolinomios(Polinomio *p1, Polinomio *p2);