#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a;

    printf("Digite um numero inteiro: ");
    scanf("%i", &a);

    int square = a * a;

    printf("O quadrado do valor digitado eh: %i\n", square);

    return 0;
}
