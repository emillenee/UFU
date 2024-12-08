// Codigos de arvore AVL foram baseados no material do professor Andre Backes

#include "arvoreAVL.h"
#include "candidato.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void criarArvoreAVL(ArvoreAVL *a) // Cria uma arvore com raiz NULL
{
  a->raiz = NULL;
}

int arvoreVaziaAVL(ArvoreAVL *a) // Verifica se a arvore esta vazia
{
  return (a->raiz == NULL);
}

NoAVL *criarN_AVL(Candidato valor) // Cria um novo no
{
  NoAVL *novo = (NoAVL *)malloc(sizeof(NoAVL));
  novo->candidato = valor;
  novo->fator = 0;
  novo->altura = 0;
  novo->direita = NULL;
  novo->esquerda = NULL;
  return novo;
}

int alturaNo(NoAVL *no) // Retorna a altura de um no
{
  if (no == NULL) // Caso NULL, altura = -1
    return -1;
  return no->altura; // Caso noo seja NULL, retorna a altura salva em sua struct
}

int fatorBalanceamento(
    NoAVL *n) // Calcula e retorna o fator de balanceamento do no
{
  if (n == NULL) // Se no NULL, seu fator e 0
    return 0;
  return alturaNo(n->esquerda) -
         alturaNo(n->direita); // Retorna o fator calculado pela diferenoa da
                               // altura esquerda e da altura direita
}

int maior(
    int x,
    int y) // Compara dois valores(altura esquerda e direita) e retorna o maior
{
  return (x > y) ? x : y;
}

void RotacaoLL(NoAVL **raiz) // Realiza uma rotacao simples para a direita
{
  if (*raiz == NULL || (*raiz)->esquerda == NULL)
    return;                        // Verificacao de nulos
  NoAVL *no = (*raiz)->esquerda;   // Caso noo NULL, cria um novo no com o filho a
                                   // esquerda da raiz
  (*raiz)->esquerda = no->direita; // Raiz->esquerda aponta para no->direita
  no->direita = *raiz;             // no->direita aponta para raiz
  (*raiz)->altura =
      maior(alturaNo((*raiz)->esquerda), alturaNo((*raiz)->direita)) +
      1; // Calcula nova altura
  no->altura = maior(alturaNo(no->esquerda), alturaNo(no->direita)) +
               1; // Calcula nova altura
  *raiz = no;     // Reenderecar a raiz
}

void RotacaoRR(NoAVL **raiz) // Realiza uma rotacao simples para a esquerda
{
  if (*raiz == NULL || (*raiz)->direita == NULL)
    return; // Verificacao de nulos
  NoAVL *no =
      (*raiz)
          ->direita;               // Caso no NULL, cria novo no com filho a direita da raiz
  (*raiz)->direita = no->esquerda; // Raiz->direita aponta para no->esquerda
  no->esquerda = *raiz;            // no->esquerda aponta para raiz
  (*raiz)->altura =
      maior(alturaNo((*raiz)->esquerda), alturaNo((*raiz)->direita)) +
      1; // Calcula nova altura
  no->altura = maior(alturaNo(no->esquerda), alturaNo(no->direita)) +
               1; // Calcula nova altura
  *raiz = no;     // Reenderecar a raiz
}

void RotacaoLR(NoAVL **raiz) // Realiza uma rotacao Direita-Esquerda
{
  if (*raiz == NULL || (*raiz)->esquerda == NULL)
    return;                      // Verificacao de nulos
  RotacaoRR(&(*raiz)->esquerda); // Primeiro, rotacao simples a esquerda com
                                 // raiz->esquerda como pivo
  RotacaoLL(raiz);               // Rotacao simples a direita com raiz como pivo
}

