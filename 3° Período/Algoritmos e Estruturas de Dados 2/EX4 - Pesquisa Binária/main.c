#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PesquisaB.h"

int main(){
    Cep ceps[5];
    lerArquivo(ceps, "cepCidades.txt");
    ceps[5].numero[0] = '\0';
    imprimirCidades(ceps);
    return 0;
}