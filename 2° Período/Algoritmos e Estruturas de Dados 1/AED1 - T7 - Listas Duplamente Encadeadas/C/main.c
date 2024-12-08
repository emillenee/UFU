#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"

int main()
{
    Lista *l1 = criar();
    Lista *l2 = criar();
    Lista *l3 = criar();
    Aluno a1 = {1, "Joao", 8.5};
    Aluno a2 = {2, "Maria", 9.0};
    Aluno a3 = {3, "Pedro", 7.5};
    Aluno a4 = {4, "Ana", 8.0};
    inserirFim(l1, a1);
    inserirFim(l1, a2);
    inserirFim(l1, a3);
    inserirFim(l2, a1);
    inserirFim(l2, a2);
    inserirFim(l2, a3);
    inserirFim(l3, a1);
    inserirFim(l3, a2);
    inserirFim(l3, a4);
    printf("Lista 1:\n");
    mostrar(l1);
    printf("Lista 2:\n");
    mostrar(l2);
    printf("Lista 3:\n");
    mostrar(l3);
    int resultado = iguais(l1, l2);
    if(resultado == 0) {
        printf("As duas primeiras listas sao iguais!\n");
    } else {
        printf("As duas primeiras listas sao diferentes!\n");
    }
    resultado = iguais(l1, l3);
    if(resultado == 0) {
        printf("A primeira e a terceira lista sao iguais!\n");
    } else {
        printf("A primeira e a terceira lista sao diferentes!\n");
    }
    limpar(l1);
    limpar(l2);
    limpar(l3);
    system("pause");
    return 0;
}
