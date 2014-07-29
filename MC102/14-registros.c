/* Registros

	 Neste tópico, vamos trabalhar com o problema de representar
	 as características de um produto numa loja. Cada produto tem
	 um nome e um identificador único, que é o valor representado no código
	 de barras de sua embalagem. Além disso, cada produto tem um
	 preço diferente (que, por simplicidade, assumiremos que é
	 sempre um número inteiro) e uma quantidade em estoque.

	 Assim, para representar um produto, devemos utilizar um vetor de char
	 e três variáveis do tipo int:
	 char *nome;
	 int identificador;
	 int preco;
	 int estoque;

	 Porém, é possível perceber que essas três variáveis deveriam,
	 de alguma forma, ser representadas de uma forma compacta. Uma
	 função que trabalha com produtos, por exemplo, teria uma assinatura
	 muito longa, como:

	 int comprar_produto(char *nome, int identificador, int preco, int estoque, int n_compra);

	 e é fácil perceber como essa assinatura ficaria muito longa se mais
	 características do produto fossem utilizadas, como o endereço de seu 
	 fabricante ou sua data de validade.

	 Para representar blocos de informação que fazem sentido de estar
	 juntos, utilizam-se registros. Em C, registros são definidos na
	 forma de variáveis tipo struct. Uma struct deve primeiro ser definida,
	 e só então declarada:
*/

struct Produto {
	char nome[20]; /* Por simplicidade, declaramos o tamanho máximo do nome do produto */
	int identificador;
	int preco;
	int estoque;
};

struct Produto p;

/* Podemos declarar nossa primeira função que lida com o produto. Nesse
	 exemplo, a função deve verificar se o produto existe em estoque e deve
	 retornar 0 para não existe e 1 para existe. Note que utilizamos a
	 notação [estrutura].[chave] para acessar elementos individuais de uma
	 struct:
*/

int existe_em_estoque(struct Produto p) {
	if (p.estoque > 0) return 1;
	else return 0;
}


/* Note que, nesse caso, utilizamos a passagem por valor, o que nos
	 impossibilita de realizar modificações no produto. Se optarmos por
	 uma passagem por referência, estaremos utilizando um ponteiro para
	 structs Produto, e a notação para acessar valores passa a ser
	 [ponteiro_para_estrutura]->[chave]. Assim, são igualmente válidas
	 as chamadas:
	 struct Produto *p;
	 p->estoque = 0;
	 (*p).estoque = 0;
	
	 Agora, podemos declarar uma função que lida com o produto. Em nosso exemplo, 
	 queremos uma função que realiza compras. A função recebe como entrada uma
	 representação de um produto e realiza a compra de N unidade. O estoque é
	 abaixado e, caso a compra seja impossível, a função retorna -1; Caso seja
	 possível, retorna o valor total da compra.
*/

int comprar(struct Produto *p, int quantidade) {
	if (p->estoque > quantidade)
		return -1;
	else {
		p->estoque -= quantidade;
		return p->preco * quantidade;
	}
}

/* Ao se utilizar structs, é comum também utilizar a definição de tipos. O
	 comando typedef permite definir novos tipos de variáveis, o que permite
	 que a chamada struct seja omitida quando uma nova variável for declarada.
	 Assim, podemos declarar: */

typedef struct {
	char nome[20];
	int identificador;
	int preco;
	int estoque;
} TipoProduto;

TipoProduto p2;

/* E, assim, a chamada para nossas função de compra pode ser trocada por: */
int comprar_com_tipo(TipoProduto *p, int quantidade) {
	if (p->estoque > quantidade)
		return -1;
	else {
		p->estoque -= quantidade;
		return p->preco * quantidade;
	}
}

/* Em adição aos registros, C também oferece suporte aos tipo enumerados. Esses
	 tipos são utilizados para representar dados que são claramente sequenciais,
	 mas cuja ordem é mais ligada à seu rótulo que a um número. Podemos, por exemplo,
	 utilizar o tipo enum para representar as cores do arco-íris, de forma que 
	 o rótulo VERMELHO é associado a 0, LARANJA a 1 e assim por diante:
*/

enum CORES {
	VERMELHO,
	LARANJA,
	AMARELO,
	VERDE,
	AZUL,
	ANIL,
	VIOLETA
};

/* Assim, podemos criar uma variável c1 para representar uma dessas cores: */
enum CORES c1;

