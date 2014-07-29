#include <stdio.h>
#include <stdlib.h>

/* Estruturas ligadas e listas ligadas simples

	 Um vetor é um espaço contínuo alocado em disco no qual
	 podemos armazenar diversas variáveis de um determinado tipo.
	 Porém, o uso de um vetor requer que saibamos, antecipadamente,
	 quantas posições de memória serão utilizadas, o que nem sempre
	 é possível. Uma estrutura de dados que cresce dinamicamente
	 quando necessário é a lista ligada.

	 Antes de falar sobre listas ligadas, deveremos compreender como
	 funciona a alocação dinâmica de memória. Quando uma variável é
	 declarada, a memória para ela é alocada de forma estática, e então
	 devolvida ao sistema ao fim da função na qual a variável é alocada.
	 Porém, podemos querer alocar um espaço de memória cujo tamanho ou
	 tipo não sabemos ao certo, ou ainda, que deve continuar sob nosso
	 controle mesmo quando a função atual terminar.

	 Esse processo se chama alocação dinâmica de memória, que é implementada
	 em C na função malloc(). A função malloc() retorna um ponteiro para tipo
	 void que é o começo de um espaço de memória contínuo com o tamanho
	 especificado como argumento. Assim, para alocar dinamicamente uma variável
	 do tipo int, deve-se utilizar um trecho de código como segue:
	 int *p;
	 p = (int *) malloc (sizeof(int));

	 Também, é possível alocar diretamente um vetor. Lembre-se que um vetor, em C,
	 nada mais é que um ponteiro para o início de um trecho de memória. Assim,
	 um vetor de 10 posições pode ser alocado como:
	 int *p;
	 p = (int *) malloc (sizeof(int) * 10);

	 Quando um trecho de memória é alocado usando malloc, ele
	 deverá posteriormente ser devolvido ao sistema usando o comando
	 free(). Na alocação estática, a devolução da memória ao sistema
	 é feita de forma automática, mas lembre-se que o processo de alocação
	 dinâmica permite que um trecho de memória permaneça sob controle do programa
	 mesmo depois do fim de uma função. Assim, temos:
	 int *p;
	 p = (int *) malloc (sizeof(int) * 10); <- aloca memória
	 free(p); <- desaloca memória

	 A idéia de alocação dinâmica pode ser utilizada para criar uma
	 estrutura que chama-se lista ligada. Ela é composta de estruturas básicas
	 chamadas de nós. Cada nó contém um dado e um ponteiro para o próximo nó:
*/

typedef struct nolista {
	int dado;
	struct nolista *proximo;
} NoLista;

/* Tudo que o nosso sistema precisa guardar é um ponteiro para o começo da
	 lista. Por convenção, o último nó da lista aponta para NULL, de forma que
	 podemos varrer nossa lista toda. Podemos facilmente definir uma função que 
	 cria um novo nó alocando a memória necessária, coloca o dado na posição
	 correta e retorna um ponteiro para a memória alocada:
*/
NoLista *novo_no(int dado) {
	NoLista *no = (NoLista *) malloc (sizeof(NoLista));
	no->dado = dado;
	no->proximo = NULL;
	return no;
}

/* Vamos supor então o problema de inserir um novo nó no começo de uma lista.
	 Uma vez que o nó de início da lista mudou, deveremos saber qual é o novo
	 nó que começa a lista. Então, nossa função pode assumir a forma:
*/
NoLista *insere_comeco(NoLista *lista_atual, int dado) {
	NoLista *novo_comeco;

	novo_comeco = (NoLista*) malloc (sizeof (NoLista));
	novo_comeco->proximo = lista_atual;
	novo_comeco->dado = dado;
	return novo_comeco;
}

/* Podemos, também, remover nos do comeco de nossa lista. Nesse caso,
   é importante verificar, antes, se o nó para o qual estamos apontando
	 não é nulo, afinal, não podemos remover um nó de uma lista vazia.
	 Assim, a função de remoção fica:
*/
NoLista *remove_comeco(NoLista *lista_atual) {
	NoLista *novo_comeco;

	if (lista_atual != NULL) {
		novo_comeco = lista_atual->proximo;
		free(lista_atual);
		return novo_comeco;
	}
	return NULL;
}

/* Se construímos uma lista, podemos varrê-la inteira, e executar,
	 em cada nó, uma função qualquer. Vamos criar uma função que
	 imprime todos os nós de uma lista. Essa função funciona imprimindo
	 um nó atual e então prosseguindo para o próximo:
*/
void imprime_lista(NoLista *lista) {
	NoLista *no_atual;
	
	no_atual = lista;
	while (no_atual != NULL) {
		printf("%d\n", no_atual->dado);
		no_atual = no_atual->proximo;
	}
}

