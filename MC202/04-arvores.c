/* Árvores binárias

	 Árvores binárias são estruturas de dados também utilizadas
	 para armazenar dados. Uma árvore binária é composta de nós, sendo
	 que cada nó possui um registro de dados e dois ponteiros, um para
	 seu filho esquerdo e um para seu filho direito. Assim, para representar
	 uma árvore binária, só é preciso armazenar um ponteiro para o primeiro
	 nó de sua estrutura:

	            Nó-pai
	           /      \
		F_esquerdo      F_direito
                    /       \
                  ...       ...

*/
#include <stdio.h>
#include <stdlib.h>

typedef struct noarvore {
	int dado;
	struct noarvore *f_esquerdo;
	struct noarvore *f_direito;
} NoArvore;

/* A árvore binária é uma estrutura inerentemente recursiva, já que
	 os filhos de uma árvore também são, por si só, árvores. Essa estrutura
	 se torna especialmente útil se determinarmos que todos os dados armazenados
	 no filho esquerdo de uma árvore são menores que o pai, e que todos os dados
	 no filho direito são maiores que o pai. Isso dá origem à árvore binária de
	 busca, que tem operações especiais para inserção e para remoção de dados
*/

void insere_binario(NoArvore **arvore, int dado) {
	if (*arvore == NULL) {
		/* Caso-base: estou apontando para uma árvore vazia */
		(*arvore) = (NoArvore *) malloc (sizeof(NoArvore));
		(*arvore)->dado = dado;
		(*arvore)->f_esquerdo = NULL;
		(*arvore)->f_direito = NULL;
		return;
	} else {
		if (dado >= (*arvore)->dado) {
			insere_binario( & ((*arvore)->f_direito), dado);
		} else {
			insere_binario( & ((*arvore)->f_esquerdo), dado);
		}
	}
}

/* Depois de inserirmos os dados numa árvore, se quisermos
	 ler os elementos em ordem crescente basta que,
	 recursivamente, imprimamos todos os elementos do filho
	 esquerdo, depois os elementos do nó atual e então os
	 elementos do filho direito:
*/

void imprime_ordenado(NoArvore **arvore) {
	if ( (*arvore) != NULL) {
		imprime_ordenado( & ((*arvore)->f_esquerdo) );
		printf("\t%d\t", (*arvore)->dado);
		imprime_ordenado( & ((*arvore)->f_direito) );
	}
}

/* Perceba que essa operação ordena os dados que inserimos
	 na árvore de forma semelhante ao quicksort()!

	 Note que a estrutura geral de nossa função de impressão é:
	 1) Executa recursivamente operações à esquerda
	 2) Executa operações no nó atual
	 3) Executa recursivamente operações à direita
	 
	 Assim, definimos um percurso chamado de inordem. De forma
	 semelhante, poderíamos varrer a árvore em pré-ordem (executando
	 operações no nó atual antes das chamadas recursivas) ou pós-ordem
	 (executando operações no nó atual após as chamadas recursivas):
*/

void imprime_preordem(NoArvore **arvore) {
	if ( (*arvore) != NULL) {
		printf("\t%d\t", (*arvore)->dado);
		imprime_preordem( & ((*arvore)->f_esquerdo) );
		imprime_preordem( & ((*arvore)->f_direito) );
	}
}

void imprime_posordem(NoArvore **arvore) {
	if ( (*arvore) != NULL) {
		imprime_posordem( & ((*arvore)->f_esquerdo) );
		imprime_posordem( & ((*arvore)->f_direito) );
		printf("\t%d\t", (*arvore)->dado);
	}
}
/* Uma vez que as árvores são compreendidas, podemos definir alguns conceitos
	 essenciais que serão utilizados ao se referir a árvores:
	 
	 Nó: ítem de informação com apontadores para outros nós.
	 Grau: número de sub-árvores de um nó
	 Folhas: nós terminais (grau 0)
	 Filhos: sub-árvores de um nó
	 Pai: ancestral direto de um nó
	 Grau de uma árvore: grau máximo de um nó de uma árvore
	 Altura: maior distância entre um nó-folha e o nó-pai de uma árvore

	 Assim, podemos definir uma função que, ao percorrer a árvore em pós-ordem,
	 calcula a altura de uma arvore:
*/

int altura(NoArvore **arvore) {
	int altura_esq;
	int altura_dir;

	if (*arvore == NULL) return 0;

	altura_esq = altura (& ((*arvore)->f_esquerdo));
	altura_dir = altura (& ((*arvore)->f_direito));

	if (altura_esq > altura_dir)
		return altura_esq + 1;
	return altura_dir + 1;
}

/* Utilizando uma árvore binária ordenada, é possível realizar
	 buscas em elementos que vão sendo adicionados progressivamente.
	 Em vetores ordenados, a busca também é realizada de forma eficiente,
	 mas os elementos que são levados em consideração são fixos. Assim,
	 temos as seguintes complexidades de execução para vetores e árvores:
	              Inserir novo   |   Ordenar valores   |   Encontrar valor
	 Vetores        O(N)                O(N logN)             O(logN)
	 Árvores        O(logN)             O(N logN)             O(logN)

	 Portanto, verificamos que as árvores binárias de busca são mais eficientes
	 que vetores quando as operações de inserir novo valor são utilizadas
	 mais frequentemente. Podemos definir nossa função de busca na forma:
*/
int busca (NoArvore **arvore, int valor) {
	/* Retorna 1 se o valor existe na árvore e 0 caso contrário */
	if ( (*arvore) == NULL) return 0;
	if (valor == (*arvore)->dado) return 1;
	if (valor < (*arvore)->dado) return busca( & ((*arvore)->f_esquerdo), valor);
	if (valor > (*arvore)->dado) return busca( & ((*arvore)->f_direito), valor);
	return 0;
}

