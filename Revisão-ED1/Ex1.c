/*
O código abaixo realiza a impressão do vetor na ordem inversa.
1 - comente o código
2 - faça uma modificação para que seja possível inserir um vetor de n elementos.
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    
    int n;
    
    printf("Escolha o tamanho do seu vetor: ");
    scanf("%d", &n);
    
    int vetor[n];
    
    for (int i = 0; i < n; i++) {       //entrada dos elementos do vetor
        scanf("%i", &vetor[i]);
    }
    
    int j, temp;

    for (j = 0; j < n/2; j++) {
        temp = vetor[j];                  //percorre o vetor invertendo a ordem dos elementos com o auxilio do temp
        vetor[j] = vetor[(n - 1) - j];
        vetor[(n - 1) - j] = temp;
    }

    printf("Vetor invertido:\n");
    for (j = 0; j < n; j++) {
        printf("%d ", vetor[j]);
    }

    return 0;
}