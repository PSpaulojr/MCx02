/* Heaps: filas de prioridade

	 Além da representação por nós ligados, uma árvore binária
	 também pode ser representada em um vetor. Nessa
	 representação, temos as seguintes relações:

	 a) Se o nó N é o nó pai, o nó 2N+1 é seu filho esquerdo e o nó
	 2N+2 é seu filho direito
	 b) Se o nó N é um nó qualquer, o nó floor( (N-1)/2) é seu nó-pai

	 Assim, a árvore:
	    3
	  /   \ 
	 2     4
	 
	 pode ser representada no vetor:
	 int arvore[3] = {3, 2, 4};

	 Essa representação tem a vantagem de que permite acesso randômico
	 a qualquer nó da árvore, além de permitir percursos de pai para
	 filho e de filho para pai. Varrendo o vetor de representação
	 sequencialmente, temos o percurso em largura da árvore. A desvantagem
	 dessa representação é que o número máximo de nós da árvore deve ser
	 pré-definido e, além disso, árvores muito desbalanceadas implicarão
	 numa grande quantidade de nós vazios.
*/

#include <stdio.h>

int pai(int N) {
	return ((N-1)/2);
}

int f_esquerdo(int N) {
	return (2*N)+1;
}

int f_direito(int N) {
	return (2*N)+2;
}

/*
	 A representação por vetor é especialmente interessante quando nossa
	 árvore não representar uma árvore binária de busca, e sim uma
	 fila de prioridades (em inglês: heap ou priority queue). Num heap,
	 os dados são inseridos na árvore de forma que o valor do nó-pai
	 é sempre superior ao valor de ambos seus filhos. Vamos definir,
	 então, funções e estruturas para construir filas de prioridade */

#define TAMANHO_HEAP 100

typedef struct {
	int n_elementos;
	int arvore[TAMANHO_HEAP];
} Heap;

void imprime_heap(Heap *h) {
	int i;
	for (i = 0; i < h->n_elementos; i++)
		printf("%d\n", h->arvore[i]);
}

/* Por construção, sabemos que o valor máximo do heap sempre estará
	 no nó inicial. Assim, podemos definir rapidamente uma função
	 que retorna o máximo valor no heap: */

int maximo(Heap *h) {
	return h->arvore[0];
}

/* O valor mínimo do heap, porém, pode estar em qualquer uma de suas
	 folhas. 

	 Vamos considerar agora a operação de retirar o valor máximo de um
	 heap. Será necessário ocupar essa posição com um novo valor máximo,
	 o que pode ser feito escolhendo um dos filhos do nó-pai. Assim,
	 sucessivamente, o valor que era o maior de todos deve descer toda
	 a estrutura da árvore até as folhas, sendo então removido do heap:
*/
void troca(int *i, int *j) { /* Essa função auxiliar será necessária */
	int k;
	k = (*i);
	(*i) = (*j);
	(*j) = k;
}

/* Para retirar o máximo do heap, vamos trocá-lo com o último
	 elemento do vetor que representa a árvore e então reposicionar
	 esse elemento, fazendo-o descer pelo heap. */

void retira_maximo(Heap *h) {
	int N;
	int descida;
	N = 0;

	troca(& (h->arvore[(h->n_elementos)]), & (h->arvore[N]) );

	/* Escolhe: devo descer pelo filho direito ou pelo
		 esquerdo? Isso deve ser feito até que o valor 
		 tenha descido até um nó-folha */
	while (f_direito(N) < h->n_elementos) {
		if (h->arvore[f_esquerdo(N)] > h->arvore[f_direito(N)]) {
			/* Desce pelo filho esquerdo */
			descida = f_esquerdo(N);
		} else {
			/* Desce pelo filho direito */
			descida = f_direito(N);
		}
		troca( & (h->arvore[descida]), & (h->arvore[N]) );
		N = descida;
	}
	h->n_elementos = h->n_elementos - 1;
}

/* Para inserir um elemento no heap, podemos posicioná-lo no
	 fim do vetor de representação e faze-lo subir até que chegue
	 na raiz ou que o valor de seu nó-pai seja superior ao seu próprio
	 valor:*/
void insere_heap(Heap *h, int dado) {
	int N = h->n_elementos;
	h->arvore[h->n_elementos] = dado;
	h->n_elementos = h->n_elementos + 1;

	while ( (N>0) &&
					(h->arvore[pai(N)] < h->arvore[N])) {

		troca(&(h->arvore[pai(N)]), & (h->arvore[N]));
		N = pai(N);
	}
}

/* Assim, temos uma fila de prioridades capaz de ordenar dados. É
	 importante perceber que:
	 a) Uma inserção com insere_heap tem complexidade O(log(N))
	 b) Uma retirada com remove_heap tem complexidade O(log(N))
	 Assim, para inserir N elementos, que estão inicialmente
	 desordenados, e depois retirá-los, teremos complexidade
	 O(N * log(N)). Esse algoritmo de ordenação é chamado heapsort.

	 No programa-exemplo, ordenaremos um pequeno vetor.
*/

int main() {
	int valores[7] = {2, 6, 3, 3, 4, 0, 1};
	int i;
	Heap h;
	Heap h2;

	h.n_elementos = 4;
	h.arvore[0] = 4;
	h.arvore[1] = 3;
	h.arvore[2] = 2;
	h.arvore[3] = 1;

	printf("Estado atual do heap:\n");
	imprime_heap(&h);
	retira_maximo(&h);
	printf("Maximo foi retirado. Estado atual do heap:\n");
	imprime_heap(&h);

	printf("Resetando heap para estado nulo\n");
	h.n_elementos = 0;
	printf("Inserindo valores do vetor no heap:\n");
	for (i=0; i<7; i++) {
		insere_heap(&h, valores[i]);
	}
	printf("Estado atual do heap:\n");
	imprime_heap(&h);
	printf("Retirando os valores do heap em ordem:\n");
	while (h.n_elementos > 0) {
		printf("%d\n", maximo(&h));
		retira_maximo(&h);
	}
	printf("Estado do heap:\n");
	imprime_heap(&h);

	
	return 0;
}

/* Exercícios

	 1) Desenhe o heap resultante da inserção sucessiva
	 dos valores no vetor v[], sendo que o heap está inicialmente
	 vazio:
	 int v[7] = {5, 2, 3, 7, 5, 8, 1};

	 2) Compare a complexidade das seguintes operações:
	 a) Inserir N elementos numa árvore binária de busca e então
	 escrever a árvore em inordem.
	 b) Aplicar o heapsort nesse mesmo conjunto de dados.
	 
	 3) Modifique o programa apresentado nesta aula de forma que
	 o algoritmo ordene os valores recebidos em ordem crescente, e
	 não em ordem decrescente.

	 4) Escreva um programa que ordena tarefas, recebidas sucessivamente,
	 de acordo com sua data de entrega. Tarefas com a data de entrega final
	 mais próxima devem aparecer primeiro em sua lista de afazeres do dia.
*/
