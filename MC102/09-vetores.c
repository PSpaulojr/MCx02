/* Vetores

	 Em diversas aplicações, temos a necessidade de armazenar dados
	 para N diversas ocorrências de um mesmo fenômeno. Vamos tomar
	 por exemplo o caso de medir várias vezes (durante o ano) a 
	 temperatura em uma floresta. É claramente impraticável declarar
	 365 variáveis do tipo float, e se referir a elas como:
	 float medicao_1_jan;
	 float medicao_2_jan;
	 ...
	 float medicao_31_dez;

	 Lembramos que uma variável é um rótulo dado a uma posição de
	 memória. Isso significa que, ao declarar uma variável, estamos
	 pedindo ao compilador que nos seja reservado um certo espaço
	 na memória, suficiente para guardar dados daquele tipo especificado.
	 Diante disso, a solução para o problema acima é reservar espaço
	 para N dados daquele tipo que especificamos - um vetor de dados.

	 Um vetor é declarado, em C, especificando-se entre [chaves] seu tamanho
	 e declarando-se seu tipo, como em:
	 int vetor_de_int[40];
	 float vetor_de_float[365];
	 char meu_vetor_de_char[100];

	 As posições de memória reservadas são enumeradas à partir do zero, e o
	 espaço reservado tem tantas posições quantas pedidas na declaração. Para
	 referir-se à primeira posição de vetor_de_int, utiliza-se:
	 vetor_de_int[0]
	 que será utilizado normalmente como uma variável tipo int. Assim, são válidos:
	 int A;
	 vetor_de_int[0] = 5;
	 A = vetor_de_int[0];
	 vetor_de_int[39] = A;
	 Note que o índice máximo que pode ser utilizado é igual ao número de posições
	 do vetor menos 1, já que começamos nossa contagem do zero.

	 Vetores permitem iterar entre todos os seus membros, utilizando uma variável
	 tipo int (ou unsigned int) como índice:
	 int i;
	 int meu_vetor[10];
	 for (i=0; i<10; i++)
	   printf("meu_vetor[%d] = %d\n", i, meu_vetor[i]);

	 Isso dá origem a um novo raciocínio sobre algoritmos, no qual lidamos com uma
	 quantidade muito maior de dados, e podemos realizar cálculos sobre eles. É 
	 importante observar, porém, que um vetor não contém, em si próprio, qualquer
	 informação sobre seu tamanho, de forma que este deverá ser armazenado numa
	 variável auxiliar. Assim, se queremos calcular a média dos valores de um vetor,
	 podemos utilizar a seguinte função:

	 float media(float dados[], int N) {
	    int i;
			float media;
			media = 0;
      for (i=0; i<N; i++)
			   media = media + dados[i];			
			media = media / N;
			return media;
   }


	 Note que a função que criamos é independente do número de valores recebidos
	 no vetor. Isso nos dá grande flexibilidade ao abordar problemas maiores, como
	 por exemplo processar estatísticas em dados governamentais. Veremos com isso
	 será importante mais adiante.

	 Um vetor, em C, é implementado como um ponteiro. Assim, as duas chamadas abaixo
	 são equivalentes:
	 float media(float dados[], int N);
	 float media(float *dados, int N);

	 Além disso, é possível declarar:
	 float meu_vetor[30];
	 float *meu_ponteiro;
	 meu_ponteiro = meu_vetor;
	 meu_ponteiro[3] = 1.5;
	 if (meu_vetor[3] == 1.5) printf("Igual!\n");

	 Por outro lado, uma variável tipo vetor tem um endereço fixo, de forma que
	 a instrução:
	 meu_vetor = meu_ponteiro;
	 é ilegal.

	 É importante perceber que a quantidade de dados alocados em um vetor é fixa,
	 de forma que é importante defini-lo como grande o suficiente para armazenar
	 todos os dados que vamos trabalhar, mas, ao mesmo tempo, não tão grande que
	 esgote a memória do computador. Pode ser uma boa ideia utilizar a instrução
	 #define para tornar mais fácil modificar o tamanho dos vetores utilizados, em
	 tempo de compilação:

	 #define TAMANHO_DO_VETOR 10
	 int meu_vetor[TAMANHO_DO_VETOR];

	 Uma vez que um vetor é um ponteiro, podemos utilizar a seguinte função para
	 ler elementos em um vetor:
	 void ler_vetor(int vetor[], int N) {
	    int i;
			int j;
			for (i=0; i<N; i++) {
			  scanf("%d", j);
				vetor[i] = j;
			}
	 }

	 Um vetor pode ser inicializado utilizando valores entre chaves, na forma:
	 int meu_vetor[] = {5, 4, 3, 6, 2, 3, 4, 1, 2};

	 Nesse caso, o tamanho do vetor alocado é automático. Assim, utilizando-se
	 a função sizeof(), pode-se determinar o número de posições do vetor:
	 int N;
	 N = sizeof(meu_vetor) / sizeof(meu_vetor[0]);
	 
	 No programa-exemplo, veremos como calcular o produto interno entre dois
	 vetores.
*/

#include <stdio.h>
#include <limits.h>

#define TAMANHO_VETOR 5

void imprimir_vetor(int vetor[], int N) {
	int i;
	for (i=0; i<N; i++) {
		printf("%d\t", vetor[i]);
	}
	printf("\n");
}


void ler_vetor(int vetor[], int N) {
	int i;
	int j;
	for (i=0; i<N; i++) {
		scanf("%d", &j);
		vetor[i] = j;
	}
}

int produto_interno(int vetor1[], int vetor2[], int N) {
	int p;
	int i;
	p = 0;
	for (i=0; i<N; i++)
		p = p + (vetor1[i] * vetor2[i]);

	return p;
}

int main() {
	int vetor_base[] = {1, 2, 6, 3, 5};
	int meu_vetor[TAMANHO_VETOR];
	ler_vetor(meu_vetor, TAMANHO_VETOR);
	printf("Vetor lido! Imprimindo...\n");
	imprimir_vetor(meu_vetor, TAMANHO_VETOR);
	printf("Produto interno com vetor-base: %d\n",
				 produto_interno(vetor_base, meu_vetor, TAMANHO_VETOR));

	return 0;
}

/* Para compilar:
	 ./gcc -ovetores vetores.c
	 ./vetores
*/

/* Exercícios:
	 1) As notas de uma aula estão armazenadas em um vetor de números
	 float. Calcule um histograma de notas que informa a quantidade
	 de alunos que tem notas menores ou iguais a 1, entre 1 e 2 e assim
	 por diante. Considere sempre os intervalos na forma: min < nota <= max.

	 2) Um vetor pol[] é usado para representar um polinômio p(x), de forma que o
	 valor armazenado em pol[n] é o coeficiente relacionado a x^n. Assim, defina
	 uma função para calcular o valor do polinômio, dada uma entrada x.

	 3) Um vetor ordenado é aquele em que um valor com índice menor nunca é maior que
	 um valor relacionado a um índice maior, ou seja, x[n]<=x[n+a], para todo a
	 maior ou igual a zero e menor que o número de posições alocadas do vetor.
	 Escreva uma função que determina se um vetor está ordenado e retorna 1 para
	 sim e 0 para não.
*/
