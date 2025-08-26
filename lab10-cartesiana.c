#include <stdio.h>
#include <stdlib.h>

//estrutura para um no da arvore
typedef struct No{
    int valor;
    struct No *esquerda;
    struct No *direita;
}No;


//estrutura para um no da pilha
typedef struct NoPilha{
    No *noarvore;
    struct NoPilha *proximo;
}NoPilha;


//estrutura para um no da fila 
typedef struct NoFila{
    No *noarvore;
    struct NoFila *proximo;
}NoFila;


//estrutura fila
typedef struct Fila{
    NoFila *inicio;
    NoFila *fim;
}Fila;



//inicializa da fila
Fila *criarfila(){
    Fila *F = (Fila*)malloc(sizeof(Fila));
    F->inicio = NULL;
    F->fim = NULL;
    return F;
}


//cria um novo no para a arvore
No* novoNo(int valor) {
    No* novoNo = (No*)malloc(sizeof(No));
    if(novoNo){
        novoNo->valor = valor;
        novoNo->esquerda = NULL;
        novoNo->direita = NULL;
    }
    return novoNo;
}


//função para enfileirar
void pushfila(Fila *F, No *noArvore){
    NoFila *aux = (NoFila*)malloc(sizeof(NoFila));
    aux->noarvore =noArvore;
    aux->proximo = NULL;
    if(F->fim == NULL){
        F->inicio = F->fim = aux;
    }
    F->fim->proximo = aux;
    F->fim = aux;
}


//função para desenfileirar
No *popfila(Fila *F){
    if(F->inicio == NULL){
        return NULL;
    }
    NoFila *aux = F->inicio;
    No* noArvore = aux->noarvore;
    F->inicio = F->inicio->proximo;
    if(F->inicio == NULL){
        F->fim = NULL;
    }
    free(aux);
    return noArvore;
}

//função para empilhar
void pushpilha(NoPilha **topo, No *noArvore){
    NoPilha* novoNo = (NoPilha*)malloc(sizeof(NoPilha));

    if(novoNo){
        novoNo->proximo = *topo;
        novoNo->noarvore = noArvore;
        *topo = novoNo;
    }
}


//função para desepilhar
No* poppilha(NoPilha** topo) {
    if (*topo == NULL) {
        return NULL;
    }
    NoPilha* temp = *topo;
    *topo = (*topo)->proximo;
    No* noArvore = temp->noarvore;
    free(temp);
    return noArvore;
}


//função para imprimir a árvore por níveis, e tem como argumento a raiz da arvore 
void imprimir_arvore(No *raiz){
    if (!raiz) return;

    Fila* F = criarfila();  //cria a fila
    int inicio = 0, fim = 0; //fim indica quando for enfileirado, inicio indica quando for desenfileirado

    pushfila(F, raiz);  //enfileira a raíz
    fim++;

    while(inicio < fim){
        int fim_menos_inicio = fim - inicio;
        for(int i = 0; i < fim_menos_inicio; ++i){
            No* aux = popfila(F);
            inicio++;
            printf("%d ", aux->valor);
            if (aux->esquerda){
                pushfila(F, aux->esquerda);
                fim++;
            }
            if (aux->direita){
                pushfila(F, aux->direita);
                fim++;
            }
        }
        printf("\n");
    }
    free(F);
}


//Função que controi e insere os elementos na árvore canônica por meio de uma pilha
No* inserir_arvore(int *A, int n){
    if (n){
        No *raiz = NULL;
        NoPilha *topo = NULL;

        for(int i = 0; i < n; ++i){
            No *aux = novoNo(i);
            No *removido = NULL;

            while(topo && A[topo->noarvore->valor] > A[i]){
                removido = poppilha(&topo);
            }

            if(topo){
                topo->noarvore->direita = aux;
            }else{
                raiz = aux;
            }

            aux->esquerda = removido;
            pushpilha(&topo, aux);
        }
        return raiz;
    }else{
        exit(1);
    }
}

int main(void){
    int n;

    while(1){
        scanf("%d", &n);
        if(n == 0){
            break;
        }
        int A[n];
        for(int i = 0; i < n; ++i){
            scanf("%d", &A[i]);
        }

        No* raiz = inserir_arvore(A, n);
        imprimir_arvore(raiz);
        printf("\n");
    }
    return 0;
}