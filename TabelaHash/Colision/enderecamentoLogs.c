#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_HASH 10

typedef struct{
    int id;
    int timestamp;
    int IP;
    int statusRequisicao;
    char tipoRequisicao[10];
    int ocupado;     
} Log;

typedef struct {
    Log tabela[TAMANHO_HASH];
} TabelaHash;

int funcao_hash(int id) {
    return id % TAMANHO_HASH;  
}

int hash2(int id) {
    return 7 - (id % 7); 
}

int sondagem_linear(TabelaHash *tabela, int id) {
    int indice = funcao_hash(id);
    int tentativas = 0;

    while (tabela->tabela[indice].ocupado && tabela->tabela[indice].id != id && tentativas < TAMANHO_HASH) {
        indice = (indice + 1) % TAMANHO_HASH; 
        tentativas++;
    }

    return (tentativas < TAMANHO_HASH) ? indice : -1;
}

int sondagem_quadratica(TabelaHash *tabela, int id) {
    int indice = funcao_hash(id);
    int i = 1;
    int tentativas = 0;

    while (tabela -> tabela[indice].ocupado && tabela->tabela[indice].id != id && tentativas < TAMANHO_HASH) {
        indice = (funcao_hash(id) + i * i) % TAMANHO_HASH; 
        i++;
        tentativas++;
    }

    return (tentativas < TAMANHO_HASH) ? indice : -1;
}

int duplo_hashing(TabelaHash *tabela, int id) {
    int indice = funcao_hash(id);
    int step = hash2(id);
    int tentativas = 0;

    while (tabela -> tabela[indice].ocupado && tabela->tabela[indice].id != id && tentativas < TAMANHO_HASH) {
        indice = (indice + step) % TAMANHO_HASH; 
        tentativas++;
    }

    return (tentativas < TAMANHO_HASH) ? indice : -1;
}

Log criarLog(int id, int timestamp, int IP, int statusRequisicao, char *tipoRequisicao) {
    Log newLog;
    
    newLog.id = id;
    newLog.timestamp = timestamp;
    newLog.IP = IP;
    newLog.statusRequisicao = statusRequisicao;
    strcpy(newLog.tipoRequisicao, tipoRequisicao);
    newLog.ocupado = 1;
    
    return newLog;
}

void inserir_linear(TabelaHash *tabela, Log logA) {
    int indice = funcao_hash(logA.id);

    if(!tabela -> tabela[indice].ocupado) {
        tabela -> tabela[indice] = logA;
    } else {
        int novo_indice = sondagem_linear(tabela, logA.id);
        if (novo_indice != -1) {
            tabela -> tabela[novo_indice] = logA;
        } else {
            printf("Erro: Tabela hash está cheia.\n");
        }
    }
}

void inserir_quadratica(TabelaHash *tabela, Log logA) {
    int indice = funcao_hash(logA.id);

    if (!tabela -> tabela[indice].ocupado) {
        tabela -> tabela[indice] = logA;
    } else {
        int novo_indice = sondagem_quadratica(tabela, logA.id);
        if (novo_indice != -1) {
            tabela -> tabela[novo_indice] = logA;
        } else {
            printf("Erro: Tabela hash está cheia.\n");
        }
    }
}

void inserir_duplo_hashing(TabelaHash *tabela, Log logA) {
    int indice = funcao_hash(logA.id);

    if (!tabela -> tabela[indice].ocupado) {
        tabela -> tabela[indice] = logA;
    } else {
        int novo_indice = duplo_hashing(tabela, logA.id);
        if (novo_indice != -1) {
            tabela -> tabela[novo_indice] = logA;
        } else {
            printf("Erro: Tabela hash está cheia.\n");
        }
    }
}

