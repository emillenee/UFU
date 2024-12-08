#include <stdio.h>
#include <stdlib.h>
#include "Pilhas.h"

int main()
{
    Pilha *p = criar();
    Numero n;

    n.num = 11;
    push(p, n);
    mostrar(p);

    n.num = 34;
    push(p, n);
    mostrar(p);

    pop(p, &n);
    mostrar(p);

    pop(p, &n);
    mostrar(p);

    n.num = 23;
    push(p, n);
    mostrar(p);

    n.num = 45;
    push(p, n);
    mostrar(p);

    pop(p, &n);
    mostrar(p);

    n.num = 121;
    push(p, n);
    mostrar(p);

    n.num = 22;
    push(p, n);
    mostrar(p);

    pop(p, &n);
    mostrar(p);

    limpar(p);
    system("pause");
    return 0;
}
