/* Tabelas de espalhamento

	 Uma tabela de espalhamento (ou hashing) é uma estrutura de dados
	 utilizada para guardar elementos de forma que possam ser acessados
	 rapidamente. Numa tabela desse tipo, um novo elemento que vai
	 ser adicionado recebe uma chave única, que é calculada de forma
	 determinística de acordo com seu conteúdo. A função que calcula
	 a posição do vetor em que o elemento será adicionado se chama
	 "função de espalhamento" ou "função de hashing".

	 Na literatura, há divergências quanto ao que são consideradas boas
	 funções de espalhamento. É possível, porém, encontrar especialmente
	 as seguintes propriedades desejáveis nessa função:

	 1) Determinismo [1]: o resultado da função de espalhamento
	 é completamente determinado pelo conteúdo que será espalhado;

	 2) Uniformidade [1], ou Injeção [2]: o resultado da função de
	 espalhamento deve ser distribuído da forma mais uniforme possível
	 no contra-domínio;

	 3) Continuidade [1]: em certas aplicações, é desejável que conteúdos
	 semelhantes sejam mapeados para posições próximas da tabela de espalhamento.
	 É o caso de buscas como Nearest Neighbour Search. Apesar disso, essa
	 propriedade é indesejável para funções de espalhamento que serão usadas
	 em criptografia.

	 4) Difusão [2]: o resultado da função de espalhamento não deve fornecer
	 nenhuma informação sobre o conteúdo que foi usado como entrada. Isso quer
	 dizer que os bits das saídas relacionadas a duas entradas diferentes deve
	 mudar com probabilidade sempre igual a 1/2.

	 Fontes:
	 [1] http://en.wikipedia.org/wiki/Hash_function#Properties
	 [2] http://www.cs.cornell.edu/courses/cs312/2008sp/lectures/lec21.html

	 Mesmo que a função de espalhamento escolhida seja bastante eficaz, uma
	 tabela - representada na memória por um vetor - tem tamanho fixo. Isso
	 quer dizer que, em determinado momento, ela ficará muito cheia. Nesse caso,
	 ocorrem colisões, e para resolvê-las duas técnicas são possíveis.

	 Uma delas é determinar uma função de re-espalhamento: se um elemento da
	 tabela está usado, então uma nova função é calculada e assim sucessivamente,
	 encontrando novas posições na tabela. Outra técnica possível é armazenar
	 os dados em listas ligadas que começam em cada posição. Em ambos os casos,
	 a eficiência da busca pode cair, embora seja necessário que a tabela fique
	 muito cheia para que essa eficiência caia perceptivelmente.

	 O uso do re-espalhamento evita o uso de ponteiros e aproveita a memória
	 de forma mais eficiente.

	 Os algoritmos para inserção, busca e remoção de elementos serão mostrados
	 a seguir.
*/


/* Em nosso programa-exemplo, definiremos uma tabela de espalhamento que armazena
	 inteiros positivos. Por convenção, temos dois conteúdos especiais:
	 -1 para um elemento vazio e -2 para um elemento que foi removido.
*/

#include <stdio.h>

#define MAX_HASH_SIZE 100
#define VAZIO -1
#define REMOVIDO -2


typedef struct hashtable {
	int elementos[MAX_HASH_SIZE];
} HashTable;

HashTable nova_tabela() {
	HashTable h;
	int i;

	for (i=0; i<MAX_HASH_SIZE; i++)
		h.elementos[i] = VAZIO;

	return h;
}

/* Funcoes de espalhamento e re-espalhamento */
int espalhar(int entrada) {
	return (entrada % MAX_HASH_SIZE);
}

int re_espalhar(int entrada, int pos_atual) {
	return (pos_atual+1) % MAX_HASH_SIZE;
}

/* Função que busca a posição de um elemento
	 numa tabela de espalhamento. Caso ele não exista,
	 retorna a posição em que ele deve ser inserido.
*/
int busca(int entrada, HashTable *h) {
	int pos;
	pos = espalhar(entrada);
	while ((h->elementos[pos] != entrada) &&
				 (h->elementos[pos] != VAZIO))
		pos = re_espalhar(entrada, pos);
	return pos;
}

/* Função para inserir um elemento na tabela */
void insere(int entrada, HashTable *h) {
	int pos;

	pos = busca(entrada, h);
	h->elementos[pos] = entrada;
}

/* Função para remover um elemento da tabela */
void deleta(int entrada, HashTable *h) {
	int pos;
	pos = busca(entrada, h);
	if (h->elementos[pos] == entrada) h->elementos[pos] = REMOVIDO;
}

int main() {
	HashTable h;
	int i;

	h = nova_tabela();

	insere(700, &h);
	insere(456, &h);
	insere(300, &h);

	i = busca(700, &h);
	printf("%d na posicao %d -> %d\n", 700, i, h.elementos[i]);
	i = busca(456, &h);
	printf("%d na posicao %d -> %d\n", 456, i, h.elementos[i]);
	i = busca(300, &h);
	printf("%d na posicao %d -> %d\n", 300, i, h.elementos[i]);

	deleta(300, &h);
	printf("Apos remocao do 300:\n");
	printf("%d na posicao %d -> %d\n", 300, i, h.elementos[i]);
	return 0;
}

/* Exercícios

	 1) Reflita (ou pesquise) como uma função de espalhamento
	 pode ser utilizada para criptografia de senhas.

	 2) Considere a função de espalhamento (entrada % MAX_HASH_SIZE) que
	 utilizamos nesta aula. Como ela se comporta em relação às características
	 enumeradas como propriedades de boas funções de espalhamento
	 (uniformidade, injeção, continuidade e difusão)? Faça o mesmo para
	 as funções encontradas nesta referência:
	 http://www.sparknotes.com/cs/searching/hashtables/section2.rhtml

	 3) Um dicionário é uma estrutura de dados que relaciona chaves tipo
	 string a conteúdos. Por exemplo, pode-se definir:
	 typedef struct {
	   char local[15]; <- esta é a chave
		 char endereco[50]; <- este é o conteúdo
	 } Elemento;
	 Utilize uma tabela de espalhamento para construir uma agenda de 
	 endereços. Implemente funções para:
	 a) adicionar um local à agenda,
	 b) remover um local,
	 c) buscar por um local.

	 4) Vários carros passam a cada minuto em uma rodovia. Defina uma
	 estrutura de dados que permita guardar a data e hora (mm/dd/aa, hh:mm:ss)
	 de cada passagem de carros nessa rodovia, considerando que não
	 sabemos todas as marcas de carro que existem e que queremos, ao fim da
	 coleta de dados, encontrar rapidamente todas as informações relativas a uma
	 marca específica de carros.
*/
