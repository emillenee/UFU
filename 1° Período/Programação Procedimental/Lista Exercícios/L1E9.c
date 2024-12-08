#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int n;

    printf("Digite um numero: ");
    scanf("%i", &n);

    int tri = n * 3;
    int suc = tri + 1;

    int dd = n * 2;
    int ant = dd - 1;

    int calc = suc + ant;

    printf("O resultado do calculo eh: %i\n", calc);

    return 0;
}
