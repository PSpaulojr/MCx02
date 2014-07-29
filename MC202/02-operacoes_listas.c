#include <stdio.h>
#include <stdlib.h>

/* Operações em listas ligadas

	 Neste módulo, serão abordados algoritmos gerais para listas
	 ligadas simples. Como já vimos anteriormente, listas ligadas simples
	 são compostas de nós, sendo que cada nó é representado por uma
	 struct contendo um bloco de dados e um ponteiro para o nó
	 seguinte. Assim, podemos defini-lo como:
*/

typedef struct nolista {
	int dado;
	struct nolista *proximo;
} NoLista;

/* Como vimos anteriormente, podemos criar uma função que adiciona
	 um nó a uma lista, sendo que uma lista vazia é representada por um
	 ponteiro para NULL. Para manter nossa funcionalidade simples,
	 vamos assumir que o nosso ponteiro é passado por referência. Daí,
	 a função que adiciona um dado à lista assume a forma:
*/
int adiciona_final(NoLista **lista, int dado) {
	/* Esta função retorna 1 caso a adição tenha sido realizada 
		 com sucesso, e 0 em caso de erro */
	NoLista *ponteiro;
	
	if ((*lista) == NULL) { /* Adicionar nó em uma lista vazia */
		(*lista) = (NoLista*) malloc (sizeof(NoLista));
			if ((*lista) != NULL ) { /* malloc() retorna NULL caso não haja
																	memória disponível */
			(*lista)->proximo = NULL;
			(*lista)->dado = dado;
			return 1;
		} else {
			return 0;
		}

	} else { /* Adicionar nó em uma lista não-vazia */
		ponteiro = (*lista);

		while (ponteiro->proximo != NULL) /* Varre lista até o fim */
			ponteiro = ponteiro->proximo;
		ponteiro->proximo = (NoLista*) malloc (sizeof(NoLista));
		if (ponteiro->proximo != NULL) {
			ponteiro->proximo->dado = dado;
			ponteiro->proximo->proximo = NULL;
			return 1;
		} else {
			return 0;
		}
		
	}

	return 0; /* O programa nunca deveria chegar até aqui. Se chegar,
							 é porque algo saiu errado */
}

/* Da mesma forma, podemos criar uma função que retorna ao sistema
	 toda a memória já alocada para a construção da lista. Adicionalmente,
	 essa função tornará nosso ponteiro para o nó inicial um ponteiro para
	 lista vazia, o que garante a consistência de nossa representação.
	 Vamos adotar, por simplicidade, nossa implementação recursiva:
*/
void deleta_lista(NoLista **lista) {
	if ( (*lista)->proximo != NULL ) /* Se a lista a seguir não é adiante */
		deleta_lista (&((*lista)->proximo)); /* desaloca a lista que começa no
																						próximo nó */
	free(*lista); /* Desaloca o nó atual */
	(*lista) = NULL; /* A lista atual passa a ser nula */
}

/* Podemos facilmente fazer uma função que imprime todos os elementos de uma
	 lista na tela. Nessa função, um ponteiro varre a lista imprimindo todos
	 os elementos. Para manter a consistência com os cabeçalhos anteriores, vamos
	 manter a passagem da lista por referência (**lista), embora isso não seja
	 estritamente necessário:
*/
void imprime_lista(NoLista **lista) {
	NoLista *ponteiro;
	ponteiro = (*lista);
	while (ponteiro != NULL) {
		printf("%d\n", ponteiro->dado);
		ponteiro = ponteiro->proximo;
	}
}

/* Um operação interessante que pode ser feita com listas é a concatenação.
	 Trata-se de uma função que recebe duas listas (que podem ou não estar vazias)
	 e faz com que uma seja adicionada ao fim de outra. Essa operação é
	 especialmente interessante quando a segunda lista é muito grande:
*/
void concatena_listas(NoLista **lista_inicio, NoLista **lista_fim) {
	NoLista *ponteiro;

	if ( (*lista_inicio) == NULL) { /* Caso especial: uma lista vazia no começo */
		(*lista_inicio) = (*lista_fim);
		return;
	}

	ponteiro = (*lista_inicio);
	/* Caso a lista não esteja vazia, varre até o último nó da lista */
	while (ponteiro->proximo != NULL)
		ponteiro = ponteiro->proximo;

	ponteiro->proximo = (*lista_fim);
}

