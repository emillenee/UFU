#ifndef CONJUNTOS_H_INCLUDED
#define CONJUNTOS_H_INCLUDED

typedef struct conj Conj;

Conj* criar();

void removerIguais(Conj *c);

void preencher(Conj *c, int t);

void inserir(Conj *c, int n);

void remover(Conj *c, int n);

Conj* uniao(Conj *c, Conj *c2);

Conj* interseccao(Conj *c, Conj *c2);

Conj* diferenca(Conj *c, Conj *c2);

void mostrar(Conj *c);

#endif // CONJUNTOS_H_INCLUDED
