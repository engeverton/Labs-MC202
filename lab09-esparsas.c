#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int i;
    int j;
    int x;
} coordenada;

// Função de comparação para qsort (ordena pela linha, depois pela coluna)
int compara(const void *a, const void *b) {
    coordenada *elem_a = (coordenada *)a;
    coordenada *elem_b = (coordenada *)b;
    if (elem_a->i != elem_b->i)
        return elem_a->i - elem_b->i;
    return elem_a->j - elem_b->j;
}

int main() {
    int k, i, j;
    scanf("%d", &k); // número de elementos
    
    coordenada *coordenadas = (coordenada *)malloc(k * sizeof(coordenada));
    
    // Leitura das coordenadas
    for (int t = 0; t < k; t++) {
        scanf("%d %d %d", &coordenadas[t].i, &coordenadas[t].j, &coordenadas[t].x);
    }
    
    // Ordena as coordenadas
    qsort(coordenadas, k, sizeof(coordenada), compara);
    
    // Vetores CSR
    int *A = (int *)malloc(k * sizeof(int));
    int *C = (int *)malloc(k * sizeof(int));
    int *R = (int *)calloc(coordenadas[k-1].i + 2, sizeof(int)); // k+1 elementos
    
    // Preenche os vetores A, C e R
    int linha_atual = -1;
    for (int t = 0; t < k; t++) {
        A[t] = coordenadas[t].x;
        C[t] = coordenadas[t].j;
        if (coordenadas[t].i != linha_atual) {
            for (int l = linha_atual + 1; l <= coordenadas[t].i; l++) {
                R[l] = t;
            }
            linha_atual = coordenadas[t].i;
        }
    }
    R[linha_atual + 1] = k; // insere k no último elemento de R
    
    // Processa as consultas
    while (scanf("%d %d", &i, &j), i != -1 && j != -1) {
        int encontrado = 0;
        if(i > coordenadas[k-1].i){
            printf("(%d,%d) = 0\n", i, j);
        }else{
            for (int t = R[i]; t < R[i + 1]; t++) {
                if (C[t] == j) {
                    printf("(%d,%d) = %d\n", i, j, A[t]);
                    encontrado = 1;
                    break;
                }
            }
            if (!encontrado) {
                printf("(%d,%d) = 0\n", i, j);
            }
        }
    }
    
    // Libera memória
    free(coordenadas);
    free(A);
    free(C);
    free(R);
    
    return 0;
}
