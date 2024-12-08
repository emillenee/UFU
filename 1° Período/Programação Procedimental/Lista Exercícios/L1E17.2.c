#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    double premio = 27000000;
    double aposta = 40;

    double a1 = 20;
    double a2 = 15;
    double a3 = 5;

    double p1 = aposta / a1;
    double v1 = premio / p1;
    printf("O primeiro amigo vai receber: %.2lf\n", v1);

    double p2 = aposta / a2;
    double v2 = premio / p2;
    printf("O primeiro amigo vai receber: %.2lf\n", v2);

    double p3 = aposta / a3;
    double v3 = premio / p3;
    printf("O primeiro amigo vai receber: %.2lf\n", v3);

    return 0;
}
