#include <stdio.h>
#include <stdlib.h>
#define MAX 150

typedef struct No {
    int valor;
    struct No *prox;
    struct No *ant;
} No;

typedef struct lista {
    int nome_conjunto;
    No *inicio;
} Lista;

// Função para inicializar uma lista
Lista *inicializar(int conjunto)
{
    Lista *L = (Lista *) malloc(sizeof(Lista));
    if (L == NULL) {
	return NULL;
    }
    L->inicio = NULL;
    L->nome_conjunto = conjunto;
    return L;
}

// Função para buscar um valor na lista
int buscar(Lista * L, int valor)
{
    No *aux = L->inicio;
    while (aux) {
	if (aux->valor == valor) {
	    return 1;		// Valor encontrado
	}
	aux = aux->prox;
    }
    return 0;			// Valor não encontrado
}

// Função para inserir um elemento na lista de forma ordenada
void inserir(Lista * L, int elemento)
{
    if (buscar(L, elemento)) {	// Verifica se o elemento já existe
	return;			// Não insere se o elemento já estiver presente
    }

    No *novo = (No *) malloc(sizeof(No));
    if (!novo) {
	return;			// Tratamento de erro ao alocar memória
    }
    novo->valor = elemento;
    novo->prox = NULL;
    novo->ant = NULL;

    if (L->inicio == NULL) {
	L->inicio = novo;	// Lista vazia, insere o primeiro elemento
    } else if (elemento < L->inicio->valor) {
	novo->prox = L->inicio;	// Insere no início
	L->inicio->ant = novo;
	L->inicio = novo;
    } else {
	No *aux = L->inicio;
	while (aux->prox && aux->prox->valor < elemento) {
	    aux = aux->prox;	// Navega até a posição correta
	}
	novo->prox = aux->prox;
	novo->ant = aux;
	if (aux->prox) {
	    aux->prox->ant = novo;	// Ajusta o anterior do próximo nó
	}
	aux->prox = novo;	// Insere o novo nó
    }
}

// Função para remover um elemento da lista
void remover(Lista * L, int x)
{
    if (!L->inicio) {
	return;			// Lista vazia
    }

    No *aux = L->inicio, *remover = NULL;

    // Caso especial para remover o primeiro nó
    if (L->inicio->valor == x) {
	remover = L->inicio;
	L->inicio = remover->prox;
	if (L->inicio) {
	    L->inicio->ant = NULL;	// Ajusta o anterior
	}
	free(remover);
	return;
    }
    // Percorre a lista até encontrar o valor
    while (aux->prox) {
	if (aux->prox->valor == x) {
	    remover = aux->prox;
	    aux->prox = remover->prox;	// Ajusta o próximo
	    if (aux->prox) {
		aux->prox->ant = aux;	// Ajusta o anterior do próximo nó
	    }
	    free(remover);
	    return;
	}
	aux = aux->prox;
    }
}

// Função para liberar a memória usada pela lista
void liberar(Lista * L)
{
    No *aux = L->inicio;
    while (aux) {
	No *temp = aux;
	aux = aux->prox;
	free(temp);
    }
    free(L);			// Libera a estrutura Lista
}

// Função para buscar um conjunto na lista de conjuntos
Lista *buscar_lista(Lista ** L, int conjunto, int *indice)
{
    for (int i = 0; i < MAX; i++) {
	if (L[i] && L[i]->nome_conjunto == conjunto) {
	    *indice = i;
	    return L[i];
	}
    }
    return NULL;		// Conjunto não encontrado
}

// Função para realizar a união de dois conjuntos
void uniao(Lista * L, Lista * L1, Lista * L2)
{
    No *inicio1 = L1->inicio;
    No *inicio2 = L2->inicio;

    while (inicio1 && inicio2) {
	if (inicio1->valor < inicio2->valor) {
	    inserir(L, inicio1->valor);
	    inicio1 = inicio1->prox;
	} else if (inicio1->valor > inicio2->valor) {
	    inserir(L, inicio2->valor);
	    inicio2 = inicio2->prox;
	} else {		// Valores iguais
	    inserir(L, inicio1->valor);
	    inicio1 = inicio1->prox;
	    inicio2 = inicio2->prox;
	}
    }

    // Insere o restante da lista L1 (se houver)
    while (inicio1) {
	inserir(L, inicio1->valor);
	inicio1 = inicio1->prox;
    }

    // Insere o restante da lista L2 (se houver)
    while (inicio2) {
	inserir(L, inicio2->valor);
	inicio2 = inicio2->prox;
    }
}

