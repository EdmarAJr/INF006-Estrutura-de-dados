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

void inicializar(FILE *input, FILE *output);
void ordenarPontos(Ponto *A, int tam);

int main() {
    FILE *input, *output;
    input = fopen("L0Q1.in", "r");
    output = fopen("L0Q1.out", "w");
    
    if (!input || !output) {
        printf("Erro ao abrir os arquivos.\n");
        return 1;
    }
    
    inicializar(input, output);

    fclose(input);
    fclose(output);

    return 0;
}

void inicializar(FILE *input, FILE *output){
    
    char line[1000]; 
    char *outer;
    char *inner;


    while (fgets(line, sizeof(line), input) != NULL) {
        char *token = strtok_r(line, " ", &outer);
        int count = 0;
        
        Ponto arrP[MAX_POINTS], arrOrd[MAX_POINTS];

        if (strcmp(token, "points ") == 0) {
            token = strtok_r(NULL, " ", &outer);
        }

        while (token != NULL) {
            Ponto p;
            if (sscanf(outer, "(%f,%f)", &p.x, &p.y) == 2) {
                arrP[count] = p;
                arrOrd[count] = p;
                count++;
            }
            token = strtok_r(NULL, " ", &outer);
        }
        
        float distance=0, shortcut=0;
    
        for (int i = 0; i < count-1; i++) {
            distance += sqrt(pow((arrP[i].x  - arrP[i+1].x), 2) + 
        pow((arrP[i].y  - arrP[i+1].y), 2));
        }
        
        shortcut = sqrt(pow((arrP[0].x  - arrP[count-1].x), 2) + pow((arrP[0].y  - arrP[count-1].y), 2));
        ordenarPontos(arrOrd, count);

        fprintf(output, "points ");
        for (int i = 0; i < count; i++) {
            fprintf(output,"(%g,%g) ", arrOrd[i].x, arrOrd[i].y);
        }
        fprintf(output, " distance %.2f shortcut %.2f\n", distance, shortcut);
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
