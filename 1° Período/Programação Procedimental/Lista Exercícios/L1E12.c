#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    double valor;

    printf("Qual o valor do produto? ");
    scanf("%lf", &valor);

    double desc = valor * 0.15;

    double novovalor = valor - desc;

    printf("O valor do produto com desconto eh: %.2lf\n", novovalor);

    return 0;
}
