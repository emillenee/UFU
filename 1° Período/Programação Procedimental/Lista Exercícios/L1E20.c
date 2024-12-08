#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int idade, atual;

    printf("Qual o ano atual? ");
    scanf("%i", &atual);

    printf("Qual a sua idade? ");
    scanf("%i", &idade);

    int nasc = atual - idade;

    printf("O ano de nascimento eh: %i\n", nasc);

    return 0;
}