/* Porém, podemos também verificar que o vetor ordenado é mais eficaz para
	 encontrar o valor máximo e mínimo de uma série - O(1) contra O(logN) da
	 árvore binária. Podemos traçar uma rotina que encontra o nó de valor mínimo
	 em uma árvore de busca:
*/
NoArvore **minimo(NoArvore **arvore) {
	if (*arvore == NULL) return NULL;
	if ( (*arvore)->f_esquerdo == NULL) return arvore;
	return minimo(& ((*arvore)->f_esquerdo));
}

/* Para remover um valor de uma árvore de busca, devemos tomar o cuidado
	 de garantir que os nós restantes mantenham suas propriedades. Assim, devemos
	 re-organizar os nós restantes de forma que o nó removido seja substituído
	 adequadamente por um de seus filhos - em nosso caso, o nó de valor mínimo de seu
	 filho direito:
*/
void remove_pai(NoArvore **arvore) {
	NoArvore *pai = (*arvore);

	if (arvore == NULL) return;
	if (*arvore == NULL) return;

	NoArvore **min_dir;
	min_dir = minimo( & ((*arvore)->f_direito));

	if (min_dir != NULL) {
		if (pai->f_esquerdo != (*min_dir)) /* evitar a auto-referência! */
			(*min_dir)->f_esquerdo = pai->f_esquerdo;
		if (pai->f_direito != (*min_dir))
			(*min_dir)->f_direito = pai->f_direito;

		(*arvore) = (*min_dir);
		(*min_dir) = NULL;
		free(pai);
	} else {
		(*arvore) = NULL;
	}
	
}

void remove_valor(NoArvore **arvore, int valor) {
	/* Retorna 1 se o valor existe na árvore e 0 caso contrário */
	if ( (*arvore) == NULL) return;
	if (valor == (*arvore)->dado) remove_pai(arvore);
	if (valor < (*arvore)->dado) remove_valor(  & ((*arvore)->f_esquerdo), valor);
	if (valor > (*arvore)->dado) remove_valor(  & ((*arvore)->f_direito), valor);
}


/* Para desalocar uma árvore, pode-se utlizar um percurso em pós-ordem: */
void desaloca (NoArvore **arvore) {
	if (*arvore != NULL) {
		desaloca (& (*arvore)->f_esquerdo);
		desaloca (& (*arvore)->f_direito);
		free(*arvore);
	}

}

int main () {
	int vetor[10] = {5, 2, 7, 3, 4, 17, 6, 12, 11, 10};
	int i;
	NoArvore *arvore;

	arvore = NULL;
	for (i = 0; i<10; i++)
		insere_binario(&arvore, vetor[i]);

	imprime_ordenado(&arvore);
	printf("\n");
	imprime_preordem(&arvore);
	printf("\n");
	imprime_posordem(&arvore);
	printf("\n");

	printf("Altura da árvore: %d\n", altura(&arvore));

	printf("Busca por valor 7: %d\n", busca(&arvore, 7));
	printf("Busca por valor 50: %d\n", busca(&arvore, 50));

	printf("Minimo da arvore: %d\n", (*minimo(&arvore))->dado);

	remove_pai(&arvore);
	imprime_ordenado(&arvore);
	printf("\n");
	remove_valor(&arvore, 7);
	imprime_ordenado(&arvore);
	printf("\n");
	printf("Busca por valor 7: %d\n", busca(&arvore, 7));
	printf("\n");
	remove_valor(&arvore, (*minimo(&arvore))->dado);
	imprime_ordenado(&arvore);
	printf("\nMinimo da arvore: %d\n", (*minimo(&arvore))->dado);

	desaloca(&arvore);
	return 0;
}

/* Exercícios

	 1) Qual é a altura mínima de uma árvore com N nós? E a altura
	 máxima?

	 2) Mostre as árvores binárias de busca resultantes da inserção
	 dos seguintes elementos, na ordem dada. Determine também
	 os percursos em inordem, pós-ordem e pré-ordem para cada
	 caso.
	 a) {1, 2, 3, 4, 5, 6, 7, 8}
	 b) {8, 7, 6, 5, 4, 3, 2, 1}
	 c) {5, 4, 6, 7, 8, 2, 3, 1}

	 3) Escreva uma função que conta quantos nós-folha existem em uma
	 árvore.

	 4) Uma árvore binária é semelhante a outra se ambas são vazias
	 ou se seus filhos esquerdo e direito são, respectivamente,
	 semelhantes. Implemente uma função que determina se duas
	 árvores são semelhantes.

	 5) Nem toda árvore binária é, necessariamente, uma árvore binária
	 de busca. Implemente uma função que detecta se uma árvore binária,
	 passada como parâmetro, é uma árvore binária de busca.


*/
