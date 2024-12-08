#include <stdio.h>
#include <stdlib.h>

int main()
{
    double ms;

    printf("Qual a velocidade em m/s? ");
    scanf("%lf", &ms);

    double kh = ms * 3.6;

    printf("A velocidade em k/h eh: %.2lf\n", kh);

    return 0;
}
