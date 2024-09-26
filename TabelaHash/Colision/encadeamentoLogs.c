#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_HASH 10

typedef struct Log{
    int id;
    int timestamp;
    int IP;
    int statusRequisicao;
    char tipoRequisicao[10];
    struct Log *next;
} Log;

typedef struct {
    Log *tabela[TAMANHO_HASH];
} TabelaHash;

int funcao_hash(int id) {
    return id % TAMANHO_HASH;
}

Log *criarLog(int id, int timestamp, int IP, int statusRequisicao, char *tipoRequisicao) {
    Log *newLog = (Log *)malloc(sizeof(Log));
    
    newLog -> id = id;
    newLog -> timestamp = timestamp;
    newLog -> IP = IP;
    newLog -> statusRequisicao = statusRequisicao;
    strcpy(newLog -> tipoRequisicao, tipoRequisicao);
    newLog -> next = NULL;
    
    return newLog;
}

void inserir(TabelaHash *tabela, Log *logA) {
    int indice = funcao_hash(logA -> id);
    logA -> next = tabela -> tabela[indice];
    tabela->tabela[indice] = logA;
}

void exibir_todas(TabelaHash *tabela) {
    for (int i = 0; i < TAMANHO_HASH; i++) {
        Log *atual = tabela->tabela[i];
        while (atual != NULL) {
            printf("Log ID: %d, timestamp: %d, IP: %d, Status da Requisição: %d, Tipo da Requisição: %s (Índice: %d)\n", atual -> id, atual -> timestamp, atual -> IP, atual -> statusRequisicao, atual -> tipoRequisicao, i);
            atual = atual -> next;
        }
    }
    printf("\n");
}

Log *buscar(TabelaHash *tabela, int id) {
    int indice = funcao_hash(id);
    Log *atual = tabela -> tabela[indice];
    
    while (atual != NULL){
        if(atual -> id == id){
            return atual;
        }
        atual = atual -> next;
    }
    
    return NULL;    
}

void excluir(TabelaHash *tabela, int id) {
    int indice = funcao_hash(id);
    Log *atual = tabela -> tabela[indice];
    Log *prev = NULL;

    while (atual != NULL) {
        if (atual -> id == id) {
            if (prev == NULL) {
                tabela -> tabela[indice] = atual -> next;
            } else {
                prev -> next = atual -> next;
            }
            
            printf("Transação com ID %d foi excluída.\n", id);
            
            return;
        }
        
        prev = atual;
        atual = atual -> next;
    }
    
    printf("Transação com ID %d não encontrada para exclusão.\n", id);
}

int contar_elementos(TabelaHash *tabela) {
    int total = 0;

    for (int i = 0; i < TAMANHO_HASH; i++) {
        Log *atual = tabela -> tabela[i];

        while (atual != NULL) {
            total++;
            atual = atual -> next;
        }
    }

    return total;
}

void inserir_dados_predefinidos(TabelaHash *tabela) {
    inserir(tabela, criarLog(0, 1400, 172165163, 404, "GET"));
    inserir(tabela, criarLog(1, 1403, 172165254, 404, "GET"));
    inserir(tabela, criarLog(2, 1410, 192168561, 404, "GET"));
    inserir(tabela, criarLog(3, 1700, 172165257, 507, "POST"));
    inserir(tabela, criarLog(4, 1600, 172165162, 200, "GET"));
    inserir(tabela, criarLog(5, 1500, 172165263, 404, "GET"));
    inserir(tabela, criarLog(6, 1550, 192168562, 500, "POST"));
    inserir(tabela, criarLog(7, 1650, 172165267, 403, "DELETE"));
    inserir(tabela, criarLog(8, 1800, 172165168, 200, "GET"));
    inserir(tabela, criarLog(9, 1750, 192168563, 401, "PUT"));
    inserir(tabela, criarLog(10, 1620, 172165264, 408, "GET"));
    inserir(tabela, criarLog(11, 1580, 172165169, 404, "POST"));
    inserir(tabela, criarLog(12, 1470, 172165260, 200, "GET"));
    inserir(tabela, criarLog(13, 1480, 192168564, 403, "PATCH"));
    inserir(tabela, criarLog(14, 1520, 172165258, 500, "GET"));
    inserir(tabela, criarLog(15, 1530, 172165265, 404, "DELETE"));
    inserir(tabela, criarLog(16, 1590, 172165266, 204, "GET"));
    inserir(tabela, criarLog(17, 1690, 192168565, 400, "POST"));
    inserir(tabela, criarLog(18, 1640, 172165170, 403, "GET"));
    inserir(tabela, criarLog(19, 1610, 172165161, 404, "PUT"));
    inserir(tabela, criarLog(20, 1570, 172165171, 401, "GET"));
    inserir(tabela, criarLog(21, 1805, 172165172, 204, "GET"));
    inserir(tabela, criarLog(22, 1820, 192168566, 500, "POST"));
    inserir(tabela, criarLog(23, 1840, 172165173, 404, "GET"));
    inserir(tabela, criarLog(24, 1860, 172165174, 200, "DELETE"));
    inserir(tabela, criarLog(25, 1880, 172165175, 408, "GET"));
    inserir(tabela, criarLog(26, 1900, 192168567, 401, "PUT"));
    inserir(tabela, criarLog(27, 1920, 172165176, 403, "GET"));
    inserir(tabela, criarLog(28, 1940, 172165177, 500, "POST"));
    inserir(tabela, criarLog(29, 1960, 192168568, 404, "GET"));
    
    printf("Transações foram inseridas com sucesso.\n");
}



int main() {
    TabelaHash tabela = {NULL};
    
    inserir_dados_predefinidos(&tabela);

    printf("\nTodas as transações inseridas: %d\n", contar_elementos(&tabela));
    exibir_todas(&tabela);

    Log *buscarLog = buscar(&tabela, 2);
    if (buscarLog != NULL) {
        printf("Log encontrado: ID: %d, timestamp: %d, IP: %d, Status da Requisição: %d, Tipo da Requisição: %s\n",
               buscarLog -> id, buscarLog -> timestamp, buscarLog -> IP, buscarLog -> statusRequisicao, buscarLog -> tipoRequisicao);
    } else {
        printf("Log não encontrado.\n");
    }
    
    printf("\nTransações excluidas:\n");
    excluir(&tabela, 13);
    excluir(&tabela, 22);
    
    printf("\nTransações Atualizadas: %d\n", contar_elementos(&tabela));
    exibir_todas(&tabela);
    
    return 0;
}