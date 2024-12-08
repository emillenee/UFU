#ifndef STRINGS_H_INCLUDED
#define STRINGS_H_INCLUDED

typedef struct string String;

String* criar();

void preencher(String *s);

int tamanho(String *s);

int contar(String *s, char c);

void mostrar(String *s);

#endif // STRINGS_H_INCLUDED
