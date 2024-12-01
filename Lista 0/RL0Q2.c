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
    float menor;
    float y;
} Ponto;

float distancia(Ponto p) {
    return sqrt(p.menor * p.menor + p.y * p.y);
}

#include <string.h>

void ordenarStrings(char strings[][MAX_STR_LEN], int n) {
    for (int i = 0; i < n - 1; i++) {
        int menor = i; 
        for (int j = i + 1; j < n; j++) {
            if (strcmp(strings[j], strings[menor]) < 0) {
                menor = j;
            }
        }
        
        if (menor != i) {
            char temp[MAX_STR_LEN];
            strcpy(temp, strings[i]);
            strcpy(strings[i], strings[menor]);
            strcpy(strings[menor], temp);
        }
    }
}

void ordenarIntegers(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int menor = i; 
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[menor]) {
                menor = j; 
            }
        }
        if (menor != i) {
            int temp = arr[i];
            arr[i] = arr[menor];
            arr[menor] = temp;
        }
    }
}

void ordenarFloats(float arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int menor = i; 
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[menor]) {
                menor = j; 
            }
        }
        if (menor != i) {
            float temp = arr[i];
            arr[i] = arr[menor];
            arr[menor] = temp;
        }
    }
}

void ordenarPontos(Ponto pontos[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int menor = i; 
        for (int j = i + 1; j < n; j++) {
            if (distancia(pontos[j]) < distancia(pontos[menor])) {
                menor = j; 
            }
        }
        if (menor != i) {
            Ponto temp = pontos[i];
            pontos[i] = pontos[menor];
            pontos[menor] = temp;
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

    char line[1000];
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
                    sscanf(token, "(%f,%f)", &pontos[countPontos].menor, &pontos[countPontos].y);
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
        
        fprintf(output, " str:");
        for (int i = 0; i < countStr; i++) fprintf(output, " %s", strings[i]);
        
        fprintf(output, " int:");
        for (int i = 0; i < countInt; i++) fprintf(output, " %d", inteiros[i]);
        
        fprintf(output, " float:");
        for (int i = 0; i < countReais; i++) {
            if (fabs(reais[i] * 10 - (int)(reais[i] * 10)) < 0.1)
                fprintf(output, " %.1f", reais[i]);
            else
                fprintf(output, " %.2f", reais[i]);
        }  
        
        fprintf(output, " p:");
        for (int i = 0; i < countPontos; i++) {
            if (pontos[i].menor == (int)pontos[i].menor && pontos[i].y == (int)pontos[i].y) {
                fprintf(output, "(%d,%d) ", (int)pontos[i].menor, (int)pontos[i].y);
            } else if (pontos[i].menor == (int)pontos[i].menor && pontos[i].y == (float)pontos[i].y) {
                if (fabs(pontos[i].y * 10 - (int)(pontos[i].y * 10)) < 0.1)
                    fprintf(output, "(%d,%.1f) ", (int)pontos[i].menor, pontos[i].y);
                else
                    fprintf(output, "(%d,%.2f) ", (int)pontos[i].menor, pontos[i].y);
            } else if (pontos[i].menor == (float)pontos[i].menor && pontos[i].y == (int)pontos[i].y) {
                if (fabs(pontos[i].menor * 10 - (int)(pontos[i].menor * 10)) < 0.1)
                    fprintf(output, "(%.1f,%d) ", pontos[i].menor, (int)pontos[i].y);
                else
                    fprintf(output, "(%.2f,%d) ", pontos[i].menor, (int)pontos[i].y);
            } else {
                if (fabs(pontos[i].menor * 10 - (int)(pontos[i].menor * 10)) < 0.1 && fabs(pontos[i].y * 10 - (int)(pontos[i].y * 10)) < 0.1)
                    fprintf(output, "(%.1f,%.1f) ", pontos[i].menor, pontos[i].y);
                else if (fabs(pontos[i].menor * 10 - (int)(pontos[i].menor * 10)) < 0.1)
                    fprintf(output, "(%.1f,%.2f) ", pontos[i].menor, pontos[i].y);
                else if (fabs(pontos[i].y * 10 - (int)(pontos[i].y * 10)) < 0.1)
                    fprintf(output, "(%.2f,%.1f) ", pontos[i].menor, pontos[i].y);
                else
                    fprintf(output, "(%.2f,%.2f) ", pontos[i].menor, pontos[i].y);
            }
        }
    }
        fprintf(output, "\n");

    fclose(input);
    fclose(output);

    return 0;
}
