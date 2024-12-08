#include "buscaBinaria.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Shell Sort para ordenar os candidatos por ESTADO
void shellEstados(Candidato *c, int linhas) {
  int i, j, h = 1;
  Candidato aux;
  do {
    h = h * 3 + 1;
  } while (h < linhas);
  do {
    h /= 3;
    for (i = h; i < linhas; i++) {
      aux = c[i];
      j = i;
      while (j >= h && strcmp(c[j - h].estado, aux.estado) > 0) {
        c[j] = c[j - h];
        j -= h;
      }
      c[j] = aux;
    }
  } while (h > 1);
}

void buscaBinariaEstado(Candidato *c, int linhas, int *inf, int *sup,
                        char *chave) {
  shellEstados(c, linhas);
  int meio = (*inf + *sup) / 2; // meio = metade do intervalo de busca
  int infCmp = meio,
      supCmp = meio; // Comparar para achar limite inferior e superior
  int cmp = strcmp(c[meio].estado,
                   chave); // compara o estado do candidato do meio com a chave
  if (cmp ==
      0) { // Se o candidato do meio do intervalo ja for do estado buscado
    // Encontrar canditado do estado e garantir que seja o primeiro
    while (infCmp > *inf &&
           strcmp(c[infCmp - 1].estado, chave) ==
               0) { // Se "infCmp" ainda for maior que o limite inferior e o
                    // candidato anterior for do mesmo estado
      infCmp--;
    }
    *inf = infCmp;
    // Encontrar o ultimo candidato do estado
    while (supCmp < *sup &&
           strcmp(c[supCmp + 1].estado, chave) ==
               0) { // Se "supCmp" ainda for menor que o limite superior e o
                    // candidato posterior for do mesmo estado
      supCmp++;
    }
    *sup = supCmp;
  } else if (cmp > 0) { // Caso o candidato do meio tenha um estado maior que o
                        // buscado
    *sup = meio -
           1; // Decrementa o limite superior para buscar no intervalo inferior
    return buscaBinariaEstado(c, linhas, inf, sup, chave);
  } else { // Caso o candidato do meio tenha um estado menor que o buscado
    *inf = meio +
           1; // Incrementa o limite inferior para buscar no intervalo superior
    return buscaBinariaEstado(c, linhas, inf, sup, chave);
  }
}

// Ordenar as cidades do intervalo de estados
void shellCidades(Candidato *c, int inf, int sup) {
  int i, j, h = 1;
  Candidato aux;
  int intervalo = (sup - inf) + 1;
  do {
    h = h * 3 + 1;
  } while (h < intervalo);
  do {
    h /= 3;
    for (i = inf + h; i <= sup; i++) {
      aux = c[i];
      j = i;
      while (j >= inf + h && strcmp(c[j - h].cidade, aux.cidade) > 0) {
        c[j] = c[j - h];
        j -= h;
      }
      c[j] = aux;
    }
  } while (h > 1);
}

void buscaBinariaCidade(Candidato *c, int *inf, int *sup, char *cidade) {
  shellCidades(c, *inf, *sup);
  int meio = (*inf + *sup) / 2; // meio = metade do intervalo de busca
  int infCmp = meio,
      supCmp = meio; // Comparar para achar limite inferior e superior
  int cmp = strcmp(c[meio].cidade,
                   cidade); // compara a cidade do candidato do meio com a chave
  if (cmp == 0) {
    // Encontrar o primeiro candidato da cidade
    while (infCmp > *inf &&
           strcmp(c[infCmp - 1].cidade, cidade) ==
               0) { // Se "infCmp" ainda for maior que o limite inferior e o
                    // candidato anterior for da mesma cidade
      infCmp--;
    }
    *inf = infCmp;
    // Encontrar o ultimo candidato da cidade
    while (supCmp < *sup &&
           strcmp(c[supCmp + 1].cidade, cidade) ==
               0) { // Se "supCmp" ainda for menor que o limite superior e o
                    // candidato posterior ainda for do mesmo estado
      supCmp++;
    }
    *sup = supCmp;
  } else if (cmp > 0) { // Caso o candidato do meio tenha uma cidade maior que a
                        // buscada
    *sup = meio -
           1; // Decrementa o limite superior para buscar no intervalo inferior
    return buscaBinariaCidade(c, inf, sup, cidade);
  } else { // Caso o candidato do meio tenha uma cidade menor que a buscada
    *inf = meio +
           1; // Incremeta o limite inferior para buscar no intervalo superior
    return buscaBinariaCidade(c, inf, sup, cidade);
  }
}

// Ordenar por numeros de partido no intervalo de cidades
void shellNumeros(Candidato *c, int inf, int sup) {
  int i, j, h = 1;
  Candidato aux;
  int intervalo = sup + inf + 1;
  do {
    h = h * 3 + 1;
  } while (h < intervalo);
  do {
    h /= 3;
    for (i = inf + h; i <= sup; i++) {
      aux = c[i];
      j = i;
      while (j >= inf + h && c[j - h].numero > aux.numero) {
        c[j] = c[j - h];
        j -= h;
      }
      c[j] = aux;
    }
  } while (h > 1);
}

