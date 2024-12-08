#include "arvoreBinaria.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void criarArvore(Arvore *a) // Cria uma arvore binaria
{
  a->raiz = NULL;
}

int arvoreVaziaABB(Arvore *a) // Verifica se a arvore esta vazia
{
  return (a->raiz == NULL);
}

void limparStringABB(char *str)
{
  // Remove espaços iniciais
  while (isspace((unsigned char)*str))
    str++;

  // Remove espaços finais
  char *end = str + strlen(str) - 1;
  while (end > str && isspace((unsigned char)*end))
    end--;

  // Coloca o terminador nulo no final da string
  *(end + 1) = '\0';
}

void lerArquivoABB(
    Arvore *a,
    const char *nomeArquivo) // Leitura de arquivo como arvore binaria
{
  FILE *arquivo = fopen(nomeArquivo, "r");
  if (arquivo == NULL)
  {
    perror("Erro ao abrir arquivo");
    return;
  }

  char buffer[256];
  while (fgets(buffer, sizeof(buffer), arquivo))
  {
    Candidato candidato;
    sscanf(buffer,
           "%4[^;];%49[^;];%d;%14[^;];%49[^;];%49[^;];%14[^;];%14[^;];%29[^;];%"
           "14[^\n]", // Leitura separada das informacoes
           candidato.estado, candidato.cidade, &candidato.numero,
           candidato.cargo, candidato.nome, candidato.nomeUrna, candidato.sigla,
           candidato.genero, candidato.grauInstrucao, candidato.cor);
    a->raiz = inserirArvore(a->raiz, candidato); // Insercao do novo no
  }
  fclose(arquivo);
}

No *criarN(Candidato valor) // Cria novo no de arvore binaria
{
  No *novo = (No *)malloc(sizeof(No));
  if (novo)
  {
    novo->candidato = valor;
    novo->esquerda = NULL;
    novo->direita = NULL;
  }
  return novo;
}

No *inserirArvore(No *raiz, Candidato valor) // Insere no em arvore binaria
{
  if (raiz == NULL) // Se for inserir no final da arvore, cria novo no
  {
    return criarN(valor);
  }
  int estadoCmp = strcmp(
      valor.estado, raiz->candidato.estado); // Compara o estado da raiz com o
                                             // do candidato a ser inserido
  if (estadoCmp < 0)                         // Se estado do candidato for menor
  {
    raiz->esquerda = inserirArvore(raiz->esquerda, valor); // Insere a esquerda
  }
  else if (estadoCmp > 0) // Se estado do candidato for maior
  {
    raiz->direita = inserirArvore(raiz->direita, valor); // Insere a direita
  }
  else // Se raiz e candidato valor tiverem mesmo estado
  {
    int cidadeCmp = strcmp(
        valor.cidade, raiz->candidato.cidade); // Compara a cidade da raiz com o
                                               // do candidato a ser inserido
    if (cidadeCmp < 0)                         // Se cidade do candidato for menor
    {
      raiz->esquerda =
          inserirArvore(raiz->esquerda, valor); // Insere a esquerda
    }
    else if (cidadeCmp > 0) // Se cidade do candidato for maior
    {
      raiz->direita = inserirArvore(raiz->direita, valor); // Insere a direita
    }
    else
    {
      if (valor.numero <
          raiz->candidato.numero) // Compara o numero da raiz com o do candidato
                                  // a ser inserido
      {
        raiz->esquerda = inserirArvore(
            raiz->esquerda,
            valor); // Se numero do candidato for menor, insere a esquerda
      }
      else if (valor.numero >
               raiz->candidato.numero) // Compara o numero da raiz com o do
                                       // candidato a ser inserido
      {
        raiz->direita = inserirArvore(
            raiz->direita,
            valor); // Se numero do candidato for maior, insere a direita
      }
      else if (valor.numero ==
               raiz->candidato.numero) // Compara o numero da raiz com o do
                                       // candidato a ser inserido
      {
        raiz->esquerda = inserirArvore(
            raiz->esquerda,
            valor); // Se numero do candidato for igual, insere a esquerda
      }
    }
  }
  return raiz;
}