void RotacaoRL(NoAVL **raiz) // Realiza uma rotacao Esquerda-Direita
{
  if (*raiz == NULL || (*raiz)->direita == NULL)
    return;                     // Verificacao de nulos
  RotacaoLL(&(*raiz)->direita); // Primeiro, rotacao simples a direita com
                                // raiz->direita como pivo
  RotacaoRR(raiz);              // Rotacao simples a esquerda com raiz como pivo
}

NoAVL *insereAVL(NoAVL **raiz, Candidato valor)
{
  if (*raiz == NULL)
  {
    return criarN_AVL(valor);
  }

  int estadoCmp = strcmp(valor.estado, (*raiz)->candidato.estado);

  if (estadoCmp < 0)
  {
    (*raiz)->esquerda = insereAVL(&(*raiz)->esquerda, valor);
  }
  else if (estadoCmp > 0)
  {
    (*raiz)->direita = insereAVL(&(*raiz)->direita, valor);
  }
  else
  {
    int cidadeCmp = strcmp(valor.cidade, (*raiz)->candidato.cidade);
    if (cidadeCmp < 0)
    {
      (*raiz)->esquerda = insereAVL(&(*raiz)->esquerda, valor);
    }
    else if (cidadeCmp > 0)
    {
      (*raiz)->direita = insereAVL(&(*raiz)->direita, valor);
    }
    else
    {
      if (valor.numero < (*raiz)->candidato.numero)
      {
        (*raiz)->esquerda = insereAVL(&(*raiz)->esquerda, valor);
      }
      else
      {
        (*raiz)->direita = insereAVL(&(*raiz)->direita, valor);
      }
    }
  }
  (*raiz)->altura =
      maior(alturaNo((*raiz)->esquerda), alturaNo((*raiz)->direita)) + 1;
  (*raiz)->fator = alturaNo((*raiz)->esquerda) - alturaNo((*raiz)->direita);

  // Verifica e aplica rotações se necessário
  return balancearAVL(raiz);
}

// Balanceia a arvore apos as inserções
NoAVL *balancearAVL(NoAVL **raiz)
{
  int fator = fatorBalanceamento(*raiz);

  // Desbalanceamento à esquerda (fator > 1)
  if (fator > 1)
  {
    // Verifica se o desbalanceamento é do tipo LL ou LR
    if (fatorBalanceamento((*raiz)->esquerda) >= 0)
    {
      RotacaoLL(raiz); // Rotação simples para a direita
    }
    else // Caso LR (subárvore esquerda-direita mais pesada)
    {
      RotacaoLR(raiz); // Rotação dupla esquerda-direita
    }
  }
  // Desbalanceamento à direita (fator < -1)
  else if (fator < -1)
  {
    // Verifica se o desbalanceamento é do tipo RR ou RL
    if (fatorBalanceamento((*raiz)->direita) <= 0)
    {
      RotacaoRR(raiz); // Rotação simples para a esquerda
    }
    else // Caso RL (subárvore direita-esquerda mais pesada)
    {
      RotacaoRL(raiz); // Rotação dupla direita-esquerda
    }
  }

  return *raiz;
}

void limparStringAVL(char *str)
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

void lerArquivoAVL(
    ArvoreAVL *a, const char *nomeArquivo) // Leitura do arquivo como arvore AVL
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
    a->raiz = insereAVL(&a->raiz, candidato); // Insercao do novo no
  }
  fclose(arquivo);
}

// Funcoes de busca
void buscarPorEstadoAVL(
    NoAVL *raiz,
    const char *estado) // Buscar em arvore binaria com estado como chave
{
  if (raiz == NULL)
  {
    return;
  }
  if (strcmp(raiz->candidato.estado, estado) > 0)
  {
    buscarPorEstadoAVL(
        raiz->esquerda,
        estado); // Estado esta localizado na subarvore da esquerda
  }
  else if (strcmp(raiz->candidato.estado, estado) < 0)
  {
    buscarPorEstadoAVL(
        raiz->direita,
        estado); // Estado esta localizado na subarvore da direita
  }
  else
  {
    imprimirCandidatoAVL(
        &(raiz->candidato));                    // Imprime candidato se o estado for igual
    buscarPorEstadoAVL(raiz->esquerda, estado); // Verifica subarvore a esquerda
    buscarPorEstadoAVL(raiz->direita, estado);  // Veifica subarvore a direita
  }
}

