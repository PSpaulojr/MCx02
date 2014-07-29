/* Recursão

	 Recursão é uma técnica de programação na qual uma função faz uma chamada
	 a si mesma. Isso permite uma estratégia de pensamento semelhante à indução.
	 Nesse caso, parte-se de uma solução simples para um caso inicial (chamado
	 caso-base), e, à partir dele, mostra-se como se calcular o caso N+1.

	 A indução matemática pode ser utilizada para definir, por exemplo, a função
	 fatorial. Para se calcular fatorial(N), basta multiplicar fatorial(N-1)
	 por N. Porém, sabemos de antemão que fatorial(1) é igual a 1; assim, temos
	 a seguinte definição:

	 fatorial(N) =
			1, se N == 1
	    fatorial(N-1) * N, se N > 1

   Essa definição pode ser escrita imediatamente em C, na forma:
	 int fatorial(int N) {
	   if (N==1) return 1;
		 else return fatorial(N-1)*N;
	 }

	 Um outro exemplo de definição numérica recursiva serve para o cálculo da
	 série de Fibonacci. Ela é definida da seguinte forma:
	 fibonacci (N) =
	     1, se (N == 1) ou (N == 2)
			 fibonacci(N-1) + fibonacci(N-2) caso N > 2

	 E, assim, imediatamente temos:
	 int fibonacci(N) {
	    if (N <= 2) return 1;
			else return fibonacci(N-1) + fibonacci(N-2);
	 }

	 A importância da recursão é reduzir o problema atual para problemas sucessivamente
	 menores, mais fáceis de resolver. O problema mais fácil de se resolver é chamado 
	 caso-base, que, em nossos exemplos, é encontrado nas chamadas fatorial(1), fibonacci(1)
	 e fibonacci(2). De forma geral, existe um número limitado de casos-base, já que esses
	 são problemas simples que podemos resolver facilmente.

	 A chamada recursiva informa ao programa como que, sucessivamente, um problema maior
	 pode ser resolvido em termos de um caso base. Assim, temos uma estrutura básica de
	 função recursiva:
	 * Se o problema é simples, retorne a solução simples conhecida
	 * Caso contrário, dê um passo na direção de tornar o problema mais simples,
	   tome a solução e modifique de um passo.

	 Uma aplicação clássica da recursão é na solução do problema das Torres de Hanoi. Nesse
	 problema, há 3 torres (que chamaremos de A, B e C), sendo que na torre A existem N discos,
	 tal que um disco nunca está acima de um disco maior que ele (ou seja, os discos estão ordenados
	 do maior para o menor, de baixo para cima). O objetivo do problema é mover todos os discos
	 para a torre B, respeitando a restrição de que um disco maior nunca pode estar acima de um
	 disco menor.

	 Veja, se houvesse apenas um disco na torre A, bastaria move-lo para a torre B e o problema
	 estaria resolvido. Porém, sobre esse disco, ainda existem N-1 discos, que devem ser movidos
	 para a torre C para permitir o movimento simples que mencionamos acima. Depois disso,
	 devemos mover todos os discos que estão na torre C para a torre B, e, portanto, nossa solução
	 terá a forma:
	 hanoi(a, b, c, N) - move N discos da torre a para a torre b, usando a torre c como apoio
	    hanoi(a, c, b, N-1)
      mover(a, b)
      hanoi(c, b, a, N-1)

   Não queremos fazer nada especial com nossa solução, apenas imprimi-la na tela. Assim, podemos
	 escrever nossa chamada em C:
	 void hanoi(int a, int b, int c, int N) {
	    if (N==1) printf("%d -> %d\n", a, b);
			else {
	      hanoi(a, c, b, N-1);
			  printf("%d -> %d\n", a, b);
			  hanoi(c, b, a, N-1);
			}
	 }
	 E assim, usando o pensamento indutivo, temos uma solução simples para um quebra-cabeças que
	 pode rapidamente se tornar bastante complicado.

	 Em chamadas recursivas, é preciso garantir que o caso-base seja alcançado sempre. Caso isso
	 não ocorra, as chamadas de função serão acumuladas no sistema, e rapidamente a memória
	 disponível para chamadas de funções acabará. Esse fenômeno, chamado de estouro de pilha
	 (stack overflow), tem causas semelhantes à de um loop cuja condição de parada nunca é
	 alcançada.

	 Uma outra técnica que é bastante usada em chamadas recursivas é utilizar passagens
	 de variáveis por referências. Essa técnica é importante porque permite que mais
	 de um valor seja retornado de uma chamada recursiva, o que permite avaliar
	 diferentes parâmetros sobre essa chamada. No nosso programa-exemplo, incorporamos
	 uma passagem de variável por referência para contar as jogadas que serão realizadas
	 no problema das Torres de Hanoi.
*/

#include <stdio.h>

int fatorial(int N) {
	int f;
	printf("Entrei em fatorial(%d)\n", N);
	if (N==1) {
		printf("Retornando fatorial(1) = 1\n");
		return 1;
	} else {
		f = fatorial(N-1) * N;
		printf("Retornando fatorial(%d) = %d\n", N, f);
		return f;
	}
}

int fibonacci(int N) {
	int f;
	printf("Entrei em fibonacci(%d)\n", N);
	if (N<3) {
		printf("Retornando fibonacci(%d) = 1\n", N);
		return 1;
	}
	f = fibonacci(N-1)+fibonacci(N-2);
	printf("Retornando fibonacci(%d) = %d\n", N, f);
	return f;
}

void hanoi(int a, int b, int c, int N, int *jogada) {
	if (N==1) {
		(*jogada)++;
		printf("Jogada %d (base): %d -> %d\n", *jogada, a, b);
	}	else {
		hanoi(a, c, b, N-1, jogada);
		(*jogada)++;
		printf("Jogada %d: %d -> %d\n", *jogada, a, b);
		hanoi(c, b, a, N-1, jogada);
	}
}

int main() {
	int jogada;
	int i;
	printf("Chamadas na função fatorial(4):\n");
	i = fatorial(4);
	printf("Fim da chamada: %d\n", i);
	

	printf("\n\n\nTeste com fibonacci(5):\n");
	i = fibonacci(5);
	printf("Fim da chamada: %d\n", i);

	printf("\n\n\nProblema das Torres de Hanoi para N=3:\n");
	jogada = 0;
	hanoi(1, 2, 3, 3, &jogada);
	return 0;
}

/* Para rodar:
	 gcc -orecursao recursao.c
	 ./recursao
*/

/* Nos resultados da execucao fibonacci(5), veja como há diferentes chamadas
	 para fibonacci(3), e cada uma delas desencadeia uma série de outras
	 chamadas. Isso significa que um mesmo valor é calculado várias vezes.
	 Na versão iterativa do problema, verifica-se que esse resultado não é
	 re-calculado, mas sim salvo em uma variável, o que leva o resultado
	 a ser obtido mais rapidamente.
*/

/* Exercicios

	 1) Dado um número inteiro N, escreva uma função recursiva que define
	 quantas vezes ele pode ser divido por um outro número inteiro - M - sem
	 que o resultado seja fracionário.

	 2) Escreva uma função recursiva que calcula o MDC de dois números dados.
*/