void buscaBinariaNumero(Candidato *c, int *inf, int *sup, int num) {
  shellNumeros(c, *inf, *sup);
  int meio = (*inf + *sup) / 2; // meio = metade do intervalo de busca
  int infCmp = meio,
      supCmp = meio; // Comparar para achar limite inferior e superior
  if (c[meio].numero == num) {
    while (infCmp > *inf &&
           c[infCmp - 1].numero ==
               num) { // Enquanto o candidato anterior ainda tiver o mesmo
                      // numero, aumenta o limite inferior
      infCmp--;
    }
    *inf = infCmp;
    while (supCmp < *sup &&
           c[supCmp + 1].numero ==
               num) { // Enquanto o candidato posterior ainda tiver o mesmo
                      // numero, aumenta o limite superior
      supCmp++;
    }
    *sup = supCmp;
  } else if (c[meio].numero > num) { // Se o numero do meio for maior, busca com
                                     // o limite superior menor
    *sup = meio - 1;
    return buscaBinariaNumero(c, inf, sup, num);
  } else { // Se o numero do meio for menor, busca com limitante inferior maior
    *inf = meio + 1;
    return buscaBinariaNumero(c, inf, sup, num);
  }
}

// Imprime um candidato
void imprimeCandidato(Candidato c) {
  printf("\n=================CANDIDATO=================\n");
  printf("Nome: %s\n", c.nome);
  printf("Nome de Urna: %s\n", c.nomeUrna);
  printf("Numero: %d\n", c.numero);
  printf("Cargo: %s\n", c.cargo);
  printf("Estado: %s\n", c.estado);
  printf("Cidade: %s\n", c.cidade);
  printf("Partido: %s\n", c.sigla);
  printf("Genero: %s\n", c.genero);
  printf("Grau de instrucao: %s\n", c.grauInstrucao);
  printf("Cor: %s\n", c.cor);
}

// Imprime todos os candidatos de um intervalo
void imprimeIntervalo(Candidato *c, int inf, int sup) {
  if (c == NULL)
    printf("Erro na leitura do arquivo.\n");
  else {
    do {
      imprimeCandidato(c[inf]);
      inf++;
    } while (inf != (sup + 1));
  }
}

// Imprime todos os candidatos de determinado genero no intervalo dado (inf,sup)
void listagemGenero(Candidato *c, int inf, int sup, char *genero) {
  if (c == NULL)
    printf("Erro na leitura do arquivo.\n");
  else {
    do {
      if (strcmp(c[inf].genero, genero) ==
          0) { // Imprime candidato do limite inferior
        imprimeCandidato(c[inf]);
      }
      inf++; // Incrementa o limite inferior para percorrer todo o intervalo
    } while (inf != (sup + 1));
  }
}

// Imprime todos os candidatos de determinado partido no intervalo dado
// (inf,sup)
void listagemPartido(Candidato *c, int inf, int sup, char *sigla) {
  if (c == NULL)
    printf("Erro na leitura do arquivo.\n");
  else {
    do {
      if (strcmp(c[inf].sigla, sigla) ==
          0) { // Imprime candidato do limite inferior
        imprimeCandidato(c[inf]);
      }
      inf++; // Incrementa o limite inferior para percorrer todo o intervalo
    } while (inf != (sup + 1));
  }
}

void limparString(char *str) {
    // Remove espaços iniciais
    while (isspace((unsigned char)*str)) str++;

    // Remove espaços finais
    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    // Coloca o terminador nulo no final da string
    *(end + 1) = '\0';
}


// Imprime todos os candidatos de determinado cor/raca no intervalo dado
// (inf,sup)
void listagemCor(Candidato *c, int inf, int sup, char *cor) {
    if (c == NULL) {
        printf("Erro na leitura do arquivo.\n");
        return;
    }

    // Limpa a string 'cor'
    limparString(cor);

    do {
        // Limpa c[inf].cor
        limparString(c[inf].cor);

        if (strcmp(c[inf].cor, cor) == 0) {
            imprimeCandidato(c[inf]);
        }
        inf++; // Incrementa o limite inferior para percorrer todo o intervalo
    } while (inf != (sup + 1));
}


// Funcao para ler os dados da planilha
void lerArquivoVetor(Candidato *c, const char *nomeArquivo) {
  FILE *arquivo = fopen(nomeArquivo, "r");
  if (arquivo == NULL) {
    perror("Erro ao abrir o arquivo");
    return;
  }

  int linhas = contarLinhas(nomeArquivo);
  char buffer[256];

  // Ignorar a primeira linha (cabecalho)
  if (fgets(buffer, sizeof(buffer), arquivo) == NULL) {
    perror("Erro ao ler a primeira linha");
    fclose(arquivo);
    return;
  }

  for (int i = 0; i < linhas; i++) {
    if (fgets(buffer, sizeof(buffer), arquivo) == NULL) {
      printf("%d", i);
      perror("Erro ao ler a linha do arquivo");
      fclose(arquivo);
      return;
    }
    sscanf(buffer,
           "%4[^;];%49[^;];%d;%14[^;];%49[^;];%49[^;];%14[^;];%14[^;];%29[^;];%"
           "14[^\n]",
           c[i].estado, c[i].cidade, &c[i].numero, c[i].cargo, c[i].nome,
           c[i].nomeUrna, c[i].sigla, c[i].genero, c[i].grauInstrucao,
           c[i].cor);
  }

  fclose(arquivo);
}

// Funcao que retorna a quantidade de linhas do arquivo
int contarLinhas(const char *nomeArquivo) {
  FILE *arquivo = fopen(nomeArquivo, "r");
  if (arquivo == NULL) {
    return -1;
  }
  int linhas = 0;
  char c;
  while ((c = fgetc(arquivo)) != EOF) {
    if (c == '\n') {
      linhas++;
    }
  }
  fclose(arquivo);
  return linhas;
}