void buscarPorCidadeAVL(
    NoAVL *raiz, const char *estado,
    const char *cidade)
{ // Buscar em arvore AVL com estado e cidade
  if (raiz == NULL)
  {
    return;
  }
  if (strcmp(raiz->candidato.estado, estado) > 0)
  {
    buscarPorCidadeAVL(raiz->esquerda, estado,
                       cidade); // Estado esta localizado na subarvore esquerda
  }
  else if (strcmp(raiz->candidato.estado, estado) < 0)
  {
    buscarPorCidadeAVL(
        raiz->direita, estado,
        cidade); // Estado esta localizado na subarvore da direita
  }
  else
  {
    if (strcmp(raiz->candidato.cidade, cidade) > 0)
    {
      buscarPorCidadeAVL(raiz->esquerda, estado, cidade);
    }
    else if (strcmp(raiz->candidato.cidade, cidade) < 0)
    {
      buscarPorCidadeAVL(raiz->direita, estado, cidade);
    }
    else
    {
      imprimirCandidatoAVL(
          &(raiz->candidato)); // Imprime candidato se a cidade for igual
      buscarPorCidadeAVL(raiz->esquerda, estado, cidade);
      buscarPorCidadeAVL(raiz->direita, estado, cidade);
    }
  }
}

void buscarPorNumeroAVL(NoAVL *raiz, const char *estado, const char *cidade,
                        int numero)
{ // Buscar em arvore binaria com estado,
  // cidade e numero como chaves
  if (raiz == NULL)
  {
    return;
  }

  if (strcmp(raiz->candidato.estado, estado) > 0)
  {
    buscarPorNumeroAVL(raiz->esquerda, estado, cidade,
                       numero); // Estado esta localizado na subarvore esquerda
  }
  else if (strcmp(raiz->candidato.estado, estado) < 0)
  {
    buscarPorNumeroAVL(
        raiz->direita, estado, cidade,
        numero); // Estado esta localizado na subarvore da direita
  }
  else
  {
    if (strcmp(raiz->candidato.cidade, cidade) > 0)
    {
      buscarPorNumeroAVL(
          raiz->esquerda, estado, cidade,
          numero); // Cidade esta localizada na subarvore esquerda
    }
    else if (strcmp(raiz->candidato.cidade, cidade) < 0)
    {
      buscarPorNumeroAVL(raiz->direita, estado, cidade,
                         numero); // Cidade esta localizada na subarvore direita
    }
    else
    {
      if (raiz->candidato.numero > numero)
      {
        buscarPorNumeroAVL(
            raiz->esquerda, estado, cidade,
            numero); // Numero esta localizado na subarvore esquerda
      }
      else if (raiz->candidato.numero < numero)
      {
        buscarPorNumeroAVL(
            raiz->direita, estado, cidade,
            numero); // Numero esta localizado na subarvore direita
      }
      else
      {
        imprimirCandidatoAVL(&(raiz->candidato));
        buscarPorNumeroAVL(raiz->esquerda, estado, cidade,
                           numero); // Verifica a subarvore esquerda
        buscarPorNumeroAVL(raiz->direita, estado, cidade,
                           numero); // Verifica a subarvore direita
      }
    }
  }
}

void imprimirCandidatoAVL(Candidato *c) // Imprime um candidato da arvore AVL
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

void liberarArvoreAVL(NoAVL *raiz)
{ // Libera a memoria do no da arvore AVL
  if (raiz == NULL)
  {
    return;
  }
  liberarArvoreAVL(raiz->esquerda);
  liberarArvoreAVL(raiz->direita);
  free(raiz);
}

