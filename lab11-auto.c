#include <stdio.h>
#include <stdlib.h>

typedef struct no{
	int dado;
	int contador;
	struct no *prox;
}no;

typedef struct lista{
    no *inicio;
    no *fim;
}Lista;

void inicializarLista(Lista *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
}

void inserir_inicio(Lista *lista, int valor){
	no *novo = malloc(sizeof(no));
	novo->dado = valor;
	novo->contador = 0;
	novo->prox = lista->inicio;
	lista->inicio = novo;

    if(lista->fim == NULL){
        lista->fim = novo;
    }
}

void inserir_fim(Lista *lista, int valor){
	no *novo = (no*)malloc(sizeof(no));
    novo->dado = valor;
	novo->contador = 0;
    novo->prox = NULL;

    if (lista->fim == NULL) {
        lista->inicio = novo;
        lista->fim = novo;
    } else {
        lista->fim->prox = novo;
        lista->fim = novo;
    }
}

void mover_frente(Lista *lista, no* anterior, no* atual) {
    if (anterior != NULL) {

        anterior->prox = atual->prox;  
        atual->prox = lista->inicio;         
        lista->inicio= atual;

		if (atual == lista->fim) {
			lista->fim = anterior;
		}
    }
}

void trocar(Lista *lista, no* anterior, no* atual){
	if (anterior != NULL){
		if (anterior == lista->inicio) {
			lista->inicio = atual; 
		} else {
			no *aux = lista->inicio;
			while (aux->prox != anterior) {
				aux = aux->prox;
			}
			aux->prox = atual; 
		}

		anterior->prox = atual->prox;
		atual->prox = anterior;
	}
}

void transpose(int *buscas, int r, Lista *lista){
	int soma = 0;

	for (int i = 0; i < r; i++) {
		no *atual = lista->inicio;
		no *anterior = NULL;
		int comparacao = 1; 
		int encontrado = 0; 
		while (atual != NULL) {
			if (atual->dado == buscas[i]) {
				trocar(lista, anterior, atual);
				soma = soma + comparacao;
				encontrado = 1;
				break;
			}
			anterior = atual;
			atual = atual->prox;
			comparacao++;
		}
		if (encontrado == 0){
			inserir_inicio(lista, buscas[i]);
			soma = soma + comparacao - 1;
		}
	}

	printf("Transpose: %d\n", soma);
}

void mtf(int *buscas, int r, Lista *lista){
	int soma = 0;

	for (int i = 0; i < r; i++) {
		no *atual = lista->inicio;
		no *anterior = NULL;
		int comparacao = 1; 
		int encontrado = 0; 
		while (atual != NULL) {
			if (atual->dado == buscas[i]) {
				mover_frente(lista, anterior, atual);
				soma = soma + comparacao;
				encontrado = 1;
				break;
			}
			anterior = atual;
			atual = atual->prox;
			comparacao++;
		}
		if (encontrado == 0){
			inserir_inicio(lista, buscas[i]);
			soma = soma + comparacao - 1;
		}
	}

	printf("MTF: %d\n", soma);
}

void sequencial(int *buscas, int r, Lista *lista){
	int soma = 0;
	for (int i = 0; i < r; i++) {
		no *atual = lista->inicio;
		int comparacao = 1;
		int encontrado = 0;
		while (atual != NULL) {
			if (atual->dado == buscas[i]) {
				soma = soma + comparacao;
				encontrado = 1;
				break;
			}
			atual = atual->prox;
			comparacao++;
		}
		if (encontrado == 0){
			inserir_fim(lista, buscas[i]);
			soma = soma + comparacao - 1;
		}

	}

	printf("Sequencial: %d\n", soma);

}

void mudar_contador(Lista *lista, no* anterior, no* atual) {
    atual->contador++;

    if (anterior != NULL) {
        anterior->prox = atual->prox;
    } else {
        lista->inicio = atual->prox;
    }

    no *aux = lista->inicio;
    no *antes = NULL;

    while (aux && aux->contador > atual->contador) {
        antes = aux;
        aux = aux->prox;
    }

    if (antes == NULL) {
        atual->prox = lista->inicio;
        lista->inicio = atual;
    } else {
        atual->prox = antes->prox;
        antes->prox = atual;
    }

    if (atual->prox == NULL) {
        lista->fim = atual;
    }
}

void inserir_antes_1(Lista *lista, int valor) {
    no *novo = (no *)malloc(sizeof(no));
    novo->dado = valor;
    novo->contador = 1;

    if (lista->inicio->contador <= 1) {
        novo->prox = lista->inicio;
        lista->inicio = novo;
    } else {
        no *atual = lista->inicio;
        while (atual->prox && atual->prox->contador > 1) {
            atual = atual->prox;
        }
        novo->prox = atual->prox;
        atual->prox = novo;
    }
}

void count(int *buscas, int r, Lista *lista) {
    int soma = 0;

    for (int i = 0; i < r; i++) {
        no *atual = lista->inicio;
        no *anterior = NULL;
        int comparacao = 1; 
        int encontrado = 0;

        while (atual != NULL) {
            if (atual->dado == buscas[i]) {
                mudar_contador(lista, anterior, atual);
                soma = soma + comparacao;
                encontrado = 1;
                break;
            }
            anterior = atual;
            atual = atual->prox;
            comparacao++;
        }

        if (encontrado == 0) {
            inserir_antes_1(lista, buscas[i]);
            soma = soma + comparacao - 1;
        }
    }

    printf("Count: %d\n", soma);
}


int main(void){
	int n, r, num;
	Lista lista;
    inicializarLista(&lista);
	scanf("%d", &n);
	scanf("%d", &r);
	int *buscas = malloc(r*sizeof(int));
	
	for(int j = 1; j <= n; j++){
		inserir_fim(&lista, j);
	}
	
	for(int i = 0; i < r; i++){
		scanf("%d", &num);
		buscas[i] = num;
	}
	
	sequencial(buscas, r, &lista);

	inicializarLista(&lista);
	for (int j = 1; j <= n; j++) {
		inserir_fim(&lista, j);
	}

	mtf(buscas, r, &lista);

	inicializarLista(&lista);
	for (int j = 1; j <= n; j++) {
		inserir_fim(&lista, j);
	}

	transpose(buscas, r, &lista);

	inicializarLista(&lista);
	for (int j = 1; j <= n; j++) {
		inserir_fim(&lista, j);
	}

	count(buscas, r, &lista);

	return 0;
}