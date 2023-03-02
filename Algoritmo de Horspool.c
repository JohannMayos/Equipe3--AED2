/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 256 // Definir o tamanho máximo de uma tabela de saltos

/* Função para criar uma tabela de saltos para um padrão */
void createTable(char *pattern, int *table)
{
    int i, len = strlen(pattern);
    for (i = 0; i < MAX; i++) {
        table[i] = len;
    }
    for (i = 0; i < len - 1; i++) {
        table[pattern[i]] = len - 1 - i;
    }
}

/* Função principal para buscar um padrão em uma string */
int search(char *string, char *pattern)
{
    int i, j, k, len_str = strlen(string), len_pat = strlen(pattern);
    int table[MAX]; // Tabela de saltos para o padrão
    createTable(pattern, table); // Criar a tabela de saltos
    
    i = len_pat - 1; // Posição final da janela
    while (i < len_str) {
        j = len_pat - 1; // Índice para comparar caracteres do padrão com a string
        k = i; // Índice para comparar caracteres da string com o padrão
        
        while (j >= 0 && string[k] == pattern[j]) { // Comparar caracteres
            k--;
            j--;
        }
        
        if (j == -1) { // Houve correspondência completa
            return k + 1; // Retornar a posição inicial do padrão na string
        } else { // Houve correspondência parcial
            i += table[string[i]]; // Mover a janela para a direita
        }
    }
    
    return -1; // Não foi encontrado um padrão na string
}

/* Função principal para testar o algoritmo */
int main()
{
    char string[] = "Dias de luta, dias de gloria";
    char pattern[] = "luta";
    int position = search(string, pattern);
    if (position != -1) {
        printf("O padrão foi encontrado na posição %d da string.\n", position);
    } else {
        printf("O padrão não foi encontrado na string.\n");
    }
    return 0;
}
