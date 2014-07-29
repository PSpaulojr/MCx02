/* Comandos de repetição

   Em determinadas situações, é interessante executar a mesma instrução várias
   vezes num mesmo programa. Queremos, é claro, especificar essa condição sem
	 ter que escrever várias vezes a instrução, o que pode ser bem pouco prático
	 caso queiramos alguns milhares (ou milhões? ou bilhões?) de repetições. Na
	 linguagem C, comandos repetidos são executados na forma de laços, ou loops.

	 A estrutura de um laço tem a seguinte semântica: enquanto acontecer uma
	 condição, execute estas instruções. Numa receita de comida, isso seria o
	 equivalente a determinar: "enquanto não sentir gosto de sal, adicione sal e
	 mexa bem". Na linguagem de programação, a condição é uma expressão Booleana,
	 e as instruções são comandos, como veremos a seguir.

	 O primeiro comando de repetição que estudaremos é o while(). Sua sintaxe
	 é como segue:

	 [parte anterior do programa]
	 while (condição) {
	   instrução1;
		 instrução2;
		 ...
		 instruçãoN;
	 }
	 [parte posterior do programa]

	 O fluxo de execução, nesse caso, vem normalmente da parte anterior do
	 programa. Ao chegar no comando while, caso a condição tenha sido cumprida,
	 o programa entra no laço e passa a executar as instruções 1 a N, e então
	 retorna à avaliação da condição. Caso a condição não seja obedecida, então
	 executar-se-á a parte posterior do programa.

	 Uma variação do while() é o do...while(), cuja sintaxe é:
	 [parte anterior do programa]
	 do {
	   instrução1;
		 instrução2;
		 ...
		 instruçãoN;
	 } while (condição);
	 [parte posterior do programa]

	 Nesse caso, o programa entra obrigatoriamente no laço, e somente após
	 executá-lo uma vez é que a condição será avaliada.

	 Por fim, há o for(), que funciona da seguinte forma:
	 [parte anterior do programa]
	 for (comando1, condição, comando2)
	   instrução1;
		 instrução2;
		 ...
		 instruçãoN;
	 }
	 [parte posterior do programa]

	 No laço for, o programa:
	 1: Executa o comando1,
	 2: Avalia a condição
	 3: Se a condição é verdadeira, executa o laço
	 4: Se a condição não é verdadeira, segue na parte posterior do programa
	 5: Ao fim do laço, executa o comando2
	 6: Volta para 2

	 Note que, se a condição do laço for sempre verdadeira, o programa nunca
	 vai parar de repetir as instruções. Esse fenômeno, que se chama Loop
	 Infinito, deve ser evitado pelo programador. Isso pode ser feito
	 colocando, no laço, uma instrução que altera a condição do loop - e,
	 no laço "for()", isso geralmente é feito no comando2.

	 Faremos um programa para calcular o fatorial de 5, demonstrando o 
	 uso do laço:
	 
	 ---
	 int i;
	 int f;
	 i = 5;
	 f = 1;
	 while (i>0) {
	    f = f * i;
			i = i - 1;
	 }
	 ---
	 Ao fim do programa, a variável f contém o fatorial de 5.

	 Podemos provar que o laço while() acima termina da seguinte forma:
	 - i é inicializado com 5
	 - i é decrementado de 1 a cada iteração
	 - i chegará a zero após 5 iterações, rejeitando a condição i>0

	 Programas bastante poderosos podem ser feitos aninhando-se laços
	 e combinando-os com estruturas de repetição.
*/


#include <stdio.h>

int main() {
	int i;
	int f;

	printf("Loops\n");
	

	printf("1) Contando de 1 a 15\n");
	i = 0;
	do {
		i = i + 1;
		printf("%d\t", i);
	} while (i<15);
	printf("\n");
	printf("\n");

	printf("2) Calculando fatorial de 5\n");
	i = 5;
	f = 1;
	while (i>0) {
		f = f * i;
		i = i - 1;
	}
	printf("O fatorial de 5 eh %d\n", f);
	printf("\n");

	printf("3) Imprimindo um tabuleiro de xadrez\n");
	printf("1 = casa branca, 0 = casa preta\n");
	for (i = 0; i < 8; i=i+1) {
		for (f = 0; f < 8; f=f+1) {
			printf("%d\t", ((i+f+1)%2)); /* Exercicio: explique porque (i+f+1)%2 */
		}
		printf("\n");
	}
	printf("\n");
	
	printf("4) Imprimindo uma piramide com 10 andares\n");
	for (i = 0; i < 10; i=i+1) { /* Para cada andar */
		for (f = 0; f <= i; f=f+1) { /* Execicio: porque precisamos de f<=i e nao
																		f<i ? */
			printf("* ");
		}
		printf("\n");
	}
	printf("---\n");

	return 0;
}

/* Para compilar/executar:
	 gcc -orepeticao repeticao.c
	 ./repeticao
*/

/* Proxima lição: algoritmos1.c */

/* Exercicios

	 1) Qual sera o valor de x apos a execucao do programa
	 abaixo?
	 int i;
	 int x;
	 for (i=0; i<10; i++)
	   x = i % 2;

	 2) O laço abaixo pára? Justifique.
	 int i;
	 i = 3;
	 while (i != 21) {
	   i *= 7;
	 }
*/
