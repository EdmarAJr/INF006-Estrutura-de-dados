<<<<<<< HEAD
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
=======
#include <stdio.h>
#include <math.h>
#define TAM 5


typedef struct ponto {
    float x;
    float y;
    } Ponto;

typedef struct pessoa {
        char nome[50];
        float reais[50];
        int inteiros[50];
        Ponto coord[50];
    } Pessoa;


void selectionSortReais(Pessoa *A, int tam) {	
 	for (int i = 0; i < tam; i++) {
 		int i_menor = i;
 		for (int j = i + 1; j < tam; j++){
 			if (A[j].reais[j] < A[i_menor].reais[i_menor])
 				i_menor = j;
 		}
     	int aux = A[i].reais[i];
     	A[i].reais[i] = A[i_menor].reais[i_menor];
     	A[i_menor].reais[i_menor] = aux;
 	}		
 }
 
void selectionSortInteiros(Pessoa *A, int tam) {	
 	for (int i = 0; i < tam; i++) {
 		int i_menor = i;
 		for (int j = i + 1; j < tam; j++){
 			if (A[j].inteiros[j] < A[i_menor].inteiros[i_menor])
 				i_menor = j;
 		}
     	int aux = A[i].inteiros[i];
     	A[i].inteiros[i] = A[i_menor].inteiros[i_menor];
     	A[i_menor].inteiros[i_menor] = aux;
 	}		
 }
 
void printStr(Pessoa *lista){
    for(int i=0; i<5; i++){
        printf("str: %s ", lista[i].nome);
    }
}

void printFloat(Pessoa *lista){
    selectionSortReais(lista, 5);
    for(int i=0; i<5; i++){
        printf("float: %.2f ", lista[i].reais[i]);
    }
}

void printInt(Pessoa *lista){
    selectionSortInteiros(lista, 5);
    for(int i=0; i<5; i++){
        printf("int: %d ", lista[i].inteiros[i]);
    }
}



int main(){
    //Pessoa lista[50] = {"Edmar", {3.15}, {}, {}};
    Pessoa lista[50];
    for(int i=0; i<5; i++){
        fgets(lista[i].nome, 50, stdin);
        //getchar();
        scanf("%f", &lista[i].reais[i]);
        scanf("%d", &lista[i].inteiros[i]);
        scanf("%f", &lista[i].coord[i].x);
        scanf("%f", &lista[i].coord[i].y);
        
    }
    


    printStr(lista);
    printFloat(lista);
    printInt(lista);
    return 0;
}
>>>>>>> 947c55ba5bde9a8bad2147047b1fd4cc81d9c853