// Funcoes de busca
void buscarPorEstadoABB(
    No *raiz,
    const char *estado) // Buscar em arvore binaria com estado como chave
{
  if (raiz == NULL)
  {
    return;
  }
  if (strcmp(raiz->candidato.estado, estado) > 0)
  {
    buscarPorEstadoABB(
        raiz->esquerda,
        estado); // Estado esta localizado na subarvore da esquerda
  }
  else if (strcmp(raiz->candidato.estado, estado) < 0)
  {
    buscarPorEstadoABB(
        raiz->direita,
        estado); // Estado esta localizado na sub arvore da direita
  }
  else
  {
    imprimirCandidatoABB(
        &(raiz->candidato));                    // Imprime candidato se o estado for igual
    buscarPorEstadoABB(raiz->esquerda, estado); // Verifica subarvore a esquerda
    buscarPorEstadoABB(raiz->direita, estado);  // Verifica subarvore a direita
  }
}

void buscarPorCidadeABB(No *raiz, const char *estado,
                        const char *cidade)
{ // Buscar em arvore binaria com
  // estado e cidade como chaves
  if (raiz == NULL)
  {
    return;
  }
  if (strcmp(raiz->candidato.estado, estado) > 0)
  {
    buscarPorCidadeABB(raiz->esquerda, estado,
                       cidade); // Estado esta localizado na subarvore esquerda
  }
  else if (strcmp(raiz->candidato.estado, estado) < 0)
  {
    buscarPorCidadeABB(
        raiz->direita, estado,
        cidade); // Estado esta localizado na subarvore da direita
  }
  else
  {
    if (strcmp(raiz->candidato.cidade, cidade) > 0)
    {
      buscarPorCidadeABB(
          raiz->esquerda, estado,
          cidade); // Cidade esta localizada na subarvore esquerda
    }
    else if (strcmp(raiz->candidato.cidade, cidade) < 0)
    {
      buscarPorCidadeABB(raiz->direita, estado,
                         cidade); // Cidade esta localizada na subarvore direita
    }
    else
    {
      imprimirCandidatoABB(
          &(raiz->candidato)); // Imprime candidato se a cidade for igual
      buscarPorCidadeABB(raiz->esquerda, estado,
                         cidade); // Verifica subarvore a esquerda
      buscarPorCidadeABB(raiz->direita, estado,
                         cidade); // Verifica subarvore a direita
    }
  }
}

void buscarPorNumeroABB(No *raiz, const char *estado, const char *cidade,
                        int numero)
{ // Buscar em arvore binaria com estado,
  // cidade e numero como chaves
  if (raiz == NULL)
  {
    return;
  }

  if (strcmp(raiz->candidato.estado, estado) > 0)
  {
    buscarPorNumeroABB(raiz->esquerda, estado, cidade,
                       numero); // Estado esta localizado na subarvore esquerda
  }
  else if (strcmp(raiz->candidato.estado, estado) < 0)
  {
    buscarPorNumeroABB(
        raiz->direita, estado, cidade,
        numero); // Estado esta localizado na subarvore da direita
  }
  else
  {
    if (strcmp(raiz->candidato.cidade, cidade) > 0)
    {
      buscarPorNumeroABB(
          raiz->esquerda, estado, cidade,
          numero); // Cidade esta localizada na subarvore esquerda
    }
    else if (strcmp(raiz->candidato.cidade, cidade) < 0)
    {
      buscarPorNumeroABB(raiz->direita, estado, cidade,
                         numero); // Cidade esta localizada na subarvore direita
    }
    else
    {
      if (raiz->candidato.numero > numero)
      {
        buscarPorNumeroABB(
            raiz->esquerda, estado, cidade,
            numero); // Numero esta localizado na subarvore esquerda
      }
      else if (raiz->candidato.numero < numero)
      {
        buscarPorNumeroABB(
            raiz->direita, estado, cidade,
            numero); // Numero esta localizado na subarvore direita
      }
      else
      {
        imprimirCandidatoABB(&(raiz->candidato));
        buscarPorNumeroABB(raiz->esquerda, estado, cidade,
                           numero); // Verifica a subarvore esquerda
        buscarPorNumeroABB(raiz->direita, estado, cidade,
                           numero); // Verifica a subarvore direita
      }
    }
  }
}

