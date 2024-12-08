#include "strings.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct string {
    char *palavra;
}String;

String* criar(){
    String *s = (String*) malloc (sizeof(String));
    s->palavra = NULL;
    return s;
}

void preencher(String *s){
    char c;
    int i = 0;
    while((c = getchar()) != '\n'){
        s->palavra = realloc(s->palavra, (i+1)*sizeof(char));
        s->palavra[i] = c;
        i++;
    }
    s->palavra = realloc(s->palavra, (i+1)*sizeof(char));
    s->palavra[i] = '\0';
}

int tamanho(String *s){
    int i = 0;
    while(s->palavra[i] != '\0'){
        i++;
    }
    return i;
}

int contar(String *s, char c){
    int t = tamanho(s);
    int contador = 0;
    for(int i = 0; i < t; i++){
        if(s->palavra[i] == c){
            contador++;
        }
    }
    return contador;
}

void mostrar(String *s){
    int t = tamanho(s);
    for(int i =0; i < t; i++){
        printf("%c", s->palavra[i]);
    }
    printf("\n");
}
