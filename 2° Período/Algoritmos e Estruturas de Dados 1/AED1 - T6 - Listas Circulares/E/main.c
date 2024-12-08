#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "ListaNum.h"

int main()
{
    Lista *l = criar();

    for (int i = 1; i <= 20; i++) {
        Num v;
        v.n = i;
        inserirFim(l, v);
    }

    printf("Lista original:\n");
    mostrar(l);

    Lista *par = criar();
    Lista *impar = criar();

    numeros(l, par, impar);
    printf("Numeros pares:\n");
    mostrar(par);
    printf("Numeros impares:\n");
    mostrar(impar);

    limpar(l);
    limpar(par);
    limpar(impar);
    system("pause");
    return 0;
}
