/*************************************** 
* Equipe: Deivisson Vinicius França de Jesus
*         Edmar Amorim dos Santos Junior
* 
***************************************/
              
/**
* 1. Considere as seguintes entrada e saída abaixo:
*                     L0Q1.in
*       points (−2,−1) (4 ,2) (4,0) (2,2) (8,6)

*                     L0Q1.out
*        points (−2,−1) (2 ,2) (4,0) (4,2) (8,6) distance 18.75 shortcut 12.21

 * Sobre a entrada
 * A cada linha um points marca o início de uma lista de pontos no espaçoo bidimensional; veja a figura abaixo.

 *  Sobre a saída
 * Na saída é preciso ordenar todos os pontos points conforme suas distâncias Euclidianas em relação à origem, ou seja, em relação ao ponto (0,0).
 * Em seguida deve-se exibir a distância total Euclidiana distance considerando os pontos na mesma ordem em que aparecem na entrada.
 * Por fim, deve-se exibir a distˆancia total Euclidiana shortcut entre o primeiro e último ponto na mesma ordem em que aparecem na entrada.

 ** Observações
 * Não faça Ctrl+C/Ctrl+V deste arquivo PDF no seu arquivo de entrada pois podem ocorrer erros.
 * Cada ponto aparece separado por apenas um espaço em branco dos demais e entre (), números com parte decimal são representados usando o ponto final e não a vírgula.
 * Sua resposta deve estar em um único arquivo chamado RL0Q1.[java, py, js, c, cpp, etc]
 * Você deve ler o arquivo L0Q1.in e escrever o arquivo L0Q1.out no mesmo diretório onde estiver rodando seu código RL0Q1.[java, py, js, c, cpp, etc]
 * Não deve ser usado nenhum recurso de ordena¸ c˜ao da linguagem de programação de sua escolha
 * Pode e vai haver mais de uma linha na estrada
 * O número de linhas na entrada deve ser o mesmo da saída, ou seja cada linha da entrada produzirá uma linha na saída
 * Os pontos podem ter coordenadas reais, ou seja o ponto (13.34,10.2) é um ponto válido para a entrada
 * não existem dois espaços em branco seguidos
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_POINTS 500
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
    input = fopen("L0Q1.in", "r");
    output = fopen("L0Q1.out", "w");
    char line[1000]; 

    if (!input || !output) {
        printf("Erro ao abrir os arquivos.\n");
        return 1;
    }

    while (fgets(line, sizeof(line), input) != NULL) {
        char *token = strtok(line, " ");
        int count = 0;
        
        Ponto arrayPontos[MAX_POINTS], arrayPontosOrdenados[MAX_POINTS];

        if (strcmp(token, "points ") == 0) {
            token = strtok(NULL, " ");
        }

        while (token != NULL) {
            Ponto ponto;
            if (sscanf(token, "(%f,%f)", &ponto.x, &ponto.y) == 2) {
                arrayPontos[count] = ponto;
                arrayPontosOrdenados[count] = ponto;
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
    
        // print(arrayPontosOrdenados, count);
        // printf("distance %.2f ", distance);
        // printf("shortcut %.2f ", shortcut);    

        fprintf(output, "points ");
        for (int i = 0; i < count; i++) {    
            if (arrayPontosOrdenados[i].x == (int)arrayPontosOrdenados[i].x && arrayPontosOrdenados[i].y == (int)arrayPontosOrdenados[i].y) {
                fprintf(output, "(%d, %d) ", (int)arrayPontosOrdenados[i].x, (int)arrayPontosOrdenados[i].y);
            } else if (arrayPontosOrdenados[i].x == (int)arrayPontosOrdenados[i].x && arrayPontosOrdenados[i].y == (float)arrayPontosOrdenados[i].y) {
                fprintf(output,"(%d, %.2f) ", (int)arrayPontosOrdenados[i].x, arrayPontosOrdenados[i].y);
            } else if (arrayPontosOrdenados[i].x == (float)arrayPontosOrdenados[i].x && (int)arrayPontosOrdenados[i].y == (int)arrayPontosOrdenados[i].y) {
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
