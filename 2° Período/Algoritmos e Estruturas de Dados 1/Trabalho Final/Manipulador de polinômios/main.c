/*
    Manipulador de Polinomios (GRUPO 5)
    {Lucas Matos Rodrigues - 12311BCC024}
    {Gustavo Costa Miranda - 12311BCC034}
    {Raquel Emillene Freire Thomé - 12311BCC026}
    {Luana Larissa de Souza Pessoa - 12311BCC037}
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Polinomio.h"
#include "ListaPoli.h"


long int charToNum(char num[]);
int charToInt(char num[]);
int validaNum(char num[]);

int main(){

    Lista *l = criar();
    Polinomio *p = policriar();
    Polinomio *p2 = policriar();
    Polinomio *pSum = policriar();
    
    int id, retorno;
    long int soma;
    char o[2], op[2], opp[2];
    char coefStr[10], grauStr[10], idStr[3];
    Termo t, t2;
    do{
        //system("cls");
        printf("************************************************************");
        printf("\n*             Calculadora de Polinomios                    *\n");
        printf("************************************************************\n");

        // Imprime o menu principal
        printf("1. Inicializar novo polinomio\n");
        printf("2. Carregar polinomio salvo  \n");
        printf("3. Somar dois polinomios     \n");
        printf("4. Calcular o valor de P(x)  \n");
        printf("5. Sair                      \n");
        printf("************************************************************\n\n");
        printf("Digite uma opcao => ");
        
        scanf("%2[^\n]", o);
        setbuf(stdin,NULL);
        if(!strcmp(o, "1") || !strcmp(o, "2")){
            if(!strcmp(o, "1")){
                t.coeficiente = 0;
                t.grau = 0;
                poliinserirInicio(p, t);
                printf("\nPolinomio, da forma P(x)= 0x^0, inicializado.\n");
            } else{
                if(tamanho(l) > 0){ // Verifica se existe um polinimio salvo
                    do{
                        retorno = 1;
                        printf("\nEscolha um dos polinomios salvos:\n");
                        mostrar(l);
                        printf("=> ");
                        scanf("%3[^\n]", idStr);               
                        setbuf(stdin,NULL);
                        if (validaNum(idStr) == 0 ){
                            id = charToInt(idStr);
                            retorno = buscarItemChave(l, id, p);
                        }
                    }while(retorno != 0 );
                }
                else{
                    printf("\nComo nao ha polinomios salvos, um da forma P(x)= 0x^0 sera criado\n");
                    t.coeficiente = 0;
                    t.grau = 0;
                    poliinserirInicio(p, t);
                    printf("\nPolinomio, da forma P(x)= 0x^0, inicializado.\n");
                }
            }

            do{  
                printf("P(x) = "); polimostrar(p);
                
                printf("\n------------------------------------------------------------");
                printf("\n1. Inserir um novo termo akxk no polinomio\n");
                printf("2. Eliminar o termo associado a k-esima potencia\n");
                printf("3. Reinicializar um polinomio para a forma: P(x)= 0X^0\n");
                printf("4. Salvar o polinomio criado\n");
                printf("5. Voltar ao menu principal\n");
                printf("------------------------------------------------------------\n");
                printf("Digite uma opcao => ");
                
                scanf("%2[^\n]", op);
                setbuf(stdin,NULL);
                if(strlen(op) == 1){
                    switch (op[0]){
                    case '1':
                        do{
                            printf("Digite o coeficiente do termo: ");
                            scanf("%10[^\n]", coefStr);               
                            setbuf(stdin,NULL);
                        }while(validaNum(coefStr) != 0);
                        t.coeficiente = charToNum(coefStr);
                        
                        do{
                            printf("Digite o grau do termo: ");
                            scanf("%10[^\n]", grauStr);               // Recebe o grau do termo     
                            setbuf(stdin,NULL);
                        }while(validaNum(grauStr) != 0);
                        t.grau = charToNum(grauStr);

                        if(polibuscarItemChave(p, t.grau, &t2)){   // Verifica se um termo do grau recebido na l66 já existe
                            poliInserirTermo(p, t );                // Caso não exista, insere o termo
                            printf("Termo inserido.\n");
                        }else{                                     // Caso o termo já exista, abre um novo menu
                            do{
                                printf("\n************************************************************");
                                printf("\n*                O termo em questao ja existe              *\n");
                                printf("************************************************************\n");
                                printf("1. Inserir o termo na posicao correspondente,\n   incrementando os indices dos demais termos\n");
                                printf("2. Substituir o termo existente\n");
                                printf("3. Adicionar o valor inserido ao valor ja existente\n   no termo ak\n");
                                printf("\n************************************************************\n");
                                printf("Digite uma opcao => ");
                                
                                scanf("%2[^\n]", opp);
                                setbuf(stdin,NULL);
                                if(strlen(opp) == 1){
                                    switch (opp[0]){         
                                    case '1':   // Insere e incrementa indices do termos posteriores
                                        poliInserirTermo(p, t);               
                                        poliIncrementa(p, t);               
                                        printf("Termo inserido.\n");
                                        break;
                                    case '2':   // Substitui o termo de grau equivalente
                                        poliremoverItem(p,t);
                                        poliInserirTermo(p,t);   
                                        printf("Termo inserido.\n");
                                        break;

                                    case '3':   // Adiciona valor ao coef do termo de grau inserido
                                        t.coeficiente += t2.coeficiente;
                                        poliremoverItem(p, t);
                                        poliInserirTermo(p,t);   
                                        printf("Termo inserido.\n");
                                        break;
                                    
                                    default:
                                        printf("-- Escolha invalida --");
                                        break;     
                                    }
                                }else printf("-- Opcao invalida! --\n");
                            }while(opp[0] < '1' || opp[0] > '3' || strlen(opp) > 1);
                        }
                        t.grau = 0;
                        if(polibuscarItemChave(p,t.grau,&t)==0 && t.coeficiente == 0)
                            poliremoverInicio(p);
                    break;

                    case '2':   // Elimina um termo em função de seu grau
                        do{
                            printf("Informe a potencia correspondente ao termo que sera eliminado: ");
                            scanf("%10[^\n]", grauStr);               
                            setbuf(stdin,NULL);
                        }while(validaNum(grauStr) != 0);
                        t.grau = charToNum(grauStr);
                        int veri= poliremoverItem(p ,t);
                        if (veri==-1){
                            printf("Termo inexistente.\n");
                        }
                        else if (veri==0){
                            printf("Termo excluido.\n ");
                        }
                        else printf("-- ERRO INESPERADO --\n");
                        break;
                    
                    case '3':   // Reinicializa o polinômio para a forma P(x) = 0x^0
                        polilimpar(p);
                        t.coeficiente = 0;
                        t.grau = 0;
                        poliinserirInicio(p, t);
                        printf("Polinomio reinicializado.\n");
                        break;


                    
                    case '4':   // Salva o polinômio da lista de polinômios
                        inserirFim(l, p);
                        printf("Polinomio salvo!\n");         
                        break;
                    
                    case '5':   // Limpa o polinômio e volta para o menu principal
                        polilimpar(p);
                        break;
                    
                    default:
                        printf("-- Opcao invalida! --\n");
                        break;
                    }                    
                }else printf("-- Opcao invalida! --\n");

            }while(strcmp(op, "5") || op[0] < '1' || op[0] > '5');


        }else if (!strcmp(o, "3")){  // Realiza a soma de dois polinômios que estejam salvos na lista de polinômios
            if(tamanho(l) > 1){
                printf("Escolha dois dos polinomios salvos:\n");
                mostrar(l);
                do{
                    retorno = 1;
                    printf("\nP1: ");
                    scanf("%3[^\n]", idStr);               
                    setbuf(stdin,NULL);
                    if (validaNum(idStr) == 0 ){
                        id = charToInt(idStr);
                        retorno = buscarItemChave(l, id, p);
                    }
                }while(retorno != 0 );  // Busca o polinômio salvo com base na escolha do usuario para "retorno"
                do{
                    retorno = 1;
                    printf("\nP2: ");
                    scanf("%3[^\n]", idStr);               
                    setbuf(stdin,NULL);
                    if (validaNum(idStr) == 0 ){
                        id = charToInt(idStr);
                        retorno = buscarItemChave(l, id, p2);
                    }
                }while(retorno != 0 ); 
                pSum = somaPolinomios(p, p2);
                printf("Resultado da soma: ");
                polimostrar(pSum);
                do{
                    printf("Voce deseja salvar esse polinomio?(s/n)\n");
                    printf("=> ");
                    scanf("%3[^\n]", idStr);
                    setbuf(stdin,NULL);
                } while(strcmp(idStr, "s") != 0 && strcmp(idStr, "S") != 0 && strcmp(idStr, "n") != 0 && strcmp(idStr, "N") != 0);
                 if(!strcmp(idStr, "S") || !strcmp(idStr, "s")){
                    inserirFim(l, pSum);
                    printf("Salvo\n");
                 }
                 else{
                    printf("Descartado\n");
                 }
            }
             else printf("\n-- Eh necessario que ao menos dois polinomios tenham sido salvos. --\n\n");
        }
        else if(!strcmp(o, "4")){
            // Calcula o valor de P(x) de acordo com um valor X inserido
            int idMaior, idMenor, qtd;
            long int maior = 0, menor, x;
            char xStr[10], qtdStr[3];

            Polinomio *lEscolhidos;
            
            if(tamanho(l) > 0){ // Verifica se existe um polinimio salvo
                do{
                    printf("Informe quantos polinomios serao calculados: ");
                    scanf("%3[^\n]", qtdStr);               
                    setbuf(stdin,NULL);
                }while(validaNum(qtdStr) != 0);
                qtd = charToInt(qtdStr);
                do{
                    printf("Digite um valor para x: ");
                    scanf("%10[^\n]", xStr);               
                    setbuf(stdin,NULL);
                }while(validaNum(xStr) != 0);
                x = charToInt(xStr);
                printf("\nEscolha os polinomios\n", qtd);
                mostrar(l);
                lEscolhidos = (Polinomio*) malloc(sizeof(Polinomio) * qtd);
                for(int i = 0; i < qtd; i++){
                    retorno = 1;
                    printf("Informe o id: ");
                    scanf("%3[^\n]", idStr);               
                    setbuf(stdin,NULL);
                    if (validaNum(idStr) == 0 ){
                        id = charToInt(idStr);
                        retorno = buscarItemChave(l, id, p);
                    }
                    if(retorno == 0){
                        lEscolhidos[i] = *p;
                    }
                }
                for(int i = 0; i < qtd; i++){
                    lEscolhidos[i];
                    poliCalcular(&(lEscolhidos[i]), x, &soma);
                    if(i == 0){
                        menor = soma;
                        idMenor = lEscolhidos[i].idem;
                    }else if (soma < menor){
                        menor = soma;
                        idMenor = lEscolhidos[i].idem;
                    }
                    printf("P%d(%d) eh igual a: %ld\n", lEscolhidos[i].idem,  x, soma);
                    if(soma > maior){
                        maior = soma;
                        idMaior = lEscolhidos[i].idem;
                    }
                }
                buscarItemChave(l, idMaior, &lEscolhidos[0]);
                if(qtd > 1){
                    printf("Maior: P%d(%ld) ", idMaior, x ); polimostrar(&lEscolhidos[0]); printf(" => %ld\n", maior);
                    buscarItemChave(l, idMenor, &lEscolhidos[0]);
                    printf("Menor: P%d(%ld) ", idMenor, x); polimostrar(&lEscolhidos[0]); printf(" => %ld\n", menor); 
                }else{
                    printf("P%d(%ld) ", idMaior, x ); polimostrar(&lEscolhidos[0]); printf(" => %ld\n", maior);
                }
                free(lEscolhidos);
            }
        }else if(!strcmp(o, "5")){
            printf("Encerrando...\n"); 
        }else{
            printf("-- Opcao invalida! --\n");                                 
        } 
    
    }while(strcmp(o, "5") || o[0] < '1' || o[0] > '5');

   polilimpar(p); free(p);
   polilimpar(p2); free(p2);
   polilimpar(pSum); free(pSum);
   limpar(l);
    system("pause");
    return 0;
}

int validaNum(char num[]){
    int tam = strlen(num);
    if(tam > 10) return 1;  // Ultrapassa o tamanho max
    for(int i = 0; i < tam; i++){
        if(num[i] < '0' || num[i] > '9') return 2;   
    }
    return 0;
}

long int charToNum(char num[]){ 
    int pot = strlen(num) - 1;
    int i = 0;
    long int cont = 0;
    while(num[i] != '\0'){
        cont += (num[i] - 48) * pow(10, (pot - i));
        i++;
    }
    return cont;
}

int charToInt(char num[]){ 
    int pot = strlen(num) - 1;
    int i = 0;
    int cont = 0;
    while(num[i] != '\0'){
        cont += (num[i] - 48) * pow(10, (pot - i));
        i++;
    }
    return cont;
}
