#include <stdio.h>

void imprime_vetor(int vetor[], int N) {
	int i;
	for (i=0; i<N; i++)
		printf("%d\t", vetor[i]);
	printf("\n");
}


/* Algoritmos de ordenação

	 Na aula anterior, vimos como o fato de um vetor estar ordenado pode
	 tornar operações de busca sobre ele bem mais simples. Em especial,
	 vimos que uma busca em um vetor ordenado pode ser realizada com
	 complexidade O(log2(N)), ao passo que uma busca em um vetor não-ordenado
	 tem complexidade O(N). Nesta aula, utilizaremos algoritmos para ordenar
	 vetores.

	 Um algoritmo de ordenação recebe como entrada um vetor não-ordenado
	 e retorna, na saída, um vetor ordenado. Nesta aula, abordaremos algoritmos
	 clássicos de ordenação. Uma das operações básicas do algoritmo de ordenação
	 é a troca de dois elementos de posição, tal qual definida abaixo:
*/
void troca(int *a, int *b) {
	int c;
	c = *a;
	*a = *b;
	*b = c;
}

/*
	 Num vetor não ordenado, em algum momento encontraremos a situação em que
	 um elemento maior está localizado num índice menor que um elemento menor,
	 ou seja, vetor[i+1] < vetor[i]. Se essa situação não ocorre nunca, então
	 o vetor está ordenado. Porém, se ocorre, podemos trocar os elementos testados
	 de lugar, corrigindo sucessivamente a não-ordenação.

	 Nesse algoritmo de ordenação, cada elemento caminha sucessivamente para sua
	 posição ideal como uma bolha - daí seu nome: bubble sort.
*/

void bubble_sort(int vetor[], int N) {
	int i;
	int j;
	j = 1;
	while (j==1) {
		j = 0;
		for (i = 0; i < (N-1); i++) {
			if (vetor[i+1] < vetor[i]) {
				troca(&(vetor[i+1]), &(vetor[i]));
				j = 1;
			}
		}
	}
}

/* Uma boa ideia, porém, seria prever o destino de cada elemento. Se selecionarmos
	 o menor elemento do vetor, sabemos que ele estará na primeira posição do vetor;
	 daí, basta executar recursivamente a rotina para o restante do vetor. Esse algoritmo
	 de ordenação por seleção se chama selection sort.
 */
void selection_sort(int vetor[], int N) {
	int i;
	int j;
	int k;
	if (N==1) return; /* Caso-base: um vetor de tamanho 1 sempre está ordenado */
	j = vetor[0];
	k = 0;
	for (i=0; i<N; i++) {
		if (vetor[i] < j) {
			j = vetor[i];
			k = i;
		}
	}
	troca(&(vetor[k]), &(vetor[0]));
	selection_sort(&(vetor[1]), N-1);
}

/* Uma característica interessante do selection sort é que ele considera, a cada
	 chamada, que o vetor - até uma posição k - está ordenada, e então ordena o vetor
	 restante. Um outro algoritmo clássico consiste em ordenar vetores cada vez maiores
	 (ao invés de cada vez menores), inserindo os novos valores nas posições adequadas.
	 Nesse caso, a "bolha" correspondente a cada nova inserção é levada até sua posição
	 final a cada nova inserção de valores no vetor. Esse algoritmo se chama ordenação
	 por inserção, ou insertion sort.
*/
void insertion_sort(int vetor[], int N) {
	int n;
	int i;
	for (n=1; n<N; n++) {
		i = n;
		while ( (i>0) && (vetor[i] < vetor[i-1]) ) {
			troca(&(vetor[i]), &(vetor[i-1]));
			i--;
		}
	}
}

