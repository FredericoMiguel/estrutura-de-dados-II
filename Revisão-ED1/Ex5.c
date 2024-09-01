/*
O código abaixo apresenta a implementação de uma pilha e suas operações básicas.

1 - comente o código
2 - implemente uma função para verificar se a pilha está vazia.
3 - proponha uma função que possa fazer expansão dinâmica quando a capacidade máxima é atingida, em vez de simplesmente negar novas inserções na pilha.
*/

#include <stdio.h>
#include <stdlib.h>

int tamanho = 1;
int *pilha;
int topo = -1;


// função para adicionar um item ao topo da pilha
void push(int elemento) {
    if (topo < tamanho - 1) {
        pilha[++topo] = elemento;
    } else {
        tamanho += 1;
        pilha = realloc(pilha, tamanho * sizeof(int));
        push(elemento);
    }
}

// função para remover o item do topo da pilha
int pop() {
    if (topo == -1) {
        printf("Pilha vazia!\n");
        return -1;
    } else {
        return pilha[topo--];
    }
}

// função para verificar o item do topo da pilha
int top() {
    if (topo == -1) {
        printf("Pilha vazia!\n");
        return -1;
    } else {
        return pilha[topo];
    }
}

// função para imprimir a pilha
void imprimir() {
    printf("Conteúdo da pilha:\n");
    for (int i = topo; i >= 0; i--) {
        printf("%d ", pilha[i]);
    }
    printf("\n");
}

//função para verificar se a lista está vazia
int empty() {
    if(topo == -1) {
        printf("Pilha vazia!\n");
        return pilha[topo] == -1;
    }
}

int main() {
    pilha = (int *)malloc(tamanho * sizeof(int));
    
    push(10);
    push(20);
    push(30);
    imprimir();
    printf("Elemento no topo: %d\n\n", top());
    printf("Elemento removido: %d\n", pop());
    imprimir();
    printf("Elemento no topo: %d\n\n", top());
    printf("Elemento removido: %d\n", pop());
    imprimir();
    printf("Elemento no topo: %d\n\n", top());
    printf("Elemento removido: %d\n", pop());
    imprimir();
    empty();
    
    return 0;
}