/* Um efeito interessante acontece nessa implementação: há dois ponteiros
	 para o mesmo nó. Isso quer dizer que, se (*lista_fim) for desalocada,
	 então uma parte da nova (*lista_inicio) se tornará inválida. Isso
	 gerará um erro de segmentation fault.

	 Além de concatenar listas, é possível inverter os elementos de uma
	 lista somente invertendo seus ponteiros. Essa operação é interessante
	 quando os dados armazenados na lista são muito grandes, de forma que
	 copiá-los seria muito custoso. Assim, podemos definir a função:
*/
void inverte_lista(NoLista **lista) {
	NoLista *atual;
	NoLista *anterior;
	NoLista *prox;

	anterior = NULL;
	atual = (*lista);
	while (atual != NULL) {
		prox = atual->proximo;
		atual->proximo = anterior;
		anterior = atual;
		atual = prox;
	}
	(*lista) = anterior;
}

/* Por fim, é possível que queiramos copiar os elementos de uma lista
	 explicitamente. A isso, se dá o nome de cópia profunda: um novo
	 espaço de memória é alocado, contendo cópias do espaço original. Isso
	 é diferente de criar um novo ponteiro para o mesmo espaço de memória. */
NoLista *copia_profunda(NoLista **origem) {
	NoLista *nova_lista;
	NoLista *ponteiro_dest;
	NoLista *ponteiro_origem;

	if ((*origem) == NULL) return NULL; /* Caso especial para lista vazia */

	nova_lista = (NoLista*) malloc(sizeof(NoLista));
	
	ponteiro_dest = nova_lista;
	ponteiro_origem = (*origem);

	ponteiro_dest->dado = ponteiro_origem->dado;
  while (ponteiro_origem->proximo != NULL) {
		ponteiro_origem = ponteiro_origem->proximo;
		ponteiro_dest->proximo = (NoLista*) malloc (sizeof(NoLista));
		ponteiro_dest = ponteiro_dest->proximo;
		ponteiro_dest->dado = ponteiro_origem->dado;
	}
	ponteiro_dest->proximo = NULL;
	return nova_lista;
}

int main() {
	int i;
	NoLista *lista1;
	NoLista *lista2;
	NoLista *lista3;

	lista1 = NULL;
	lista2 = NULL;

	printf("Adicionando dados a lista\n");
	for (i = 0; i < 5; i++) {
		adiciona_final(&lista1, i);
		adiciona_final(&lista2, i+10);
	}
	printf("Verificando listas\n");
	printf("Lista 1\n");
	imprime_lista(&lista1);
	printf("Lista 2\n");
	imprime_lista(&lista2);

	printf("Concatenando listas\n");
	concatena_listas(&lista1, &lista2);
	printf("Lista 1\n");
	imprime_lista(&lista1);
	printf("Lista 2\n");
	imprime_lista(&lista2);

	printf("Invertendo lista 1\n");
	inverte_lista(&lista1);
	printf("Lista 1\n");
	imprime_lista(&lista1);
	printf("Lista 2\n"); /* Desafio: explique este resultado! */
	imprime_lista(&lista2);


	lista3 = copia_profunda(&lista1);
	inverte_lista(&lista3);
	printf("Lista 1\n");
	imprime_lista(&lista1);
	printf("Lista 3\n");
	imprime_lista(&lista3);


	deleta_lista(&lista1);
	deleta_lista(&lista3);



	return 0;
}

/* Exercícios

	 1) No programa acima, se a chamada inverte_lista(&lista1)
	 for trocada para inverte_lista(&lista2), quais serão
	 os resultados das seguintes chamadas:
	 a) imprime_lista(&lista1)
	 b) imprime_lista(&lista2)
	 c) deleta_lista(&lista1)

	 2) Escreva uma função com o cabeçalho:
	 int conta_elementos(NoLista **lista);
	 Essa função deve retornar o número de elementos da lista
	 ligada recebida como entrada.

	 3) Escreva uma função que recebe como entradas duas listas
	 ligadas e intercala seus elementos, ou seja, entradas como:
	 A1 -> A2 -> A3
	 B1 -> B2 -> B3 -> B4 -> B5
	 retornariam a saída:
	 A1 -> B1 -> A2 -> B2 -> A3 -> B3 -> B4 -> B5

	 4) Escreva uma função que ordena os elementos de uma lista
	 ligada. Durante a chamada dessa função, não é permitido
	 alocar vetores e nem realizar novas chamadas a malloc().
*/