void destruirArvoreAVL(ArvoreAVL *a)
{ // Destroi e libera toda a arvore avl
  liberarArvoreAVL(a->raiz);
  a->raiz = NULL;
}

// Funcoes de busca e listagem de genero, raca/cor e partido

// Imprimir Genero

// Imprimir todos candidatos de um determinado genero de alguma cidade
void listarCandidatosGeneroCAVL(NoAVL *raiz, const char *estado,
                                const char *cidade, const char *genero)
{
  if (raiz == NULL)
  {
    return;
  }

  if (strcmp(raiz->candidato.estado, estado) > 0)
  {
    listarCandidatosGeneroCAVL(
        raiz->esquerda, estado, cidade,
        genero); // Estado esta localizado na subarvore esquerda
  }
  else if (strcmp(raiz->candidato.estado, estado) < 0)
  {
    listarCandidatosGeneroCAVL(
        raiz->direita, estado, cidade,
        genero); // Estado esta localizado na subarvore da direita
  }
  else
  {
    if (strcmp(raiz->candidato.cidade, cidade) > 0)
    {
      listarCandidatosGeneroCAVL(
          raiz->esquerda, estado, cidade,
          genero); // Cidade esta localizada na subarvore esquerda
    }
    else if (strcmp(raiz->candidato.cidade, cidade) < 0)
    {
      listarCandidatosGeneroCAVL(
          raiz->direita, estado, cidade,
          genero); // Cidade esta localizada na subarvore direita
    }
    else
    {
      if (strcmp(raiz->candidato.genero, genero) ==
          0)
      { // Se o candidato for do genero buscado, ele é impresso
        imprimirCandidatoAVL(&(raiz->candidato));
      }
      listarCandidatosGeneroCAVL(raiz->esquerda, estado, cidade,
                                 genero); // Verifica a subarvore esquerda
      listarCandidatosGeneroCAVL(raiz->direita, estado, cidade,
                                 genero); // Verifica a subarvore direita
    }
  }
}

// Imprimir todos candidatos de um determinado genero de algum estado
void listarCandidatosGeneroEAVL(NoAVL *raiz, const char *estado,
                                const char *genero)
{
  if (raiz == NULL)
  {
    return;
  }
  if (strcmp(raiz->candidato.estado, estado) > 0)
  {
    listarCandidatosGeneroEAVL(
        raiz->esquerda, estado,
        genero); // Estado esta localizado na subarvore da esquerda
  }
  else if (strcmp(raiz->candidato.estado, estado) < 0)
  {
    listarCandidatosGeneroEAVL(
        raiz->direita, estado,
        genero); // Estado esta localizado na sub arvore da direita
  }
  else
  {
    if (strcmp(raiz->candidato.genero, genero) ==
        0)
    { // Se o candidato for do genero buscado, ele é impresso
      imprimirCandidatoAVL(&(raiz->candidato));
    }
    listarCandidatosGeneroEAVL(raiz->esquerda, estado,
                               genero); // Verifica a subarvore esquerda
    listarCandidatosGeneroEAVL(raiz->direita, estado,
                               genero); // Verifica a subarvore direita
  }
}

