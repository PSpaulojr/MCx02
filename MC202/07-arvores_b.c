/* Árvores B

	 Até o momento, conhecemos algumas maneiras de armazenar dados. Podemos
	 utilizar um vetor desordenado, um vetor ordenado ou uma árvore binária para tal.
	 Na tabela abaixo, podemos verificar os tempos de execução de operações de
	 inserção, remoção e busca para cada uma dessas estruturas de dados:

	               Vetor  Vetor Ordenado   Árvore Binária
	 Inserção     O(1)       O(N)           O(N log2(N))
	 Remoção      O(N)       O(N)           O(N log2(N))
	 Busca        O(N)       O(N log2(N))   O(N log2(N))

   Vemos que a árvore binária é uma estrutura na qual são necessários menos
	 acessos à memória para realizar buscas, inserções e remoções. No caso de dados
	 armazenados em disco, é interessante que esses acessos sejam minimizados, 
	 já que um acesso a disco é várias ordens de grandeza mais lento que uma operação
	 em memória. Nesse contexto, aparecem as árvores B.
	 
   Árvores B são generalizações de árvores binárias que permitem que cada nó
	 armazene uma quantidade arbitrária de entradas. Por esse motivo, um nó da
	 árvore é chamado de página. As árvores B satisfazem as seguintes propriedades:
	 
   1) Cada página contém, no máximo, d páginas filhas
   2) Cada página, exceto a raiz e as folhas, tem pelo menos floor(D/2) páginas
	     filhas
   3) A página raiz tem ao menos duas páginas filha, a menos que ela seja uma folha
	 4) Toda página folha possui a mesma profundidade que, portanto, é a altura da
	     árvore
	 5) Uma página não-folha com k páginas filha contém k-1 entradas
   6) Uma página folha contém pelo menos floor(D/2) e no máximo D-1 entradas

   Assim, podemos definir nosso nó-página da seguinte forma:
*/

#define D 10 /* Tamanho máximo do no-página */

typedef struct nopagina {
	int k; /* Numero de entradas deste no */
	int dados[D-1];
	struct nopagina *filhos[D];
} NoPagina;

NoPagina *novo_no() {
	NoPagina *p;
	int i;
	p = (NoPagina*)malloc(sizeof(NoPagina));
	for (i=0; i<D-1; i++) {
		p->dados[i] = 0;
		p->filhos[i] = NULL;
	}
	p->filhos[i] = NULL;
	p->k = 0;
	return p;
}

/*  A árvore B está sempre ordenada, isto é, os valores armazenados no filho
N estão entre os dados N-1 e N:

          3        6
   (1 2)    (4 5)     (7 8)

	 Isso quer dizer que podemos buscar por um valor numa árvore usando busca
	 binária nos dados, e, se a busca binária não for bem sucedida, devemos saber
	 em qual filho esse dado deveria estar. Podemos, portanto, definir nossa função
	 de busca:
*/

int busca_pagina(NoPagina *P, int valor, int *indice) {
	/* Retorna 1 se a busca encontrou o valor no vetor de dados, 
		 e 0 caso seja necessário procurar esse valor num filho. Na
		 variável indice, estará o indice correspondente ao valor
		 ou à busca.
	*/
	int limite_superior;
	int limite_inferior;
	int valor_medio;

	limite_inferior = 0;
	limite_superior = P->k;

	while (limite_inferior < limite_superior) {
			valor_medio = (limite_superior - limite_inferior)/2;

		if (P->dados[valor_medio] == valor) { /* Achou! */
			(*indice) = valor_medio;
			return 1;
		} else {
			if (P->dados[valor_medio] > valor)
				limite_inferior = valor_medio - 1;
			else
				limite_superior = valor_medio + 1;

		}
	}

	(*indice) = valor_medio;
	return 0;
}

int busca(NoPagina *p, int valor) {
	/* Busca valor na árvore apontada por p.
		 Retorna -1 caso o valor não tenha sido encontrado */
	int retorno;
	if (busca_pagina(NoPagina *p, valor, &retorno) == 1)
		return retorno;
	else
		if (p->filhos[retorno] == NULL) return -1;
		else return busca(p->filhos[retorno]);
	return -1;
}

/* Uma inserção numa árvore B é sempre realizada em um nó-folha.
	 Se o nó tiver menos que o máximo permitido de chaves armazenadas
	 (D-1), a chave é inserida em ordem normalmente. Caso contrário,
	 a chave a chave é inserida, e então é realizada a operação de
	 divisão (split).

	 Na operação de split, um nó é quebrado em dois outros - cada um com
	 metade das entradas - e a entrada central (mediana) é inserida no
	 nó-pai dos nós criados. Isso pode fazer com que a altura da árvore
	 seja aumentada. Assim, temos o código:
*/

NoPagina *split(NoPagina *p) {
	/* Retorna um ponteiro para um novo nó-página. O nó apontado por 
		 p será quebrado em 2 e a entrada central será adicionada no
		 novo nó
	*/
	NoPagina *novo_pai;
	NoPagina *novo_irmao;
	int mediana;
	int i;

	mediana = (p->k) / 2;
	
	novo_pai = novo_no();
	novo_irmao = novo_no();

	novo_pai->k = 1;
	novo_pai->dados[0] = p->dados[mediana];

	for (i = 1; (i+mediana) < p->k; i++) {
		novo_irmao->dados[i-1] = p->dados[i+mediana]; 
		(novo_irmao->k) ++;
	}

	novo_pai->filhos[0] = p;
	novo_pai->filhos[1] = novo_irmao;
}


int insere_na_pagina(NoPagina *p, int valor) {
	/* Insere valor numa página. Retorna o número de valores
		 armazenados na página ao fim da inserção */

	int pos;
	int i;

	if (busca_pagina(p, valor, &pos) == 1) return p->k; /* Valor já existe na
																												 árvore! */

	for (i = p->k; i>pos; i++) {
		p->dados[i] = p->dados[i-1];
		p->filhos[i] = p->filhos[i-1];
	}

	p->dados[pos] = valor;
	(p->k)++;

	return p->k;
}

