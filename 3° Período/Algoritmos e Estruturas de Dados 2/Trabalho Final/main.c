#include "arvoreAVL.h"
#include "arvoreBinaria.h"
#include "buscaBinaria.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void maiusculas(char *palavra) {
  for (int i = 0; palavra[i]; i++) {
    palavra[i] = toupper(palavra[i]);
  }
}

int lerInfoPesquisa() {
  int funOp;
  do {
    printf("\nDeseja pesquisar por qual informacao?\n");
    printf("1. Estado\n");
    printf("2. Cidade\n");
    printf("3. Numero do partido\n");
    printf("4. Voltar.\n");
    scanf("%d", &funOp);
    getchar();
  } while (funOp < 1 || funOp > 4);
  return funOp;
}

void lerFiltroPesquisa(int *op1, int *op2, char *gen, int *opGen, char *part,
                       char *rc) {
  do {
    printf("\nGostaria de ordenar a busca por genero, partido ou raca/cor? \n1 "
           "- Sim \n2 - Nao\n");
    scanf("%d", op1);
    getchar();
    while (*op1 != 1 && *op1 != 2) {
      printf("Opcao invalida. Tente novamente.\n");
      printf("\nGostaria de ordenar a busca por genero, partido ou raca/cor? "
             "\n1 - Sim \n2 - Nao\n");
      scanf("%d", op1);
      getchar();
    }
    if (*op1 == 1) {
      do {
        printf("\nFazer a busca ordenada por \n1 - Genero \n2 - Partido \n3 - "
               "Raca/cor\n");
        scanf("%d", op2);
        getchar();
        while (*op2 != 1 && *op2 != 2 && *op2 != 3) {
          printf("Opcao invalida. Tente novamente.\n");
          printf("\nFazer a busca ordenada por \n1 - Genero \n2 - Partido \n3 "
                 "- Raca/cor\n");
          scanf("%d", op2);
          getchar();
        }

        if (*op2 == 1) {
          do {
            char fm;
            printf("\nDigite o genero(F/M): ");
            scanf("%c", &fm);
            getchar();
            fm = toupper(fm);
            if (fm != 'F' && fm != 'M') {
              printf("Opcao invalida!");
            } else {
              if (fm == 'F') {
                *opGen = 1;
              } else if (fm == 'M') {
                *opGen = 2;
              }
            }
          } while (*opGen != 1 && *opGen != 2);
        } else if (*op2 == 2) {
          printf("Digite o partido: ");
          scanf("%[^\n]s", part);
          fflush(stdin);
          maiusculas(part);
        } else if (*op2 == 3) {
          printf("Digite a cor/raca(AMARELA/BRANCA/INDIGENA/PARDA/PRETA/NAO "
                 "DIVULGAVEL/NAO INFORMADO): ");
          scanf("%14[^\n]", rc);
          fflush(stdin);
          maiusculas(rc);
        }
      } while (*op2 != 1 && *op2 != 2 && *op2 != 3);
    } else if (*op1 != 2) {
      printf("Opcao invalida!\n");
    }
  } while (*op1 != 1 && *op1 != 2);
}