// Funcoes de imprimir

void imprimirCandidatoABB(
    Candidato *c) // Imprime um candidato da arvore binaria
{
  if (c != NULL)
  {
    printf("\n=================CANDIDATO=================\n");
    printf("Nome: %s\n", c->nome);
    printf("Nome de Urna: %s\n", c->nomeUrna);
    printf("Numero: %d\n", c->numero);
    printf("Cargo: %s\n", c->cargo);
    printf("Estado: %s\n", c->estado);
    printf("Cidade: %s\n", c->cidade);
    printf("Sigla: %s\n", c->sigla);
    printf("Genero: %s\n", c->genero);
    printf("Grau de Instrucao: %s\n", c->grauInstrucao);
    printf("Cor: %s\n", c->cor);
  }
}

void liberarArvoreABB(No *raiz) // Liberar memoria da arvore binaria
{
  if (raiz == NULL)
  {
    return;
  }
  liberarArvoreABB(raiz->esquerda);
  liberarArvoreABB(raiz->direita);
  free(raiz);
}

void destruirArvoreABB(Arvore *a) // Destroi e libera memoria da arvore inteira
{
  liberarArvoreABB(a->raiz);
  a->raiz = NULL;
}

// Imprimir por Genero

// Listar candidatos por genero quando pesquisar por cidade
void listarCandidatosGeneroCABB(No *raiz, const char *estado,
                                const char *cidade, const char *genero)
{
  if (raiz == NULL)
  {
    return;
  }

  if (strcmp(raiz->candidato.estado, estado) > 0)
  {
    listarCandidatosGeneroCABB(
        raiz->esquerda, estado, cidade,
        genero); // Estado esta localizado na subarvore esquerda
  }
  else if (strcmp(raiz->candidato.estado, estado) < 0)
  {
    listarCandidatosGeneroCABB(
        raiz->direita, estado, cidade,
        genero); // Estado esta localizado na subarvore da direita
  }
  else
  {
    if (strcmp(raiz->candidato.cidade, cidade) > 0)
    {
      listarCandidatosGeneroCABB(
          raiz->esquerda, estado, cidade,
          genero); // Cidade esta localizada na subarvore esquerda
    }
    else if (strcmp(raiz->candidato.cidade, cidade) < 0)
    {
      listarCandidatosGeneroCABB(
          raiz->direita, estado, cidade,
          genero); // Cidade esta localizada na subarvore direita
    }
    else
    {
      if (strcmp(raiz->candidato.genero, genero) ==
          0)
      { // Se o candidato for do genero buscado, ele é impresso
        imprimirCandidatoABB(&(raiz->candidato));
      }
      listarCandidatosGeneroCABB(raiz->esquerda, estado, cidade,
                                 genero); // Verifica subarvore a esquerda
      listarCandidatosGeneroCABB(raiz->direita, estado, cidade,
                                 genero); // Verifica subarvore a direita
    }
  }
}

// Listar candidatos por genero quando pesquisar por estado
void listarCandidatosGeneroEABB(No *raiz, const char *estado,
                                const char *genero)
{
  if (raiz == NULL)
  {
    return;
  }
  if (strcmp(raiz->candidato.estado, estado) > 0)
  {
    listarCandidatosGeneroEABB(
        raiz->esquerda, estado,
        genero); // Estado esta localizado na subarvore da esquerda
  }
  else if (strcmp(raiz->candidato.estado, estado) < 0)
  {
    listarCandidatosGeneroEABB(
        raiz->direita, estado,
        genero); // Estado esta localizado na sub arvore da direita
  }
  else
  {
    if (strcmp(raiz->candidato.genero, genero) ==
        0)
    { // Se o candidato for do genero buscado, ele é impresso
      imprimirCandidatoABB(&(raiz->candidato));
    }
    listarCandidatosGeneroEABB(raiz->esquerda, estado,
                               genero); // Verifica subarvore a esquerda
    listarCandidatosGeneroEABB(raiz->direita, estado,
                               genero); // Verifica subarvore a direita
  }
}

