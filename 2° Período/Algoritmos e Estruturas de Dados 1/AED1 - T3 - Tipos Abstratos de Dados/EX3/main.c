#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrizes.h"

int main()
{
    Matriz *m;
    int l, c;
    scanf("%i", &l);
    scanf("%i", &c);
    m = criar(l, c);

    atribuir(m, 2, 2, 5.2);
    acessar(m, 2, 2);

    printf("%i\n", numLinhas(m));
    printf("%i\n", numColunas(m));

    Matriz *m2;
    int l2, c2;
    scanf("%i", &l2);
    scanf("%i", &c2);
    m2 = criar(l2, c2);

    printf("Min e Max: \n");
    float mini, maxi;
    scanf("%f", &mini);
    scanf("%f", &maxi);
    printf("\n");

    srand(time(NULL));

    preencherAleatorio(m, mini, maxi);
    mostrarM(m);
    printf("\n");
    preencherAleatorio(m2, mini, maxi);
    mostrarM(m2);
    printf("\n");

    mostrarM(somar(m, m2));
    printf("\n");

    destruir(m);
    destruir(m2);

    system("pause");
    return 0;
}
