#include <stdio.h>
#include <stdlib.h>

int main()
{
    float n1, n2, n3, n4;

    printf("Digite quatro notas para ser calculada a media aritmetica\n");

    printf("NOTA: ");
    scanf("%f", &n1);

    printf("NOTA: ");
    scanf("%f", &n2);

    printf("NOTA: ");
    scanf("%f", &n3);

    printf("NOTA: ");
    scanf("%f", &n4);

    float media = (n1 + n2 + n3 + n4)/4;

    printf("A media eh: %.1f\n", media);

    return 0;
}
