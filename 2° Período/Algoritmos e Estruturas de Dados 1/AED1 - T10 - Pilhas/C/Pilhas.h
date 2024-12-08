#ifndef PILHAS_H_INCLUDED
#define PILHAS_H_INCLUDED

#define MAX 100
typedef struct caractere{
    char c;
}Caractere;

typedef struct pilha Pilha;

Pilha *criar();
void limpar(Pilha *p);

int push(Pilha *p, Caractere it);
int pop(Pilha *p, Caractere *it);
int consultar(Pilha *p, Caractere *it);
int tamanho(Pilha *p);
int pilhaVazia(Pilha *p);
int pilhaCheia(Pilha *p);

void mostrar(Pilha *p);

int iguais(Pilha *p1, Pilha *p2);

int valida(char *exp);

#endif // PILHAS_H_INCLUDED