/* É interessante perceber que é possível criar uma função que
	 insere um nó entre o nó apontado atualmente e o seguinte.
	 O nó apontado atualmente passa a apontar para o novo nó,
	 e o novo nó criado apontará para o que antes era apontado
	 pelo nó recebido como entrada:
*/
void insere_no(NoLista *local, NoLista *no_inserir) {
	no_inserir->proximo = local->proximo;
	local->proximo = no_inserir;
}

/* Podemos, então, rapidamente criar uma função que insere
	 um elemento no final da lista ligada. Para tal, varreremos
	 a lista até o fim e inseriremos o nó. Nessa função, supomos
	 que nossa lista nao está vazia:
*/
void insere_fim(NoLista *inicio_lista, int dado) {
	NoLista *ponteiro_varredura;
	NoLista *no_inserir;

	ponteiro_varredura = inicio_lista;
	while(ponteiro_varredura->proximo != NULL)
		ponteiro_varredura = ponteiro_varredura->proximo;

	no_inserir = novo_no(dado);
	insere_no(ponteiro_varredura, no_inserir);
}

/* E, também utilizando a idéia de varredura, podemos criar uma
	 função que desaloca toda a memória alocada pela lista. */
void desaloca_lista(NoLista *inicio_lista) {
	NoLista *no_atual;
	NoLista *no_anterior;

	no_atual = inicio_lista;
	while (no_atual != NULL) {
		no_anterior = no_atual;
		no_atual = no_atual->proximo;
		free(no_anterior);
	}
}

/* É possível realizar a mesma operação utilizando uma função
	 recursiva:
*/
void desaloca_lista_recursiva(NoLista *inicio_lista) {
	if (inicio_lista !=NULL) {
		desaloca_lista_recursiva(inicio_lista->proximo);
		free(inicio_lista);
	}
}

/* Veja que nossa função de inserção só funciona de forma
	 elegante se a lista atual não é vazia. Caso seja, é preciso primeiro
	 inserir um nó no começo da lista e depois começar a inserir nós no
	 fim da lista - a não ser que mudemos o cabeçalho das funções de inserção,
	 passando o ponteiro para começo da lista por referência e não mais por
	 valor. Para resolver isso, podemos definir que uma lista sempre tem um nó
	 inicial vazio, e apenas o segundo nó e os seguintes contém dados - trata-se
	 de uma lista ligada com nó cabeça.

	 Uma outra variação da lista é a lista circular, na qual o último nó aponta
	 para o nó inicial. Assim, é possível iteragir indefinidamente sobre
	 os dados. Listas circulares são interessantes para armazenar, por
	 exemplo, os últimos N caracteres recebidos como entrada.

	 Por fim, os nós podem apontar não somente para o próximo nó, mas também
	 para o nó anterior. Assim, é possível iteragir sobre os dados da lista
	 nos dois sentidos (para frente e para trás). Essas estruturas são chamadas
	 de listas duplamente ligadas.

	 Dentre as aplicações de listas ligadas (e suas variações), podemos citar:
	 - Representar matrizes esparsas, de forma que cada nó representa uma 
	 posição (linha, coluna) da matriz e o valor lá contido e nós não representados
	 são assumidos como zero.
	 - Representar polinômios, de forma que cada nó representa um coeficiente e
	 o expoente relacionado a ele.
	 - Representar uma pilha (ver programa-exemplo), numa estrutura first-in-last-out
	 de tamanho variável
	 - Representar uma fila FIFO, também de tamanho variável.
*/

/* Neste programa exemplo, demonstraremos como uma pila (FILO) funciona */
int main() {
	NoLista *pilha;
	int valores[12] = {55, 23, 43, 2, 54, 12, 10, 2, 3, 4, 32, 100};
	int i;

	pilha = NULL;
	for (i=0; i<12; i++)
		pilha = insere_comeco(pilha, valores[i]);

	imprime_lista(pilha);
	desaloca_lista(pilha);

	return 0;
}

/* Exercícios

	 1) Escreva uma função cujo cabeçalho é:
	 NoLista *inverte_lista(NoLista *lista);
	 A função deve, modificando apenas os ponteiros dos nós
	 (NoLista.proximo), inverter a lista ligada.

	 2) Modifique as funções apresentadas neste texto para
	 que passem a utilizar listas duplamente ligadas com
	 nó cabeça.

	 3) Escreva uma função que recebe como entrada um vetor
	 de inteiros e retorna, para cada posição, a soma dos
	 últimos 15 elementos. Sua função deve utilizar uma lista
	 circular (com ou sem nó cabeça, a seu critério)

	4) Escreva uma função que permita multiplicar matrizes
	representadas de forma esparsa.
*/
