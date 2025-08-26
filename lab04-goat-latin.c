#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_PALAVRAS 100002
#define MAX 300002
#define TAM_MAX 504

// Função que processa o vetor frase, tirando os caracteres especiais e os números, e neste caso já somando-os
int processa_frase(char *frase, char *nova_frase, int *soma)
{
    // indice: armazena o índice do novo_vetor
    // contador: armazena o tamanho de cada palavra
    // primeiro: armazena o índice de cada palavra
    int indice = 0, contador = 0, primeiro = 0;
    char *temp = malloc(10 * sizeof(char));	// Vetor que armazena os algarismos presentes nas palavras para depois ser transformado em um número inteiro

    // Loop que lê cada caractere do vetor frase, para armazenar no novo vetor
    for (int j = 0; frase[j] != '\0'; j++) {
	// Delimita cada palavra, guarda o índice da primeira letra e calcula o tamanho da palavra
	if (frase[j] != ' ') {
	    if (contador == 0) {
		primeiro = j;
	    }
	    contador++;
	} else if (contador > 0) {	// Adicionada verificação
	    // n: armazena a quantidade de caracteres especiais em uma palavra
	    // p: armazena a quantidade de algarismos em uma palavra
	    int k = primeiro;
	    int n = 0;
	    int p = 0;
	    while (k < j) {
		if (isdigit(frase[k])) {	// Verifica se o caractere é um número, e não armazena no vetor 
		    int m = 0;
		    while (k < j && isdigit(frase[k])) {	// Continua lendo algarismos consecutivos
			temp[m++] = frase[k++];	// Armazena os algarismos no vetor temp
			p++;
		    }
		    temp[m] = '\0';	// Garante que o último caractere é o \0
		    *soma += atoi(temp);	// Transforma o vetor em um número inteiro e já o soma
		} else if (isalpha(frase[k])) {	// Verifica se o caractere é uma letra
		    nova_frase[indice++] = frase[k++];	// Armazena normalmente na nova frase
		} else {	// Verifica se for um caractere especial e só altera o índice
		    k++;
		    n++;
		}
	    }
	    // Se for uma palavra só de números, caracteres ou ambos, não adicionar mais um espaço desnecessário
	    if (p == contador || n == contador || (p + n) == contador) {
		indice--;
	    }
	    // Coloca um espaço após cada palavra
	    nova_frase[indice++] = ' ';
	    contador = 0;
	}
    }
    // Garante que o último caractere é o \0
    nova_frase[indice] = '\0';
    free(temp);			// Libera memória do vetor temp

    return indice;		// Retorna o tamanho da nova frase processada
}

int main()
{
    char **palavras;		// Matriz que irá armazenar uma palavra em cada linha
    char *frase = malloc(MAX * sizeof(char));	// Vetor que armazena a frase de entrada
    palavras = malloc(MAX_PALAVRAS * sizeof(char *));

    for (int i = 0; i < MAX_PALAVRAS; i++) {
	palavras[i] = malloc(TAM_MAX * sizeof(char));
    }

    while (scanf(" %[^\n]", frase) != EOF) {
	int soma = 0;
	int tamanho = strlen(frase);	// Tamanho do vetor frase
	frase[tamanho] = ' ';	// Garante que o penúltimo caractere é um espaço
	frase[tamanho + 1] = '\0';	// Garante que o último caractere é o \0

	char *nova_frase = malloc((MAX) * sizeof(char));	// Cria um novo vetor para processar e tirar todos os caracteres especiais e números  

	// contador conta o tamanho de cada palavra, delimitada por espaço
	// primeiro armazena o índice do primeiro elemento de cada palavra
	// palavra armazena a quantidade de palavras na frase

	int novo_tamanho = processa_frase(frase, nova_frase, &soma);	// Chama a função que processa a frase e retorna o tamanho do novo vetor 

	int contador = 0, primeiro = 0, palavra = 0;

	// Loop para ler cada caractere da frase processada e armazena na matriz palavras já modificando
	for (int j = 0; j < novo_tamanho; j++) {
	    // Delimita cada palavra, guarda o índice da primeira letra e calcula o tamanho da palavra
	    if (nova_frase[j] != ' ') {
		if (contador == 0) {
		    primeiro = j;
		}
		contador++;
	    } else if (contador > 0) {
		if (nova_frase[primeiro] == 'a'
		    || nova_frase[primeiro] == 'e'
		    || nova_frase[primeiro] == 'i'
		    || nova_frase[primeiro] == 'o'
		    || nova_frase[primeiro] == 'u'
		    || nova_frase[primeiro] == 'A'
		    || nova_frase[primeiro] == 'E'
		    || nova_frase[primeiro] == 'I'
		    || nova_frase[primeiro] == 'O'
		    || nova_frase[primeiro] == 'U') {

		    strncpy(palavras[palavra], nova_frase + primeiro, contador);	// Adiciona matriz palavras
		    palavras[palavra][contador] = '\0';
		} else {
		    strncpy(palavras[palavra], nova_frase + primeiro + 1,
			    contador - 1);
		    palavras[palavra][contador - 1] = nova_frase[primeiro];
		    palavras[palavra][contador] = '\0';	// Finaliza a palavra com o \0
		}

		strcat(palavras[palavra], "ma");
		int sufixo_len = strlen(palavras[palavra]);
		for (int n = 0; n < contador; n++) {	// Adiciona a quantidade de a's ao fim de cada palavra
		    palavras[palavra][sufixo_len++] = 'a';
		}
		palavras[palavra][sufixo_len] = '\0';

		contador = 0;
		palavra++;
	    }
	}

	// Imprime a soma
	if (soma == 1) {
	    printf("%d goat says:", soma);
	} else {
	    printf("%d goats say:", soma);
	}

	// Loop para imprimir cada palavra da matriz palavras
	for (int i = 0; i < palavra; i++) {
	    printf(" %s", palavras[i]);
	}
	printf("\n");

	// Libera memória do vetor nova_frase
	free(nova_frase);
    }

    // Libera memória da matriz
    for (int i = 0; i < MAX_PALAVRAS; i++) {
	free(palavras[i]);
    }
    free(palavras);
    free(frase);

    return 0;
}