// Imprimir candidatos de um genero apos pesquisa por numero
void listarCandidatosGeneroNAVL(NoAVL *raiz, const char *estado,
                                const char *cidade, int num,
                                const char *genero)
{
  if (raiz == NULL)
  {
    return;
  }

  if (strcmp(raiz->candidato.estado, estado) > 0)
  {
    listarCandidatosGeneroNAVL(
        raiz->esquerda, estado, cidade, num,
        genero); // Estado esta localizado na subarvore esquerda
  }
  else if (strcmp(raiz->candidato.estado, estado) < 0)
  {
    listarCandidatosGeneroNAVL(
        raiz->direita, estado, cidade, num,
        genero); // Estado esta localizado na subarvore da direita
  }
  else
  {
    if (strcmp(raiz->candidato.cidade, cidade) > 0)
    {
      listarCandidatosGeneroNAVL(
          raiz->esquerda, estado, cidade, num,
          genero); // Cidade esta localizada na subarvore esquerda
    }
    else if (strcmp(raiz->candidato.cidade, cidade) < 0)
    {
      listarCandidatosGeneroNAVL(
          raiz->direita, estado, cidade, num,
          genero); // Cidade esta localizada na subarvore direita
    }
    else
    {
      if (raiz->candidato.numero > num)
      {
        listarCandidatosGeneroNAVL(
            raiz->esquerda, estado, cidade, num,
            genero); // Numero esta localizado na subarvore esquerda
      }
      else if (raiz->candidato.numero < num)
      {
        listarCandidatosGeneroNAVL(
            raiz->direita, estado, cidade, num,
            genero); // Numero esta localizado na subarvore direita
      }
      else
      {
        if (strcmp(raiz->candidato.genero, genero) ==
            0)
        { // Se o candidato for do genero buscado, ele é impresso
          imprimirCandidatoAVL(&(raiz->candidato));
        }
        listarCandidatosGeneroNAVL(raiz->esquerda, estado, cidade, num,
                                   genero); // Verifica a subarvore esquerda
        listarCandidatosGeneroNAVL(raiz->direita, estado, cidade, num,
                                   genero); // Verifica a subarvore direita
      }
    }
  }
}

// Imprimir Partido

// Imprimir todos candidatos de um determinado partido de alguma cidade
void listarCandidatosPartidoCAVL(NoAVL *raiz, const char *estado,
                                 const char *cidade, const char *partido)
{
  if (raiz == NULL)
  {
    return;
  }

  if (strcmp(raiz->candidato.estado, estado) > 0)
  {
    listarCandidatosPartidoCAVL(
        raiz->esquerda, estado, cidade,
        partido); // Estado esta localizado na subarvore esquerda
  }
  else if (strcmp(raiz->candidato.estado, estado) < 0)
  {
    listarCandidatosPartidoCAVL(
        raiz->direita, estado, cidade,
        partido); // Estado esta localizado na subarvore da direita
  }
  else
  {
    if (strcmp(raiz->candidato.cidade, cidade) > 0)
    {
      listarCandidatosPartidoCAVL(
          raiz->esquerda, estado, cidade,
          partido); // Cidade esta localizada na subarvore esquerda
    }
    else if (strcmp(raiz->candidato.cidade, cidade) < 0)
    {
      listarCandidatosPartidoCAVL(
          raiz->direita, estado, cidade,
          partido); // Cidade esta localizada na subarvore direita
    }
    else
    {
      if (strcmp(raiz->candidato.sigla, partido) ==
          0)
      { // Se o candidato for do genero buscado, ele é impresso
        imprimirCandidatoAVL(&(raiz->candidato));
      }
      listarCandidatosPartidoCAVL(raiz->esquerda, estado, cidade,
                                  partido); // Verifica a subarvore esquerda
      listarCandidatosPartidoCAVL(raiz->direita, estado, cidade,
                                  partido); // Verifica a subarvore direita
    }
  }
}

// Imprimir todos candidatos de um determinado partido de algum estado
void listarCandidatosPartidoEAVL(NoAVL *raiz, const char *estado,
                                 const char *partido)
{
  if (raiz == NULL)
  {
    return;
  }
  if (strcmp(raiz->candidato.estado, estado) > 0)
  {
    listarCandidatosPartidoEAVL(
        raiz->esquerda, estado,
        partido); // Estado esta localizado na subarvore da esquerda
  }
  else if (strcmp(raiz->candidato.estado, estado) < 0)
  {
    listarCandidatosPartidoEAVL(
        raiz->direita, estado,
        partido); // Estado esta localizado na sub arvore da direita
  }
  else
  {
    if (strcmp(raiz->candidato.sigla, partido) ==
        0)
    { // Se o candidato for do partido buscado, ele é impresso
      imprimirCandidatoAVL(&(raiz->candidato));
    }
    listarCandidatosPartidoEAVL(raiz->esquerda, estado,
                                partido); // Verifica a subarvore esquerda
    listarCandidatosPartidoEAVL(raiz->direita, estado,
                                partido); // Verifica a subarvore direita
  }
}

