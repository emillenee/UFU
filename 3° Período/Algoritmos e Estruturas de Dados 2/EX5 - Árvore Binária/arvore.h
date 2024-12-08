typedef struct codigoPostal{
    char cep[10];
    char estado[3];
    char cidade[50];
    char rua[100];
}CodigoP;

typedef struct no{
    CodigoP valor;
    struct no *esquerdo;
    struct no *direito;
}No;

typedef struct raiz{
    No *raiz;
}Arvore;

void criarArvore(Arvore *a);
int arvoreVazia(Arvore *a);
int contarLinhas(const char *nomeArquivo);
void lerArquivoABB(Arvore *a, const char *nomeArquivo);
No* criarN(CodigoP valor);
No* inserirN(No *raiz, CodigoP valor);
No* inserirArvore(No *raiz, CodigoP valor);
No* removeArvore(No *raiz, CodigoP valor);
void pesquisar(No *raiz, CodigoP *cep);
void percorrerCentral(No *raiz);
void percorrerPreFixado(No *raiz);
void percorrerPosFixado(No *raiz);
int alturaArvore(No *raiz);
No* menorArvore(No *raiz);
No* maiorArvore(No *raiz);
void imprimirCodigoP(CodigoP *p);