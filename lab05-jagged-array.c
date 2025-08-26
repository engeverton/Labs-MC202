#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void){
    int n; //quantidade de linhas
    double soma = 0;
    int coluna; 
    int qtd;  //quantidade de valores na matriz
    double media;
    double variancia = 0;
    double desvio_padrao;
    double z;

    scanf("%d", &n);

    qtd = (n*n + n)/2; 

    double **matriz = (double**)malloc(n * sizeof(double*));
    
    //aloca memória para para a matriz
    for (int i = 0; i < n; i++){
        coluna = i + 1;
        matriz[i] = (double*)malloc(coluna*sizeof(double));
    }

    //lê as entradas, adiciona na matriz e soma cada valor
    for(int j = 0; j < n; j++){
        coluna = j + 1;
        for(int k = 0; k < coluna; k++){
            scanf(" %lf", &matriz[j][k]);
            soma = soma + matriz[j][k];
        }
    }

    media = soma/qtd; //calcula a media

    //calcula a variancia
    for(int j = 0; j < n; j++){
        coluna = j + 1;
        for(int k = 0; k < coluna; k++){
            variancia = variancia + pow(matriz[j][k] - media, 2.0);
        }
    }

    variancia = variancia/qtd;
    desvio_padrao = sqrt(variancia); // calcula o desvio-padrao

    //imprime o valor z
    for(int j = 0; j < n; j++){
        coluna = j + 1;
        for(int k = 0; k < coluna; k++){
            z = (matriz[j][k] - media)/desvio_padrao;
            if (k > 0){
                printf(" "); //faz com que não imprima espaço antes do primeiro elemento
            }
            printf("%.4lf", z);
        }
        printf("\n");
    }

    printf("\n");
    printf("%.4lf %.4lf\n", media, desvio_padrao);

    // Liberar a memória alocada
    for (int i = 0; i < n; i++) {
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}