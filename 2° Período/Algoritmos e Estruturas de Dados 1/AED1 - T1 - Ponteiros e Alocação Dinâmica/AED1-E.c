#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[100];
}Filho;

typedef struct {
    char cpf[12];
    char civil[10];
    Filho *filhos;
    int numFilhos;
} Cliente;

int main()
{
    int numT, n;
    printf("Qual a quantidade total de clientes? \n => ");
    scanf("%d", &numT);
    
    Cliente *clientes = (Cliente*)malloc(numT*sizeof(Cliente));
    
    int op; // Opção
    do{
        printf("Escolha uma opção: \n");
        printf("(1) - Adicionar Cliente \n");
        printf("(2) - Remover Cliente \n");
        printf("(3) - Mostrar Cadastros \n");
        printf("(4) - Sair \n");
        printf(" => ");
        scanf("%d", &op);
        
        if(op == 1){
            
            int c;
            printf("Quantos clientes deseja adicionar? \n => ");
            scanf("%d", &n);
            setbuf(stdin, NULL);
            
            for(int i = 0; i < n; i++){
                printf("Qual o CPF do cliente %i? \n => ", i+1);
                fgets(clientes[i].cpf, sizeof(clientes[i].cpf), stdin);
                
                printf("Qual o estado civil? \n => ");
                fgets(clientes[i].civil, sizeof(clientes[i].civil), stdin);
                
                printf("Qual a quantidade de filhos? \n => ");
                scanf("%i", &clientes[i].numFilhos);
                setbuf(stdin, NULL);
                
                if(clientes[i].numFilhos != 0){
                    clientes[i].filhos = (Filho*)malloc(clientes[i].numFilhos*sizeof(Filho));
                    
                    for(int j = 0; j < clientes[i].numFilhos; j++){
                        printf("Qual o nome do filho %i? \n => ", j+1);
                        fgets(clientes[i].filhos[j].nome, sizeof(clientes[i].filhos[j].nome), stdin);
                    }
                }
                else{
                    printf("Cliente adicionado com sucesso! \n\n");
                }
            }
        }
        else if(op == 2){
            int v;
            printf("Qual o número do cliente que deseja remover? \n");
            scanf("%i", &v);
            v = v-1;
            
            if(v < 0 || v >= n){
                printf("*Cliente não existe* \n");
            }
            else{
                free(clientes[v].filhos);
                
                for(int i = v; i < n-1; i++){
                    clientes[i] = clientes[i+1];
                }
                
                n--;
                
                clientes = (Cliente*)realloc(clientes, n*sizeof(Cliente));
            }
        }
        else if(op == 3){
            printf("Os CPFs cadastrados são: \n\n");
            
            for(int i = 0; i < n; i++){
                printf("Cliente %i \n", i+1);
                
                printf("CPF: %s", clientes[i].cpf);
                printf("Estado Civil: %s", clientes[i].civil);
                
                if(clientes[i].numFilhos != 0){
                    printf("Filhos: \n");
                    for(int j = 0; j < clientes[i].numFilhos; j++){
                        printf("%i) %s", j+1, clientes[i].filhos[j].nome);
                    }
                    printf("\n");
                }
                else{
                    printf("Sem filhos. \n\n");
                }
            }
        }
        
    }while(op != 4);
    
    printf("------- Obrigado por usar nosso sistema! -------\n");
    
    for(int i = 0; i < n; i++){
        free(clientes[i].filhos);
    }
    
    free(clientes);

    printf("\n");
    system("pause");
    return 0;
}