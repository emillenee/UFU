#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"

int main()
{
    Lista *l = criar();
    Aluno a1 = {1, "Joao", 8.5};
    Aluno a2 = {2, "Maria", 9.0};
    Aluno a3 = {3, "Pedro", 7.5};
    inserirFim(l, a1);
    inserirFim(l, a2);
    inserirFim(l, a3);
    inserirFim(l, a1);
    inserirFim(l, a2);
    printf("Lista antes de remover os duplicados:\n");
    mostrar(l);
    int resultado = remDuplicados(l);
    if(resultado == 0) {
        printf("Duplicados removidos com sucesso!\n");
    } else {
        printf("Erro ao remover duplicados!\n");
    }
    printf("Lista apos remover os duplicados:\n");
    mostrar(l);
    limpar(l);
    system("pause");
    return 0;
}
