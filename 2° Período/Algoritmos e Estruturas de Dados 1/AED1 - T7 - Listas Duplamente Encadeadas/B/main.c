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
    printf("Lista antes da troca:\n");
    mostrar(l);
    int resultado = trocar(l, 0, 2);
    if(resultado == 0) {
        printf("Troca realizada com sucesso!\n");
    } else {
        printf("Erro na troca!\n");
    }
    printf("Lista apos a troca:\n");
    mostrar(l);
    limpar(l);
    system("pause");
    return 0;
}
