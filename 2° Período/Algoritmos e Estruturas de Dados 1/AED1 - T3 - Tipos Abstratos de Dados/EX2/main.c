#include <stdio.h>
#include <stdlib.h>
#include "conjuntos.h"

int main(){

    Conj *a;
    a = criar();
    int ta;
    printf("Digite o tamanho do conjunto: \n");
    scanf("%i", &ta);
    preencher(a, ta);
    mostrar(a);

    int i;
    printf("Qual numero deseja inserir? \n");
    scanf("%i", &i);
    inserir(a, i);
    mostrar(a);

    int r;
    printf("Qual numero deseja remover? \n");
    scanf("%i", &r);
    remover(a, r);
    mostrar(a);

    Conj *b;
    b = criar();
    int tb;
    printf("Digite o tamanho do conjunto: \n");
    scanf("%i", &tb);
    preencher(b, tb);
    mostrar(b);

    printf("A uniao eh: \n");
    mostrar(uniao(a, b));
    printf("A interseccao eh: \n");
    mostrar(interseccao(a, b));
    printf("A diferenca eh: \n");
    mostrar(diferenca(a, b));

    free(a);
    free(b);
    system("pause");
    return 0;
}
