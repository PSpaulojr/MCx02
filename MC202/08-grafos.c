/* Grafos

	 Grafos, formalmente, são definidos como coleções de vértices
	 unidos por arestas. São usados para representar elementos que podem
	 ser abstraídos como diferentes estados que se interligam de alguma
	 forma determinada. Um caso especial de grafo é a árvore, que já foi
	 vista em aulas anteriores.

	 Grafos podem ser direcionados ou não-direcionados. Em um grafo não-direcionado,
	 uma ligação do vértice i para o vértice j é simétrico à ligação do vértice
	 j para o vértice i. Isso não é verdadeiro no grafo direcionado.

	 Uma maneira de representar um grafo na memória é através de uma matriz
	 de adjacências. Nessa representação, a matriz A[][] tem dimensão
	 N x N, onde N é o número de vértices do grafo. A[i][j] == 1 se há ligação
	 entre o vértice i e o vértice j, e A[i][j] == 0 caso contrário.

	 Outra maneira de representar um grafo é através de um vetor V[] de listas
	 ligadas. A lista na posição V[i] indica a quais outros vértices o vértice
	 i é ligado. Embora seja um pouco mais complicada de implementar, essa
	 representação é mais eficientes, como veremos a seguir.

	 Tarefas típicas em matrizes:

   Adicionar um novo vértice
	   Matriz: O(V^2)
		 Lista: O(V)

	 Adicionar uma nova aresta
	   Matriz: O(1)
		 Lista: O(A)

	 Verificar adjacência entre dois vértices
	   Matriz: O(1)
		 Lista: O(A)

	 Obter todas as arestas ligadas a um vértice:
	   Matriz: O(N)
		 Lista: O(A)
		 
	 Consumo de memória:
	   Matriz: O(N^2)
		 Lista: O(N*A)

	 Uma grande parte dos grafos com os quais lidamos na prática são esparsos,
	 isto é, cada vértice se conecta apenas a poucos outros vértices. Dessa forma,
	 podemos dizer que A <<< N. Um exemplo desse comportamento é uma rede social, em
	 que cada vértice representa um perfil e uma aresta representa uma relação
	 de amizade - claramente, existem muitos mais pessoas na rede social do que
	 cada pessoa tem amigos.

	 Por se tratar de uma implementação mais simples, vamos adotar neste exemplo
	 uma implementação matricial para nosso grafo. Assim, temos:
*/

#define MAX_VERTICES 100

typedef struct {
	int adjacencias[MAX_VERTICES][MAX_VERTICES];
	int n_vertices;
} Grafo;

Grafo novo_grafo(int n_vertices) {
	Grafo g;
	int i;
	int j;

	g.n_vertices = n_vertices;
 
	for (i=0; i<MAX_VERTICES; i++)
		for (j=0; j<MAX_VERTICES; j++)
			g.adjacencias[i][j] = 0;

	return g;
}

/* Podemos imediatamente criar funções para adicionar uma aresta
	 entre os vértices i e j, e também uma função para verificar se
	 existe uma aresta entre os vértices i e j */

void adicionar_aresta(Grafo *g, int i, int j) {
	g->adjacencias[i][j] = 1;
	g->adjacencias[j][i] = 1;
}

int adjacente(Grafo *g, int i, int j) {
	return g->adjacencias[i][j];
}

/* Uma funcionalidade bastante utilizada em grafos é realizar um
	 percurso partindo de um vértice i. A seguir, vamos mostrar dois
	 algoritmos canônicos para realizar esse percurso. São eles o 
	 percurso em profundidade e o percurso em largura.

	 Num percurso em profundidade, marcamos o vértice i como lido.
	 Depois, encontramos um vértice j adjacente a i e, recursivamente,
	 realizamos o percurso em profundidade em j. Após, passamos para os
	 outros vértices adjacentes a i; assim, o código fica:
*/

#include <stdio.h>

void percurso_profundidade(Grafo *g, int *acessados, int i) {
	int j;
	acessados[i] = 1;
	printf("%d\n", i);

	for (j = 0; j < g->n_vertices; j++) {
		if (g->adjacencias[i][j] == 1)
			if (acessados[j] == 0)
				percurso_profundidade(g, acessados, j);
	}
}

/* Num percurso em largura, ao invés de considerar cada vértice acessado
	 imediatamente, ele é colocado numa fila FIFO junto a todos os vértices
	 adjacentes ao atual. Após enfileirar todos os vértices adjacentes ao
	 atual, daí sim o percurso passa aos vértices seguintes. Vamos
	 implementar nossa fila usando um vetor, como segue:
*/

void percurso_largura(Grafo *g, int i) {
	int j;
	int vertice_atual;
	int acessados[MAX_VERTICES];
	int fila[MAX_VERTICES];
	int comeco_fila;
	int final_fila;

	for (j = 0; j < MAX_VERTICES; j++)
		acessados[j] = 0;


	comeco_fila = 0;
	final_fila = 1;
	fila[comeco_fila] = i;
	acessados[i] = 1;

	while (comeco_fila != final_fila) {
		/* Proximo vertice */
		vertice_atual = fila[comeco_fila];
		comeco_fila++;

		printf("%d\n", vertice_atual);

		/* Enfileira todos os vertices adjacentes ao atual */
		for (j = 0; j < g->n_vertices; j++) { 
		if (g->adjacencias[vertice_atual][j] == 1)
			if (acessados[j] == 0) {
				fila[final_fila] = j;
				final_fila++;
				acessados[j] = 1;
			}
		}
	}
}

/* Em nosso programa exemplo, vamos mostrar a diferença entre os dois percursos */

int main() {
	Grafo g;
	int acessos[4];
	g = novo_grafo(4);
	adicionar_aresta(&g, 0, 1);
	adicionar_aresta(&g, 1, 2);
	adicionar_aresta(&g, 2, 3);
	adicionar_aresta(&g, 0, 3);

	printf("Percurso em profundidade:\n");
	percurso_profundidade(&g, acessos, 0);
	printf("Percurso em largura:\n");
	percurso_largura(&g, 0);

	return 0;
}

/* Exercícios

	 1) Calcule a complexidade dos percursos em profundidade
	 e em largura mostrados neste exemplo. Faça o mesmo, considerando
	 a representação por lista ligada. Qual das duas representações
	 leva a percursos mais eficientes?

	 2) Os grafos implementados nesta aula são direcionais ou não-direcionais?
	 Porque?

	 3) Mostre como os seguintes fenômenos podem ser modelados por grafos. Os
	 grafos do seu modelo são direcionados ou não-direcionados?
	 a) A transmissão de uma doença por contato inter-pessoal
	 b) Uma rede de amizades
	 c) A árvore de pré-requisitos de um curso
	 d) O sistema de metrô de uma grande cidade

	 4) Implemente um algoritmo que calcula se existe algum caminho
	 entre os vértices i e j de um dado grafo.
	 
	 5) Implemente um algoritmo que imprime na tela uma árvore binária, numa forma
	 facilmente legível, como:
	         A
	       /   \
			  B     C
             /  \
            D    E
           /
          F

	 6) Implemente um algoritmo que determina, em uma rede de amizades,
	 se o indivíduo j é amigo de um amigo de i.
*/
