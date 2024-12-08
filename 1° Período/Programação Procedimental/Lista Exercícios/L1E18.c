#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    double g, r;
    const double PI = 3.14;

    printf("Qual o angulo em graus? ");
    scanf("%lf", &g);

    r = g * PI / 180;

    printf("Esse angulo equivale a: %.2lf radianos.\n", r);

    return 0;
}
