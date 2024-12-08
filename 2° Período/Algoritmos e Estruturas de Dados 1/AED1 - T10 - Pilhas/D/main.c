#include <stdio.h>
#include <stdlib.h>
#include "Pilhas.h"

int main()
{
    int num;
    printf("Escreva um decimal: ");
    scanf("%d", &num);

    Pilha *p = criar();

    binarioP(p, num);

    printf("O numero binario eh: [");

    while (pilhaVazia(p) != 0){
        Caractere n;
        pop(p, &n);
        printf(" %c ", n.c);
    }
    printf("]\n");

    limpar(p);

    system("pause");
    return 0;
}
