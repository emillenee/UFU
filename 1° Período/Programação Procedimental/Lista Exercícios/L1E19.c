#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    double c, l;

    printf("Qual o comprimento do terreno? ");
    scanf("%lf", &c);

    printf("Qual a largura do terreno? ");
    scanf("%lf", &l);

    double perimetro = c * 2 + l * 2;

    double p;

    printf("Qual o preco do arame? ");
    scanf("%lf", &p);

    double custo = perimetro * 5 * p;

    printf("O custo para certar o terreno sera: %.2lf\n", custo);

    return 0;
}
