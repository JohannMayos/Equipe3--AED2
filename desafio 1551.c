#include <stdio.h>
#include <string.h>

#define MAX_LEN 1005
#define ALPHABET_SIZE 26

void build_shift_table(char *pattern, int *shift_table) { //A função build_shift_table é responsável por construir uma tabela 
    int m = strlen(pattern);                                //uma tabela de deslocamento para a busca do padrão em uma string usando o algoritmo de Horspool
    int i;
//O parâmetro pattern é a string contendo o padrão que se deseja buscar e o parâmetro shift_table é o vetor que vai armazenar a tabela de deslocamento.

    for (i = 0; i < ALPHABET_SIZE; i++) {
        shift_table[i] = m;
    }

    for (i = 0; i < m - 1; i++) {
        shift_table[pattern[i] - 'a'] = m - i - 1;
    }
}

int horspool(char *text, char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    int shift_table[ALPHABET_SIZE];

    build_shift_table(pattern, shift_table);

    int i = m - 1;
    while (i < n) {
        int k = 0;
        while (k < m && text[i - k] == pattern[m - k - 1]) {
            k++;
        }

        if (k == m) {
            return 1; // achou o padrão
        }

        i += shift_table[text[i - m] - 'a'];
    }

    return 0; // não achou o padrão
}

int main() {//A função main é responsável por ler várias strings e, para cada uma delas, contar quantas letras diferentes
    int n;   // do alfabeto estão presentes na string. Dependendo do número de letras diferentes encontradas, a função imprime uma mensagem diferente
    scanf("%d", &n);

    getchar(); // descarta o \n após o número de casos de teste

    while (n--) {
        char text[MAX_LEN];
        fgets(text, MAX_LEN, stdin);

        int m = strlen(text);
        if (text[m - 1] == '\n') {
            text[m - 1] = '\0';
        }

        int i;
        for (i = 0; i < m; i++) {
            if (text[i] == ',' || text[i] == ' ') {
                text[i] = '\0';
            }
        }

        int unique_chars = 0;
        int freq[ALPHABET_SIZE] = {0};
        for (i = 0; i < m; i++) {
            if (text[i] >= 'a' && text[i] <= 'z' && freq[text[i] - 'a'] == 0) {
                unique_chars++;
                freq[text[i] - 'a'] = 1;
            }
        }

        if (unique_chars == 26) {
            printf("frase completa\n");
        } else if (unique_chars >= 13) {
            printf("frase quase completa\n");
        } else {
            printf("frase mal elaborada\n");
        }
    }

    return 0;
}

