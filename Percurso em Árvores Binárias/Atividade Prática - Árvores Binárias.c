#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da árvore
typedef struct Node {
    int Id;
    int quantComents;
    int quantCurtidas;
    int quantInteracoes;
    struct Node* esquerda;  // left
    struct Node* direita;   // right
} Node;

// Função para criar um novo nó
Node* createNode(int Id, int quantComents, int quantCurtidas, int quantInteracoes) {
    
    Node* newNode = (Node*)malloc(sizeof(Node));
    
    newNode->Id = Id;
    newNode->quantComents = quantComents;
    newNode->quantCurtidas = quantCurtidas;
    newNode->quantInteracoes = quantComents + quantCurtidas;
    newNode->esquerda = NULL; // inicializa como NULL
    newNode->direita = NULL;  // inicializa como NULL
    return newNode;
}


// Função para inserir um nó na árvore usando o Id como critério
Node* insertNode(Node* root, int Id, int quantComents, int quantCurtidas, int quantInteracoes) {
    if (root == NULL) {
        return createNode(Id, quantComents, quantCurtidas, quantInteracoes);
    }
    
    if (quantInteracoes < root->quantInteracoes) {
        // Insere à esquerda se o Id é menor que o do nó atual
        root->esquerda = insertNode(root->esquerda, Id, quantComents, quantCurtidas, quantInteracoes);
    } else if (quantInteracoes > root->quantInteracoes) {
        // Insere à direita se o Id é maior que o do nó atual
        root->direita = insertNode(root->direita, Id, quantComents, quantCurtidas, quantInteracoes);
    } else {
        // Em caso de empate (mesmo Id), podemos ignorar ou fazer uma reinserção
        printf("Id %d já existe na árvore.\n", Id);
    }
    
    return root;
}

// Função para buscar um usuário pelo ID
Node* buscarID(Node* root, int Id) {
    if (root == NULL || root->Id == Id) {
        return root;
    }
    
    if (Id < root->Id) {
        return buscarID(root->esquerda, Id);
    } else {
        return buscarID(root->direita, Id);
    }
}


// Função para encontrar o menor nó (usado na remoção)
Node* minNode(Node* node) {
    Node* current = node;
    while (current && current->esquerda != NULL) {
        current = current->esquerda;
    }
    return current;
}

// Função para remover um usuário pelo ID
Node* deleteUser(Node* root, int Id) {
    if (root == NULL) {
        return root; // Caso base: árvore vazia ou usuário não encontrado
    }
    
    // Procurando o nó a ser removido
    if (Id < root->Id) {
        root->esquerda = deleteUser(root->esquerda, Id);
    } else if (Id > root->Id) {
        root->direita = deleteUser(root->direita, Id);
    } else {
        // Achamos o nó a ser removido

        // Caso 1: Nó sem filhos (nó folha)
        if (root->esquerda == NULL && root->direita == NULL) {
            free(root);
            return NULL;
        }
        
        // Caso 2: Nó com apenas um filho
        else if (root->esquerda == NULL) { // Tem apenas filho direito
            Node* temp = root->direita;
            free(root);
            return temp;
        } else if (root->direita == NULL) { // Tem apenas filho esquerdo
            Node* temp = root->esquerda;
            free(root);
            return temp;
        }
        
        // Caso 3: Nó com dois filhos
        else {
            // Encontrando o sucessor em ordem (menor nó da subárvore direita)
            Node* temp = minNode(root->direita);
            
            // Copiando os dados do sucessor para o nó atual
            root->Id = temp->Id;
            root->quantComents = temp->quantComents;
            root->quantCurtidas = temp->quantCurtidas;
            root->quantInteracoes = temp->quantInteracoes;
            
            // Removendo o sucessor da subárvore direita
            root->direita = deleteUser(root->direita, temp->Id);
        }
    }
    return root;
}

// Função para exibir a árvore em ordem decrescente de idade
void exibirEmOrdem(Node* root) {
    if (root != NULL) {
        exibirEmOrdem(root->esquerda);  // Visita a subárvore esquerda
        printf("ID: %d, Quantidade de Comentários: %d, Quantidade de Curtidas: %d, Quantidade total de interações: %d\n", root->Id, root->quantComents, root->quantCurtidas, root->quantInteracoes);  // Imprime o nó atual
        exibirEmOrdem(root->direita);   // Visita a subárvore direita
    }
}

// Função para exibir a árvore no percurso pré-ordem
void exibirPreOrdem(Node* root) {
    if (root != NULL) {
        printf("ID: %d, Quantidade de Comentários: %d, Quantidade de Curtidas: %d, Quantidade total de interações: %d\n", root->Id, root->quantComents, root->quantCurtidas, root->quantInteracoes);
        exibirPreOrdem(root->esquerda);
        exibirPreOrdem(root->direita);
    }
}

// Função para exibir a árvore no percurso pós-ordem
void exibirPosOrdem(Node* root) {
    if (root != NULL) {
        exibirPosOrdem(root->esquerda);
        exibirPosOrdem(root->direita);
        printf("ID: %d, Quantidade de Comentários: %d, Quantidade de Curtidas: %d, Quantidade total de interações: %d\n", root->Id, root->quantComents, root->quantCurtidas, root->quantInteracoes);
    }
}

// Função principal
int main() {
    Node* root = NULL;
    
    // Inserindo usuários
    root = insertNode(root, 101, 50, 120, 170);
    root = insertNode(root, 102, 40, 700, 740);
    root = insertNode(root, 103, 20, 50, 70);
    root = insertNode(root, 104, 30, 30, 60);
    root = insertNode(root, 105, 70, 1200, 1270);

    // Exibindo usuários em ordem
    printf("Usuários em ordem de interações:\n");
    exibirEmOrdem(root);
    printf("\n");
    printf("Usuários em pré-ordem de interações:\n");
    exibirPreOrdem(root);
    printf("\n");
    printf("Usuários em pós-ordem de interações:\n");
    exibirPosOrdem(root);

    // Removendo um usuário
    root = deleteUser(root, 105);
    printf("\nApós remoção do usuário (Em ordem, pré-ordem e pós-ordem respectivamente):\n");
    exibirEmOrdem(root);
    printf("\n");
    exibirPreOrdem(root);
    printf("\n");
    exibirPosOrdem(root);

    return 0;
}