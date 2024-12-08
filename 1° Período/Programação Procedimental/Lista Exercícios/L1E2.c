#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a, b, c;

    printf("Digite tres numeros inteiros\n");

    printf("Primeiro valor: ");
    scanf("%i", &a);

    printf("Segundo valor: ");
    scanf("%i", &b);

    printf("Terceiro valor: ");
    scanf("%i", &c);

    int soma = a + b + c;

    printf("A soma dos valores eh: %i", soma);

    return 0;
}
