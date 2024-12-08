#include <stdio.h>
#include <stdlib.h>

int main()
{
    int inteiro;
    float real;

    printf("Digite um numero inteiro: ");
    scanf("%i", &inteiro);
    printf("O numero inteiro lido eh: %i\n", inteiro);

    printf("Digite um numero real: ");
    scanf("%f", &real);
    printf("O numero real lido eh: %f\n", real);

    return 0;
}
