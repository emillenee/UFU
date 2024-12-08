#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a, b;
    printf("Quais as dimensões da matriz?\n");
    scanf("%d %d", &a, &b);
    
    //Alocação
    int **m = (int**)malloc(a*sizeof(int*));
    
    for(int i = 0; i < a; i++){
        *(m+i) = (int*)malloc(b*sizeof(int));
    }
    
    if(m == NULL){
        printf("Erro ao alocar\n");
    }
    
    //Vetor medias
    double *md = (double*)malloc(a*sizeof(double));
    
    //Preencher e calcular as medias

    printf("Digite os elementos da matriz: \n");

    for(int i = 0; i < a; i++){
        int soma = 0;
        for(int j = 0; j < b; j++){
            scanf("%d", (*(m+i)+j));
            soma += *(*(m+i)+j);
        }
        *(md+i) = soma/(b*1.0);
    }
    
    //
    
    for(int i = 0; i < a; i++){
        for(int j = 0; j < b; j++){
           printf("%.2lf ", *(*(m+i)+j) - *(md+i));
        }
        printf("\n");
    }
    
    //Liberar
    for(int i = 0; i < a; i++){
        free(*(m+i));
    }
    
    free(m);
    
    printf("\n");
    system("pause");
    return 0;
}