#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    double valor;
    struct No *prox;
} No;

typedef struct lista {
    No *inicio;
    int tamanho;
} Lista;

Lista *inicializar(){
    Lista *L = malloc(sizeof(Lista));
    if (L == NULL) {
	    return NULL;
    } else {
	    L->inicio = NULL;
	    L->tamanho = 0;
    }

    return L;
}


void inserir(Lista * L, int p, double valor){
    int i = 0;
    No *novo = malloc(sizeof(No));
    novo->valor = valor;

    if (p == 0 || L->inicio == NULL) {
	    novo->prox = L->inicio;
	    L->inicio = novo;
    } else {
	No *aux = L->inicio;

	while (aux->prox != NULL && i < (p - 1)) {
	    aux = aux->prox;
	    i++;
	}
	novo->prox = aux->prox;
	aux->prox = novo;
    }
    L->tamanho++;

}

void remover(Lista * L, int p){
    int i = 0;
    No *aux = L->inicio;
    No *remover;

    if (p == 0) {
	    L->inicio = aux->prox;
	    L->tamanho--;
	    free(aux);
    } else {
	    while (i < (p - 1)) {	
	        aux = aux->prox;
	        i++;
	    }
	    remover = aux->prox;
	    aux->prox = remover->prox;
	    L->tamanho--;
	    free(remover);
    }
}

void imprimir(Lista * L)
{
    No *aux = L->inicio;
    while (aux) {
	    printf("%.2f ", aux->valor);
	    aux = aux->prox;
    }
    printf("\n");

}

void reverter(Lista * L, int i, int t)
{
    if (L == NULL || L->inicio == NULL || i < 0 || t >= L->tamanho || i > t) {
	    return;			// Posições inválidas
    }
    int j = 0, k = 0, l = 1;
    No *atual;
    No *final = L->inicio;
    No *seg;
    No *aux;
    No *aux2 = L->inicio;

    while (j < (i - 1)) {
	    aux2 = aux2->prox;
	    j++;
    }

    while (k < (t)) {
	    final = final->prox;
	    k++;
    }

    if (i == 0) {
	    atual = L->inicio;
	    L->inicio = final;
	    aux = final->prox;
    } else {
	    atual = aux2->prox;
	    aux2->prox = final;
	    aux = final->prox;
    }

    while (l <= (t - i + 1)) {
	    seg = atual->prox;
	    atual->prox = aux;
	    aux = atual;
	    atual = seg;
	    l++;
    }

}

void mover(Lista * L, int i, int t, int p)
{
    int j = 0, k = 0, l = 0;
    No *aux = L->inicio;
    No *aux2 = L->inicio;
    No *aux3 = L->inicio;
    No *q;

    if(p == (t+1)){
        return;
    }else{
        while (j < (p - 1)) {
	    aux = aux->prox;
	    j++;
    }

    while (l < (t)) {
	    aux3 = aux3->prox;
	    l++;
    }
    while (k < i - 1) {
	    aux2 = aux2->prox;
	    k++;
    }

    if (p == 0) {
	    q = aux2->prox;
	    L->inicio = q;
	    aux2->prox = aux3->prox;
	    aux3->prox = aux;
    } else if (i == 0) {
	    q = L->inicio;
	    L->inicio = aux3->prox;
	    aux3->prox = aux->prox;
	    aux->prox = q;
    } else {
        q = aux2->prox;
        aux2->prox = aux3->prox;
        aux3->prox = aux->prox;
        aux->prox = q;}
    }
}

void liberar(Lista * L)
{
    No *aux = L->inicio;
    while (aux) {
	    No *ant = aux;
	    aux = aux->prox;
	    free(ant);
    }
    free(L);
}


int main(void)
{
    char segundo;
    int p, i, t;
    double x;
    Lista *L = NULL;

    while (scanf("%c", &segundo) && segundo != 't') {
        if (segundo == 'c') {
            if (L) {
                liberar(L);
            }
            L = inicializar();
        } else if (segundo == 'i') {
            scanf(" %d %lf", &p, &x);
            inserir(L, p, x);
        } else if (segundo == 'r') {
            scanf(" %d", &p);
            if (L->inicio) {
                remover(L, p);
            }
        } else if (segundo == 'p') {
            if (L->inicio) {
                imprimir(L);
            } else {
                printf("\n");
            }
        } else if (segundo == 'v') {
            scanf(" %d %d", &i, &t);
            if (L->inicio) {
                if (i >= 0 && t >= i && L->tamanho > t) {
                    reverter(L, i, t);
                }
            }
        } else if (segundo == 'x') {
            scanf(" %d %d %d", &i, &t, &p);
            if (L->inicio) {
                if ((i >= 0) && (t >= i) && (t < L->tamanho) && L->tamanho >= p) {
                    mover(L, i, t, p);
                }
            }
        }
    }

    liberar(L);
    return 0;
}