/**
 * 1. Considere as seguintes entrada e saída abaixo:
*                     L0Q1.in
       
*       points (−2,−1) (4 ,2) (4,0) (2,2) (8,6)

*                     L0Q1.out
*        points (−2,−1) (2 ,2) (4,0) (4,2) (8,6) distance 18.75 shortcut 12.21

 *Sobre a entrada
 * Acada linha um points marca o in´ıcio de uma lista de pontos no espa¸co bidimensional; veja a figura abaixo.

 *  Sobre a saída
 * Na saída é preciso ordenar todos os pontos points conforme suas distâncias Euclidianas em relação à origem, ou seja, em relação ao ponto (0,0).
 * Em seguida deve-se exibir a distância total Euclidiana distance considerando os pontos na mesma ordem em que aparecem na entrada.
 * Por fim, deve-se exibir a distˆancia total Euclidiana shortcut entre o primeiro e último ponto na mesma ordem em que aparecem na entrada.

 ** Observações
 * Não faça Ctrl+C/Ctrl+V deste arquivo PDF no seu arquivo de entrada pois podem ocorrer erros.
 * Cada ponto aparece separado por apenas um espa¸co em branco dos demais e entre (), números com parte decimal são representados usando o ponto final e não a vírgula.
 * Sua resposta deve estar em um único arquivo chamado RL0Q1.[java, py, js, c, cpp, etc]
 * Você deve ler o arquivo L0Q1.in e escrever o arquivo L0Q1.out no mesmo diretório onde estiver rodando seu código RL0Q1.[java, py, js, c, cpp, etc]
 * Não deve ser usado nenhum recurso de ordena¸ c˜ao da linguagem de programação de sua escolha
 * Pode e vai haver mais de uma linha na estrada
 * O número de linhas na entrada deve ser o mesmo da saída, ou seja cada linha da entrada produzirá uma linha na saída
 * Os pontos podem ter coordenadas reais, ou seja o ponto (13.34,10.2) é um ponto válido para a entrada
 * não existem dois espaços em branco seguidos

 * 
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define TAM 5

typedef struct ponto {
        float x;
        float y;
    } Ponto;
    
// void selectionSort(Ponto *A, int tam) {	
// 	for (int i = 0; i < tam; i++) {
// 		int i_menor = i;
// 		for (int j = i + 1; j < tam; j++){
// 			if (A[j].x < A[i_menor].x)
// 				i_menor = j;
// 		}
//     	int aux = A[i].x;
//     	A[i].x = A[i_menor].x;
//     	A[i_menor].x = aux;
// 	}		
// }

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

void print(Ponto *A) {
    printf("Points: ");
    for (int i = 0; i < TAM; i++) {
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
    
int main(){
    //Ponto arrayPontos[] = {{-2,-1}, {4,2}, {4,0}, {2,2}, {8,6}};
    Ponto arrayPontos[] = {{10,10}, {-10, -10}, {5,5}, {-5,-5}, {0,0} };
    //Ponto arrayPontos[TAM];
    float distance=0, shortcut=0;
    
    
    // for (int i = 0; i < TAM; i++) {
    //     scanf("%f", &arrayPontos[i].x);
    //     scanf("%f", &arrayPontos[i].y);
    // }
    
    for (int i = 0; i < TAM-1; i++) {
        distance += sqrt(pow((arrayPontos[i].x  - arrayPontos[i+1].x), 2) + 
    pow((arrayPontos[i].y  - arrayPontos[i+1].y), 2));
    }
    
    shortcut = sqrt(pow((arrayPontos[0].x  - arrayPontos[TAM-1].x), 2) + pow((arrayPontos[0].y  - arrayPontos[TAM-1].y), 2));
    
    selectionSort(arrayPontos, TAM);
    
    
    print(arrayPontos);
    printf("distance %.2f ", distance);
    printf("shortcut %.2f ", shortcut);
    
    // //printf("%d", arrayPontos[0].y);
    
    // float distancia1 = sqrt(pow((arrayPontos[0].x  - arrayPontos[1].x), 2) + 
    // pow((arrayPontos[0].y  - arrayPontos[1].y), 2));
    
    // float distancia2 = sqrt(pow((arrayPontos[1].x  - arrayPontos[2].x), 2) + 
    // pow((arrayPontos[1].y  - arrayPontos[2].y), 2));
    
    // float distancia3 = sqrt(pow((arrayPontos[2].x  - arrayPontos[3].x), 2) + 
    // pow((arrayPontos[2].y  - arrayPontos[3].y), 2));
    
    // float distancia4 = sqrt(pow((arrayPontos[3].x  - arrayPontos[4].x), 2) + 
    // pow((arrayPontos[3].y  - arrayPontos[4].y), 2));
    
    // float menorDistancia = sqrt(pow((arrayPontos[0].x  - arrayPontos[4].x), 2) + 
    // pow((arrayPontos[0].y  - arrayPontos[4].y), 2));
    
    // float distancia = pow((arrayPontos[0].x - arrayPontos[1].x), 2);
    
    // // // printf("%d\n", arrayPontos[0].x);
    // // // printf("%d\n", arrayPontos[1].x);
    
    // printf("A->B: %.2f\n", distancia1);
    // printf("B->C: %.2f\n", distancia2);
    // printf("C->D: %.2f\n", distancia3);
    // printf("D->E: %.2f\n", distancia4);
    // printf("distance %.2f ", distancia1+distancia2+distancia3+distancia4);
    // printf("shortcut %.2f ", menorDistancia);
     
    return 0;
}
