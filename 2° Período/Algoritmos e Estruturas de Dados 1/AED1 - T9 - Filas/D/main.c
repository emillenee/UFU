#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Filas.h"

int main()
{
    //criar a fila de pacientes
    Fila *f = criar();

    //adicionar pacientes a fila
    inserirP(f, "Joao");
    inserirP(f, "Maria");
    inserirP(f, "Pedro");
    printf("Esta eh a fila antes de comecar os atendimentos: \n");
    mostrar(f);

    printf("O medico esta pronto para receber um paciente.\n");
    atender(f);
    printf("Fila apos o atendimento: \n");
    mostrar(f);
    printf("O medico esta pronto para receber outro paciente.\n");
    atender(f);
    printf("Fila apos o atendimento: \n");
    mostrar(f);

    limpar(f);
    system("pause");
    return 0;
}
