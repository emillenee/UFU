#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    double ca, co;

    printf("Qual o valor do cateto adjacente? ");
    scanf("%lf", &ca);

    printf("Qual o valor do cateto oposto? ");
    scanf("%lf", &co);

    double hip = sqrt(pow(ca, 2.0) + pow(co, 2.0));

    printf("A hipotenusa desse triangulo eh: %.1lf\n", hip);

    return 0;
}
