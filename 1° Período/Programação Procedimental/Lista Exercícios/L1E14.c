#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    double diaria = 30.00;
    int dias;

    printf("Qual a quantidade de dias trabalhados pelo encanador? ");
    scanf("%i", &dias);

    double total = diaria * dias;
    double desc = total * 0.075;
    double liq = total - desc;

    printf("A quantia liquida a ser paga eh: %.2lf\n", liq);

    return 0;
}
