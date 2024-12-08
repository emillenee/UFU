#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

int main(){
    Arvore *a = (Arvore *)malloc(sizeof(Arvore));
    if (a == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a árvore.\n");
        return 1;
    }
    criarArvore(a);

    lerArquivoABB(a, "codigosPostais.txt");

    CodigoP cepPesquisa;
    strcpy(cepPesquisa.cep, "54310-230");
    pesquisar(a->raiz, &cepPesquisa);

    printf("Altura da ABB: %d\n", alturaArvore(a->raiz));
    No *menor = menorArvore(a->raiz);
    No *maior = maiorArvore(a->raiz);
    if (menor != NULL) {
        printf("Menor CEP: \n");
        imprimirCodigoP(&menor->valor);
        printf("\n\n");
    }
    if (maior != NULL) {
        printf("Maior CEP: \n");
        imprimirCodigoP(&maior->valor);
        printf("\n\n");
    }

    printf("Percurso Central:\n");
    percorrerCentral(a->raiz);
    printf("\n\n");
    printf("Percurso Pré-Fixado:\n");
    percorrerPreFixado(a->raiz);
    printf("\n\n");
    printf("Percurso Pós-Fixado:\n");
    percorrerPosFixado(a->raiz);
    printf("\n\n");

    free(a);
    return 0;
}