void exibir_todas(TabelaHash *tabela) {
    for (int i = 0; i < TAMANHO_HASH; i++) {
        if (tabela -> tabela[i].ocupado) {
            printf("Log ID: %d, timestamp: %d, IP: %d, Status da Requisição: %d, Tipo da Requisição: %s (Índice: %d)\n", tabela -> tabela[i].id, tabela -> tabela[i].timestamp, tabela -> tabela[i].IP, tabela -> tabela[i].statusRequisicao, tabela -> tabela[i].tipoRequisicao, i);
        }
    }
}

// Função de busca com sondagem linear
int buscar_linear(TabelaHash *tabela, int id) {
    int indice = sondagem_linear(tabela, id);

    if (tabela->tabela[indice].ocupado && tabela->tabela[indice].id == id) {
        printf("Log com ID %d encontrado no índice %d.\n", tabela->tabela[indice].id, indice);
        return indice;
    } else {
        printf("Log com ID %d não encontrado.\n", id);
        return -1;
    }
}

// Função de busca com sondagem quadratica
int buscar_quadratica(TabelaHash *tabela, int id) {
    int indice = sondagem_quadratica(tabela, id);

    if (tabela->tabela[indice].ocupado && tabela->tabela[indice].id == id) {
        printf("Log com ID %d encontrado no índice %d.\n", tabela->tabela[indice].id, indice);
        return indice;
    } else {
        printf("Log com ID %d não encontrado.\n", id);
        return -1;
    }
}

// Função de busca com duplo hashing
int buscar_duplo_hashing(TabelaHash *tabela, int id) {
    int indice = duplo_hashing(tabela, id);

    if (tabela->tabela[indice].ocupado && tabela->tabela[indice].id == id) {
        printf("Log com ID %d encontrado no índice %d.\n", tabela->tabela[indice].id, indice);
        return indice;
    } else {
        printf("Log com ID %d não encontrado.\n", id);
        return -1;
    }
}

// Função de exclusão com sondagem linear
int excluir_linear(TabelaHash *tabela, int id) {
    int indice = sondagem_linear(tabela, id);
    
    if (tabela->tabela[indice].ocupado && tabela->tabela[indice].id == id) {
        tabela->tabela[indice].ocupado = 0;
        printf("Log com ID %d excluído do índice %d.\n", id, indice);
        return indice;
    } else {
        printf("Log com ID %d não encontrado, não pode ser excluído.\n", id);
        return -1;
    }
}

// Função de exclusão com sondagem quadratica
int excluir_quadratica(TabelaHash *tabela, int id) {
    int indice = sondagem_quadratica(tabela, id);
    
    if (tabela->tabela[indice].ocupado && tabela->tabela[indice].id == id) {
        tabela->tabela[indice].ocupado = 0;
        printf("Log com ID %d excluído do índice %d.\n", id, indice);
        return indice;
    } else {
        printf("Log com ID %d não encontrado, não pode ser excluído.\n", id);
        return -1;
    }
}

// Função de exclusão com duplo hashing
int excluir_duplo_hashing(TabelaHash *tabela, int id) {
    int indice = duplo_hashing(tabela, id);
    
    if (tabela->tabela[indice].ocupado && tabela->tabela[indice].id == id) {
        tabela->tabela[indice].ocupado = 0;
        printf("Log com ID %d excluído do índice %d.\n", id, indice);
        return indice;
    } else {
        printf("Log com ID %d não encontrado, não pode ser excluído.\n", id);
        return -1;
    }
}

