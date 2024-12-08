/*
 Nome: Raquel Emillene Freire Thomé
 Matrícula: 12311BCC026
 Nome: Vitória Fernandes Costa Silva
 Matrícula: 12311BCC001
 Nome: Luana Larissa de Souza Pessoa
 Matrícula: 12311BCC037
 */

#include "Grafos.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  /*-- Programa principal --*/

  TipoGrafo Grafo, GrafoT;
  TipoValorVertice V1, V2, Adj;
  TipoPeso Peso;
  int opcao;
  char nomeArquivo[100];

  do {
    printf("------------------\n");
    printf("Escolha uma opcao:\n");
    printf("------------------\n");
    printf("1. Ler os dados do grafo a partir de um artigo.\n");
    printf("2. Imprimir o grafo completo.\n");
    printf("3. Inserir uma nova aresta.\n");
    printf("4. Remover uma aresta.\n");
    printf("5. Verificar se existe rodovia entre duas cidades.\n");
    printf("6. Verificar cidades até 100 Km.\n");
    printf("7. Verificar se o grafo é acíclico.\n");
    printf("8. Sair.\n");

    scanf("%d", &opcao);
    switch (opcao) {
    case 1:
      printf("Digite o nome do arquivo a ser lido: \n"
             "50cidades.txt\n"
             "50cidadesaciclico.txt\n"
             "50cidadesciclico.txt\n"
             "");
      scanf("%s", nomeArquivo);
      lerArquivo(&Grafo, nomeArquivo);
      break;
    case 2:
      ImprimeGrafo(&Grafo);
      break;
    case 3:
      printf("Digite o número relacionado a primeira cidade: ");
      scanf("%d", &V1);
      V1--;
      printf("Digite o número relacionado a segunda cidade: ");
      scanf("%d", &V2);
      V2--;
      printf("Digite a distância em km entre as duas cidades: ");
      scanf("%d", &Peso);
      InsereAresta(&V1, &V2, &Peso, &Grafo);
      break;
    case 4:
      printf("Digite o número relacionado a primeira cidade: ");
      scanf("%d", &V1);
      V1--;
      printf("Digite o número relacionado a segunda cidade: ");
      scanf("%d", &V2);
      V2--;
      printf("Digite a distância em km entre as duas cidades: ");
      scanf("%d", &Peso);
      RetiraAresta(&V1, &V2, &Peso, &Grafo);
      break;
    case 5:
      printf("Digite o número relacionado a primeira cidade: ");
      scanf("%d", &V1);
      V1--;
      printf("Digite o número relacionado a segunda cidade: ");
      scanf("%d", &V2);
      V2--;
      int p;
      int t = ExisteAresta(V1, V2, &Grafo, &p);
      if (t) {
        printf("Existe rodovia entre as cidades e a distância é de %dkm\n", p);
      } else {
        printf("\nNão existe rodovia cadastrada entre as duas cidades.\n");
      }
      break;
    case 6:
      printf("Digite o número relacionado a cidade que quer analisar: ");
      scanf("%d", &V1);
      V1--;
      cemKM(V1, &Grafo);
      break;
    case 7:
      break;
    case 8:
      printf("Saindo...\n");
      break;
    default:
      printf("Opcao invalida!\n");
      break;
    }
  } while (opcao != 8);

  return 0;
}