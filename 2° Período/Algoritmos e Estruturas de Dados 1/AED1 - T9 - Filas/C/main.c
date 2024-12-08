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

//LETRA C
int removerNeg(Fila *f){
    if(f == NULL) return 2;
    int valor;
    int qtd = tamanho(f);
    while(qtd > 0){
        removerR(f, &valor);
        if(valor >= 0)
            inserir(f, valor);
        qtd--;
    }
    return 0;
}

int main()
{
    Fila *f = criar();

    inserir(f, -1);
    inserir(f, 2);
    inserir(f, -3);
    inserir(f, 4);
    inserir(f, -5);
    mostrar(f);

    removerNeg(f);
    mostrar(f);

    limpar(f);
    system("pause");
    return 0;
}
