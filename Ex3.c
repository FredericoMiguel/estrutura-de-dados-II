/*
O código abaixo apresenta a implementação de uma lista linear.

Para esse exemplo, faça:
- Implemente funções adicionais como buscar(int elemento) para encontrar a posição de um elemento na lista.
ou 
- Adicione métodos para inverter a lista, encontrar o máximo/mínimo, ou ordenar a lista.
*/

#include <stdio.h>
#define MAX_SIZE 10

int lista[MAX_SIZE];
int tamanho = 0;

void inserir(int elemento) {
    if (tamanho < MAX_SIZE) {
        lista[tamanho++] = elemento;
    } else {
        printf("Lista cheia!\n");
    }
}

void remover(int index) {
    if (index < 0 || index >= tamanho) {
        printf("Índice inválido!\n");
    } else {
        for (int i = index; i < tamanho - 1; i++) {
            lista[i] = lista[i + 1];
        }
        tamanho--;
    }
}

void imprimir() {
    printf("Elementos da lista:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", lista[i]);
    }
    printf("\n");
}

void buscar(int elemento) {
    for(int i = 0; i < tamanho; i++) {
        if(elemento == lista[i]) {
            printf("O elemento %d foi encontrado na posição %d \n", elemento, i + 1);
            break;
        }else {
            printf("Elemento %d não se encontra na lista \n", elemento);
            break;
        }
    }
}

void inverter() {
    for (int i = 0; i < tamanho/2; i++) {
        int temp= lista[i];                  
        lista[i] = lista[(tamanho - 1) - i];
        lista[(tamanho - 1) - i] = temp;
    }
}

void determinarMaior() {
    int maior;
    for(int i = 0; i < tamanho; i++) {
        if(maior < lista[i]) {
            maior = lista[i];
        }
    }
    printf("O maior elemento da lista é %d \n", maior);
}

void determinarMenor() {
    int menor;
    for(int i = 0; i < tamanho; i++) {
        if(menor > lista[i]) {
            menor = lista[i];
        }
    }
    
    printf("O menor elemento da lista é %d \n", menor);
}

int main() {
    inserir(10);
    inserir(20);
    inserir(30);
    buscar(10);
    imprimir();
    remover(1);
    inverter();
    imprimir();
    determinarMaior();
    determinarMenor();
    return 0;
}