// Imprimir candidatos de um partido apos pesquisa por numero
void listarCandidatosPartidoNAVL(NoAVL *raiz, const char *estado,
                                 const char *cidade, int num,
                                 const char *partido)
{
  if (raiz == NULL)
  {
    return;
  }

  if (strcmp(raiz->candidato.estado, estado) > 0)
  {
    listarCandidatosPartidoNAVL(
        raiz->esquerda, estado, cidade, num,
        partido); // Estado esta localizado na subarvore esquerda
  }
  else if (strcmp(raiz->candidato.estado, estado) < 0)
  {
    listarCandidatosPartidoNAVL(
        raiz->direita, estado, cidade, num,
        partido); // Estado esta localizado na subarvore da direita
  }
  else
  {
    if (strcmp(raiz->candidato.cidade, cidade) > 0)
    {
      listarCandidatosPartidoNAVL(
          raiz->esquerda, estado, cidade, num,
          partido); // Cidade esta localizada na subarvore esquerda
    }
    else if (strcmp(raiz->candidato.cidade, cidade) < 0)
    {
      listarCandidatosPartidoNAVL(
          raiz->direita, estado, cidade, num,
          partido); // Cidade esta localizada na subarvore direita
    }
    else
    {
      if (raiz->candidato.numero > num)
      {
        listarCandidatosPartidoNAVL(
            raiz->esquerda, estado, cidade, num,
            partido); // Numero esta localizado na subarvore esquerda
      }
      else if (raiz->candidato.numero < num)
      {
        listarCandidatosPartidoNAVL(
            raiz->direita, estado, cidade, num,
            partido); // Numero esta localizado na subarvore direita
      }
      else
      {
        if (strcmp(raiz->candidato.sigla, partido) ==
            0)
        { // Se o candidato for do partido buscado, ele é impresso
          imprimirCandidatoAVL(&(raiz->candidato));
        }
        listarCandidatosPartidoNAVL(raiz->esquerda, estado, cidade, num,
                                    partido); // Verifica a subarvore esquerda
        listarCandidatosPartidoNAVL(raiz->direita, estado, cidade, num,
                                    partido); // Verifica a subarvore direita
      }
    }
  }
}

// Imprimir Cor

// Imprimir todos candidatos de uma determinada cor de alguma cidade
void listarCandidatosCorCAVL(NoAVL *raiz, char *estado,
                             char *cidade, char *cor)
{
  if (raiz == NULL)
  {
    return;
  }

  limparStringAVL(cor);
  limparStringAVL(raiz->candidato.cor);

  if (strcmp(raiz->candidato.estado, estado) > 0)
  {
    listarCandidatosCorCAVL(
        raiz->esquerda, estado, cidade,
        cor); // Estado esta localizado na subarvore esquerda
  }
  else if (strcmp(raiz->candidato.estado, estado) < 0)
  {
    listarCandidatosCorCAVL(
        raiz->direita, estado, cidade,
        cor); // Estado esta localizado na subarvore da direita
  }
  else
  {
    if (strcmp(raiz->candidato.cidade, cidade) > 0)
    {
      listarCandidatosCorCAVL(
          raiz->esquerda, estado, cidade,
          cor); // Cidade esta localizada na subarvore esquerda
    }
    else if (strcmp(raiz->candidato.cidade, cidade) < 0)
    {
      listarCandidatosCorCAVL(
          raiz->direita, estado, cidade,
          cor); // Cidade esta localizada na subarvore direita
    }
    else
    {
      if (strcmp(raiz->candidato.cor, cor) ==
          0)
      { // Se o candidato for da cor/raca buscado, ele é impresso
        imprimirCandidatoAVL(&(raiz->candidato));
      }
      listarCandidatosCorCAVL(raiz->esquerda, estado, cidade,
                              cor); // Verifica a subarvore esquerda
      listarCandidatosCorCAVL(raiz->direita, estado, cidade,
                              cor); // Verifica a subarvore direita
    }
  }
}

