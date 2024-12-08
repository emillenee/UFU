/*
 Nome: Raquel Emillene Freire Thomé
 Matrícula: 12311BCC026
 Nome: Vitória Fernandes Costa Silva
 Matrícula: 12311BCC001
 Nome: Luana Larissa de Souza Pessoa
 Matrícula: 12311BCC037
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Códigos baseados nos slides e nas aulas

typedef struct atleta
{
    char nome[30];
    char nacionalidade[30];
    int medalhas;
    float premiacao;
} Atleta;

// LETRA A -> Ordem crescente de premiação
void bubbleSort(Atleta a[], int n)
{
    Atleta temp;
    int troca;
    for (int i = 0; i <= n; i++)
    {
        troca = 0;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (a[j].premiacao > a[j + 1].premiacao)
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                troca = 1;
            }
        }
        if (troca == 0)
            return;
    }
}

void selectionSort(Atleta a[], int n)
{
    Atleta temp;
    int menor;
    for (int i = 0; i < n - 1; i++)
    {
        menor = i;
        for (int j = i + 1; j < n; j++)
        {
            if (a[j].premiacao < a[menor].premiacao)
            {
                menor = j;
            }
        }
        if (menor != i)
        {
            temp = a[i];
            a[i] = a[menor];
            a[menor] = temp;
        }
    }
}

// LETRA B -> Ordem decrescente de medalhas
void bubbleDecres(Atleta a[], int n)
{
    Atleta temp;
    int troca;
    for (int i = 0; i <= n; i++)
    {
        troca = 0;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (a[j].medalhas < a[j + 1].medalhas)
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                troca = 1;
            }
        }
        if (troca == 0)
            return;
    }
}

void selectionDecres(Atleta a[], int n)
{
    Atleta temp;
    int maior;
    for (int i = 0; i < n - 1; i++)
    {
        maior = i;
        for (int j = i + 1; j <= n - 1; j++)
        {
            if (a[j].medalhas > a[maior].medalhas)
            {
                maior = j;
            }
        }
        if (a[maior].medalhas > a[i].medalhas)
        {
            temp = a[i];
            a[i] = a[maior];
            a[maior] = temp;
        }
    }
}

// LETRA C -> Ordem alfabética
void bubbleAlfabetic(Atleta a[], int n)
{
    Atleta temp;
    int troca;
    for (int i = 0; i <= n; i++)
    {
        troca = 0;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (strcmp(a[j].nome, a[j + 1].nome) > 0)
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                troca = 1;
            }
        }
        if (troca == 0)
            return;
    }
}

void selectionAlfabetic(Atleta a[], int n)
{
    Atleta temp;
    int menor;
    for (int i = 0; i < n - 1; i++)
    {
        menor = i;
        for (int j = i + 1; j <= n - 1; j++)
        {
            if (strcmp(a[j].nome, a[menor].nome) < 0)
            {
                menor = j;
            }
        }
        if (strcmp(a[menor].nome, a[i].nome) < 0)
        {
            temp = a[i];
            a[i] = a[menor];
            a[menor] = temp;
        }
    }
}

// Função que imprime o vetor
void mostrar(Atleta a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("{ Nome: %s, Nacionalidade: %s, Qtd de medalhas: %d, Premiacao: %.2f }\n",
               a[i].nome, a[i].nacionalidade, a[i].medalhas, a[i].premiacao);
    }
}

// Função que lê os dados do arquivo .txt
void lerArquivo(Atleta a[], int n)
{
    FILE *arquivo = fopen("atletas.txt", "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo");
        return;
    }
    for (int i = 0; i < n; i++)
    {
        fscanf(arquivo, "%[^,],%[^,],%d,%f\n", a[i].nome, a[i].nacionalidade, &a[i].medalhas, &a[i].premiacao);
    }
    fclose(arquivo);
}

int main()
{

    int n = 10;
    Atleta atletas[n];

    int OP = 0;
    do
    {
        printf("---------------------------------------\n");
        printf("Escolha como ler os dados dos atletas:\n");
        printf("1. Direto do arquivo .txt\n");
        printf("2. Digitar manualmente\n");
        printf("---------------------------------------\n");

        scanf("%d", &OP);
        if (OP == 1)
        {
            lerArquivo(atletas, n);
        }
        else if (OP == 2)
        {
            for (int i = 0; i < n; i++)
            {
                printf("Digite o nome do atleta %d: ", i + 1);
                scanf("%s", atletas[i].nome);
                printf("Digite a nacionalidade do atleta %d: ", i + 1);
                scanf("%s", atletas[i].nacionalidade);
                printf("Digite a quantidade de medalhas do atleta %d: ", i + 1);
                scanf("%d", &atletas[i].medalhas);
                printf("Digite a premiacao do atleta %d: ", i + 1);
                scanf("%f", &atletas[i].premiacao);
            }
        }
        else
        {
            printf("Opcao invalida!\n");
        }
    } while (OP != 1 && OP != 2);

    printf("A lista de atletas eh:\n\n");
    mostrar(atletas, n);
    printf("\n");

    int opcao = 0;
    int subOP, subOP2, subOP3;

    do
    {
        printf("------------------\n");
        printf("Escolha uma opcao:\n");
        printf("------------------\n");
        printf("1. Crescente de premiacao\n");
        printf("2. Decrescente de medalhas\n");
        printf("3. Ordem alfabetica\n");
        printf("4. Sair\n");

        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            printf("Escolha o metodo:\n");
            printf("1. Bubble Sort\n");
            printf("2. Selection Sort\n");
            scanf("%d", &subOP);
            if (subOP == 1)
            {
                bubbleSort(atletas, n);
                mostrar(atletas, n);
                printf("\n");
            }
            else if (subOP == 2)
            {
                selectionSort(atletas, n);
                mostrar(atletas, n);
                printf("\n");
            }
            else
            {
                printf("Opcao invalida!\n\n");
            }
            break;
        case 2:
            printf("Escolha o metodo:\n");
            printf("1. Bubble Sort\n");
            printf("2. Selection Sort\n");
            scanf("%d", &subOP2);
            if (subOP2 == 1)
            {
                bubbleDecres(atletas, n);
                mostrar(atletas, n);
                printf("\n");
            }
            else if (subOP2 == 2)
            {
                selectionDecres(atletas, n);
                mostrar(atletas, n);
                printf("\n");
            }
            else
            {
                printf("Opcao invalida!\n\n");
            }
            break;
        case 3:
            printf("Escolha o metodo:\n");
            printf("1. Bubble Sort\n");
            printf("2. Selection Sort\n");
            scanf("%d", &subOP3);
            if (subOP3 == 1)
            {
                bubbleAlfabetic(atletas, n);
                mostrar(atletas, n);
                printf("\n");
            }
            else if (subOP3 == 2)
            {
                selectionAlfabetic(atletas, n);
                mostrar(atletas, n);
                printf("\n");
            }
            else
            {
                printf("Opcao invalida!\n\n");
            }
            break;
        case 4:
            printf("Saindo do programa...\n\n");
            break;
        default:
            printf("Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 4);
    return 0;
}