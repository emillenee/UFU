#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    double degrau, altura;

    printf("Qual a altura do degrau em centrimetros? ");
    scanf("%lf", &degrau);

    //transformação de centrimetros para metros
    double hde = degrau / 100;

    printf("Qual a altura total desejada em metros? ");
    scanf("%lf", &altura);

    double q = altura / hde;

    printf("A quantidade de degraus necessaria eh: %.2lf\n", q);

    return 0;
}
