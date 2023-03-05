/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100010
#define MAXM 100010

char T[MAXN]; // Texto
char P[MAXM]; // Padrão
int n, m; // Tamanho do texto e do padrão
int last[MAXM]; // Última ocorrência de cada caractere no padrão
int s[MAXM]; // Salto
int r[MAXM]; // Retrocesso

// Função que realiza a pré-processamento da última ocorrência de cada caractere no padrão
void preprocess_last() {
    memset(last, -1, sizeof(last)); // Inicializa todas as posições com -1
    for (int i = 0; i < m; i++) {
        last[P[i]] = i; // Armazena a última ocorrência de cada caractere
    }
}

// Função que realiza o pré-processamento da função de salto
void preprocess_s() {
    int j = m + 1;
    for (int i = m; i >= 0; i--) {
        while (j <= m && P[i] != P[j-1]) { // Enquanto os caracteres não são iguais
            if (s[j] == 0) s[j] = j - i; // Define o salto se ainda não foi definido
            j = r[j]; // Retrocede para o próximo prefixo
        }
        j--;
        r[i] = j; // Armazena o retrocesso
    }
}

// Função que realiza a busca de todas as ocorrências do padrão no texto
void search() {
    int j = m + 1;
    for (int i = n; i >= 0; i--) {
        while (j <= m && T[i] != P[j-1]) { // Enquanto os caracteres não são iguais
            j = r[j]; // Retrocede para o próximo prefixo
        }
        if (--j == 0) { // Encontrou uma ocorrência do padrão
            printf("%d\n", i+1); // Imprime a posição da ocorrência
            j = s[1]; // Avança para o próximo salto
        }
    }
}

int main() {
    while (scanf("%s %s", T, P) != EOF) {
        n = strlen(T);
        m = strlen(P);

        memset(s, 0, sizeof(s)); // Inicializa todas as posições do salto com 0
        memset(r, 0, sizeof(r)); // Inicializa todas as posições do retrocesso com 0

        preprocess_last(); // Realiza a pré-processamento da última ocorrência de cada caractere no padrão
        preprocess_s(); // Realiza a pré-processamento da função de salto
        search(); // Realiza a busca de todas as ocorrências do padrão no texto
    }

    return 0;
}
