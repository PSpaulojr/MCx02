/* Busca em vetores

	 O problema de busca em vetores pode ser enunciado da seguinte forma:
	 "dado um vetor V, qual é a posição em que se encontra o valor x?".
	 
	 Esse problema é especialmente importante em aplicações que lidam
	 com bancos de dados. Poderíamos querer saber se um determinado
	 CPF já está em nossa lista de clientes, por exemplo. Buscar
	 rapidamente por essa informação se torna uma necessidade imediata,
	 especialmente em bancos de dados com milhões (talvez bilhões) de
	 clientes.

	 Uma maneira óbvia de fazer essa busca é testando sequencialmente
	 todos os valores do vetor, como na função abaixo:
*/

int busca_sequencial(int vetor[], int tamanho, int chave) {
	/* Busca uma chave num vetor atraves de busca sequencial */
	int i;
	for (i=0; i<tamanho; i++)
		if (vetor[i] == chave) return i;

	return -1; /* Se não encontrou, retorna -1 */
}

/* A função busca_sequencial() não depende de qualquer hipótese
	 feita sobre o tamanho do vetor. Podemos realizar algumas análises
	 sobre a eficiência desse algoritmo:

	 - No melhor caso, busca_sequencial() encontra a chave na
	 primeira posição do vetor, e retorna imediatamente.
	 - No pior caso, a chave não é encontrada e todos os valores do
	 vetor devem ser acessados.
	 - No caso médio, a chave é encontrada na metade do vetor, então
	 somente metade dos valores do vetor deve ser acessada.

	 Quando um algoritmo é analizado dessa forma, utiliza-se a notação
	 Big-Oh (ou: O-maiúsculo). Essa notação descreve o limiar superior
	 de uma função quando seu argumento tende a infinito. No contexto
	 da análise de algoritmos, é usada para verificar como o tempo de 
	 execução de um algoritmo irá crescer, utilizando-se das seguintes
	 estratégias:

	 * Descontam-se os coeficientes constantes
	 * Considera-se apenas a função de maior crescimento

	 Assim, temos que, para busca_sequencial(), o tempo de execução,
	 em relação ao tamanho do vetor (que chamaremos de N) é descrito,
	 na notação Big-Oh, como:
	 * Melhor caso: O(1)
	 * Pior caso: O(N)
	 * Caso médio: O(N/2) = O(N)

	 Se nosso vetor está ordenado, porém, a função de busca não
	 precisa necessariamente varrer todos os valores do vetor. Se
	 for encontrado um valor maior que a chave, então já sabemos que
	 a busca é vazia. Assim, temos:
*/

int busca_sequencial_ordenada(int vetor[], int tamanho, int chave) {
	int i;
	for (i=0; i<tamanho; i++) {
		if (vetor[i] == chave) return i;
		if (vetor[i] > chave) break;
	}
	return -1;
}

/* Nesse caso, verificamos que:
	 - No melhor caso, a chave de busca é encontrada imediatamente - O(1)
	 - No pior caso, a chave não é encontrada, mas não chega a ser maior
	 que o último elemento do vetor, portanto todos os valores do vetor
	 são testador - O(N)
	 - No caso médio, a chave é encontrada no meio do vetor ou é
	 maior que a mediana do vetor - O(N/2) = O(N)

	 Porém, nosso procedimento de busca está sendo claramente inocente. Vamos
	 supor o seguinte procedimento de busca, em um vetor ordenado v[] de
	 tamanho N:
	 - Testamos o valor v[N/2]
	 - Se ele é menor que a chave, buscamos pela chave em índices
	   entre (N/2)+1 e N-1
	 - Se ele é maior que a chave, buscamos pela chave em índices
	   entre 0 e (N/2)-1
	 - Se ele é igual a nossa chave, retornamos o índice

	 Devemos adicionar um caso trivial, que ocorre quando o espaço
	 de busca é de tamanho zero, caso que ocorre se a chave não existe no
	 vetor. A função, portanto, fica:
*/

