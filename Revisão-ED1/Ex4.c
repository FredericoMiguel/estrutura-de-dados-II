/*
O código apresenta uma lista duplamente ligada com operações básicas para inserir, deletar e imprimir.

1 - comente o código.
2 - Modifique a operação de inserção de dados, para que o usuário seja capaz de inserir valores para a lista.
3 - Faça uma operação de buscar por um valor específico, informado pelo usuário, onde o programa deve apresentar se o valor foi encontrado e, em caso afirmativo, exibir detalhes(vizinhos) do nó correspondente.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

Node* head = NULL;

void insertFront() {
    int value;
    
    printf("Insira um elemento à sua fila: \n");
    scanf("%d", &value);
    
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = head;
    newNode->prev = NULL;
    if (head != NULL)
        head->prev = newNode;
    head = newNode;
}

void deleteNode(Node* node) {
    if (node == head)
        head = node->next;
    if (node->next != NULL)
        node->next->prev = node->prev;
    if (node->prev != NULL)
        node->prev->next = node->next;
    free(node);
}

void printList() {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void searchNode(int value) {
    Node* temp = head;
    int search = 0;

    while(temp != NULL){
        if(value == temp -> data) {
            printf("Valor encontrado. Vizinhos:\n");
            
            if(temp -> prev != NULL) {
                printf("%d ", temp -> prev -> data);
            }
            
            if(temp -> next != NULL) {
                printf("%d ", temp -> next -> data);
            }
            
            search = 1;
            break;
        }
        
        temp = temp -> next;
    }
    
    if(search == 0) {
        printf("Valor não encontrado.\n");
    }
}

int main() {
    insertFront();
    insertFront();
    insertFront();
    printList();
    searchNode(20);
    return 0;
}