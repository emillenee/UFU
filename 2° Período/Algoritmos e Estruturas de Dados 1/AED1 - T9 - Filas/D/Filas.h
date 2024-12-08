#ifndef FILAS_H_INCLUDED
#define FILAS_H_INCLUDED

typedef struct paciente {
    char nome[50];
}Paciente;

typedef struct fila Fila;

Fila *criar();
void limpar(Fila *f);
int inserirP(Fila *f, char *nome);
int atender(Fila *f);

void mostrar(Fila *f);
int filaVazia(Fila *f);

#endif // FILAS_H_INCLUDED
