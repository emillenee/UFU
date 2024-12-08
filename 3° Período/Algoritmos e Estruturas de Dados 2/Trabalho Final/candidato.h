#ifndef CANDIDATO_H
#define CANDIDATO_H

typedef struct candidato { // Definicao da struct de candidato
  char estado[5];
  char cidade[50];
  int numero;
  char cargo[15];
  char nome[50];
  char nomeUrna[50];
  char sigla[15];
  char genero[15];
  char grauInstrucao[30];
  char cor[15];
} Candidato;

#endif
