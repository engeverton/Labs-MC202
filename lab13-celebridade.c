    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
     
    #define TAM 200003  
     
    typedef struct No {
        int nome;
        struct No *prox; 
    } No;
     
    int hash_string(char nome[]) {
        unsigned int hash_str = 0;
        for (int i = 0; nome[i] != '\0'; i++) {
            hash_str = hash_str * 37 + nome[i];
        }
        return hash_str % TAM;
    }
     
    void inicializar(No *tabela[]) {
        for (int i = 0; i < TAM; i++) {
            tabela[i] = NULL;
        }
    }
     
    void inserir(No *tabela[], int p1, int p2) {
        int indice = p1 % TAM;
     
        No* novo = malloc(sizeof(No));
        novo->nome = p2;
        novo->prox = tabela[indice];
        tabela[indice] = novo;
    }
     
    int conhece(No *tabela[], int p1, int p2) {
        int indice = p1 % TAM;
        No *atual = tabela[indice];
        
        while (atual != NULL) {
            if (atual->nome == p2) {
                return 1;
            }
            atual = atual->prox;
        }
        return 0;
    }
     
    int encontrar_celebridade(No *tabela[], int pessoas[], int qtd) {
        int candidato = pessoas[0];

        for (int i = 1; i < qtd; i++) {
            if (conhece(tabela, candidato, pessoas[i])) {
                candidato = pessoas[i];
            }
        }

        for (int i = 0; i < qtd; i++) {
            if (pessoas[i] != candidato) {
                if (conhece(tabela, candidato, pessoas[i]) || !conhece(tabela, pessoas[i], candidato)) {
                    return -1;
                }
            }
        }
        return candidato;
    }
     
    void registrar_nome(char *nomes[], int hash_str, char nome[]){
        if (nomes[hash_str] == NULL) {
	        nomes[hash_str] = (char *) malloc(strlen(nome) + 1);
	        strcpy(nomes[hash_str], nome);
    }
    }
     
    char* buscar_nome(char *nomes[], int hash_str) {
        return nomes[hash_str];
    }
     
    int main(void) {
        No *tabela[TAM];
        inicializar(tabela);
     
        char *nomes[TAM] = {NULL};
        int pessoas[TAM], qtd_pessoas = 0;
        char frase[115], pessoa[52], conhecido[52];

        while (fgets(frase, sizeof(frase), stdin) && frase[0] != '\n') {
            frase[strcspn(frase, "\n")] = '\0';
            char *conhece = strstr(frase, " conhece ");
            if (conhece) {
                *conhece = '\0';
                strcpy(pessoa, frase);
                strcpy(conhecido, conhece + 9);
     
                int p1 = hash_string(pessoa);
                int p2 = hash_string(conhecido);
     
                if (nomes[p1] == NULL) {
                    pessoas[qtd_pessoas++] = p1;
                    registrar_nome(nomes, p1, pessoa);
                }
     
                if (nomes[p2] == NULL) {
                    pessoas[qtd_pessoas++] = p2;
                    registrar_nome(nomes, p2, conhecido);
                }
     
                inserir(tabela, p1, p2);
            }
        }
    
        int celebridade = encontrar_celebridade(tabela, pessoas, qtd_pessoas);
     
        if (celebridade != -1) {
            printf("%s e' celebridade.\n", buscar_nome(nomes, celebridade));
        } else {
            printf("Nao ha' celebridade.\n");
        }
        return 0;
}