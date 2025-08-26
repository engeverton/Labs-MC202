#include <stdio.h>
#include <math.h>

// Função que cria o vetor R, a partir dos máximos dos blocos de elementos do vetor V
void novovetor_r(int R[], int V[], int r, int n)
{
    for (int b = 0; b < n; b += r) {
	int max = V[b];
	for (int a = b; (a < b + r) && (a < n); a++) {
	    if (max < V[a]) {
		max = V[a];
	    }
	}
	R[b / r] = max;
    }
}

// Função que atualiza o vetor V e o R
void atualizar(int R[], int V[], int n, int i, int x, int r)
{
    V[i] = x;
    int bloco = i / r;
    int max = V[bloco * r];
    for (int a = bloco * r; (a < (bloco + 1) * r) && (a < n); a++) {
	if (max < V[a]) {
	    max = V[a];
	}
    }
    R[bloco] = max;
}

// Função para calcular o máximo de acordo com o truque
void calcular_maximo(int V[], int R[], int i, int j, int r)
{
    int max_r = 0;
    int max_v = 0;
    int indice_i = i / r;
    int indice_j = j / r;

    if (indice_i == indice_j) {
	// Caso onde i e j estão no mesmo bloco
	for (int q = i; q <= j; q++) {
	    if (max_v < V[q]) {
		max_v = V[q];
	    }
	}
	printf("%d\n", max_v);
	return;
    }
    // Máximo nos blocos intermediários
    for (int l = indice_i + 1; l < indice_j; l++) {
	if (max_r < R[l]) {
	    max_r = R[l];
	}
    }

    // Máximo nos elementos à direita de i 
    for (int q = i; q < (indice_i + 1) * r; q++) {
	if (max_v < V[q]) {
	    max_v = V[q];
	}
    }

    // Máximo nos elementos à esquerda de j 
    for (int q = indice_j * r; q <= j; q++) {
	if (max_v < V[q]) {
	    max_v = V[q];
	}
    }

    // Comparando os máximos encontrados
    if (max_r > max_v) {
	printf("%d\n", max_r);
    } else {
	printf("%d\n", max_v);
    }
}

int main(void)
{
    int n, i, x, j, r;
    char operacao;

    scanf("%d", &n);
    int V[n];

    //loop para ler e armazenar os elementos do vetor V
    for (int k = 0; k < n; k++) {
	scanf("%d", &V[k]);
    }

    // Determina o tamanho do bloco (raiz de n)
    r = sqrt(n);
    if (r * r < n) {
	r++;
    }
    //cria um vetor R e inicializa os elementos com 0
    int R[r];
    for (int p = 0; p < r; p++) {
	R[p] = 0;
    }

    //chamada de função para criar o vetor R
    novovetor_r(R, V, r, n);

    //Lê as entradas e calcula o maximo ou atualiza de acordo com a operação pedida (a ou m)
    while (scanf(" %c", &operacao) == 1) {
	if (operacao == 'm') {
	    scanf("%d %d", &i, &j);
	    calcular_maximo(V, R, i, j, r);
	} else if (operacao == 'a') {
	    scanf("%d %d", &i, &x);
	    atualizar(R, V, n, i, x, r);
	}
    }

    return 0;
}
