#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int Soma(int x){
    int f = x;
    for(int i = 1; i < x; i++){
        f += i;
    }
    return f;
}

int Fatorial(int x){
    int t = 1;
    for(int i = 1; i <= x; i++){
        x = x*i;
    }
    return t;
}

int Elevado(int x, int y){
    int t = 1;
    for(int i = 1; i <= y; i++){
        t = t*x;
    }
    return t;
}

int Exponencial(int x, int n){
    int t = 0;
    for(int i = 0; i <= n; i++){
        t += Elevado(x, i)/Fatorial(i)*1.0;
    }
    return t;
}

int Div(int a, int b, int *q, int *r){
    if(b == 0){
        return -1;
    }
    else{
        *q = a/b;
        *r = a%b;
        return 0;
    }
}

void CalculaHexagono(float l, float *a, float *p){
    *p = l * 6;
    *a = (3 * Elevado(l, 2) * sqrt(3)) / 2;
}

int String(char a, int t, char *s){
    int cont = 0;
    for(int i = 0; i < t; i++){
        if(s[i] == a || s[i] == a-32 || s[i] == a+32){
            s[i] = '*';
            cont++;
        }
    }
    return cont;
}

void Swap(char *v, int t){
    char temp[t+1];
    temp [t] = '\0';
    
    for(int i = 0; i < t; i++){
        temp[i] = v[t-i-1];
    }
    strcpy(v, temp);
}

void NumInt(int *v, int t, float *media, int *maior){
    int sum = 0;
    *maior = v[0];
    
    for(int i = 0; i < t; i++){
        sum += v[i];
        if(v[i] > *maior){
            *maior = v[i];
        }
    }
    *media = sum/(float)t;
}

int main(){
    
    char q;
    printf("Digite a letra do exercicio que deseja testar: \n");
    scanf("%c", &q);
    setbuf(stdin, NULL);

    if(q == 'a' || q == 'A'){
        int x;
        printf("Qual o numero inteiro? \n");
        scanf("%i", &x);
        printf("A soma eh: %i\n", Soma(x));
    }
    else if(q == 'b' || q == 'B'){
        int x, y;
        printf("Digite os valores de X e Y: \n");
        scanf("%i", &x);
        scanf("%i", &y);
        printf("X elevado a Y eh: %i\n", Elevado(x, y));
    }
    else if(q == 'c' || q == 'C'){
        int x, n;
        printf("Digite os valores de x e n: \n");
        scanf("%i", &x);
        scanf("%i", &n);
        printf("O valor aproximado de euler elevado a x eh: %.2f", Exponencial(x, n)*1.0);
    }
    else if(q == 'd' || q == 'D'){
        int a, b, q, r;
        printf("Quais os valores para a e b? \n");
        scanf("%i", &a);
        scanf("%i", &b);
    
        int x = Div(a, b, &q, &r);
    
        if(x == -1){
            printf("Nao eh possivel realizar as operacoes.\n");
        }
        else{
            printf("O quociente eh: %i\nO resto eh: %i\n", q, r);
        }
    }
    else if(q == 'e' || q == 'E'){
        float l, a, p;
        printf("Qual o tamanho do lado do hexagono?\n");
        scanf("%f", &l);
        
        CalculaHexagono(l, &a, &p);
        
        printf("O perimetro eh: %.2f\nA area eh: %.2f\n", p, a);
    }
    else if(q == 'f' || q == 'F'){
        char c;
        char s[25];
        
        printf("Qual caractere deseja substituir?\n");
        scanf("%c", &c);
        setbuf(stdin, NULL);
        printf("Onde deseja fazer as substituicoes?\n");
        fgets(s, sizeof(s), stdin);
        
        int t = strlen(s);
        
        int q = String(c, t, s);
        
        printf("Depois das substituicoes: %s", s);
        printf("A quantidade de substituicoes foi: %i", q);
    }
    else if(q == 'g' || q == 'G'){
        char v[25];
        printf("Qual o vetor?\n");
        fgets(v, sizeof(v), stdin);
        int t = strlen(v);
        Swap(v, t);
        printf("O vetor invertido eh: %s", v);
    }
    else if(q == 'h' || q == 'H'){
        
        printf("Letra H nao foi finalizada :(\n");
        
    }
    else if(q == 'i' || q == 'I'){
        int v[6];
        printf("Digite um vetor de seis numeros: \n");
        
        for(int i = 0; i < 6; i++){
            scanf("%i", &v[i]);
        }
        
        float med;
        int maior;
        
        NumInt(v, 6, &med, &maior);
        
        printf("O maior valor do vetor eh: %i\n", maior);
        printf("A media eh: %.2f\n", med);
        
    }
    else{
        printf("--- Opção invalida ---");
    }
    
    system("pause");
    return 0;
}

