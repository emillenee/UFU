#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, j = 0;
    printf("Qual o tamanho do vetor? \n");
    scanf("%d", &n);
    
    //Alocação
    int *vet = (int*)malloc(n*sizeof(int));
    
    if(vet == NULL){
        printf("Erro ao alocar\n");
    }
    
    //Leitura

    printf("Quais os elementos do vetor? \n");

    for(int i = 0; i < n; i++){
        scanf("%d", vet+i);
    }
    
    //
    
    for(int i = 0; i < n; i++){
        if(*(vet+i) % 2 == 0){
            *(vet+j) = *(vet+i);
            j++;
        }
    }
    
    //Realocação
    
    vet = (int*)realloc(vet, j*sizeof(int));
    
    //Imprimir para verificar
    
    for(int i = 0; i < j; i++){
        printf("%d ", *(vet+i));
    }
    printf("\n");
    
    //Liberar
    free(vet);
    
    printf("\n");
    system("pause");
    return 0;
}