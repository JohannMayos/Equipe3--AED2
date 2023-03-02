#include <stdio.h>
#include <string.h>

#define MAX_PATTERN_LEN 128

int bmBc[256];
int bmGs[MAX_PATTERN_LEN];
int suff[MAX_PATTERN_LEN];

void preProcessPattern(char *pattern, int patternLen) {
    int i, j, last;

    // preenche a tabela de saltos de caractere ruim
    for (i = 0; i < 256; i++) {
        bmBc[i] = patternLen;
    }
    for (i = 0; i < patternLen - 1; i++) {
        bmBc[(int)pattern[i]] = patternLen - i - 1;
    }

    // preenche a tabela de sufixos bons
    for (i = 0; i < patternLen; i++) {
        bmGs[i] = patternLen;
    }
    last = patternLen - 1;
    for (i = patternLen - 1; i >= 0; i--) {
        if (i == 0 || suff[patternLen - i - 1] == i) {
            while (last >= patternLen - 1 - i && pattern[last] != pattern[last - patternLen + i]) {
                if (bmGs[last] == patternLen) {
                    bmGs[last] = patternLen - 1 - i;
                }
                last--;
            }
            suff[patternLen - i - 1] = last - patternLen + 1 + i;
        }
    }
    for (i = 0; i <= last; i++) {
        if (bmGs[i] == patternLen) {
            bmGs[i] = last + 1;
        }
    }
}

int isPasswordValid(char *password, int passwordLen) {
    char uppercase = 0, lowercase = 0, digit = 0;
    int i;

    // verifica se a senha contém pelo menos uma letra maiúscula, uma letra minúscula e um número
    for (i = 0; i < passwordLen; i++) {
        if (password[i] >= 'A' && password[i] <= 'Z') {
            uppercase = 1;
        }
        if (password[i] >= 'a' && password[i] <= 'z') {
            lowercase = 1;
        }
        if (password[i] >= '0' && password[i] <= '9') {
            digit = 1;
        }
    }
    if (!uppercase || !lowercase || !digit) {
        return 0;
    }

    // verifica se a senha não possui nenhum caractere de pontuação, acentuação ou espaço
    preProcessPattern(".,;:-_()[]{}<>\\/\"'`~!@#$%^&*+=?", 28);
    int j = 0;
    while (j <= passwordLen - 28) {
        for (i = 27; i >= 0 && password[i+j] == ".,;:-_()[]{}<>\\/\"'`~!@#$%^&*+=?"[i]; i--);
        if (i < 0) {
            return 0;
        }
        j += bmGs[i];
        if (j > passwordLen - 28) {
            return 1;
        }
        j += bmGs[i];
	}
}

//Execução da validação da senha//

int main() {
    char password[100];
    int passwordLen;
    int hasSpaces = 0;

    // lê a senha a ser validada do usuário
    fgets(password, 100, stdin);
    passwordLen = strlen(password) - 1;
    password[passwordLen] = '\0';
    

    // verifica se a senha é válida
    
    for (int i = 0; i < passwordLen; i++) {
        if (password[i] == ' ') {
            hasSpaces = 1;
            break;
        }
    }
    
    
    if (!hasSpaces && passwordLen >= 6 && passwordLen <= 32 && isPasswordValid(password, passwordLen)) {
        printf("Senha valida.");
    } 
	else {
        printf("Senha invalida.");
    }

    return 0;
}




