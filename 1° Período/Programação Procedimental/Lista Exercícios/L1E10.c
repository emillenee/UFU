#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int l;

    printf("Qual o tamanho do lado do quadrado? ");
    scanf("%i", &l);

    int area = pow(l, 2.0);

    printf("A area do quadrado eh: %i\n", area);

    return 0;
}
