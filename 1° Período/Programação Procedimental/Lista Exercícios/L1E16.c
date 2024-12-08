#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    double seg;

    printf("Qual a quantidade de segundos? ");
    scanf("%lf", &seg);

    double minutos = seg / 60;
    double horas = minutos / 60;

    printf("HORAS: %.1lf\n", horas);
    printf("MINUTOS: %.0lf\n", minutos);
    printf("SEGUNDOS: %.0lf\n", seg);

    return 0;
}
