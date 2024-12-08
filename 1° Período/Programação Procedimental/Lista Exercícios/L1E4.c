#include <stdio.h>
#include <stdlib.h>

int main()
{
    double reais, dolar;

    printf("Qual o valor em reais? ");
    scanf("%lf", &reais);

    printf("Qual a cotacao do dolar? ");
    scanf("%lf", &dolar);

    double conversao = reais * dolar;

    printf("O valor em reais corresponde a: %.2lf em dolares.\n", conversao);

    return 0;
}
