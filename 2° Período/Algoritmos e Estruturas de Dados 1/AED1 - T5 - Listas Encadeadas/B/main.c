#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista.h"

int main()
{
    Lista *l1 = criar();
    Lista *l2 = criar();

    Aluno a;
    a.mat = 1;
    a.n1 = 7.2;
    strcpy(a.nome, "Paulo");

    Aluno b;
    b.mat = 2;
    b.n1 = 4.2;
    strcpy(b.nome, "Andre");

    Aluno c;
    c.mat = 3;
    c.n1 = 1.4;
    strcpy(c.nome, "Ana");

    Aluno d;
    d.mat = 4;
    d.n1 = 3.9;
    strcpy(d.nome, "Rodrigo");

    Aluno e;
    e.mat = 5;
    e.n1 = 9.1;
    strcpy(e.nome, "Vitoria");

    printf("Inserir aluno %s no inicio da lista 1:\n", a.nome);
    inserirInicio(l1, a);
    mostrar(l1);

    printf("\nInserir aluno %s no inicio da lista 1:\n", b.nome);
    inserirInicio(l1, b);
    mostrar(l1);

    printf("\nInserir aluno %s na posicao 1 da lista 1:\n", c.nome);
    inserirPosicao(l1, c, 1);
    mostrar(l1);

    printf("\nInserir aluno %s no fim da lista 1:\n", d.nome);
    inserirFim(l1, d);
    mostrar(l1);

    printf("\nInserir aluno %s no fim da lista 1:\n", e.nome);
    inserirFim(l1, e);
    mostrar(l1);

    printf("\nRemover posicao 2 da lista 1:\n");
    removerPosicao(l1, 2);
    mostrar(l1);

    printf("\nRemover inicio da lista 1:\n");
    removerInicio(l1);
    mostrar(l1);

    printf("\nRemover fim da lista 1:\n");
    removerFim(l1);
    mostrar(l1);

    printf("\nRemover aluno %s da lista 1:\n", c.nome);
    removerItem(l1, c);
    mostrar(l1);

    printf("\nInserir aluno %s no inicio da lista 1:\n", a.nome);
    inserirInicio(l1, a);
    mostrar(l1);

    printf("\nPreenchendo lista 2:\n ");
    inserirInicio(l2, b);
    inserirInicio(l2, c);
    inserirInicio(l2, e);
    mostrar(l2);

    printf("\nConcatenar lista 1 e lista 2: \n");
    Lista *concatenada = concatena(l1, l2);
    mostrar(concatenada);

    limpar(l1);
    limpar(l2);
    limpar(concatenada);

    system("pause");
    return 0;
}
