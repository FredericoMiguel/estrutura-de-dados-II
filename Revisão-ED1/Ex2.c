/*
O código abaixo recebe do usuário elementos que são inseridos em uma matriz 3x3, em seguida, imprime a soma de sua diagonal principal.
- faça uma modificação para que seja possível dinamizar o tamanho da matriz (utilizar alocação dinâmica de memória usando malloc)
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    
    int *mat ;
    int i, j, l, c;
    
    scanf("%d %d", &l, &c);
    
    int matriz[l][c];
    
    mat = malloc (l * c * sizeof (int));

    for (i=0; i < l; i++) {
        for (j=0; j < c; j++) {
            mat[(i*c) + j] = 0;
        }
    }
    int soma = 0;

    printf("Insira os elementos da matriz lxc: \n");
    for (i = 0; i < c; i++) {
        for (j = 0; j < l; j++) {
            scanf("%d", &matriz[i][j]);
            if (i == j) {
                soma += matriz[i][j];
            }
        }
    }

    printf("Soma dos elementos da diagonal principal: %d \n", soma);
    return 0;
}