int main() {
    TabelaHash tabela_linear = {0};
    
    printf("Inserção com Sondagem Linear:\n\n");
    
    inserir_linear(&tabela_linear, criarLog(0, 1400, 172165163, 404, "GET"));
    inserir_linear(&tabela_linear, criarLog(1, 1403, 172165254, 404, "GET"));
    inserir_linear(&tabela_linear, criarLog(2, 1410, 192168561, 404, "GET"));
    inserir_linear(&tabela_linear, criarLog(3, 1700, 172165257, 507, "POST"));
    inserir_linear(&tabela_linear, criarLog(4, 1600, 172165162, 200, "GET"));
    inserir_linear(&tabela_linear, criarLog(15, 1530, 172165265, 404, "DELETE"));
    inserir_linear(&tabela_linear, criarLog(18, 1640, 172165170, 403, "GET"));
    inserir_linear(&tabela_linear, criarLog(21, 1805, 172165172, 204, "GET"));
    inserir_linear(&tabela_linear, criarLog(24, 1860, 172165174, 200, "DELETE"));
    
    exibir_todas(&tabela_linear);
    
    printf("\n");
    buscar_linear(&tabela_linear, 3);
    buscar_linear(&tabela_linear, 50);
    
    printf("\n");
    excluir_linear(&tabela_linear, 15);
    excluir_linear(&tabela_linear, 99);
    
    printf("\n");
    exibir_todas(&tabela_linear);
    
    TabelaHash tabela_quadratica = {0};
    
    printf("\nInserção com Sondagem Quadrática:\n\n");
    
    inserir_quadratica(&tabela_quadratica, criarLog(12, 1500, 172165263, 404, "GET"));
    inserir_quadratica(&tabela_quadratica, criarLog(23, 1550, 192168562, 500, "POST"));
    inserir_quadratica(&tabela_quadratica, criarLog(34, 1650, 172165267, 403, "DELETE"));
    inserir_quadratica(&tabela_quadratica, criarLog(45, 1800, 172165168, 200, "GET"));
    inserir_quadratica(&tabela_quadratica, criarLog(56, 1750, 192168563, 401, "PUT"));
    inserir_quadratica(&tabela_quadratica, criarLog(67, 1590, 172165266, 204, "GET"));
    inserir_quadratica(&tabela_quadratica, criarLog(78, 1610, 172165161, 404, "PUT"));
    inserir_quadratica(&tabela_quadratica, criarLog(89, 1820, 192168566, 500, "POST"));
    inserir_quadratica(&tabela_quadratica, criarLog(90, 1880, 172165175, 408, "GET"));
    
    exibir_todas(&tabela_quadratica);
    
    printf("\n");
    buscar_quadratica(&tabela_quadratica, 12);
    buscar_quadratica(&tabela_quadratica, 72);
    
    printf("\n");
    excluir_linear(&tabela_quadratica, 23);
    excluir_linear(&tabela_quadratica, 55);
    
    printf("\n");
    exibir_todas(&tabela_quadratica);
    
    TabelaHash tabela_duplo = {0};
    
    printf("\nInserção com Duplo Hashing:\n\n");
    
    inserir_duplo_hashing(&tabela_duplo, criarLog(10, 1620, 172165264, 408, "GET"));
    inserir_duplo_hashing(&tabela_duplo, criarLog(11, 1580, 172165169, 404, "POST"));
    inserir_duplo_hashing(&tabela_duplo, criarLog(12, 1470, 172165260, 200, "GET"));
    inserir_duplo_hashing(&tabela_duplo, criarLog(13, 1480, 192168564, 403, "PATCH"));
    inserir_duplo_hashing(&tabela_duplo, criarLog(14, 1520, 172165258, 500, "GET"));
    inserir_duplo_hashing(&tabela_duplo, criarLog(17, 1690, 192168565, 400, "POST"));
    inserir_duplo_hashing(&tabela_duplo, criarLog(20, 1570, 172165171, 401, "GET"));
    inserir_duplo_hashing(&tabela_duplo, criarLog(23, 1840, 172165173, 404, "GET"));
    inserir_duplo_hashing(&tabela_duplo, criarLog(26, 1900, 192168567, 401, "PUT"));
    
    exibir_todas(&tabela_duplo);
    
    printf("\n");
    buscar_duplo_hashing(&tabela_duplo, 13);
    buscar_duplo_hashing(&tabela_duplo, 32);
    
    printf("\n");
    excluir_duplo_hashing(&tabela_duplo, 17);
    excluir_duplo_hashing(&tabela_duplo, 21);
    
    printf("\n");
    exibir_todas(&tabela_duplo);
    
    return 0;
}
