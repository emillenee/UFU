#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Letras.h"

typedef struct lista{
    Letras letra[26];
    Texto *caracter;
    int tam_texto;
}Lista;
