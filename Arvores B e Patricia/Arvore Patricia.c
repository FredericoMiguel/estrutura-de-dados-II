#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do nó da Árvore Patricia
typedef struct PatriciaNode {
    char *key;                     // Chave armazenada (palavra ou parte dela)
    int isEndOfWord;               // Indica se é o final de uma palavra
    struct PatriciaNode *left;     // Filhos para prefixos diferentes
    struct PatriciaNode *right;    // Filhos para prefixos iguais
} PatriciaNode;

// Função para criar um novo nó
PatriciaNode* createNode(const char *key, int isEndOfWord) {
    PatriciaNode *node = (PatriciaNode *)malloc(sizeof(PatriciaNode));
    node->key = strdup(key); // Copia a chave
    node->isEndOfWord = isEndOfWord;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Função para encontrar o primeiro índice onde duas strings divergem
int findMismatchIndex(const char *str1, const char *str2) {
    int i = 0;
    while (str1[i] && str2[i] && str1[i] == str2[i]) {
        i++;
    }
    return i;
}

// Função para inserir uma palavra na Árvore Patricia
PatriciaNode* insertPatricia(PatriciaNode *root, const char *word) {
    if (!root) {
        return createNode(word, 1); // Novo nó para palavra
    }

    int mismatchIndex = findMismatchIndex(root->key, word);

    // Caso 1: A palavra é um prefixo do nó atual
    if (mismatchIndex == strlen(root->key)) {
        if (mismatchIndex == strlen(word)) {
            // Palavra já existe
            root->isEndOfWord = 1;
        } else {
            // Inserir a parte restante na subárvore direita
            root->right = insertPatricia(root->right, word + mismatchIndex);
        }
        return root;
    }

    // Caso 2: O nó atual é um prefixo da palavra
    if (mismatchIndex == strlen(word)) {
        PatriciaNode *newNode = createNode(word, 1);
        newNode->right = root;
        return newNode;
    }

    // Caso 3: Há um ponto de divergência
    PatriciaNode *splitNode = createNode(root->key + mismatchIndex, root->isEndOfWord);
    splitNode->left = root->left;
    splitNode->right = root->right;

    root->key[mismatchIndex] = '\0'; // Divide a chave do nó atual
    root->isEndOfWord = 0;
    root->left = splitNode;
    root->right = createNode(word + mismatchIndex, 1);

    return root;
}

// Função para buscar uma palavra na Árvore Patricia
int searchPatricia(PatriciaNode *root, const char *word) {
    if (!root) {
        return 0; // Palavra não encontrada
    }

    int mismatchIndex = findMismatchIndex(root->key, word);

    // Palavra é prefixo do nó atual
    if (mismatchIndex == strlen(word) && mismatchIndex <= strlen(root->key)) {
        return root->isEndOfWord;
    }

    // Ir para a subárvore direita
    if (mismatchIndex == strlen(root->key)) {
        return searchPatricia(root->right, word + mismatchIndex);
    }

    return 0; // Palavra não encontrada
}

// Função para exibir as palavras na Árvore Patricia
void printPatricia(PatriciaNode *root, char *buffer, int depth) {
    if (!root) {
        return;
    }

    // Copiar a chave atual no buffer
    strncpy(buffer + depth, root->key, strlen(root->key));
    depth += strlen(root->key);

    // Exibir a palavra se for um final válido
    if (root->isEndOfWord) {
        buffer[depth] = '\0';
        printf("%s\n", buffer);
    }

    // Recursão para subárvores
    printPatricia(root->left, buffer, depth);
    printPatricia(root->right, buffer, depth);
}

// Função para listar as palavras de autocomplete a partir de um prefixo
void autocompletePatricia(PatriciaNode *root, const char *prefix, char *buffer, int depth) {
    if (!root) {
        return;
    }

    // Verifica o ponto de divergência
    int mismatchIndex = findMismatchIndex(root->key, prefix);

    // Caso o prefixo corresponda completamente à chave
    if (mismatchIndex == strlen(prefix)) {
        // Copia a chave para o buffer e continua a busca nas subárvores
        strncpy(buffer + depth, root->key, strlen(root->key));
        depth += strlen(root->key);

        // Se for o final de uma palavra, imprime no autocomplete
        if (root->isEndOfWord) {
            buffer[depth] = '\0';
            printf("%s\n", buffer);
        }

        // Recursão para a subárvore esquerda e direita
        autocompletePatricia(root->left, prefix + mismatchIndex, buffer, depth);
        autocompletePatricia(root->right, prefix + mismatchIndex, buffer, depth);
    } else if (mismatchIndex == 0) {
        // Caso o prefixo não corresponda completamente, retorna sem fazer nada
        return;
    } else {
        // Caso o prefixo não corresponda, a recursão continua nas subárvores
        return;
    }
}

// Função principal para testar a Árvore Patricia
int main() {
    PatriciaNode *root = NULL;
    char buffer[100]; // Buffer para exibição das palavras

    // Exemplo inserção de palavras  - substituir pelo arquivo dicionario.txt
    root = insertPatricia(root, "carro");
    root = insertPatricia(root, "car");
    root = insertPatricia(root, "cat");
    root = insertPatricia(root, "dog");
    root = insertPatricia(root, "cart");

    // Busca de palavras - exemplo
    printf("Busca por 'car': %s\n", searchPatricia(root, "car") ? "Encontrada" : "Não encontrada");
    printf("Busca por 'cart': %s\n", searchPatricia(root, "cart") ? "Encontrada" : "Não encontrada");
    printf("Busca por 'bat': %s\n", searchPatricia(root, "bat") ? "Encontrada" : "Não encontrada");
    
    // Exemplo de Autocomplete - prefixo "ca"
    printf("\nSugestões para 'car':\n");
    autocompletePatricia(root, "car", buffer, 0);

    // Exibir todas as palavras
    printf("\nPalavras na árvore:\n");
    printPatricia(root, buffer, 0);

    return 0;
}