// Listar candidatos por genero quando pesquisar numero
void listarCandidatosGeneroNABB(No *raiz, const char *estado,
                                const char *cidade, int num,
                                const char *genero)
{
  if (raiz == NULL)
  {
    return;
  }

  if (strcmp(raiz->candidato.estado, estado) > 0)
  {
    listarCandidatosGeneroNABB(
        raiz->esquerda, estado, cidade, num,
        genero); // Estado esta localizado na subarvore esquerda
  }
  else if (strcmp(raiz->candidato.estado, estado) < 0)
  {
    listarCandidatosGeneroNABB(
        raiz->direita, estado, cidade, num,
        genero); // Estado esta localizado na subarvore da direita
  }
  else
  {
    if (strcmp(raiz->candidato.cidade, cidade) > 0)
    {
      listarCandidatosGeneroNABB(
          raiz->esquerda, estado, cidade, num,
          genero); // Cidade esta localizada na subarvore esquerda
    }
    else if (strcmp(raiz->candidato.cidade, cidade) < 0)
    {
      listarCandidatosGeneroNABB(
          raiz->direita, estado, cidade, num,
          genero); // Cidade esta localizada na subarvore direita
    }
    else
    {
      if (raiz->candidato.numero > num)
      {
        listarCandidatosGeneroNABB(
            raiz->esquerda, estado, cidade, num,
            genero); // Numero esta localizado na subarvore esquerda
      }
      else if (raiz->candidato.numero < num)
      {
        listarCandidatosGeneroNABB(
            raiz->direita, estado, cidade, num,
            genero); // Numero esta localizado na subarvore direita
      }
      else
      {
        if (strcmp(raiz->candidato.genero, genero) ==
            0)
        { // Se o candidato for do genero buscado, ele é impresso
          imprimirCandidatoABB(&(raiz->candidato));
        }
        listarCandidatosGeneroNABB(raiz->esquerda, estado, cidade, num,
                                   genero); // Verifica a subarvore esquerda
        listarCandidatosGeneroNABB(raiz->direita, estado, cidade, num,
                                   genero); // Verifica a subarvore direita
      }
    }
  }
}

// Imprimir partido

// Listar candidatos por partido quando pesquisar por cidade
void listarCandidatosPartidoCABB(No *raiz, const char *estado,
                                 const char *cidade, const char *partido)
{
  if (raiz == NULL)
  {
    return;
  }

  if (strcmp(raiz->candidato.estado, estado) > 0)
  {
    listarCandidatosPartidoCABB(
        raiz->esquerda, estado, cidade,
        partido); // Estado esta localizado na subarvore esquerda
  }
  else if (strcmp(raiz->candidato.estado, estado) < 0)
  {
    listarCandidatosPartidoCABB(
        raiz->direita, estado, cidade,
        partido); // Estado esta localizado na subarvore da direita
  }
  else
  {
    if (strcmp(raiz->candidato.cidade, cidade) > 0)
    {
      listarCandidatosPartidoCABB(
          raiz->esquerda, estado, cidade,
          partido); // Cidade esta localizada na subarvore esquerda
    }
    else if (strcmp(raiz->candidato.cidade, cidade) < 0)
    {
      listarCandidatosPartidoCABB(
          raiz->direita, estado, cidade,
          partido); // Cidade esta localizada na subarvore direita
    }
    else
    {
      if (strcmp(raiz->candidato.sigla, partido) ==
          0)
      { // Se o candidato for do partido buscado, ele é impresso
        imprimirCandidatoABB(&(raiz->candidato));
      }
      listarCandidatosPartidoCABB(raiz->esquerda, estado, cidade,
                                  partido); // Verifica a subarvore esquerda
      listarCandidatosPartidoCABB(raiz->direita, estado, cidade,
                                  partido); // Verifica a subarvore direita
    }
  }
}