/* Poderiamos fazer uma declaracao semelhante utilizando o typedef, como vimos acima: 
typedef enum {
	VERMELHO,
	LARANJA,
	AMARELO,
	VERDE,
	AZUL,
	ANIL,
	VIOLETA
} TipoCor; 

TipoCor c2;

   Isso não pode ser feito diretamente neste código fonte. O motivo é que, na primeira 
	 declaração, feita acima sem o typedef, o compilador já associou o rótulo VERMELHO a
	 0, LARANJA a 1 e assim por diante, e uma nova declaração do mesmo rótulo gera erro.
	 Opcionalmente, o valor inicial da associação pode ser mudado, utilizando
	 o operador =, como no exemplo abaixo - é possível, também, definir valores arbitrários para
	 cada um dos rótulos.
*/
typedef enum {
	DOMINGO = 1,
	SEGUNDA,
	TERCA,
	QUARTA,
	QUINTA,
	SEXTA,
	SABADO = 100
} TipoDiaDaSemana;

/* Os tipos enumerados, bem como outras structs, podem ser utilizados como membros
	 de structs. Em nosso programa-exemplo, vamos lidar com o problema
	 de calcular distâncias entre pontos. Para tal, representaremos pontos
	 como uma struct: */

typedef struct {
	float x;
	float y;
} TipoPontoCartesiano;

/* Note que é fácil definir uma função que imprime os pontos na tela
	 no formato (x, y): */
#include <stdio.h>
void imprime_ponto(TipoPontoCartesiano p1) {
	printf("(%f, %f)\n", p1.x, p1.y);
}

/* Vamos definir uma função distância que recebe duas referências para pontos
	 e calcula a distância entre eles: */
#include <math.h>

float distancia(TipoPontoCartesiano p1, TipoPontoCartesiano p2) {
	float dx;
	float dy;

	dx = (p1.x) - (p2.x);
	dy = (p1.y) - (p2.y);

	return sqrt(dx*dx + dy*dy); /* sqrt() esta definido no <math.h> */
}

/* A próxima função soma as coordenadas de dois pontos: */
TipoPontoCartesiano soma(TipoPontoCartesiano p1, TipoPontoCartesiano p2) {
	TipoPontoCartesiano s;
	s.x = p1.x + p2.x;
	s.y = p1.y + p2.y;
	return s;
}

/* Por fim, definiremos uma função que inverte as coordenadas x e y
	 de um ponto: */
void transpor(TipoPontoCartesiano *p) {
	float tmp;
	tmp = p->x;
	p->x = p->y;
	p->y = tmp;
}

int main() {
	TipoPontoCartesiano p1;
	TipoPontoCartesiano p2;	

	p1.x = 5.0;
	p1.y = 3.0;
	p2.x = 4.0;
	p2.y = 5.0;

	printf("Pontos para calcular:\n");
	imprime_ponto(p1);
	imprime_ponto(p2);

	printf("\nDistancia: %f\n", distancia(p1, p2));

	p1 = soma(p1, p2);
	transpor(&p2);
	printf("\n\nNovos pontos:\n");
	imprime_ponto(p1);
	imprime_ponto(p2);
	printf("\nDistancia: %f\n", distancia(p1, p2));

	return 0;
}

/* Para rodar:
	 ./gcc -oregistros 14-registros.c
	 ./registros
*/

/* Exercícios

	 1) Defina structs que podem representar:
	    a) Um local de interesse no planeta Terra
			b) Um ponto no espaço
			c) Um cliente de uma loja
			d) Espécies de seres vivos

	 2) Defina tipos enumerados para representar:
	    a) Tamanhos de camisetas
			b) Graus de parentesco
			c) Hierarquias de sua escola ou local de trabalho

	 3) Considere que um conjunto com N pontos é representado
	 em um vetor de structs do tipo PontoCartesiano:
	 #define MAX_PONTOS 100
	 TipoPontoCartesiano pontos[MAX_PONTOS];
	 Escreva uma função que calcula os índices dos dois pontos
	 que são mais próximos entre si.

	 4) Os tipos struct permitem que um vetor seja representado
	 junto de seu tamanho. Defina uma struct que representa um
	 vetor de inteiros junto de outras informações
	 pertinentes, na forma:
	 typedef struct {
     [seu código]
	 } MeuVetor;
	 e implemente as seguintes operações:

	 void ordenar(MeuVetor *v);
   void imprimir_todos_os_numeros(MeuVetor *v);
	 void somar_valor_a_todos(MeuVetor *v, int valor);

	 5) Considere o cenário de uma empresa de turismo que
	 vende pacotes de viagem. Ao todo, ela possui 3 diferentes
	 pacotes, sendo um deles para Angra dos Reis, outro para
	 Paris e, por fim, um para Nova Iorque. Cada um desses
	 pacotes tem um preço diferente, definido a priori (que
	 pode ser assumido como R$500, R$5000 e R$3500). Cada um
	 desses pacotes tem, inicialmente, 100 vagas. Implemente um sistema que:
	 a) Recebe pedidos de compras de pacotes. Se há vagas para
	 o pacote, o pedido é realizado com sucesso; caso contrário ele é ignorado.
	 b) Permite consultar a receita já recebida pela empresa até o momento
	 c) Permite consultar qual é o pacote de viagens mais popular
	 até o momento.
*/
