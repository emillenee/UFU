#include "Grafos.h"
#include <string.h>

/* Definition of global variables */
TipoCidade Cidades[MAXNUMVERTICES];
int NArestas;
TipoPeso Peso;
TipoValorVertice NVertices;
long i;
short FimListaAdj;

/*--Entram aqui os operadores do Programa 2.4--*/
void FLVazia(TipoLista *Lista) {
  Lista->Primeiro = (TipoApontador)malloc(sizeof(TipoCelula));
  Lista->Ultimo = Lista->Primeiro;
  Lista->Primeiro->Prox = NULL;
}

short Vazia(TipoLista Lista) { return (Lista.Primeiro == Lista.Ultimo); }

void Insere(TipoItem *x, TipoLista *Lista) {
  /*-- Insere depois do ultimo item da lista --*/
  Lista->Ultimo->Prox = (TipoApontador)malloc(sizeof(TipoCelula));
  Lista->Ultimo = Lista->Ultimo->Prox;
  Lista->Ultimo->Item = *x;
  Lista->Ultimo->Prox = NULL;
}

/*-- Fim operadores do Programa 2.4 --*/
void FGVazio(TipoGrafo *Grafo) {
  long i;
  for (i = 0; i < Grafo->NumVertices; i++)
    FLVazia(&Grafo->Adj[i]);
}

void InsereAresta(TipoValorVertice *V1, TipoValorVertice *V2, TipoPeso *Peso,
                  TipoGrafo *Grafo) {
  TipoItem x;
  x.Vertice = *V2;
  x.Peso = *Peso;
  Insere(&x, &Grafo->Adj[*V1]);
}

short ExisteAresta(TipoValorVertice Vertice1, TipoValorVertice Vertice2,
                   TipoGrafo *Grafo, TipoPeso *Peso) {
  TipoApontador Aux;
  short EncontrouAresta = FALSE;
  Aux = Grafo->Adj[Vertice1].Primeiro->Prox;
  while (Aux != NULL && EncontrouAresta == FALSE) {
    if (Vertice2 == Aux->Item.Vertice) {
      EncontrouAresta = TRUE;
      *Peso = Aux->Item.Peso;
    }
    Aux = Aux->Prox;
  }
  return EncontrouAresta;
}

// TipoItem cidadesProximas[]
void cemKM(TipoValorVertice V, TipoGrafo *Grafo) {
  int f = 0;
  TipoApontador Aux;
  Aux = Grafo->Adj[V].Primeiro->Prox;
  printf("Cidades com ligação direta a menos de 100km de %s: \n",
         Cidades[V].Nome);
  while (Aux != NULL) {
    if (Aux->Item.Peso <= 100) {
      printf("%s - %dkm de distância\n", Cidades[Aux->Item.Vertice].Nome,
             Aux->Item.Peso);
      f = 1;
    }
    Aux = Aux->Prox;
  }
  if (f == 0) {
    printf("Não há cidades com até 100km de distância de %s\n",
           Cidades[V].Nome);
  }
}

/*
TipoItem cidadesProximas[]
void cemKM(TipoValorVertice Vertice, TipoGrafo *Grafo, ){
    aux = Grafo->Adj[Vertice];
    while(aux != NULL){
        if(peso < 100){

        }
    }
}
*/

/* Operadores para obter a lista de adjacentes */
short ListaAdjVazia(TipoValorVertice *Vertice, TipoGrafo *Grafo) {
  return (Grafo->Adj[*Vertice].Primeiro == Grafo->Adj[*Vertice].Ultimo);
}

TipoApontador PrimeiroListaAdj(TipoValorVertice *Vertice, TipoGrafo *Grafo) {
  return (Grafo->Adj[*Vertice].Primeiro->Prox);
}

void ProxAdj(TipoValorVertice *Vertice, TipoGrafo *Grafo, TipoValorVertice *Adj,
             TipoPeso *Peso, TipoApontador *Prox, short *FimListaAdj) {
  /* Retorna Adj e Peso do Item apontado por Prox */
  *Adj = (*Prox)->Item.Vertice;
  *Peso = (*Prox)->Item.Peso;
  *Prox = (*Prox)->Prox;
  if (*Prox == NULL)
    *FimListaAdj = TRUE;
}