// Listar candidatos por partido quando pesquisar por estado
void listarCandidatosPartidoEABB(No *raiz, const char *estado,
                                 const char *partido)
{
  if (raiz == NULL)
  {
    return;
  }
  if (strcmp(raiz->candidato.estado, estado) > 0)
  {
    listarCandidatosPartidoEABB(
        raiz->esquerda, estado,
        partido); // Estado esta localizado na subarvore da esquerda
  }
  else if (strcmp(raiz->candidato.estado, estado) < 0)
  {
    listarCandidatosPartidoEABB(
        raiz->direita, estado,
        partido); // Estado esta localizado na sub arvore da direita
  }
  else
  {
    if (strcmp(raiz->candidato.sigla, partido) ==
        0)
    { // Se o candidato for do partido buscado, ele é impresso
      imprimirCandidatoABB(&(raiz->candidato));
    }
    listarCandidatosPartidoEABB(raiz->esquerda, estado,
                                partido); // Verifica a subarvore esquerda
    listarCandidatosPartidoEABB(raiz->direita, estado,
                                partido); // Verifica a subarvore direita
  }
}

// Listar candidatos por partido quando pesquisar por numero
void listarCandidatosPartidoNABB(No *raiz, const char *estado,
                                 const char *cidade, int num,
                                 const char *partido)
{
  if (raiz == NULL)
  {
    return;
  }

  if (strcmp(raiz->candidato.estado, estado) > 0)
  {
    listarCandidatosPartidoNABB(
        raiz->esquerda, estado, cidade, num,
        partido); // Estado esta localizado na subarvore esquerda
  }
  else if (strcmp(raiz->candidato.estado, estado) < 0)
  {
    listarCandidatosPartidoNABB(
        raiz->direita, estado, cidade, num,
        partido); // Estado esta localizado na subarvore da direita
  }
  else
  {
    if (strcmp(raiz->candidato.cidade, cidade) > 0)
    {
      listarCandidatosPartidoNABB(
          raiz->esquerda, estado, cidade, num,
          partido); // Cidade esta localizada na subarvore esquerda
    }
    else if (strcmp(raiz->candidato.cidade, cidade) < 0)
    {
      listarCandidatosPartidoNABB(
          raiz->direita, estado, cidade, num,
          partido); // Cidade esta localizada na subarvore direita
    }
    else
    {
      if (raiz->candidato.numero > num)
      {
        listarCandidatosPartidoNABB(
            raiz->esquerda, estado, cidade, num,
            partido); // Numero esta localizado na subarvore esquerda
      }
      else if (raiz->candidato.numero < num)
      {
        listarCandidatosPartidoNABB(
            raiz->direita, estado, cidade, num,
            partido); // Numero esta localizado na subarvore direita
      }
      else
      {
        if (strcmp(raiz->candidato.sigla, partido) ==
            0)
        { // Se o candidato for do partido buscado, ele é impresso
          imprimirCandidatoABB(&(raiz->candidato));
        }
        listarCandidatosPartidoNABB(raiz->esquerda, estado, cidade, num,
                                    partido); // Verifica a subarvore esquerda
        listarCandidatosPartidoNABB(raiz->direita, estado, cidade, num,
                                    partido); // Verifica a subarvore direita
      }
    }
  }
}

// Imprimir cor

// Listar candidatos por cor quando pesquisar por cidade
void listarCandidatosCorCABB(No *raiz, char *estado, char *cidade, char *cor)
{
  if (raiz == NULL)
  {
    return;
  }

  limparStringABB(cor);
  limparStringABB(raiz->candidato.cor);

  if (strcmp(raiz->candidato.estado, estado) > 0)
  {
    listarCandidatosCorCABB(
        raiz->esquerda, estado, cidade,
        cor); // Estado esta localizado na subarvore esquerda
  }
  else if (strcmp(raiz->candidato.estado, estado) < 0)
  {
    listarCandidatosCorCABB(
        raiz->direita, estado, cidade,
        cor); // Estado esta localizado na subarvore da direita
  }
  else
  {
    if (strcmp(raiz->candidato.cidade, cidade) > 0)
    {
      listarCandidatosCorCABB(
          raiz->esquerda, estado, cidade,
          cor); // Cidade esta localizada na subarvore esquerda
    }
    else if (strcmp(raiz->candidato.cidade, cidade) < 0)
    {
      listarCandidatosCorCABB(
          raiz->direita, estado, cidade,
          cor); // Cidade esta localizada na subarvore direita
    }
    else
    {
      if (strcmp(raiz->candidato.cor, cor) ==
          0)
      { // Se o candidato for da cor/raca buscado, ele é impresso
        imprimirCandidatoABB(&(raiz->candidato));
      }
      listarCandidatosCorCABB(raiz->esquerda, estado, cidade,
                              cor); // Verifica a subarvore esquerda
      listarCandidatosCorCABB(raiz->direita, estado, cidade,
                              cor); // Verifica a subarvore direita
    }
  }
}

