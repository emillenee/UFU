#include <stdio.h>
#include <stdlib.h>
#include "Pilhas.h"

int main(){

    char exp[100];
    scanf("%s", exp);

    int resultado = valida(exp);
    if(resultado == 0)
        printf("Valida \n");
    else
        printf("Nao eh valida \n");

    system("pause");
    return 0;
}
