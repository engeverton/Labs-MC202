#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int chave;
    int custo;
} No;

typedef struct heap_min {
    No *heap;
    int *indice;
    int capacidade;
    int tamanho;
} heap_min;

heap_min *inicializar(int n)
{
    heap_min *h = malloc(sizeof(heap_min));
    h->heap = malloc(n * sizeof(No));
    h->indice = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
	h->indice[i] = -1;
    }
    h->capacidade = n;
    h->tamanho = 0;
    return h;
}

void heapup(heap_min * h, int i)
{
    while (i > 0
	   && (h->heap[i].custo < h->heap[(i - 1) / 2].custo
	       || (h->heap[i].custo == h->heap[(i - 1) / 2].custo
		   && h->heap[i].chave < h->heap[(i - 1) / 2].chave))) {
	No aux = h->heap[i];
	h->heap[i] = h->heap[(i - 1) / 2];
	h->heap[(i - 1) / 2] = aux;
	h->indice[h->heap[i].chave] = i;
	h->indice[h->heap[(i - 1) / 2].chave] = (i - 1) / 2;
	i = (i - 1) / 2;
    }
}

void heapfy(heap_min * h, int i)
{
    int menor = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    if (esquerda < h->tamanho
	&& (h->heap[esquerda].custo < h->heap[menor].custo
	    || (h->heap[esquerda].custo == h->heap[menor].custo
		&& h->heap[esquerda].chave < h->heap[menor].chave))) {
	menor = esquerda;
    }

    if (direita < h->tamanho
	&& (h->heap[direita].custo < h->heap[menor].custo
	    || (h->heap[direita].custo == h->heap[menor].custo
		&& h->heap[direita].chave < h->heap[menor].chave))) {
	menor = direita;
    }

    if (menor != i) {
	No aux = h->heap[i];
	h->heap[i] = h->heap[menor];
	h->heap[menor] = aux;
	h->indice[h->heap[i].chave] = i;
	h->indice[h->heap[menor].chave] = menor;
	heapfy(h, menor);
    }
}


void diminuir(heap_min * h, int chave, int nova)
{
    int i = h->indice[chave];
    if (i == -1 || nova >= h->heap[i].custo) {
	return;
    }
    h->heap[i].custo = nova;
    heapup(h, i);
}

void inserir(heap_min * h, int chave, int custo)
{
    if (h->indice[chave] != -1) {
	diminuir(h, chave, custo);
	return;
    }

    if (h->capacidade == h->tamanho) {
	return;
    }

    h->tamanho++;
    int i = h->tamanho - 1;
    h->heap[i].chave = chave;
    h->heap[i].custo = custo;
    h->indice[chave] = i;
    heapup(h, i);
}


void remover(heap_min * h)
{
    if (h == NULL || h->tamanho <= 0) {
	printf("heap vazio\n");
	return;
    }

    int min_chave = h->heap[0].chave;
    int min_custo = h->heap[0].custo;

    printf("minimo {%d,%d}\n", min_chave, min_custo);
    h->indice[min_chave] = -1;
    if (h->tamanho > 1) {
	h->heap[0] = h->heap[h->tamanho - 1];
	h->indice[h->heap[0].chave] = 0;
    }
    h->tamanho--;
    if (h->tamanho > 0) {
	heapfy(h, 0);
    }
}



void liberar(heap_min * h)
{
    free(h->indice);
    free(h->heap);
    free(h);
}



int main(void)
{
    char comando;
    int n, chave, custo;
    heap_min *h = NULL;

    while (scanf("%c", &comando) && comando != 't') {
	if (comando == 'c') {
	    scanf(" %d", &n);
	    if (h) {
		liberar(h);
	    }
	    h = inicializar(n);
	} else if (comando == 'i') {
	    scanf(" %d %d", &chave, &custo);
	    inserir(h, chave, custo);
	} else if (comando == 'm') {
	    remover(h);
	} else if (comando == 'd') {
	    scanf(" %d %d", &chave, &custo);
	    diminuir(h, chave, custo);
	}
    }

    liberar(h);
    return 0;


    return 0;
}