// Listar candidatos por cor quando pesquisar por estado
void listarCandidatosCorEABB(No *raiz, char *estado, char *cor)
{
  if (raiz == NULL)
  {
    return;
  }
  limparStringABB(cor);
  limparStringABB(raiz->candidato.cor);

  if (strcmp(raiz->candidato.estado, estado) > 0)
  {
    listarCandidatosCorEABB(
        raiz->esquerda, estado,
        cor); // Estado esta localizado na subarvore da esquerda
  }
  else if (strcmp(raiz->candidato.estado, estado) < 0)
  {
    listarCandidatosCorEABB(
        raiz->direita, estado,
        cor); // Estado esta localizado na sub arvore da direita
  }
  else
  {
    if (strcmp(raiz->candidato.cor, cor) ==
        0)
    { // Se o candidato for da cor/raca buscado, ele é impresso
      imprimirCandidatoABB(&(raiz->candidato));
    }
    listarCandidatosCorEABB(raiz->esquerda, estado,
                            cor); // Verifica a subarvore esquerda
    listarCandidatosCorEABB(raiz->direita, estado,
                            cor); // Verifica a subarvore direita
  }
}

// Listar candidatos por cor quando pesquisar por numero
void listarCandidatosCorNABB(No *raiz, char *estado, char *cidade, int num, char *cor)
{
  if (raiz == NULL)
  {
    return;
  }

  limparStringABB(cor);
  limparStringABB(raiz->candidato.cor);

  if (strcmp(raiz->candidato.estado, estado) > 0)
  {
    listarCandidatosCorNABB(
        raiz->esquerda, estado, cidade, num,
        cor); // Estado esta localizado na subarvore esquerda
  }
  else if (strcmp(raiz->candidato.estado, estado) < 0)
  {
    listarCandidatosCorNABB(
        raiz->direita, estado, cidade, num,
        cor); // Estado esta localizado na subarvore da direita
  }
  else
  {
    if (strcmp(raiz->candidato.cidade, cidade) > 0)
    {
      listarCandidatosCorNABB(
          raiz->esquerda, estado, cidade, num,
          cor); // Cidade esta localizada na subarvore esquerda
    }
    else if (strcmp(raiz->candidato.cidade, cidade) < 0)
    {
      listarCandidatosCorNABB(
          raiz->direita, estado, cidade, num,
          cor); // Cidade esta localizada na subarvore direita
    }
    else
    {
      if (raiz->candidato.numero > num)
      {
        listarCandidatosCorNABB(
            raiz->esquerda, estado, cidade, num,
            cor); // Numero esta localizado na subarvore esquerda
      }
      else if (raiz->candidato.numero < num)
      {
        listarCandidatosCorNABB(
            raiz->direita, estado, cidade, num,
            cor); // Numero esta localizado na subarvore direita
      }
      else
      {
        if (strcmp(raiz->candidato.cor, cor) ==
            0)
        { // Se o candidato for da cor/raca buscado, ele é impresso
          imprimirCandidatoABB(&(raiz->candidato));
        }
        listarCandidatosCorNABB(raiz->esquerda, estado, cidade, num,
                                cor); // Verifica a subarvore esquerda
        listarCandidatosCorNABB(raiz->direita, estado, cidade, num,
                                cor); // Verifica a subarvore direita
      }
    }
  }
}