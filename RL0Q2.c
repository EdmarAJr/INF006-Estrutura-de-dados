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
