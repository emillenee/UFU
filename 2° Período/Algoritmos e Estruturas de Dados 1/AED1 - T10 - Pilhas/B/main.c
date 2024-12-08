#include <stdio.h>
#include <stdlib.h>
#include "Pilhas.h"

int main(){

    Pilha *p1 = criar();
    Pilha *p2 = criar();
    Numero n;

    n.num = 11;
    push(p1, n);
    n.num = 22;
    push(p1, n);
    n.num = 33;
    push(p1, n);
    mostrar(p1);

    n.num = 11;
    push(p2, n);
    n.num = 22;
    push(p2, n);
    n.num = 33;
    push(p2, n);
    mostrar(p2);

    int resultado = iguais(p1, p2);
    if (resultado == 0) {
        printf("As pilhas sao iguais \n");
    } else {
        printf("As pilhas sao diferentes \n");
    }

    limpar(p1);
    limpar(p2);

    system("pause");
    return 0;
}
