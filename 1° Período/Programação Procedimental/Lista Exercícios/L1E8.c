#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;

    printf("Digite um numero: ");
    scanf("%i", &n);

    int ant = n - 1;

    printf("O antecessor eh: %i\n", ant);

    int suc = n + 1;

    printf("O sucessor eh: %i\n", suc);

    return 0;
}
