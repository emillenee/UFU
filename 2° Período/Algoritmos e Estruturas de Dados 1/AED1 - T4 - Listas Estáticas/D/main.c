#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista.h"

int main()
{
    printf("1 - Criando a lista: \n");
    Lista *minhaLista = criar();
    mostrar(minhaLista);
    Aluno a;
    a.mat = 30;
    strcpy(a.nome, "Carlos");
    a.n1 = 3.4;
    printf("2 - Inserindo do inicio: \n");
    inserirInicio(minhaLista, a);
    mostrar(minhaLista);
    a.mat = 20;
    strcpy(a.nome, "Ana");
    a.n1 = 10.3;
    printf("3 - Inserindo no inicio: \n");
    inserirInicio(minhaLista, a);
    mostrar(minhaLista);
    a.mat = 40;
    strcpy(a.nome, "Jonas");
    a.n1 = 7.0;
    printf("4 - Inserindo no fim: \n");
    inserirFim(minhaLista, a);
    mostrar(minhaLista);
    a.mat = 50;
    strcpy(a.nome, "Beatriz");
    a.n1 = 7.5;
    printf("5 - Inserindo na segunda posicao: \n");
    inserirPosicao(minhaLista, a, 2);
    mostrar(minhaLista);

    printf("\n Depois de remover o aluno eh adicionado novamente para manter a lista completa \n\n");
    printf("6 - Removendo o inicio: \n");
    removerInicio(minhaLista);
    mostrar(minhaLista);

    //inserindo novamente:
    a.mat = 20;
    strcpy(a.nome, "Ana");
    a.n1 = 10.3;
    inserirInicio(minhaLista, a);

    printf("7 - Removendo o fim: \n");
    removerFim(minhaLista);
    mostrar(minhaLista);

    //inserindo novamente:
    a.mat = 40;
    strcpy(a.nome, "Jonas");
    a.n1 = 7.0;
    inserirFim(minhaLista, a);

    printf("8 - Removendo da segunda posicao: \n");
    removerPosicao(minhaLista, 2);
    mostrar(minhaLista);

    //inserindo novamente:
    a.mat = 50;
    strcpy(a.nome, "Beatriz");
    a.n1 = 7.5;
    inserirPosicao(minhaLista, a, 2);

    printf("8 - Removendo item de matricula 50: \n");
    removerItem(minhaLista, 50);
    mostrar(minhaLista);

    //inserindo novamente:
    a.mat = 50;
    strcpy(a.nome, "Beatriz");
    a.n1 = 7.5;
    inserirPosicao(minhaLista, a, 2);

    Aluno r;
    printf("9 - Buscando item de matricula 20: \n");
    buscarItemChave(minhaLista, 20, &r);
    printf("O aluno eh: ");
    printf(" {%d, ",r.mat);
    printf("%s, ",r.nome);
    printf("%.2f}\n",r.n1);

    printf("10 - Buscando posicao 3: \n");
    buscarPosicao(minhaLista, 3, &r);
    printf("O aluno eh: ");
    printf(" {%d, ",r.mat);
    printf("%s, ",r.nome);
    printf("%.2f}\n",r.n1);

    printf("11 - Conferindo se a lista contem Ana: \n");
    if(contemItem(minhaLista, 20) == 0){
        printf("Contem\n");
    }
    else printf("Não contem\n");

    printf("12 - A lista reversa eh: \n");
    Lista *rev = criar();
    reversa(minhaLista, rev);
    mostrar(rev);

    printf("13 - Ana aparece: \n");
    printf("%i vez(es)\n", contaItem(minhaLista, 20));

    destruir(minhaLista);
    system("pause");
    return 0;
}
