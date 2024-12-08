#include <stdio.h>
#include <stdlib.h>
#include "Fila.h"

//LETRA B
Fila *intercalar(Fila *f1, Fila *f2){
    if(f1 == NULL) return f2;
    if(f2 == NULL) return f1;
    Fila *ret = criar();
    int valor;
    while(filaVazia(f1) != 0 || filaVazia(f2) != 0){
        if(removerR(f1, &valor) == 0)
            inserir(ret, valor);
        if(removerR(f2, &valor) == 0)
            inserir(ret, valor);
    }
    return ret;
}

int main()
{
    Fila *f1 = criar();
    Fila *f2 = criar();

    inserir(f1, 1);
    inserir(f1, 3);
    inserir(f1, 5);
    mostrar(f1);

    inserir(f2, 2);
    inserir(f2, 4);
    inserir(f2, 6);
    mostrar(f2);

    Fila *inter = intercalar(f1, f2);
    mostrar(inter);

    limpar(f1);
    limpar(f2);
    limpar(inter);

    system("pause");
    return 0;
}
