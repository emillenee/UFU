#include <stdio.h>
#include <stdlib.h>

int main()
{
    //Alocação
    int **m1 = (int**)malloc(3*sizeof(int*));
    int **m2 = (int**)malloc(3*sizeof(int*));
    int **m3 = (int**)malloc(3*sizeof(int*));

    for(int i = 0; i < 3; i++){
        *(m1+i) = (int*)malloc(3*sizeof(int));
        *(m2+i) = (int*)malloc(3*sizeof(int));
        *(m3+i) = (int*)malloc(3*sizeof(int));
    }
    
    if(m1 == NULL || m2 == NULL || m3 == NULL){
        printf("Erro ao alocar\n");
    }
    
    //Preencher as duas matrizes
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            scanf("%d", (*(m1+i)+j));
        }
    }
    
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            scanf("%d", (*(m2+i)+j));
        }
    }
    
    //Soma
    
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            *(*(m3+i)+j) = *(*(m1+i)+j) + *(*(m2+i)+j);
        }
    }
    
    //Imprimir matrizes e liberar memória
    
    printf("Primeira matriz: \n");
    
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            printf("%d ", *(*(m1+i)+j));
        }
        printf("\n");
        free(*(m1+i));
    }
    
    printf("\n");
    printf("Segunda matriz: \n");
    
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            printf("%d ", *(*(m2+i)+j));
        }
        printf("\n");
        free(*(m2+i));
    }
    
    printf("\n");
    printf("Matriz soma: \n");
    
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            printf("%d ", *(*(m3+i)+j));
        }
        printf("\n");
        free(*(m3+i));
    }
    
    printf("\n");
    
    free(m1);
    free(m2);
    free(m3);
    
    printf("\n");
    system("pause");
    return 0;
}