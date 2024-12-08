typedef struct cep{
    char numero[10];
    char sigla[3];
    char nome[50];
    char endereco[100];
}Cep;

void lerArquivo(Cep *ceps, const char *nomeArquivo);

int buscaBinaria(Cep ceps[], int n, Cep busca);

void imprimirCidades(Cep ceps[]);