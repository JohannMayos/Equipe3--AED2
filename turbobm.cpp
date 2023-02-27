#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define NOT_FOUND -1
#define MAX 10000

// Realiza a pré-computação dos caracteres ruins em um array//

void preBmBc(char *x, int m, int bmBc[]) {
    int i;
    for (i = 0; i < 256; i++) {
        bmBc[i] = m;
    }
    for (i = 0; i < m - 1; i++) {
        bmBc[x[i]] = m - 1 - i;
    }
}

// Função auxiliar para cálculo do comprimento dos sufixos do padrão//
void suffixes(char *x, int m, int *suff) {
    int f, g, i;
    suff[m - 1] = m; //algoritmo de morris-pratt//
    g = m - 1;
    for (i = m - 2; i >= 0; i--) {
        if (i > g && suff[i + m - 1 - f] < i - g) {
            suff[i] = suff[i + m - 1 - f];
        } else {
            if (i < g) {
                g = i;
            }
            f = i;
            while (g >= 0 && x[g] == x[g + m - 1 - f]) {
                g--;
            }
            suff[i] = f - g;
        }
    }
}

// Tabela de salto de sufixos bons. Armazena a informação de quantos caracteres se pode pular ao encontrar um sufixo do padrão que combina com o final da substring//

void preBmGs(char *x, int m, int bmGs[]) {
    int i, j;
    int suff[m];
    suffixes(x, m, suff);
    for (i = 0; i < m; i++) {
        bmGs[i] = m;
    }
    j = 0;
    for (i = m - 1; i >= 0; i--) {
        if (suff[i] == i + 1) {
            while (j < m - 1 - i) {
                if (bmGs[j] == m) {
                    bmGs[j] = m - 1 - i;
                }
                j++;
            }
        }
    }
    for (i = 0; i <= m - 2; i++) {
        bmGs[m - 1 - suff[i]] = m - 1 - i;
    }
}

//Função principal da busca de padrões, executando os pré-processamentos//

int turboBm(char *x, int m, char *y, int n) {
    int bmBc[256];
    int bmGs[m];
    int i, j, shift, u, v, turboShift;
    preBmBc(x, m, bmBc);
    preBmGs(x, m, bmGs);
    j = 0;
    shift = m;
    while (j <= n - m) {
        i = m - 1;
        while (i >= 0 && x[i] == y[i + j]) {
            i--;
        }
        if (i < 0) {
            return j;
        }
        u = m - 1 - i;
        v = bmGs[i];
        turboShift = u < v ? v : u;
        shift = bmBc[y[i + j]] - m + 1 + i;
        shift = shift > turboShift ? shift : turboShift;
        j += shift;
    }
    return NOT_FOUND;
}

//Execução da busca de padrões//

int main() {
	
	setlocale(LC_ALL, "PORTUGUESE");
  
    char x[MAX];
    char y[MAX];
    
    printf("Insira a cadeia de caracteres a ser analisada:\n");
    fgets(y, MAX, stdin);
    
    printf("Agora insira o padrão a ser achado:\n");
    fgets(x, MAX, stdin);
    
    int result = turboBm(x, strlen(x), y, strlen(y));
  
    if (result == NOT_FOUND) {
        printf("Padrão Não Encontrado\n");
    } 
  	else {
        printf("Padrão Encontrado na Posição: %d");
    }
  
  return 0;
}
