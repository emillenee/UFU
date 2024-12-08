#include <stdio.h>
#include <stdlib.h>
#include "Fila.h"

int main()
{
    Fila *f = criar();

    inserir(f, 10);
    mostrar(f);

    inserir(f, 20);
    mostrar(f);

    remover(f);
    mostrar(f);

    inserir(f, 30);
    mostrar(f);

    inserir(f, 45);
    mostrar(f);

    inserir(f, 21);
    mostrar(f);

    remover(f);
    mostrar(f);

    remover(f);
    mostrar(f);

    limpar(f);
    system("pause");
    return 0;
}
