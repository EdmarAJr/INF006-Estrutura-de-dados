#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_POINTS 100
typedef struct ponto {
        float x;
        float y;
    } Ponto;

void selectionSort(Ponto *A, int tam) {
    for (int i = 0; i < tam - 1; i++) {
        int i_menor = i;
        for (int j = i + 1; j < tam; j++) {
            if (abs(A[j].x) < abs(A[i_menor].x) ||
                (abs(A[j].x) == abs(A[i_menor].x) && abs(A[j].y) < abs(A[i_menor].y))) {
                i_menor = j;
            }
        }

        Ponto temp = A[i];
        A[i] = A[i_menor];
        A[i_menor] = temp;
    }
}

void print(Ponto *A, int tam) {
    printf("points: ");
    for (int i = 0; i < tam; i++) {
        if (A[i].x == (int)A[i].x && A[i].y == (int)A[i].y) {
            printf("(%d, %d) ", (int)A[i].x, (int)A[i].y);
        } else if (A[i].x == (int)A[i].x && A[i].y != (int)A[i].y) {
            printf("(%d, %.2f) ", (int)A[i].x, A[i].y);
        } else if (A[i].x != (int)A[i].x && (int)A[i].y == (int)A[i].y) {
            printf("(%.2f, %d) ", A[i].x, (int)A[i].y);
        } else {
            printf("(%.2f, %.2f) ", A[i].x, A[i].y);
        }
    }
}    

int main() {
    FILE *input, *output;
    //char line[1000];
    input = fopen("L0Q1.in", "r");
    output = fopen("L0Q1.out", "w");
    char line[255];

    if (!input || !output) {
        printf("Erro ao abrir os arquivos.\n");
        return 1;
    }

    while (fgets(line, sizeof(line), input) != NULL) {
        char *token = strtok(line, ",");
        int count = 0;
        
        Ponto arrayPontos[MAX_POINTS], arrayPontosOrdenados[MAX_POINTS];

        if (strcmp(token, "points") == 0) {
            token = strtok(NULL, " ");
        }

        while (token != NULL) {
            Ponto p;
            if (sscanf(token, "(%f,%f)", &p.x, &p.y) == 2) {
                arrayPontos[count] = p;
                arrayPontosOrdenados[count] = p;
                count++;
            }
            token = strtok(NULL, " ");
        }
        
        float distance=0, shortcut=0;
    
        for (int i = 0; i < count-1; i++) {
            distance += sqrt(pow((arrayPontos[i].x  - arrayPontos[i+1].x), 2) + 
        pow((arrayPontos[i].y  - arrayPontos[i+1].y), 2));
        }
        
        shortcut = sqrt(pow((arrayPontos[0].x  - arrayPontos[count-1].x), 2) + pow((arrayPontos[0].y  - arrayPontos[count-1].y), 2));
        
        selectionSort(arrayPontosOrdenados, count);
    
        print(arrayPontosOrdenados, count);
        printf("distance %.2f ", distance);
        printf("shortcut %.2f ", shortcut);    

        fprintf(output, "points");
        for (int i = 0; i < count; i++) {    
            if (arrayPontosOrdenados[i].x == (int)arrayPontosOrdenados[i].x && arrayPontosOrdenados[i].y == (int)arrayPontosOrdenados[i].y) {
                fprintf(output, "(%d, %d) ", (int)arrayPontosOrdenados[i].x, (int)arrayPontosOrdenados[i].y);
            } else if (arrayPontosOrdenados[i].x == (int)arrayPontosOrdenados[i].x && arrayPontosOrdenados[i].y != (int)arrayPontosOrdenados[i].y) {
                fprintf(output,"(%d, %.2f) ", (int)arrayPontosOrdenados[i].x, arrayPontosOrdenados[i].y);
            } else if (arrayPontosOrdenados[i].x != (int)arrayPontosOrdenados[i].x && (int)arrayPontosOrdenados[i].y == (int)arrayPontosOrdenados[i].y) {
                fprintf(output,"(%.2f, %d) ", arrayPontosOrdenados[i].x, (int)arrayPontosOrdenados[i].y);
            } else {
                fprintf(output,"(%.2f, %.2f) ", arrayPontosOrdenados[i].x, arrayPontosOrdenados[i].y);
            }
        }
        fprintf(output, " distance %.2f shortcut %.2f\n", distance, shortcut);
    }

    fclose(input);
    fclose(output);

    return 0;
}