// Imprimir todos candidatos de uma determinada cor de algum estado
void listarCandidatosCorEAVL(NoAVL *raiz, char *estado, char *cor)
{
  if (raiz == NULL)
  {
    return;
  }

  limparStringAVL(cor);
  limparStringAVL(raiz->candidato.cor);

  if (strcmp(raiz->candidato.estado, estado) > 0)
  {
    listarCandidatosCorEAVL(
        raiz->esquerda, estado,
        cor); // Estado esta localizado na subarvore da esquerda
  }
  else if (strcmp(raiz->candidato.estado, estado) < 0)
  {
    listarCandidatosCorEAVL(
        raiz->direita, estado,
        cor); // Estado esta localizado na sub arvore da direita
  }
  else
  {
    if (strcmp(raiz->candidato.cor, cor) ==
        0)
    { // Se o candidato for da cor/raca buscado, ele é impresso
      imprimirCandidatoAVL(&(raiz->candidato));
    }
    listarCandidatosCorEAVL(raiz->esquerda, estado,
                            cor); // Verifica a subarvore esquerda
    listarCandidatosCorEAVL(raiz->direita, estado,
                            cor); // Verifica a subarvore direita
  }
}

// Imprimir candidatos de uma cor apos pesquisa por numero
void listarCandidatosCorNAVL(NoAVL *raiz, char *estado, char *cidade, int num, char *cor)
{
  if (raiz == NULL)
  {
    return;
  }

  limparStringAVL(cor);
  limparStringAVL(raiz->candidato.cor);

  if (strcmp(raiz->candidato.estado, estado) > 0)
  {
    listarCandidatosCorNAVL(
        raiz->esquerda, estado, cidade, num,
        cor); // Estado esta localizado na subarvore esquerda
  }
  else if (strcmp(raiz->candidato.estado, estado) < 0)
  {
    listarCandidatosCorNAVL(
        raiz->direita, estado, cidade, num,
        cor); // Estado esta localizado na subarvore da direita
  }
  else
  {
    if (strcmp(raiz->candidato.cidade, cidade) > 0)
    {
      listarCandidatosCorNAVL(
          raiz->esquerda, estado, cidade, num,
          cor); // Cidade esta localizada na subarvore esquerda
    }
    else if (strcmp(raiz->candidato.cidade, cidade) < 0)
    {
      listarCandidatosCorNAVL(
          raiz->direita, estado, cidade, num,
          cor); // Cidade esta localizada na subarvore direita
    }
    else
    {
      if (raiz->candidato.numero > num)
      {
        listarCandidatosCorNAVL(
            raiz->esquerda, estado, cidade, num,
            cor); // Numero esta localizado na subarvore esquerda
      }
      else if (raiz->candidato.numero < num)
      {
        listarCandidatosCorNAVL(
            raiz->direita, estado, cidade, num,
            cor); // Numero esta localizado na subarvore direita
      }
      else
      {
        if (strcmp(raiz->candidato.cor, cor) ==
            0)
        { // Se o candidato for da cor/raca buscado, ele é impresso
          imprimirCandidatoAVL(&(raiz->candidato));
        }
        listarCandidatosCorNAVL(raiz->esquerda, estado, cidade, num,
                                cor); // Verifica a subarvore esquerda
        listarCandidatosCorNAVL(raiz->direita, estado, cidade, num,
                                cor); // Verifica a subarvore direita
      }
    }
  }
}