int busca_binaria(int vetor[], int tamanho, int chave) {
	/* Busca binaria em um vetor */
	int min, max, med;
	max = tamanho;
	min = 0;
	while (min < max) {
		med = (max+min)/2;
		if (vetor[med] == chave) return med;
		if (vetor[med] > chave) max = med - 1;
		else min = med + 1;
	}
	return -1;
}

/*
	 Assim, nossa estratégia reduz o espaço de busca pela metade a cada
	 iteração. A cada um desses passos de redução, apenas uma comparação
	 é feita (ou, pelo menos, uma quantidade constante de comparações), ou seja,
	 cada passo tem complexidade O(1). Porém, é possível saber que só é possível
	 reduzir pela metade o espaço de busca um máximo de log2(N) vezes, o que
	 significa que a operação de complexidade O(1) é executada O(log2(N)) vezes,
	 de forma que o algoritmo como um todo tem complexidade O(log2(N)) * O(1) =
	 O(log2(N)).

	 No programa abaixo, verificaremos se, de fato, a troca de um procedimento
	 de complexidade linear (O(N)) por um de complexidade logaritmica (O(log2(N)))
	 representa diferença no tempo de execução do programa.
*/

#include <stdio.h>
#include <time.h>

#define MEMSIZE	(1<<20) /* 2^20 */


int main() {
	int c1, c2; /* Contadores de relogio */
	int i; /* Indice para uso geral */
	int vet[MEMSIZE]; /* Vetor que sera usado para testes */
	float ts, tb; /* Tempo decorrido para busca sequencial (ts) e binaria (tb) */
	const int n_test = 1000; /* Numero de testes em cada algoritmo */

	/* Preparacao do vetor */
	for (i=0; i<MEMSIZE; i++)
		vet[i] = i*2; /* Garantimos que numeros pares existem no conjunto, mas
									 numeros impares nao. */

	printf("Vetor de testes preparado\n");
	printf("Busca sequencial... ");
	c1 = clock();
	for (i=0; i<n_test; i++) {
		busca_sequencial(vet, MEMSIZE, i*(MEMSIZE/n_test));
	}
	c2 = clock();
	ts = (c2-c1)/(float)(CLOCKS_PER_SEC*n_test);
	printf("%f segundos\n", ts);

	printf("Vetor de testes preparado\n");
	printf("Busca binaria... ");
	c1 = clock();
	for (i=0; i<n_test; i++) {
		busca_binaria(vet, MEMSIZE, i*(MEMSIZE/n_test));
	}
	c2 = clock();
	tb = (c2-c1)/(float)(CLOCKS_PER_SEC*n_test);
	printf("%f segundos\n", tb);

	printf("\nA busca binaria foi %f vezes mais rapida que a sequencial\n", ts/tb);

	return 0;
}

/* Para executar:
	 ./gcc -obusca busca.c
	 ./busca
*/

/* Exercicios:

	 1) Em bancos de dados baseados em conteúdo, é comum que estejamos buscando por
	 elementos próximos, mas não necessariamente iguais a uma chave.
	 a) Escreva uma função de busca binária que retorna o índice do elemento do vetor que é
	 mais próximo a uma chave dada. Qual é a complexidade do seu algoritmo, no
	 pior caso?
	 b) Escreva uma função de busca sequencial para o mesmo problema. Qual é a complexidade
	 desse algoritmo, no pior caso?
	 c) Por fim, verifique o tempo de execucao de cada uma das funções propostas,
	 considerando 10 diferentes tamanhos de vetores, entre 10^2 e 10^12. Comente os resultados
	 obtidos, à luz da notação Big-Oh.

	 2) Encontre a complexidade das seguintes operações em vetores, no caso médio e usando
	 o algoritmo mais eficiente que você conseguir:
	 a) Inserir um valor num vetor ordenado, mantendo-o ordenado
	 b) Inserir um valor no final de um vetor não-ordenado (assuma que há memória reservada suficiente)
	 c) Buscar o valor mínimo num vetor ordenado
	 d) Buscar o valor mínimo num vetor não-ordenado
	 e) Buscar um valor qualquer num vetor ordenado
	 f) Buscar um valor qualquer num vetor não-ordenado
*/