/* Uma vez que esses algoritmos simples de ordenação são compreendidos, vamos
	 investigar uma estratégia diferente de pensar o problema de ordenação.

	 Suponha que sabemos o valor da mediana de um vetor. Nesse caso, sabemos
	 que todos os valores mais altos que a mediana devem estar no fim do vetor,
	 e todos os elementos mais baixos devem estar no começo. Não sabemos (ao menos 
	 por enquanto) estimar a mediana de um vetor não-ordenado, então vamos assumir
	 que o valor vetor[0] é uma possível estimativa, que será, depois, colocada em
	 seu devido lugar.

	 Uma vez que essa operação é feita, podemos ordenar os vetores à direita e à
	 esquerda da posição em que vetor[0] foi colocado, realizando uma operação semelhante.
	 Os vetores vão se tornando sucessivamente menores, até que um vetor de tamanho 3 (ou
	 menos) é encontrado - nesse caso, a ordenação é trivial ao se realizar o procedimento
	 da mediana. Esse algoritmo de ordenação é tipicamente rápido e, por isso, é chamado
	 de quicksort.
 */

void quick_sort(int vetor[], int N) {
	int pivot;
	int j;
	int i;

	if (N<=1) return;

	pivot = vetor[0];
	i = 1;
	j = N-1;

	while (i < j) {
		while (vetor[j] > pivot)
			j--;

		if (vetor[i] > pivot)
			troca(&(vetor[i]), &(vetor[j]));

		i++;
	}

	troca(&(vetor[j]), &(vetor[0]));

	if (N > 3) {
		quick_sort(vetor, j);
		quick_sort(&(vetor[j]), N-j);	
	}
}

/* No Quick Sort, caso o valor de vetor[0] seja exatamente igual à mediana
	 do vetor, então estamos quebrando um problema de tamanho N em dois problemas de
	 tamanho N/2 e, adicionalmente, realizando uma operação de complexidade N, ou seja:
	 T(N) = 2*T(N/2) + O(N)
	 Cada problema de tamanho N/2 é quebrado em dois problemas de tamanho N/4, até cair
	 em problemas triviais - complexidade O(1) - após log2(N) quebras. Assim, temos um total
	 de N*log2(N) operações, e, portanto, a complexidade do algoritmo é O(N*log2(N)).

	 No pior caso, porém, sempre encontramos vetor[0] como sendo o maior elemento do vetor.
	 Daí, quebramos nosso problema de tamanho N em um problema de tamanho 1, um problema de
	 tamanho N-1 e isso tudo a um custo O(N):
	 T(N) = T(N-1) + T(1) + O(N)
	 Dessa vez, as quebras serão realizadas N vezes. Assim, no pior caso, temos O(N^2)
	 operações, o que é um decréscimo considerável de desempenho.

	 Mesmo assim, o pior caso é um caso bastante raro. O quick sort é um algoritmo bastante
	 rápido, usado em diversas aplicações industriais.
*/



int main() {
	int vetor1[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
	int vetor2[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
	int vetor3[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
	int vetor4[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

	printf("Vetores originais:\n");
	imprime_vetor(vetor1, 11);
	imprime_vetor(vetor2, 11);
	imprime_vetor(vetor3, 11);
	imprime_vetor(vetor4, 11);

	bubble_sort(vetor1, 11);
	selection_sort(vetor2, 11);
	insertion_sort(vetor3, 11);	
	quick_sort(vetor4, 11);

	printf("Vetores ordenados:\n");
	imprime_vetor(vetor1, 11);
	imprime_vetor(vetor2, 11);
	imprime_vetor(vetor3, 11);
	imprime_vetor(vetor4, 11);
}

/* Para executar:
	 ./gcc -oordenacao ordenacao.c
	 ./ordenacao
*/

/* Exercícios

	 1) Re-escreva a função selection_sort() de forma
	 a eliminar a chamada recursiva, mantendo a ideia
	 inicial.

	 2) Qual dos três algoritmos discutidos é mais eficiente
	 no melhor caso, no caso médio e no pior caso?

	 3) Escreva uma função de ordenação com o cabeçalho:
	 void ordena_distancia(int vetor[], int tamanho, int chave)
	 que ordena os valores do vetor recebido como entrada de acordo
	 com o quadrado de sua diferença em relação à chave recebida,
	 ou seja, uma entrada:
	 ordena_distancia({5, 3, 2, 0}, 4, 3)
	 retorna:
	 vetor[] == {3, 2, 5, 0}

*/
