#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    double salario;

    printf("Qual o salario atual? ");
    scanf("%lf", &salario);

    double aumento = salario * 0.25;

    double novosalario = salario + aumento;

    printf("O salario com aumento de 25 por cento eh: %.2lf\n", novosalario);

    return 0;
}
