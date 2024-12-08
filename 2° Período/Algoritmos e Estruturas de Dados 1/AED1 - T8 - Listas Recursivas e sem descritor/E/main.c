#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Lista.h"

int main()
{
    Lista *l = criar();

    //Pedir o numero binario
    char b[50];
    printf("Digite um numero binario: \n");
    scanf("%s", b);

    //Armazena ao contrario na lista
    int t = strlen(b) - 1;
    for (int i = t; i >= 0; i--) {
        adicionar(l, b[i] - '0');
    }

    //Mostra normal
    printf("O numero binario eh: ");
    mostrar(l);

    //Pedir valor a ser somado
    int valor;
    printf("Digite um valor para somar ao binario: \n");
    scanf("%i", &valor);

    //Transformar binário em inteiro
    int inteiro = transforma(l, t);
    printf("Resultado: %i\n", valor + inteiro);

    limpar(l);
    system("pause");
    return 0;
}
