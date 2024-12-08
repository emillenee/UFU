/*
 Nome: Raquel Emillene Freire Thomé
 Matrícula: 12311BCC026
 Nome: Vitória Fernandes Costa Silva
 Matrícula: 12311BCC001
 Nome: Luana Larissa de Souza Pessoa
 Matrícula: 12311BCC037
 */

// Códigos baseados nos slides e nas aulas

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Função Ordenação BubleSort

void bubbleSort(int a[], int n, int *t, int *comp) {
  int temp;
  int troca;
  for (int i = 0; i <= n; i++) {
    troca = 0;
    for (int j = 0; j < n - i - 1; j++) {
      (*comp)++;
      if (a[j] > a[j + 1]) {
        temp = a[j];
        a[j] = a[j + 1];
        a[j + 1] = temp;
        troca = 1;
        (*t)++;
      }
    }
    if (troca == 0)
      return;
  }
}

// Função Ordenação selectionSort

void selectionSort(int a[], int n, int *t, int *comp) {
  int temp;
  int menor;
  for (int i = 0; i < n - 1; i++) {
    menor = i;
    for (int j = i + 1; j < n; j++) {
      if (a[j] < a[menor]) {
        menor = j;
      } 
      (*comp)++;
    }
    if (menor != i) {
      temp = a[i];
      a[i] = a[menor];
      a[menor] = temp;
      (*t)++;
    }
  }
}

// Código adaptado da função de ordenação do slide

void insertionSort(int vet[], int n, int *t, int *comp) {
  int i, j, tmp;
  for (i = 1; i < n; i++) {
    tmp = vet[i];
    for (j = i - 1; j >= 0; j--) {
      (*comp)++;
      if (vet[j] > tmp) {
        (*comp)++;
        vet[j + 1] = vet[j];
        (*t)++;
      } else {
        break;
      }
    }
    vet[j + 1] = tmp;
  }
}

// Função Ordenação ShellSort

void shellSort(int vetor[], int n, int *t, int *comp) {
  int i, j, h = 1;
  int aux;
  do {
    h = h * 3 + 1;
  } while (h < n);
  do {
    h /= 3;
    for (i = h; i < n; i++) {
      aux = vetor[i];
      j = i;
      while (j >= h && vetor[j - h] > aux) {
        (*comp)++;
        vetor[j] = vetor[j - h];
        j -= h;
        (*t)++;
      }
      (*comp)++;
      vetor[j] = aux;
    }
  } while (h > 1);
}

/*FUNÇÃO PARA IMPRIMIR TABELA*/

void imprimirTabela(double tempo_ord, int t_ord, int comp, double tempo_inv,
                    int t_inv, int comp2, double tempo_ale, int t_ale,
                    int comp3, const char *nomeAlgoritmo) {
  printf("\n\nTabela de Resultados para %s\n", nomeAlgoritmo);
  printf("+--------------------------------------------------------------------"
         "-------------------------+\n");
  printf("| Entrada                             | Tempo (s)      | Nro Trocas  "
         "  | Nro comparacoes      |\n");
  printf("+--------------------------------------------------------------------"
         "-------------------------+\n");
  printf(
      "| 10000 números inteiros ordenados    | %-15f| %-13d |%-14d        |\n",
      tempo_ord, t_ord, comp);
  printf(
      "| 10000 números inteiros decrescentes | %-15f| %-13d |%-14d        |\n",
      tempo_inv, t_inv, comp2);
  printf(
      "| 10000 números inteiros aleatorios   | %-15f| %-13d |%-14d        |\n",
      tempo_ale, t_ale, comp3);
  printf("+--------------------------------------------------------------------"
         "-------------------------+\n");
}

