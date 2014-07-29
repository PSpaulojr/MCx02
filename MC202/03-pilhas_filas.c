/* Pilhas, filas e aplicações

	 Duas importantes estruturas de dados amplamente utilizadas
	 em diversas aplicações são as pilhas e as filas. Uma pilha é uma
	 estrutura na qual dados são retirados na ordem inversa em que
	 são inseridos, de forma semelhante a uma pilha de papéis. Numa fila,
	 por sua vez, dados são retirados na ordem em que são inseridos, como
	 uma fila de pessoas que chega a um caixa.

	 Tanto as pilhas quanto as filas podem ser implementadas utilizando
	 listas ligadas ou vetores. Nesta aula, utilizaremos as listas ligadas,
	 mantendo a consistência com o que vínhamos abordando nas aulas anteriores.

	 Em nossa aplicação, criaremos um tipo abstrato de dados que contém
	 ponteiros para o começo e para o final de uma lista ligada. Implementaremos
	 as operações de inserir e retirar elementos do começo e do final de nossa
	 estrutura. A pilha poderá inserir e retirar elementos somente do começo da
	 lista, e a fila poderá inserir elementos no começo e retirar no final:

	 [x] -> A -> B -> [y]
	 A pilha pode inserir [x] e retirar [x]. A fila pode inserir [x] e retirar
	 [y].

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct nolista {
	int dado;
	struct nolista *proximo;
} NoLista;

typedef struct lista {
	int n_elementos;
	NoLista *inicio;
	NoLista *final;
} Lista;

Lista *nova_lista() {
	Lista *novo;
	novo = (Lista*) malloc(sizeof(Lista));
	novo->n_elementos = 0;
	novo->inicio = 0;
	novo->final = 0;
	return novo;
}

void insere_comeco(Lista *minha_lista, int dado) {
	NoLista *novo_no;
	novo_no = (NoLista*) malloc(sizeof(Lista));
	novo_no->proximo = minha_lista->inicio;
	novo_no->dado = dado;
	minha_lista->inicio = novo_no;

	if (minha_lista->n_elementos == 0) {
		novo_no->proximo = NULL;
		minha_lista->final = novo_no;
	}

	minha_lista->n_elementos = (minha_lista->n_elementos) + 1;
}

void insere_final(Lista *minha_lista, int dado) {
	NoLista *novo_no;
	novo_no = (NoLista*) malloc(sizeof(Lista));
	novo_no->proximo = NULL;
	novo_no->dado = dado;

	if (minha_lista->n_elementos == 0) {
		minha_lista->final = novo_no;
		minha_lista->inicio = novo_no;
	} else {
		minha_lista->final->proximo = novo_no;
		minha_lista->final = novo_no;
	}

	minha_lista->n_elementos = (minha_lista->n_elementos) + 1;
}

int remove_comeco(Lista *minha_lista) {
	int dado;
	NoLista *proximo;

	if (minha_lista->n_elementos == 0) {
		/* Não posso remover dados de uma lista vazia */
		return -1;
	}

	dado = minha_lista->inicio->dado;
	proximo = minha_lista->inicio->proximo;

	free(minha_lista->inicio);
	
	minha_lista->inicio = proximo;
	minha_lista->n_elementos = minha_lista->n_elementos - 1;
	return dado;
}

void desaloca_lista(Lista *minha_lista) {
	while (minha_lista->n_elementos > 0)
		remove_comeco(minha_lista);
	free(minha_lista);
}

