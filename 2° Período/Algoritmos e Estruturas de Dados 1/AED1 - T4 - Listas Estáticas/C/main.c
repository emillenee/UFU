#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista.h"

int main()
{
    printf("1 - Conseguindo o tamanho da lista: \n");
    int t = 4;
    printf("Tamanho = %i\n", t);

    Lista *minhaLista = criar(t);
    Aluno a;
    a.mat = 30;
    strcpy(a.nome, "Carlos");
    a.n1 = 3.4;
    inserirInicio(minhaLista, a);
    a.mat = 20;
    strcpy(a.nome, "Ana");
    a.n1 = 10.3;
    inserirInicio(minhaLista, a);
    a.mat = 40;
    strcpy(a.nome, "Jonas");
    a.n1 = 7.0;
    inserirFim(minhaLista, a);
    a.mat = 50;
    strcpy(a.nome, "Beatriz");
    a.n1 = 7.5;
    inserirPosicao(minhaLista, a, 2);
    printf("A lista eh: \n");
    mostrar(minhaLista);

    destruir(minhaLista);
    system("pause");

    return 0;
}
