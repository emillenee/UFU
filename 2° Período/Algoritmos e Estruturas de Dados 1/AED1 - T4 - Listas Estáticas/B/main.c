#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista.h"

int main()
{
    Lista *minhaLista = criar();
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

    printf("1 - Conferindo se a lista contem Ana: \n");
    if(contemItem(minhaLista, 20) == 0){
        printf("Contem\n");
    }
    else printf("Não contem\n");

    printf("2 - A lista reversa eh: \n");
    Lista *rev = criar();
    reversa(minhaLista, rev);
    mostrar(rev);

    printf("3 - Ana aparece: \n");
    printf("%i vez(es)\n", contaItem(minhaLista, 20));

    free(minhaLista);
    system("pause");
    return 0;
}
