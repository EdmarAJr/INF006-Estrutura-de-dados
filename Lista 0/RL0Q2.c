/*************************************** 
* Equipe: Deivisson Vinicius França de Jesus
*         Edmar Amorim dos Santos Junior
* 
***************************************/

/**
 *  Considere as seguintes input e saída abaixo:
 *                          L0Q2.in
 *       maria 3.15 jose 4 8 −1 12.7 (−1,−1) julia (−0.5,−0.5) 74.5 3.15 
         jose 4 8 −1 12.7 (8,2) carlos (−0.5,−0.5)
 
 *                           L0Q2.out
 *       str : jose julia maria int:−1 4 8 float :3.15 12.7 p:(−0.5,−0.5) (−1,−1)
 *       str : carlos jose int:−1 4 8 float :3.15 12.7 74.5 p:(−0.5,−0.5) (8,2)
 
 * Esta questão consiste em ler uma lista de valores contendo strings, inteiros, reais e pontos no espaço bidimensional. A saída consiste em ordenar de maneira crescente, as strings por ordem alfabética, os inteiros, os reais e por fim os pontos por ordem crescente em relação a suas distância Euclidianas em relação a origem, o ponto (0,0).
 
 ** Observações
 * Não faça Ctrl+C/Ctrl+V deste arquivo PDF no seu arquivo de input pois podem ocorrer erros.
 * Cada ponto aparece separado (), números com parte decimal são representados usando o ponto final e não a vírgula.
 * Sua resposta deve estar em um único arquivo chamado RL0Q2.[java, py, js, c, cpp, etc]
 * Você deve ler o arquivo L0Q2.in e escrever o arquivo L0Q1.out no mesmo diretório onde estiver rodando seu código RL0Q2.[java, py, js, c, cpp, etc]
 * Não deve ser usado nenhum recurso de ordenação da linguagem de programação de sua escolha
 * Pode e vai haver mais de uma linha na estrada
 * O número de linhas na input deve ser o mesmo da saída, ou seja cada linha da input produzirá uma linha na saída
 * Os pontos podem ter coordenadas reais, ou seja o ponto (13.34,10.2) é um ponto válido para a input
 * não existem dois espaços em branco seguidos
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAX_ITEMS 500
#define MAX_STR_LEN 50

typedef struct {
    float x;
    float y;
} Ponto;

void inicializar(FILE *input, FILE *output);
void ordenarStrings(char strings[][MAX_STR_LEN], int n);
void ordenarIntegers(int arr[], int n);
void ordenarFloats(float arr[], int n);
void ordenarPontos(Ponto *A, int tam);

int main() {
    FILE *input = fopen("L0Q2.in", "r");
    FILE *output = fopen("L0Q2.out", "w");

    if (!input || !output) {
        printf("Erro ao abrir os arquivos.\n");
        return 1;
    }

    inicializar(input, output);

    fclose(input);
    fclose(output);

    return 0;
}

void inicializar(FILE *input, FILE *output) {
    char line[1000];
    char *outer;
    char *inner;

    while (fgets(line, sizeof(line), input)) {
        char strings[MAX_ITEMS][MAX_STR_LEN] = {0};
        int inteiros[MAX_ITEMS] = {0};
        float reais[MAX_ITEMS] = {0};
        Ponto pontos[MAX_ITEMS] = {0};
        int countS = 0, countI = 0, countR = 0, countP = 0;

        line[strcspn(line, "\n")] = '\0';
        char* token = strtok_r(line, " ", &outer);

        while (token != NULL) {
            if (isdigit(token[0]) || token[0] == '-' || token[0] == '(') {
                if (strchr(token, '(')) {
                    sscanf(token, "(%f,%f)", &pontos[countP].x, &pontos[countP].y);
                    countP++;
                } else {
                    char *end;
                    float val = strtof(token, &end);
                    if (*end == '\0') { 
                        if (strchr(token, '.')) {
                            reais[countR++] = val;
                        } else {
                            inteiros[countI++] = (int)val;
                        }
                    }
                }
            } else {
                strcpy(strings[countS++], token);
            }
             token = strtok_r(NULL, " ", &outer);
        }

        ordenarStrings(strings, countS);
        ordenarIntegers(inteiros, countI);
        ordenarFloats(reais, countR);
        ordenarPontos(pontos, countP);

        fprintf(output, "str:");
        for (int i = 0; i < countS; i++) fprintf(output, "%s ", strings[i]);

        fprintf(output, " int:");
        for (int i = 0; i < countI; i++) fprintf(output, "%d ", inteiros[i]);

        fprintf(output, " float:");
        for (int i = 0; i < countR; i++) fprintf(output, "%.2f ", reais[i]);

        fprintf(output, " p:");
        for (int i = 0; i < countP; i++) {
            fprintf(output, "(%g,%g) ", pontos[i].x, pontos[i].y);
        }

        fprintf(output, "\n"); 
    }
}

void ordenarStrings(char strings[][MAX_STR_LEN], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(strings[j], strings[j + 1]) > 0) {
                char temp[MAX_STR_LEN];
                strcpy(temp, strings[j]);
                strcpy(strings[j], strings[j + 1]);
                strcpy(strings[j + 1], temp);
            }
        }
    }
}

void ordenarIntegers(int *arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

void ordenarFloats(float *arr, int n) {
    for (int i = 1; i < n; i++) {
        float key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

void ordenarPontos(Ponto *A, int tam) {
    for (int i = 1; i < tam; i++) {
        Ponto key = A[i];
        int j = i - 1;

        while (j >= 0 && 
              (abs(A[j].x) > abs(key.x) || 
              (abs(A[j].x) == abs(key.x) && abs(A[j].y) > abs(key.y)))) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = key;
    }
}
