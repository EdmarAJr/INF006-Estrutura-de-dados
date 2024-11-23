#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_ITEMS 100
#define MAX_STR_LEN 50

typedef struct {
    float x;
    float y;
} Ponto;

// Função para calcular a distância euclidiana
float distancia(Ponto p) {
    return sqrt(p.x * p.x + p.y * p.y);
}

// Função para ordenar strings
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

// Função para ordenar inteiros ou reais
void ordenarFloats(float arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                float temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Função para ordenar pontos pela distância
void ordenarPontos(Ponto pontos[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (distancia(pontos[j]) > distancia(pontos[j + 1])) {
                Ponto temp = pontos[j];
                pontos[j] = pontos[j + 1];
                pontos[j + 1] = temp;
            }
        }
    }
}

int main() {
    FILE *entrada = fopen("L0Q2.in", "r");
    FILE *saida = fopen("L0Q2.out", "w");

    if (!entrada || !saida) {
        printf("Erro ao abrir os arquivos.\n");
        return 1;
    }

    char line[1000];
    while (fgets(line, sizeof(line), entrada)) {
        char strings[MAX_ITEMS][MAX_STR_LEN];
        float reais[MAX_ITEMS];
        int inteiros[MAX_ITEMS];
        Ponto pontos[MAX_ITEMS];
        int countStr = 0, countReais = 0, countInt = 0, countPontos = 0;

        char *token = strtok(line, " ");
        while (token != NULL) {
            if (sscanf(token, "(%f,%f)", &pontos[countPontos].x, &pontos[countPontos].y) == 2) {
                countPontos++;
            } else if (sscanf(token, "%f", &reais[countReais]) == 1) {
                if (strchr(token, '.')) { // Diferenciar entre float e int
                    countReais++;
                } else {
                    inteiros[countInt++] = (int) reais[countReais];
                    countReais--;
                }
            } else {
                strcpy(strings[countStr++], token);
            }
            token = strtok(NULL, " ");
        }

        // Ordenar os dados
        ordenarStrings(strings, countStr);
        ordenarFloats((float *)inteiros, countInt);
        ordenarFloats(reais, countReais);
        ordenarPontos(pontos, countPontos);

        // Escrever no arquivo de saída
        fprintf(saida, "str:");
        for (int i = 0; i < countStr; i++) fprintf(saida, " %s", strings[i]);
        fprintf(saida, " int:");
        for (int i = 0; i < countInt; i++) fprintf(saida, " %d", inteiros[i]);
        fprintf(saida, " float:");
        for (int i = 0; i < countReais; i++) fprintf(saida, " %.2f", reais[i]);
        fprintf(saida, " p:");
        for (int i = 0; i < countPontos; i++) fprintf(saida, " (%.2f,%.2f)", pontos[i].x, pontos[i].y);
        fprintf(saida, "\n");
    }

    fclose(entrada);
    fclose(saida);

    return 0;
}
