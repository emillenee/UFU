#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *vet;
    vet = (int*)malloc(5*sizeof(int));
    
    if(vet == NULL){
        printf("Erro ao alocar\n");
    }

    printf("Digite os 5 valores: \n");

    for(int i=0; i<5; i++){
        scanf("%d", vet+i);
    }

    printf("O vetor eh: \n");

    for(int i=0; i<5; i++){
        printf("%d ", *(vet+i));
    }

    free(vet);

    printf("\n");
    system("pause");
    return 0;
}