void Retira(TipoApontador p, TipoLista *Lista, TipoItem *Item) {
  /*--Obs.: item a ser retirado e o seguinte ao apontado por p--*/
  TipoApontador q;
  if (Vazia(*Lista) || p == NULL || p->Prox == NULL) {
    printf("Erro: Lista vazia ou posicao nao existe\n");
    return;
  }
  q = p->Prox;
  *Item = q->Item;
  p->Prox = q->Prox;
  if (p->Prox == NULL)
    Lista->Ultimo = p;
  free(q);
}

void RetiraAresta(TipoValorVertice *V1, TipoValorVertice *V2, TipoPeso *Peso,
                  TipoGrafo *Grafo) {
  TipoApontador AuxAnterior, Aux;
  short EncontrouAresta = FALSE;
  TipoItem x;
  AuxAnterior = Grafo->Adj[*V1].Primeiro;
  Aux = Grafo->Adj[*V1].Primeiro->Prox;
  while (Aux != NULL && EncontrouAresta == FALSE) {
    if (*V2 == Aux->Item.Vertice) {
      Retira(AuxAnterior, &Grafo->Adj[*V1], &x);
      Grafo->NumArestas--;
      EncontrouAresta = TRUE;
    }
    AuxAnterior = Aux;
    Aux = Aux->Prox;
  }
}

void LiberaGrafo(TipoGrafo *Grafo) {
  TipoApontador AuxAnterior, Aux;
  for (i = 0; i < Grafo->NumVertices; i++) {
    Aux = Grafo->Adj[i].Primeiro->Prox;
    free(Grafo->Adj[i].Primeiro); /*Libera celula cabeca*/
    Grafo->Adj[i].Primeiro = NULL;
    while (Aux != NULL) {
      AuxAnterior = Aux;
      Aux = Aux->Prox;
      free(AuxAnterior);
    }
  }
  Grafo->NumVertices = 0;
}

void ImprimeGrafo(TipoGrafo *Grafo) {
  int i;
  TipoApontador Aux;
  for (i = 0; i < Grafo->NumVertices; i++) {
    printf("Cidade %d: %s ->", i + 1, Cidades[i].Nome);
    if (!Vazia(Grafo->Adj[i])) {
      Aux = Grafo->Adj[i].Primeiro->Prox;
      while (Aux != NULL) {
        printf(" %s (%d)", Cidades[Aux->Item.Vertice].Nome, Aux->Item.Peso);
        Aux = Aux->Prox;
      }
    }
    putchar('\n');
  }
}

void ImprimeLista(TipoLista Lista) {
  TipoApontador Aux;
  Aux = Lista.Primeiro->Prox;
  while (Aux != NULL) {
    printf("%3d (%12d)", Aux->Item.Vertice, Aux->Item.Peso);
    Aux = Aux->Prox;
  }
}

void GrafoTransposto(TipoGrafo *Grafo, TipoGrafo *GrafoT) {
  TipoValorVertice v, Adj;
  TipoPeso Peso;
  TipoApontador Aux;
  GrafoT->NumVertices = Grafo->NumVertices;
  GrafoT->NumArestas = Grafo->NumArestas;
  FGVazio(GrafoT);
  for (v = 0; v <= Grafo->NumVertices - 1; v++) {
    if (!ListaAdjVazia(&v, Grafo)) {
      Aux = PrimeiroListaAdj(&v, Grafo);
      FimListaAdj = FALSE;
      while (!FimListaAdj) {
        ProxAdj(&v, Grafo, &Adj, &Peso, &Aux, &FimListaAdj);
        InsereAresta(&Adj, &v, &Peso, GrafoT);
      }
    }
  }
}

// Função que lê os dados do arquivo .txt
void lerArquivo(TipoGrafo *Grafo, const char *nomeArquivo) {
  FILE *arquivo = fopen(nomeArquivo, "r");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo\n");
    return;
  }

  fscanf(arquivo, "%d", &Grafo->NumVertices);
  FGVazio(Grafo);

  // Ler os nomes das cidades
  for (int i = 0; i < Grafo->NumVertices; i++) {
    fscanf(arquivo, "%s", Cidades[i].Nome);
  }

  int numArestas;
  fscanf(arquivo, "%d", &numArestas);
  Grafo->NumArestas = 0;

  TipoValorVertice origem, destino;
  TipoPeso peso;
  for (int i = 0; i < numArestas; i++) {
    fscanf(arquivo, "%d,%d,%d", &origem, &destino, &peso);
    InsereAresta(&origem, &destino, &peso, Grafo);
  }

  fclose(arquivo);
}
