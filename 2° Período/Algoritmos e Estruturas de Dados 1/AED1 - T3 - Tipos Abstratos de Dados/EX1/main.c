#include "strings.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    String *a;
    a = criar();
    preencher(a);
    printf("%i\n", tamanho(a));
    char c;
    printf("Qual a letra?\n");
    scanf("%c", &c);
    printf("A letra aparece %i vezes.\n", contar(a, c));
    mostrar(a);
    free(a);
    system("pause");
    return 0;
}