int main() {
  int op;
  char nomeArquivo[40];
  do {
    printf("\n------------------\n");
    printf("Escolha uma Opcao:\n");
    printf("------------------\n");
    printf("1. Ler arquivo padrao\n");
    printf("2. Ler outro arquivo\n");
    printf("3. Sair\n");
    scanf("%d", &op);
    while (op < 1 || op > 3) {
      printf("Opcao invalida. Digite novamente.\n");
      scanf("%d", &op);
    }

    if (op == 1) {
      strcpy(nomeArquivo, "eleicoes.txt");
    } else if (op == 2) {
      printf("\nQual o nome do arquivo que deseja ler?\n");
      scanf("%s", nomeArquivo);
    } else if (op == 3) {
      printf("Saindo...\n");
      return 0;
    }

    // Leitura busca binaria
    int linhas = contarLinhas(nomeArquivo);
    Candidato *c = (Candidato *)malloc(
        linhas * sizeof(Candidato)); // Alocacao de um vetor com a quantidade de
                                     // linhas do arquivo
    time_t ini, fim;
    ini = clock();
    lerArquivoVetor(c, nomeArquivo);
    fim = clock();
    double tempoLerBinaria = (double)(fim - ini) / CLOCKS_PER_SEC;
    printf("\nTempo de leitura do arquivo como vetor de busca binaria: %f "
           "segundos\n",
           tempoLerBinaria);

    // Criar a arvore e fazer leitura do arquivo como arvore binaria
    Arvore a;
    criarArvore(&a);

    ini = clock();
    lerArquivoABB(&a, nomeArquivo);
    fim = clock();
    double tempoArvoreBB = (double)(fim - ini) / CLOCKS_PER_SEC;
    printf("\nTempo de leitura do arquivo como arvore binaria: %f segundos\n",
           tempoArvoreBB);

    // Criar a arvore e fazer leitura do arquivo como arvore avl
    ArvoreAVL avl;
    criarArvoreAVL(&avl);

    ini = clock();
    lerArquivoAVL(&avl, nomeArquivo);
    fim = clock();
    double tempoArvoreVL = (double)(fim - ini) / CLOCKS_PER_SEC;
    printf("\nTempo de leitura do arquivo como arvore avl: %f segundos\n",
           tempoArvoreVL);

    if (op == 1 || op == 2) {
      int opcao;
      do {
        printf("\n------------------\n");
        printf("Escolha uma Opcao:\n");
        printf("------------------\n");
        printf("1. Busca Binaria\n");
        printf("2. Arvore Binaria de Busca sem balanceamento\n");
        printf("3. Arvore AVL\n");
        printf("4. Voltar.\n");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:; // Busca binaria
          {
            int subOpcao;
            do {
              int inf = 1, sup = linhas, num;
              Candidato *resultado;
              int opOrd1 = 0, opOrd2 = 0, opGen = 0, numero = 0;
              char genero[15], partido[15], cor[15], estado[3], cidade[50];
              printf("\n========= Busca Binaria =========");
              subOpcao = lerInfoPesquisa();

              if (subOpcao == 1 || subOpcao == 2 ||
                  subOpcao ==
                      3) // Se escolheu uma das 3 opcoes de busca binaria
              {
                printf("\nQual estado deseja pesquisar?\n");
                scanf(" %[^\n]s", estado); // Leitura do estado
                maiusculas(estado);        // Transforma a string em maiuscula

                ini = clock();
                buscaBinariaEstado(c, linhas, &inf, &sup, estado);
                fim = clock();
                double tempoBuscaBinariaEstado =
                    (double)(fim - ini) / CLOCKS_PER_SEC;

                if (subOpcao == 2 ||
                    subOpcao == 3) // Se escolheu opcao 2 ou 3 de busca binaria
                {
                  printf("\nQual cidade deseja pesquisar?\n");
                  scanf(" %[^\n]s", cidade); // Leitura da cidade
                  maiusculas(cidade);        // Transforma string em maiuscula

                  ini = clock();
                  buscaBinariaCidade(
                      c, &inf, &sup,
                      cidade); // Realiza a busca binaria com a cidade digitada
                  fim = clock();
                  double tempoBuscaBinariaCidade =
                      (double)(fim - ini) / CLOCKS_PER_SEC;

                  if (subOpcao == 3) // Se escolheu opcao 3 de busca binaria
                  {
                    printf("\nQual numero deseja pesquisar?\n");
                    scanf("%d", &num); // Leitura do numero

                    ini = clock();
                    buscaBinariaNumero(
                        c, &inf, &sup,
                        num); // Realiza a busca binaria com o numero digitado
                    fim = clock();
                    double tempoBuscaBinariaNumero =
                        (double)(fim - ini) / CLOCKS_PER_SEC;

                    // Lê se o usuario quer filtrar por genero, partido ou cor
                    lerFiltroPesquisa(&opOrd1, &opOrd2, genero, &opGen, partido,
                                      cor);

                    if (opOrd2 == 1) // Caso deseje filtrar a busca por genero,
                                     // partido ou cor
                    {
                      if (opGen == 1) // Listar genero feminino
                      {
                        listagemGenero(c, inf, sup, "FEMININO");
                        printf("\nTempo da busca binaria por Numero: %f "
                               "segundos\n",
                               tempoBuscaBinariaNumero);
                      } else if (opGen == 2) // Listar genero masculino
                      {
                        listagemGenero(c, inf, sup, "MASCULINO");
                        printf("\nTempo da busca binaria por Numero: %f "
                               "segundos\n",
                               tempoBuscaBinariaNumero);
                      }
                    } else if (opOrd2 == 2) // Listar candidatos de um partido
                    {
                      listagemPartido(c, inf, sup, partido);
                      printf(
                          "\nTempo da busca binaria por Numero: %f segundos\n",
                          tempoBuscaBinariaNumero);
                    } else if (opOrd2 == 3) // Listar candidatos de uma cor
                    {
                      listagemCor(c, inf, sup, cor);
                      printf(
                          "\nTempo da busca binaria por Numero: %f segundos\n",
                          tempoBuscaBinariaNumero);
                    } else if (opOrd1 ==
                               2) // Caso escolha nao utilizar nenhum filtro
                    {
                      imprimeIntervalo(c, inf, sup);
                      printf(
                          "\nTempo da busca binaria por Numero: %f segundos\n",
                          tempoBuscaBinariaNumero);
                    }
                  }

                  if (subOpcao ==
                      2) // Se escolheu a opcao 2 de busca binaria (cidade)
                  {
                    lerFiltroPesquisa(&opOrd1, &opOrd2, genero, &opGen, partido,
                                      cor); // Verifica se deseja filtrar por
                                            // genero, partido ou raca/cor
                    if (opOrd2 == 1) // Caso deseje filtrar a busca por genero,
                                     // partido ou cor
                    {
                      if (opGen == 1) // genero feminino
                      {
                        listagemGenero(c, inf, sup,
                                       "FEMININO"); // Imprimir apenas cadidatos
                                                    // do genero feminino
                        printf("\nTempo da busca binaria por cidade: %f "
                               "segundos\n",
                               tempoBuscaBinariaCidade);
                      } else if (opGen == 2) // genero masculino
                      {
                        listagemGenero(
                            c, inf, sup,
                            "MASCULINO"); // Imprimir apenas cadidatos do genero
                                          // masculino
                        printf("\nTempo da busca binaria por cidade: %f "
                               "segundos\n",
                               tempoBuscaBinariaCidade);
                      }
                    } else if (opOrd2 == 2) // Se filtra por partido
                    {
                      listagemPartido(c, inf, sup,
                                      partido); // Imprimir apenas cadidatos do
                                                // partido digitado
                      printf(
                          "\nTempo da busca binaria por cidade: %f segundos\n",
                          tempoBuscaBinariaCidade);
                    } else if (opOrd2 == 3) // Se filtra por raca/cor
                    {
                      listagemCor(c, inf, sup,
                                  cor); // Imprimir apenas candidatos da
                                        // raca/cor digitado
                      printf(
                          "\nTempo da busca binaria por cidade: %f segundos\n",
                          tempoBuscaBinariaCidade);
                    } else if (opOrd1 ==
                               2) // Caso escolha nao utilizar nenhum filtro
                    {
                      imprimeIntervalo(
                          c, inf, sup); // Imprime todo o intervalo da cidade
                      printf(
                          "\nTempo da busca binaria por cidade: %f segundos\n",
                          tempoBuscaBinariaCidade);
                    }
                  }
                }

                if (subOpcao ==
                    1) // Se escolheu opcao 1 de busca binaria (estado)
                {
                  lerFiltroPesquisa(&opOrd1, &opOrd2, genero, &opGen, partido,
                                    cor); // Verifica se deseja filtrar por
                                          // genero, partido ou raca/cor
                  if (opOrd2 == 1)        // Se filtrar por genero
                  {
                    if (opGen == 1) // Listar genero feminino
                    {
                      listagemGenero(c, inf, sup,
                                     "FEMININO"); // Imprimir apenas cadidatos
                                                  // do genero feminino
                      printf(
                          "\nTempo da busca binaria por estado: %f segundos\n",
                          tempoBuscaBinariaEstado);
                    } else if (opGen == 2) // Listar genero masculino
                    {
                      listagemGenero(c, inf, sup,
                                     "MASCULINO"); // Imprimir apenas cadidatos
                                                   // do genero masculino
                      printf(
                          "\nTempo da busca binaria por estado: %f segundos\n",
                          tempoBuscaBinariaEstado);
                    }
                  } else if (opOrd2 == 2) // Se filtra por partido
                  {
                    listagemPartido(c, inf, sup,
                                    partido); // Imprimir apenas cadidatos do
                                              // partido digitado
                    printf("\nTempo da busca binaria por estado: %f segundos\n",
                           tempoBuscaBinariaEstado);
                  } else if (opOrd2 == 3) // Se filtra por raca/cor
                  {
                    listagemCor(
                        c, inf, sup,
                        cor); // Imprimir apenas candidatos da raca/cor digitado
                    printf("\nTempo da busca binaria por estado: %f segundos\n",
                           tempoBuscaBinariaEstado);
                  } else if (opOrd1 ==
                             2) // Caso escolha nao utilizar nenhum filtro
                  {
                    imprimeIntervalo(c, inf,
                                     sup); // Imprime todo o intervalo do estado
                    printf("\nTempo da busca binaria por estado: %f segundos\n",
                           tempoBuscaBinariaEstado);
                  }
                }
              }
              if (subOpcao == 4) // Caso deseje voltar
              {
                printf("Voltando...");
                break;
              }
            } while (subOpcao != 4);
            break;
          }
        case 2:;
          {
            int subOpcao;
            do {
              int opOrd1 = 0, opOrd2 = 0, opGen = 0, numero = 0;
              char genero[15], partido[15], cor[15], estado[3], cidade[50];
              printf("\n========= Arvore Binaria =========");
              subOpcao = lerInfoPesquisa();
              if (subOpcao == 1 || subOpcao == 2 ||
                  subOpcao == 3) // Se escolheu uma das 3 opcoes de busca com
                                 // arvore binaria
              {
                printf("\nQual estado deseja pesquisa?\n");
                scanf("%[^\n]s", estado); // Leitura do estado
                maiusculas(estado);       // Transforma a string em maiuscula

                if (subOpcao == 2 ||
                    subOpcao == 3) // Se escolheu opcao 2 ou 3 de busca com
                                   // arvore binaria
                {
                  printf(
                      "\nQual cidade deseja pesquisar?\n"); // Leitura da cidade
                  scanf(" %[^\n]s", cidade);
                  maiusculas(cidade);

                  if (subOpcao ==
                      3) // Se escolheu opcao 3 de busca com arvore binaria
                  {
                    printf(
                        "\nQual o numero do candidato?\n"); // Leitura do numero
                    scanf("%d", &numero);

                    lerFiltroPesquisa(&opOrd1, &opOrd2, genero, &opGen, partido,
                                      cor);
                    if (opOrd2 == 1) // Caso deseje filtrar a busca por genero,
                                     // partido ou cor
                    {
                      if (opGen == 1) // Listar genero feminino
                      {
                        ini = clock();
                        listarCandidatosGeneroNABB(a.raiz, estado, cidade,
                                                   numero, "FEMININO");
                        fim = clock();
                        double tempoABBEstadoGF =
                            (double)(fim - ini) / CLOCKS_PER_SEC;
                        printf("\nTempo da busca na Arvore Binaria por Genero: "
                               "%f segundos\n",
                               tempoABBEstadoGF);
                      } else if (opGen == 2) // Listar genero masculino
                      {
                        ini = clock();
                        listarCandidatosGeneroNABB(a.raiz, estado, cidade,
                                                   numero, "MASCULINO");
                        fim = clock();
                        double tempoABBEstadoGM =
                            (double)(fim - ini) / CLOCKS_PER_SEC;
                        printf("\nTempo da busca na Arvore Binaria por Genero: "
                               "%f segundos\n",
                               tempoABBEstadoGM);
                      }
                    } else if (opOrd2 == 2) // Listar candidatos de um partido
                    {
                      ini = clock();
                      listarCandidatosPartidoNABB(a.raiz, estado, cidade,
                                                  numero, partido);
                      fim = clock();
                      double tempoABBEstadoPartido =
                          (double)(fim - ini) / CLOCKS_PER_SEC;
                      printf("\nTempo da busca na Arvore Binaria por Partido: "
                             "%f segundos\n",
                             tempoABBEstadoPartido);
                    } else if (opOrd2 == 3) // Listar candidatos de uma cor
                    {
                      ini = clock();
                      listarCandidatosCorNABB(a.raiz, estado, cidade, numero,
                                              cor);
                      fim = clock();
                      double tempoABBEstadoCor =
                          (double)(fim - ini) / CLOCKS_PER_SEC;
                      printf("\nTempo da busca na Arvore Binaria por Cor: %f "
                             "segundos\n",
                             tempoABBEstadoCor);
                    } else if (opOrd1 ==
                               2) // Listar todos candidatos com o numero
                    {
                      ini = clock();
                      buscarPorNumeroABB(a.raiz, estado, cidade, numero);
                      fim = clock();
                      double tempoABBNumero =
                          (double)(fim - ini) / CLOCKS_PER_SEC;
                      printf("\nTempo da busca na Arvore Binaria por Numero: "
                             "%f segundos\n",
                             tempoABBNumero);
                    }
                  }

                  if (subOpcao == 2) // Pesquisa por cidade
                  {
                    lerFiltroPesquisa(&opOrd1, &opOrd2, genero, &opGen, partido,
                                      cor);

                    if (opOrd2 == 1) // Caso deseje filtrar a busca por genero,
                                     // partido ou cor
                    {
                      if (opGen == 1) // Listar genero feminino
                      {
                        ini = clock();
                        listarCandidatosGeneroCABB(a.raiz, estado, cidade,
                                                   "FEMININO");
                        fim = clock();
                        double tempoABBGeneroCABBF =
                            (double)(fim - ini) / CLOCKS_PER_SEC;
                        printf("\nTempo da busca na Arvore Binaria por genero: "
                               "%f segundos\n",
                               tempoABBGeneroCABBF);
                      } else if (opGen == 2) // Listar genero masculino
                      {
                        ini = clock();
                        listarCandidatosGeneroCABB(a.raiz, estado, cidade,
                                                   "MASCULINO");
                        fim = clock();
                        double tempoABBGeneroCABBM =
                            (double)(fim - ini) / CLOCKS_PER_SEC;
                        printf("\nTempo da busca na Arvore Binaria por genero: "
                               "%f segundos\n",
                               tempoABBGeneroCABBM);
                      }
                    } else if (opOrd2 == 2) // Listar candidatos de um partido
                    {
                      ini = clock();
                      listarCandidatosPartidoCABB(a.raiz, estado, cidade,
                                                  partido);
                      fim = clock();
                      double tempoABBPartidoCABB =
                          (double)(fim - ini) / CLOCKS_PER_SEC;
                      printf("\nTempo da busca na Arvore Binaria por partido: "
                             "%f segundos\n",
                             tempoABBPartidoCABB);
                    } else if (opOrd2 == 3) // Listar candidatos de uma cor
                    {
                      ini = clock();
                      listarCandidatosCorCABB(a.raiz, estado, cidade, cor);
                      fim = clock();
                      double tempoABBCorCABB =
                          (double)(fim - ini) / CLOCKS_PER_SEC;
                      printf("\nTempo da busca na Arvore Binaria por cor: %f "
                             "segundos\n",
                             tempoABBCorCABB);
                    } else if (opOrd1 == 2) // Listar todos candidatos da cidade
                    {
                      ini = clock();
                      buscarPorCidadeABB(a.raiz, estado, cidade);
                      fim = clock();
                      double tempoABBCidade =
                          (double)(fim - ini) / CLOCKS_PER_SEC;
                      printf(
                          "\nTempo da busca na Arvore Binaria: %f segundos\n",
                          tempoABBCidade);
                    }
                  }
                }

                if (subOpcao == 1) // Pesquisa por estado
                {
                  lerFiltroPesquisa(&opOrd1, &opOrd2, genero, &opGen, partido,
                                    cor);
                  if (opOrd2 == 1) // Caso deseje filtrar a busca por genero,
                                   // partido ou cor
                  {
                    if (opGen == 1) // Listar genero feminino
                    {
                      ini = clock();
                      listarCandidatosGeneroEABB(a.raiz, estado, "FEMININO");
                      fim = clock();
                      double tempoABBEstadoGF =
                          (double)(fim - ini) / CLOCKS_PER_SEC;
                      printf("\nTempo da busca na Arvore Binaria por genero: "
                             "%f segundos\n",
                             tempoABBEstadoGF);
                    } else if (opGen == 2) // Listar genero masculino
                    {
                      ini = clock();
                      listarCandidatosGeneroEABB(a.raiz, estado, "MASCULINO");
                      fim = clock();
                      double tempoABBEstadoGM =
                          (double)(fim - ini) / CLOCKS_PER_SEC;
                      printf("\nTempo da busca na Arvore Binaria por genero: "
                             "%f segundos\n",
                             tempoABBEstadoGM);
                    }
                  } else if (opOrd2 == 2) // Listar candidatos de um partido
                  {
                    ini = clock();
                    listarCandidatosPartidoEABB(a.raiz, estado, partido);
                    fim = clock();
                    double tempoABBEstadoPartido =
                        (double)(fim - ini) / CLOCKS_PER_SEC;
                    printf("\nTempo da busca na Arvore Binaria por partido: %f "
                           "segundos\n",
                           tempoABBEstadoPartido);
                  } else if (opOrd2 == 3) // Listar candidatos de uma cor
                  {
                    ini = clock();
                    listarCandidatosCorEABB(a.raiz, estado, cor);
                    fim = clock();
                    double tempoABBEstadoCor =
                        (double)(fim - ini) / CLOCKS_PER_SEC;
                    printf("\nTempo da busca na Arvore Binaria por cor: %f "
                           "segundos\n",
                           tempoABBEstadoCor);
                  } else if (opOrd1 == 2) // Listtar todos candidatos do estado
                  {
                    ini = clock();
                    buscarPorEstadoABB(a.raiz, estado);
                    fim = clock();
                    double tempoABBEstado =
                        (double)(fim - ini) / CLOCKS_PER_SEC;
                    printf("\nTempo da busca na Arvore Binaria: %f segundos\n",
                           tempoABBEstado);
                  }
                }
              }
              if (subOpcao == 4) // Caso deseje voltar
              {
                printf("Voltando...");
                break;
              }
            } while (subOpcao != 4);
            break;
          }
        case 3: {
          int subOpcao;
          do {
            int opOrd1 = 0, opOrd2 = 0, opGen = 0, numero = 0;
            char genero[15], partido[15], cor[15], estado[3], cidade[50];
            printf("\n========= Arvore AVL =========");
            subOpcao = lerInfoPesquisa();
            if (subOpcao == 1 || subOpcao == 2 ||
                subOpcao == 3) // Se escolheu uma das 3 opcoes de busca com
                               // arvore binaria
            {
              printf("\nQual estado deseja pesquisa?\n");
              scanf("%[^\n]s", estado); // Leitura do estado
              maiusculas(estado);       // Transforma a string em maiuscula

              if (subOpcao == 2 ||
                  subOpcao ==
                      3) // Se escolheu opcao 2 ou 3 de busca com arvore binaria
              {
                printf("\nQual cidade deseja pesquisar?\n");
                scanf(" %[^\n]s", cidade); // Leitura da cidade
                maiusculas(cidade);

                if (subOpcao ==
                    3) // Se escolheu opcao 3 de busca com arvore binaria
                {
                  printf("\nQual o numero do candidato?\n");
                  scanf("%d", &numero); // Leitura do numero

                  lerFiltroPesquisa(&opOrd1, &opOrd2, genero, &opGen, partido,
                                    cor);
                  if (opOrd2 == 1) // Caso deseje filtrar a busca por genero,
                                   // partido ou cor
                  {
                    if (opGen == 1) // Listar genero feminino
                    {
                      ini = clock();
                      listarCandidatosGeneroNAVL(avl.raiz, estado, cidade,
                                                 numero, "FEMININO");
                      fim = clock();
                      double tempoAVLEstadoGF =
                          (double)(fim - ini) / CLOCKS_PER_SEC;
                      printf("\nTempo da busca na Arvore AVL por Genero: %f "
                             "segundos\n",
                             tempoAVLEstadoGF);
                    } else if (opGen == 2) // Listar genero masculino
                    {
                      ini = clock();
                      listarCandidatosGeneroNAVL(avl.raiz, estado, cidade,
                                                 numero, "MASCULINO");
                      fim = clock();
                      double tempoAVLEstadoGM =
                          (double)(fim - ini) / CLOCKS_PER_SEC;
                      printf("\nTempo da busca na Arvore AVL por Genero: %f "
                             "segundos\n",
                             tempoAVLEstadoGM);
                    }
                  } else if (opOrd2 == 2) // Listar candidatos de um partido
                  {
                    ini = clock();
                    listarCandidatosPartidoNAVL(avl.raiz, estado, cidade,
                                                numero, partido);
                    fim = clock();
                    double tempoAVLEstadoPartido =
                        (double)(fim - ini) / CLOCKS_PER_SEC;
                    printf("\nTempo da busca na Arvore AVL por Partido: %f "
                           "segundos\n",
                           tempoAVLEstadoPartido);
                  } else if (opOrd2 == 3) // Listar candidatos de uma cor
                  {
                    ini = clock();
                    listarCandidatosCorNAVL(avl.raiz, estado, cidade, numero,
                                            cor);
                    fim = clock();
                    double tempoAVLEstadoCor =
                        (double)(fim - ini) / CLOCKS_PER_SEC;
                    printf(
                        "\nTempo da busca na Arvore AVL por Cor: %f segundos\n",
                        tempoAVLEstadoCor);
                  } else if (opOrd1 ==
                             2) // Listtar todos candidatos com o numero
                  {
                    ini = clock();
                    buscarPorNumeroAVL(avl.raiz, estado, cidade, numero);
                    fim = clock();
                    double tempoAVLNumero =
                        (double)(fim - ini) / CLOCKS_PER_SEC;
                    printf("\nTempo da busca na Arvore AVL por Numero: %f "
                           "segundos\n",
                           tempoAVLNumero);
                  }
                }

                if (subOpcao == 2) // Pesquisa por cidade
                {
                  lerFiltroPesquisa(&opOrd1, &opOrd2, genero, &opGen, partido,
                                    cor);

                  if (opOrd2 == 1) // Caso deseje filtrar a busca por genero,
                                   // partido ou cor
                  {
                    if (opGen == 1) // Listar genero feminino
                    {
                      ini = clock();
                      listarCandidatosGeneroCAVL(avl.raiz, estado, cidade,
                                                 "FEMININO");
                      fim = clock();
                      double tempoAVLGeneroCAVLF =
                          (double)(fim - ini) / CLOCKS_PER_SEC;
                      printf("\nTempo da busca na Arvore AVL por genero: %f "
                             "segundos\n",
                             tempoAVLGeneroCAVLF);
                    } else if (opGen == 2) // Listar genero masculino
                    {
                      ini = clock();
                      listarCandidatosGeneroCAVL(avl.raiz, estado, cidade,
                                                 "MASCULINO");
                      fim = clock();
                      double tempoAVLGeneroCAVLM =
                          (double)(fim - ini) / CLOCKS_PER_SEC;
                      printf("\nTempo da busca na Arvore AVL por genero: %f "
                             "segundos\n",
                             tempoAVLGeneroCAVLM);
                    }
                  } else if (opOrd2 == 2) // Listar candidatos de um partido
                  {
                    ini = clock();
                    listarCandidatosPartidoCAVL(avl.raiz, estado, cidade,
                                                partido);
                    fim = clock();
                    double tempoAVLPartidoCAVL =
                        (double)(fim - ini) / CLOCKS_PER_SEC;
                    printf("\nTempo da busca na Arvore AVL por partido: %f "
                           "segundos\n",
                           tempoAVLPartidoCAVL);
                  } else if (opOrd2 == 3) // Listar candidatos de uma cor
                  {
                    ini = clock();
                    listarCandidatosCorCAVL(avl.raiz, estado, cidade, cor);
                    fim = clock();
                    double tempoAVLCorCAVL =
                        (double)(fim - ini) / CLOCKS_PER_SEC;
                    printf(
                        "\nTempo da busca na Arvore AVL por cor: %f segundos\n",
                        tempoAVLCorCAVL);
                  } else if (opOrd1 == 2) // Listtar todos candidatos da cidade
                  {
                    ini = clock();
                    buscarPorCidadeAVL(avl.raiz, estado, cidade);
                    fim = clock();
                    double tempoAVLCidade =
                        (double)(fim - ini) / CLOCKS_PER_SEC;
                    printf("\nTempo da busca na Arvore AVL: %f segundos\n",
                           tempoAVLCidade);
                  }
                }
              }

              if (subOpcao == 1) // Pesquisa por estado
              {
                lerFiltroPesquisa(&opOrd1, &opOrd2, genero, &opGen, partido,
                                  cor);
                if (opOrd2 ==
                    1) // Caso deseje filtrar a busca por genero, partido ou cor
                {
                  if (opGen == 1) // Listar genero feminino
                  {
                    ini = clock();
                    listarCandidatosGeneroEAVL(avl.raiz, estado, "FEMININO");
                    fim = clock();
                    double tempoAVLEstadoGF =
                        (double)(fim - ini) / CLOCKS_PER_SEC;
                    printf("\nTempo da busca na Arvore AVL por genero: %f "
                           "segundos\n",
                           tempoAVLEstadoGF);
                  } else if (opGen == 2) // Listar genero masculino
                  {
                    ini = clock();
                    listarCandidatosGeneroEAVL(avl.raiz, estado, "MASCULINO");
                    fim = clock();
                    double tempoAVLEstadoGM =
                        (double)(fim - ini) / CLOCKS_PER_SEC;
                    printf("\nTempo da busca na Arvore AVL por genero: %f "
                           "segundos\n",
                           tempoAVLEstadoGM);
                  }
                } else if (opOrd2 == 2) // Listar candidatos de um partido
                {
                  ini = clock();
                  listarCandidatosPartidoEAVL(avl.raiz, estado, partido);
                  fim = clock();
                  double tempoAVLEstadoPartido =
                      (double)(fim - ini) / CLOCKS_PER_SEC;
                  printf("\nTempo da busca na Arvore AVL por partido: %f "
                         "segundos\n",
                         tempoAVLEstadoPartido);
                } else if (opOrd2 == 3) // Listar candidatos de uma cor
                {
                  ini = clock();
                  listarCandidatosCorEAVL(avl.raiz, estado, cor);
                  fim = clock();
                  double tempoAVLEstadoCor =
                      (double)(fim - ini) / CLOCKS_PER_SEC;
                  printf(
                      "\nTempo da busca na Arvore AVL por cor: %f segundos\n",
                      tempoAVLEstadoCor);
                } else if (opOrd1 == 2) // Listtar todos candidatos do estado
                {
                  ini = clock();
                  buscarPorEstadoAVL(avl.raiz, estado);
                  fim = clock();
                  double tempoAVLEstado = (double)(fim - ini) / CLOCKS_PER_SEC;
                  printf("\nTempo da busca na Arvore AVL: %f segundos\n",
                         tempoAVLEstado);
                }
              }
            }
            if (subOpcao == 4) // Caso deseje voltar
            {
              printf("Voltando...");
              break;
            }
          } while (subOpcao != 4);
          break;
        }
        case 4:
          // Liberando memoria utilizada
          free(c); // Vetor de busca binaria
          destruirArvoreABB(&a);
          destruirArvoreAVL(&avl);
          printf("Voltando...\n");
          break;
        default:
          printf("Opcao invalida. Tente novamente.\n");
          break;
        }
      } while (opcao != 4);
    }
  } while (op != 3);

  return 0;
}