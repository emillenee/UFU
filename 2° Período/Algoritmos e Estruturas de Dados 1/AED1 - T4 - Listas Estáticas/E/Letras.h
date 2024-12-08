#ifndef LETRAS_H_INCLUDED
#define LETRAS_H_INCLUDED

typedef struct letras{
    int quantidade;
}Letras;

typedef struct texto{
    char *text;
}Texto;

typedef struct lista Lista;

Lista *criar();
int inserir(Lista *l, char c);
void contarLetras(Lista *l);

#endif // LETRAS_H_INCLUDED
