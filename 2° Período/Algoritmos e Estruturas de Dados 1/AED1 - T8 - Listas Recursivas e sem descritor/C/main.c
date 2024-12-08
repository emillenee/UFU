#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"

int main()
{
    Lista *l = criar();
    inserirInicio(l, 72);
    inserirFim(l, 2);
    inserirPosicao(l, 15, 2);
    inserirFim(l, 8);
    inserirFim(l, 53);
    mostrar(l);

    printf("\nReversa: \n");
    mostrarReversa(l);
    printf("\n");

    limpar(l);
    system("pause");
    return 0;
}
