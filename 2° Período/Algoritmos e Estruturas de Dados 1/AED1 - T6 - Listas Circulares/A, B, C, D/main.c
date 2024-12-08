#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista.h"

int main()
{
    Lista *l1 = criar();
    Aluno a,b,c,d,e,f, retorno;
    a.mat = 1;
    strcpy(a.nome, "Cleber");
    a.n1 = 5;

    b.mat = 2;
    strcpy(b.nome, "Dostoievski");
    b.n1 = 8;

    c.mat = 3;
    strcpy(c.nome, "Kenio");
    c.n1 = 7;

    d.mat = 4;
    strcpy(d.nome, "Darques");
    d.n1 = 10;

    e.mat = 5;
    strcpy(e.nome, "Cassandra Clare");
    e.n1 = 6;

    f.mat = 6;
    strcpy(f.nome, "Quezia");
    f.n1 = 5.9;

    printf("Lista 1: ");
    inserirInicio(l1, a);
    inserirFim(l1, b);
    inserirFim(l1, d);
    inserirPosicao(l1, c, 1);
    mostrar(l1);

    printf("Busca aluno de matricula 2 em L1:\n");
    buscarItemChave(l1, 2, &retorno);
    printf("Aluno: %s\nMatricula: %d\nNota: %.2f\n\n", retorno.nome, retorno.mat, retorno.n1);

    printf("Remover elemento da posicao central de L1:\n");
    removerCentral(l1);
    mostrar(l1);

    printf("Remove primeira ocorrencia da matricula 2 em L1\n");
    removerItem(l1, b);
    mostrar(l1);
    printf("\n");

    Lista *l2 = criar();
    printf("Lista 2: ");
    inserirInicio(l2, c);
    inserirFim(l2, a);
    inserirFim(l2, f);
    inserirPosicao(l2, d, 1);
    mostrar(l2);
    printf("\n");

    printf("Interseccao das listas 1 e 2:\n");
    Lista *jun = interseccao(l1, l2);
    mostrar(jun);

    limpar(l1);
    limpar(l2);
    limpar(jun);

    system("pause");
    return 0;
}
