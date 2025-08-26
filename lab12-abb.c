#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no{
	int k;
	char *nome;
	float pontos;
	struct no *esq;
	struct no *dir;
}No;


No *buscar (No *raiz, int k){
	No *aux = raiz;
	while(aux){
		if(k < aux->k){
			aux = aux->esq;
		}else if (k > aux->k){
			aux = aux->dir;
		}else{
			return aux;
        }
    }
    return NULL;
}



void inserir(int k, float pontos, char *nome, No **raiz){
	if (buscar(*raiz, k)){
		return;
	}	
	
	No **aux = raiz;
    while (*aux) {
        if (k < (*aux)->k) {
            aux = &(*aux)->esq;
        } else {
            aux = &(*aux)->dir;
        }
    }

    No *novo = malloc(sizeof(No));
    if (novo == NULL) {
        printf("memoria insuficiente\n");
        return;
    }
    novo->k = k;
    novo->pontos = pontos;
    novo->nome = malloc((strlen(nome)+1) * sizeof(char));
    strcpy(novo->nome, nome);
    novo->esq = novo->dir = NULL;
    *aux = novo;

}



No *remover(No *raiz, int k) {
    if (raiz == NULL) {
        return NULL;
    }

    if (raiz->k == k) {
        if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz->nome);
            free(raiz);
            return NULL;
        }
        if (raiz->esq == NULL || raiz->dir == NULL) {
            No *aux = (raiz->esq != NULL) ? raiz->esq : raiz->dir;
            free(raiz->nome);
            free(raiz);
            return aux;
        }

        No *aux = raiz->esq;
        while (aux->dir != NULL) {
            aux = aux->dir;
        }
        raiz->k = aux->k;
        raiz->pontos = aux->pontos;
        free(raiz->nome);
        raiz->nome = malloc((strlen(aux->nome) + 1) * sizeof(char));
        strcpy(raiz->nome, aux->nome);
        raiz->esq = remover(raiz->esq, aux->k);
        
    }else if (k < raiz->k) {
        raiz->esq = remover(raiz->esq, k);
    } else {
        raiz->dir = remover(raiz->dir, k);
    }

    return raiz;
}

No* minimo(No* raiz) {
    while (raiz->esq != NULL) {
        raiz = raiz->esq;
    }
    return raiz;
}

No* maximo(No* raiz) {
    while (raiz->dir!= NULL) {
        raiz = raiz->dir;
    }
    return raiz;
}

No* sucessor(No* raiz, No* buscado) {
    if (buscado->dir != NULL) {
        return minimo(buscado->dir);
    }

    No* sucessor = NULL;
    No* aux = raiz;
    while (aux != NULL) {
        if (buscado->k < aux->k) {
            sucessor = aux;
            aux = aux->esq;
        } else if (buscado->k > aux->k) {
            aux = aux->dir;
        } else {
            break;
        }
    }
    return sucessor;
}

No* predecessor(No* raiz, No* buscado) {
    if (buscado->esq != NULL) {
        return maximo(buscado->esq);
    }

    No* predecessor = NULL;
    No* aux = raiz;
    while (aux != NULL) {
        if (buscado->k > aux->k) {
            predecessor = aux;
            aux = aux->dir;
        } else if (buscado->k < aux->k) {
            aux = aux->esq;
        } else {
            break;
        }
    }
    return predecessor;
}

void buscar_intervalo(No* raiz, int *encontrado, int x, int y){
    if(raiz){
        if(raiz->k > x){
            buscar_intervalo(raiz->esq, encontrado, x, y);
        }

        if (raiz->k >= x && raiz->k <= y) {
            if (*encontrado == 0) {
                printf("clientes no intervalo [%d,%d]: ", x, y);
            }
            printf("%d ", raiz->k);
            *encontrado = 1;
        }

        if(raiz->k < y){
            buscar_intervalo(raiz->dir,encontrado, x, y);
        }
    }
}

void imprimir(No *raiz){
    if(raiz){
        imprimir(raiz->esq);
        printf("%s (%d) ", raiz->nome, raiz->k);
        imprimir(raiz->dir);
    }
}

void liberar(No* raiz){
    if (raiz) {
        liberar(raiz->esq);
        liberar(raiz->dir);
        free(raiz->nome);
        free(raiz);
    }
}

int main(void){
	char *comando = malloc(17*sizeof(char));
	int x, y, k;
	float pontos;
    char *nome = malloc(101 * sizeof(char));;
	
	No *raiz = NULL;
	
	while (scanf("%s", comando) && strcmp(comando, "terminar") != 0) {
		if(strcmp(comando, "criar") == 0){
			if(raiz){
			    liberar(raiz);
                raiz = NULL;
			}
		}else if (strcmp(comando, "inserir") == 0){
            scanf("%d, %101[^,], %f", &k, nome, &pontos);
            inserir(k, pontos, nome, &raiz);
		}else if (strcmp(comando, "buscar") == 0){
            scanf("%d", &k);
			No *buscado = buscar(raiz, k);
			if (buscado){
				printf("cliente %d: %s, %.2f pontos\n", k, buscado->nome, buscado->pontos);
			}else{
				printf("nao ha cliente %d\n", k);
			}
		}else if (strcmp(comando, "remover") == 0){
			scanf("%d", &k);
			raiz = remover(raiz, k);
		}else if (strcmp(comando, "minimo") == 0){
			if(raiz){
					No *valor_minimo = minimo(raiz);
					printf("minimo: %d\n", valor_minimo->k);
			}else{
				printf("arvore vazia\n");
			}
		}else if (strcmp(comando, "maximo") == 0){
			if(raiz){
					No *valor_maximo = maximo(raiz);
					printf("maximo: %d\n", valor_maximo->k);
			}else{
				printf("arvore vazia\n");
			}
        }else if (strcmp(comando, "sucessor") == 0){
            scanf("%d", &k);
            No *buscado = buscar(raiz, k);
            if(buscado){
                No *valor_sucessor = sucessor(raiz, buscado);
                if(valor_sucessor){
                    printf("sucessor de %d: %d\n",k, valor_sucessor->k);
                }else{
                    printf("sucessor de %d: nao ha\n", k);
                }
            }else{
                printf("nao ha cliente %d\n", k);
            }
        }else if (strcmp(comando, "predecessor") == 0){
            scanf("%d", &k);
            No *buscado = buscar(raiz, k);
            if(buscado){
                No *valor_predecessor = predecessor(raiz, buscado);
                if(valor_predecessor){
                    printf("predecessor de %d: %d\n",k, valor_predecessor->k);
                }else{
                    printf("predecessor de %d: nao ha\n", k);
                }
            }else{
                printf("nao ha cliente %d\n", k);
            }
        }else if(strcmp(comando, "imprimir") == 0){
            if(raiz){
                printf("clientes: ");
                imprimir(raiz);
                printf("\n");
            }else{
                printf("arvore vazia\n");
            }
        }else if(strcmp(comando, "buscar-intervalo") == 0){
            scanf("%d %d", &x, &y);
            int encontrado = 0;
            if(raiz){
                buscar_intervalo(raiz, &encontrado, x, y);
                if(encontrado){
                    printf("\n");
                }else{
                    printf("clientes no intervalo [%d,%d]: nenhum\n", x, y);
                }
            }else{
                printf("clientes no intervalo [%d,%d]: nenhum\n", x, y);
            }
        }
    }
    liberar(raiz);
	return 0;
}