#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    double a, b, c;

    printf("Digite tres valores: \n");

    printf("VALOR: ");
    scanf("%lf", &a);

    printf("VALOR: ");
    scanf("%lf", &b);

    printf("VALOR: ");
    scanf("%lf", &c);

    double calc = pow(a, 2.0) + pow(b, 2.0) + pow(c, 2.0);

    printf("A soma dos quadrados eh: %.2lf\n", calc);

    return 0;
}
