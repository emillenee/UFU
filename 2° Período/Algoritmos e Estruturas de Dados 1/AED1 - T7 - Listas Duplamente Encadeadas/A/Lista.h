#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

typedef struct aluno{
    int mat;
    char nome[30];
    float n1;
}Aluno;

typedef struct no No;
typedef struct lista Lista;

Lista *criar();
void limpar(Lista *l);

int inserirInicio(Lista *l,Aluno it);
int inserirFim(Lista *l,Aluno it);
int inserirPosicao(Lista *l,Aluno it,int pos);

int removerInicio(Lista *l);
int removerFim(Lista *l);
int removerPosicao(Lista *l,int pos);
int removerItem(Lista *l,int it);

int buscarItemChave(Lista *l,int chave,Aluno *retorno);
int buscarPosicao(Lista *l,int posicao,Aluno *retorno);

int listaVazia(Lista *l);
int listaCheia(Lista *l);
int tamanho(Lista *l);
void mostrar(Lista *l);

int limparSem(Lista *l);
int buscarMaior(Lista *l, Aluno *retorno);

int trocar(Lista *l, int a, int b);
int iguais(Lista *l, Lista *l2);
int remDuplicados(Lista *l);

#endif // LISTA_H_INCLUDED