/* Dentre as aplicações de filas, podemos citar o buffer. Um buffer é um
	 espaço de memória em que mensagens ficam armazenadas até que possam ser
	 processadas. Isso pode ser realizado utilizando chamadas diretas para
	 insere_final() e remove_comeco(), como veremos no programa-exemplo.

	 Uma importante aplicação de pilhas é a eliminação de recursão. Quando uma
	 função é chamada em C, ela é colocada, junto a seus parâmetros, numa pilha
	 de execução, ou seja, ao se chamar a versão recursiva de fatorial(N), o que
	 acontece é o seguinte:
	 * empilha fatorial(N);
	 * empilha fatorial(N-1);
	 ...
	 * caso base: coloca na pilha o resultado de fatorial(1);
	 * retira da pilha fatorial(2)
	 * coloca na pilha o resultado de fatorial(2)
	 ...
	 * retira da pilha fatorial(N);
	 * coloca na pilha o resultado de fatorial(N)
	 * segue a execução do programa

	 Podemos simular esse mesmo processo usando nossa própria estrutura de pilha.
	 Ao fazer isso, podemos evitar que algumas operações sejam feitas, como a
	 cópia de estruturas de dados desnecessárias para a pilha. Além disso, a pilha
	 de execução tem tamanho limitado, ao passo que a memória alocada com malloc()
	 pode ocupar toda a memória do computador, de forma que problemas maiores
	 podem ser abordados.

	 Vamos, assim, definir algumas funções que utilizam o raciocínio recursivo, mas
	 utilizam nossa própria pilha para resolvê-lo.
*/
int fatorial(int N) {
	Lista *pilha;
	int resultado;
	int parcial;

	pilha = nova_lista();
	insere_comeco(pilha, N);

	resultado = 1;
	
	/* Casos adicionais */
	while (pilha->n_elementos > 0) {
		parcial = remove_comeco(pilha);
		if (parcial > 1) {
			resultado = resultado * parcial;
			insere_comeco(pilha, parcial - 1);
		}
		
	}

	desaloca_lista(pilha);
	return resultado;
}

int fibonacci(int N) {
	Lista *pilha;
	int resultado;
	int parcial;
	pilha = nova_lista();
	insere_comeco(pilha, N);

	resultado = 0;

	while (pilha->n_elementos > 0) {
		parcial = remove_comeco(pilha);
		if (parcial <= 2) resultado = resultado + 1; /* Caso-base */
		else { /* Outros casos */
			insere_comeco(pilha, parcial - 1);
			insere_comeco(pilha, parcial - 2);
		}
	}

	desaloca_lista(pilha);
	return resultado;
}


int main() {
	Lista *fila;
	Lista *pilha;
	int i;
	
	printf("Inserindo e retirando numeros na ordem em:\nFILA\tPILHA\n");
	fila = nova_lista();
	pilha = nova_lista();

	for (i = 0; i < 5; i++) {
		insere_comeco(pilha, i);
		insere_final(fila, i);
	}

	for (i = 0; i < 5; i++) {
		printf("%d\t%d\n", remove_comeco(fila), remove_comeco(pilha));
	}

	desaloca_lista(fila);
	desaloca_lista(pilha);
	printf("---\n");

	printf("Fatorial(4) = %d\n", fatorial(4));
	for (int i = 1; i < 7; i++) {
		printf("Fibonacci(%d) = %d\n", i, fibonacci(i));
	}
	return 0;
}

/* Exercícios

	 1) Que estrutura (pilha ou fila) você deve utilizar para:
	 a) armazenar documentos que são enviados a uma impressora compartilhada?
	 b) armazenar processos que serão executados num processador?
	 c) simular o conteúdo das torres no problema das Torres de Hanoi?
	 d) armazenar resultados intermediários de operações matemáticas?

	 2) Programe uma estrutura de dados que utiliza duas pilhas para simular o
	 comportamento de uma fila.

	 3) Construa um programa que simula duas situações diferentes. Na primeira,
	 há N caixas, cada um com sua respectiva fila de clientes. Na segunda, há
	 N caixas, mas somente uma fila de clientes. A cada instante de execução,
	 existe uma chance P de chegar um novo cliente (no primeiro caso, ele
	 irá aleatoriamente para uma das filas do supermercado). Cada cliente será
	 atendido num tempo constante igual a T. Seu programa deve calcular:
	 a) A soma do tempo ocioso de cada caixa
	 b) O tempo médio de espera de cada cliente
	 Bônus: quais outras variáveis poderiam ser consideradas em seu modelo?
	 
	 4) Utilize a técnica de eliminação de recursão com pilhas explícitas
	 para escrever uma rotina que resolva o problema das Torres de Hanoi
*/