int main() {
  int n = 10000;

  // Vetor ordenado
  int *ord = NULL;
  for (int i = 0; i < n; i++) {
    ord = (int *)realloc(ord, ((i + 1) * sizeof(int)));
    ord[i] = i;
  }

  // Vetor inverso
  int *inv = NULL;
  for (int i = 0; i < n; i++) {
    inv = (int *)realloc(inv, ((i + 1) * sizeof(int)));
    inv[i] = n - i;
  }

  // Vetor aleatório
  int *alea = NULL;
  srand(time(NULL));
  for (int i = 0; i < n; i++) {
    alea = (int *)realloc(alea, ((i + 1) * sizeof(int)));
    alea[i] = rand() % 500;
  }

  // Vetor temporário
  int *temp = NULL;

  time_t ini;
  time_t fim;

  // tempos do bubbleSort

  // vetor ordenado
  double tempo_ord_bub;
  int t_ord_bub = 0;
  int c_ord_bub = 0;

  ini = clock();
  bubbleSort(ord, n, &t_ord_bub, &c_ord_bub);
  fim = clock();

  tempo_ord_bub = (double)(fim - ini) / CLOCKS_PER_SEC;

  // vetor descrecente
  double tempo_inv_bub;
  int t_inv_bub = 0;
  int c_inv_bub = 0;

  temp = (int *)malloc(n * sizeof(int));

  // copiando vetor descresente para vetor temporário que será ordenado:
  for (int i = 0; i < n; i++) {
    temp[i] = inv[i];
  }

  ini = clock();
  bubbleSort(temp, n, &t_inv_bub, &c_inv_bub);
  fim = clock();

  free(temp);

  tempo_inv_bub = (double)(fim - ini) / CLOCKS_PER_SEC;

  // vetor aleatório

  double tempo_ale_bub;
  int t_ale_bub = 0;
  int c_ale_bub = 0;

  temp = (int *)malloc(n * sizeof(int));

  // copiando vetor aleatório para vetor temporário que será ordenado:
  for (int i = 0; i < n; i++) {
    temp[i] = alea[i];
  }

  ini = clock();
  bubbleSort(temp, n, &t_ale_bub, &c_ale_bub);
  fim = clock();

  free(temp);

  tempo_ale_bub = (double)(fim - ini) / CLOCKS_PER_SEC;

  /*FUNÇÃO PARA IMPRIMIR TABELA DO BUBBLESORT*/

  imprimirTabela(tempo_ord_bub, t_ord_bub, c_ord_bub, tempo_inv_bub, t_inv_bub,
                 c_inv_bub, tempo_ale_bub, t_ale_bub, c_ale_bub, "Bubble Sort");

  // tempos de SelectionSort

  // vetor ordenado
  double tempo_ord_sel;
  int t_ord_sel = 0;
  int c_ord_sel = 0;

  ini = clock();
  selectionSort(ord, n, &t_ord_sel, &c_ord_sel);
  fim = clock();

  tempo_ord_sel = (double)(fim - ini) / CLOCKS_PER_SEC;

  // vetor decrescente
  double tempo_inv_sel;
  int t_inv_sel = 0;
  int c_inv_sel = 0;

  temp = (int *)malloc(n * sizeof(int));

  // copiando vetor decrescente para vetor temporário que será ordenado:
  for (int i = 0; i < n; i++) {
    temp[i] = inv[i];
  }

  ini = clock();
  selectionSort(temp, n, &t_inv_sel, &c_inv_sel);
  fim = clock();

  free(temp);

  tempo_inv_sel = (double)(fim - ini) / CLOCKS_PER_SEC;

  // vetor aleatório

  double tempo_ale_sel;
  int t_ale_sel = 0;
  int c_ale_sel = 0;

  temp = (int *)malloc(n * sizeof(int));

  // copiando vetor aleatório para vetor temporário que será ordenado:
  for (int i = 0; i < n; i++) {
    temp[i] = alea[i];
  }

  ini = clock();
  selectionSort(temp, n, &t_ale_sel, &c_ale_sel);
  fim = clock();

  free(temp);

  tempo_ale_sel = (double)(fim - ini) / CLOCKS_PER_SEC;

  /*FUNÇÃO IMPRIMIR TABELA*/

  imprimirTabela(tempo_ord_sel, t_ord_sel, c_ord_sel, tempo_inv_sel, t_inv_sel,
                 c_inv_sel, tempo_ale_sel, t_ale_sel, c_ale_sel,
                 "Selection Sort");

  // tempos de InsertionSort

  // vetor ordenado
  double tempo_ord_ins;
  int t_ord_ins = 0;
  int c_ord_ins = 0;

  ini = clock();
  insertionSort(ord, n, &t_ord_ins, &c_ord_ins);
  fim = clock();

  tempo_ord_ins = (double)(fim - ini) / CLOCKS_PER_SEC;

  // vetor descrecente
  double tempo_inv_ins;
  int t_inv_ins = 0;
  int c_inv_ins = 0;

  temp = (int *)malloc(n * sizeof(int));

  // copiando vetor descresente para vetor temporário que será ordenado:
  for (int i = 0; i < n; i++) {
    temp[i] = inv[i];
  }

  ini = clock();
  insertionSort(temp, n, &t_inv_ins, &c_inv_ins);
  fim = clock();

  free(temp);

  tempo_inv_ins = (double)(fim - ini) / CLOCKS_PER_SEC;

  // vetor aleatório

  double tempo_ale_ins;
  int t_ale_ins = 0;
  int c_ale_ins = 0;

  temp = (int *)malloc(n * sizeof(int));

  // copiando vetor aleatório para vetor temporário que será ordenado:
  for (int i = 0; i < n; i++) {
    temp[i] = alea[i];
  }

  ini = clock();
  insertionSort(temp, n, &t_ale_ins, &c_ale_ins);
  fim = clock();

  free(temp);

  tempo_ale_ins = (double)(fim - ini) / CLOCKS_PER_SEC;

  /*TABELA INSERTIONSORT*/

  imprimirTabela(tempo_ord_ins, t_ord_ins, c_ord_ins, tempo_inv_ins, t_inv_ins,
                 c_inv_ins, tempo_ale_ins, t_ale_ins, c_ale_ins,
                 "Insertion Sort");

  // tempos de ShellSort

  // vetor ordenado
  double tempo_ord_she;
  int t_ord_she = 0;
  int c_ord_she = 0;

  ini = clock();
  shellSort(ord, n, &t_ord_she, &c_ord_she);
  fim = clock();

  tempo_ord_she = (double)(fim - ini) / CLOCKS_PER_SEC;

  // vetor decrescente
  double tempo_inv_she;
  int t_inv_she = 0;
  int c_inv_she = 0;

  temp = (int *)malloc(n * sizeof(int));

  // copiando vetor decrescente para vetor temporário que será ordenado:
  for (int i = 0; i < n; i++) {
    temp[i] = inv[i];
  }

  ini = clock();
  shellSort(temp, n, &t_inv_she, &c_inv_she);
  fim = clock();

  free(temp);

  tempo_inv_she = (double)(fim - ini) / CLOCKS_PER_SEC;

  // vetor aleatório

  double tempo_ale_she;
  int t_ale_she = 0;
  int c_ale_she = 0;

  temp = (int *)malloc(n * sizeof(int));

  // copiando vetor aleatório para vetor temporário que será ordenado:
  for (int i = 0; i < n; i++) {
    temp[i] = alea[i];
  }

  ini = clock();
  shellSort(temp, n, &t_ale_she, &c_ale_she);
  fim = clock();

  free(temp);

  tempo_ale_she = (double)(fim - ini) / CLOCKS_PER_SEC;

  /*TABELA SHELLSORT*/

  imprimirTabela(tempo_ord_she, t_ord_she, c_ord_she, tempo_inv_she, t_inv_she,
                 c_inv_she, tempo_ale_she, t_ale_she, c_ale_she, "Shell Sort");

  // liberando memória alocada dinamicamente
  free(ord);
  free(inv);
  free(alea);

  return 0;
}