// Função para realizar a interseção de dois conjuntos
void intersecao(Lista * L, Lista * L1, Lista * L2)
{
    No *inicio1 = L1->inicio;
    No *inicio2 = L2->inicio;

    while (inicio1 && inicio2) {
	if (inicio1->valor < inicio2->valor) {
	    inicio1 = inicio1->prox;
	} else if (inicio1->valor > inicio2->valor) {
	    inicio2 = inicio2->prox;
	} else {		// Valores iguais
	    inserir(L, inicio1->valor);
	    inicio1 = inicio1->prox;
	    inicio2 = inicio2->prox;
	}
    }
}

// Função para realizar a diferença de dois conjuntos
void diferenca(Lista * L, Lista * L1, Lista * L2)
{
    No *inicio1 = L1->inicio;

    while (inicio1) {
	if (!buscar(L2, inicio1->valor)) {
	    inserir(L, inicio1->valor);	// Insere apenas se não está em L2
	}
	inicio1 = inicio1->prox;
    }
}

// Função para imprimir a lista
void imprimir(Lista * L)
{
    if (!L || !L->inicio) {	// Verifica se a lista existe e tem elementos
	printf("C%d = {}\n", L->nome_conjunto);
	return;
    }

    No *aux = L->inicio;
    printf("C%d = {", L->nome_conjunto);
    while (aux) {
	printf("%d", aux->valor);
	aux = aux->prox;
	if (aux)
	    printf(", ");
    }
    printf("}\n");
}

int main(void)
{
    char caractere;
    int conjunto, conjunto1, conjunto2;
    Lista **L = (Lista **) calloc(MAX, sizeof(Lista *));
    int j = 0;
    int t, x;
    int indice;			// Alocação correta do índice

    while (scanf("%c ", &caractere) && caractere != 't') {
	if (caractere == 'c') {
	    scanf("%d ", &conjunto);
	    Lista *existe = buscar_lista(L, conjunto, &indice);
	    if (existe) {
		liberar(existe);	// Libera a memória antes de reinicializar
		L[indice] = inicializar(conjunto);	// Atualiza a lista
	    } else {
		L[j++] = inicializar(conjunto);	// Adiciona nova lista
	    }
	} else if (caractere == 'i') {
	    scanf("%d %d ", &conjunto, &t);
	    Lista *lst = buscar_lista(L, conjunto, &indice);
	    if (lst) {		// Verifica se a lista existe
		for (int i = 0; i < t; i++) {
		    scanf("%d ", &x);
		    inserir(lst, x);
		}
	    }
	} else if (caractere == 'p') {
	    scanf("%d", &conjunto);
	    Lista *lst = buscar_lista(L, conjunto, &indice);
	    if (lst) {
		imprimir(lst);
	    }
	} else if (caractere == 'r') {
	    scanf("%d %d ", &conjunto, &t);
	    Lista *lst = buscar_lista(L, conjunto, &indice);
	    if (lst) {		// Verifica se a lista existe
		for (int i = 0; i < t; i++) {
		    scanf("%d ", &x);
		    remover(lst, x);
		}
	    }
	} else if (caractere == 'u' || caractere == 'n'
		   || caractere == 'm') {
	    scanf("%d %d %d ", &conjunto, &conjunto1, &conjunto2);
	    Lista *lst1 = buscar_lista(L, conjunto1, &indice);
	    Lista *lst2 = buscar_lista(L, conjunto2, &indice);
	    Lista *lstRes = buscar_lista(L, conjunto, &indice);
	    if (!lstRes) {
		lstRes = inicializar(conjunto);
		L[j++] = lstRes;
	    } else {
		liberar(lstRes);
		lstRes = inicializar(conjunto);
		L[indice] = lstRes;	// Atualiza a lista
	    }
	    if (caractere == 'u') {
		uniao(lstRes, lst1, lst2);
	    } else if (caractere == 'n') {
		intersecao(lstRes, lst1, lst2);
	    } else if (caractere == 'm') {
		diferenca(lstRes, lst1, lst2);
	    }
	} else if (caractere == 'e') {
	    scanf("%d %d", &conjunto, &x);
	    Lista *lst = buscar_lista(L, conjunto, &indice);
	    if (lst && buscar(lst, x)) {
		printf("%d esta em C%d\n", x, conjunto);
	    } else {
		printf("%d nao esta em C%d\n", x, conjunto);
	    }
	}
    }

    for (int i = 0; i < j; i++) {
	liberar(L[i]);
    }

    free(L);
    return 0;
}