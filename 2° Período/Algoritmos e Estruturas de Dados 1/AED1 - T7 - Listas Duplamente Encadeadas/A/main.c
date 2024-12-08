#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"

int main()
{
    int op = 0;
    Lista *al = criar();
    while(op != 6){
        printf("Escolha uma opcao:\n");
        printf("1) Cadastrar aluno\n");
        printf("2) Remover aluno\n");
        printf("3) Listar alunos cadastrados\n");
        printf("4) Mostrar aluno com maior nota\n");
        printf("5) Remover todos os alunos\n");
        printf("6) Sair\n");
        scanf("%i", &op);
        switch(op){
            case 1:{
                Aluno a;
                printf("Qual a matricula?\n");
                scanf("%i", &a.mat);
                printf("Qual o nome?\n");
                scanf("%s", a.nome);
                printf("Qual a nota?\n");
                scanf("%f", &a.n1);
                inserirFim(al, a);
                break;
            }
            case 2:{
                int chave;
                printf("Qual a matricula do aluno que deseja remover?\n");
                scanf("%i", &chave);
                removerItem(al, chave);
                break;
            }
            case 3:{
                mostrar(al);
                break;
            }
            case 4:{
                Aluno r;
                buscarMaior(al, &r);
                printf("[ {%d, ", r.mat);
                printf("%s, ", r.nome);
                printf("%.2f ]\n} ", r.n1);
                break;
            }
            case 5:{
                limparSem(al); //sem excluir lista
                break;
            }
            case 6:{
                printf("Saindo...\n");
                break;
            }
            default:{
                printf("Opcao invalida. Tente novamente.\n");
            }
        }
    }
    limpar(al);
    return 0;
}
