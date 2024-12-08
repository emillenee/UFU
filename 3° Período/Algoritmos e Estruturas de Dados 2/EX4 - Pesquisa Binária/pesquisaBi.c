#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PesquisaB.h"

int buscaBinaria(Cep ceps[], int n, Cep busca){
    
}

void lerArquivo(Cep *ceps, const char *nomeArquivo){
    FILE *arquivo = fopen(nomeArquivo, "r");
    if(arquivo == NULL){
        perror("Erro ao abrir arquivo");
        return;
    }

    int linhas = 0;
    char ch;
    while (!feof(arquivo)) {
        ch = fgetc(arquivo);
        if (ch == '\n') {
            linhas++;
        }
    }

    for(int i = 0; i < linhas; i++){
        fscanf(arquivo, "%s %s %s %[^\n]", ceps[i].numero, ceps[i].sigla,
        ceps[i].nome, ceps[i].endereco);
    }

    fclose(arquivo);
}

void imprimirCidades(Cep ceps[]){
    int i = 0;
    while(ceps[i].numero[0] != '0'){
        printf("Nome: %s\n", ceps[i].nome);
        printf("Número: %s\n", ceps[i].numero);
        printf("Sigla: %s\n", ceps[i].sigla);
        printf("Endereço: %s\n", ceps[i].endereco);
        printf("-------------------------\n");
        i++;
    }
}