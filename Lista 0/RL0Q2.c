#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAX_ITEMS 100
#define MAX_STR_LEN 50

typedef struct {
    float x;
    float y;
} Ponto;

float distancia(Ponto p) {
    return sqrt(p.x * p.x + p.y * p.y);
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

void ordenarIntegers(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

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
    FILE *input = fopen("L0Q2.in", "r");
    FILE *output = fopen("L0Q2.out", "w");

    if (!input || !output) {
        printf("Erro ao abrir os arquivos.\n");
        return 1;
    }

    char line[255];
    while (fgets(line, sizeof(line), input)) {
        char strings[MAX_ITEMS][MAX_STR_LEN];
        float reais[MAX_ITEMS];
        int inteiros[MAX_ITEMS];
        Ponto pontos[MAX_ITEMS];
        int countStr = 0, countReais = 0, countInt = 0, countPontos = 0;

        char* token = strtok(line, " ");

        while (token != NULL) {
            if (isdigit(token[0]) || token[0] == '-' || token[0] == '(') {
                if (strchr(token, '(') != NULL) {  
                    sscanf(token, "(%f,%f)", &pontos[countPontos].x, &pontos[countPontos].y);
                    countPontos++;
                } else { 
                    char *end;
                    float val = strtof(token, &end);
                    if (*end == '\0' || (*end == 'f' && *(end + 1) == '\0')) {  
                        if (strchr(token, '.') != NULL) {  
                            reais[countReais++] = val;
                        } else {  
                            inteiros[countInt++] = (int)val;
                        }
                    }
                }
            } else {
                strcpy(strings[countStr++], token);
            }
            token = strtok(NULL, " ");
        }

        ordenarStrings(strings, countStr);
        ordenarIntegers(inteiros, countInt);
        ordenarFloats(reais, countReais);
        ordenarPontos(pontos, countPontos);

        fprintf(output, "str:");
        for (int i = 0; i < countStr; i++) fprintf(output, " %s", strings[i]);
        fprintf(output, " int:");
        for (int i = 0; i < countInt; i++) fprintf(output, " %d", inteiros[i]);
        fprintf(output, " float:");
        for (int i = 0; i < countReais; i++) fprintf(output, " %.2f", reais[i]);
        fprintf(output, " p:");
        for (int i = 0; i < countPontos; i++) {            
            if (pontos[i].x == (int)pontos[i].x && pontos[i].y == (int)pontos[i].y) {
                fprintf(output, "(%d, %d) ", (int)pontos[i].x, (int)pontos[i].y);
            } else if (pontos[i].x == (int)pontos[i].x && pontos[i].y == (float)pontos[i].y) {
                fprintf(output,"(%d, %.2f) ", (int)pontos[i].x, pontos[i].y);
            } else if (pontos[i].x == (float)pontos[i].x && pontos[i].y == (int)pontos[i].y) {
                fprintf(output,"(%.2f, %d) ", pontos[i].x, (int)pontos[i].y);
            } else {
                fprintf(output,"(%.2f, %.2f) ", pontos[i].x, pontos[i].y);
            }
        }
        fprintf(output, "\n");
    }

    fclose(input);
    fclose(output);

    return 0;
}
