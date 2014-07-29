/* Algoritmos e resolucao de problemas 

	 Neste ponto do curso, ja sabemos utilizar:
	 - Variáveis e operações matemáticas básicas
	 - Entrada e saída de dados
	 - Condicionais
	 - Laços de repetição

	 Nesta lição, vamos discutir alguns problemas que podem ser
	 resolvidos utilizando essas ferramentas.

	 PROBLEMA 1: GERANDO SÉRIES TEMPORAIS
	 Um problema que pode ser abordado é a geração de números
	 de acordo com uma regra que leva em conta o antecessor. Por
	 exemplo, queremos gerar números em uma série na qual um valor
	 é sempre a metade do antecessor. Então, temos:
	 novo_valor = antecessor / 2;
	 Porém, quando o novo valor é gerado e impresso na tela, passamos
	 a uma nova iteração na qual ele se torna o antecessor. Daí, temos:
	 antecessor = novo_valor;

	 Uma forma mais compacta de fazer essa mesma operação e atribuir
	 diretamente o novo valor à variável antecessor. Por uma questão
	 de semântica, vamos chamá-la de valor. Assim:
	 valor = valor / 2;

	 Para gerar 15 números dessa série, começando em 30, podemos usar
	 o seguinte programa:
	 int i = 0;
	 float valor = 30;
	 do {
			printf("%3.5f\t", valor);
			valor = valor / 2;
	    i = i+1;
	 } while (i<15);

	 É claro que esses valores vão rapidamente convergir para zero. Vamos
	 gerar, então, uma série um pouco mais interessante: sempre que o seu
	 valor cai para baixo de 5, seu valor é triplicado. Daí, temos:
	 int i = 0;
	 float valor = 30;
	 do {
			printf("%3.5f\t", valor);
			valor = valor / 2;
			if (valor < 5) {
			  valor = valor * 3;
			}
	    i = i+1;
	 } while (i<15);

	 Séries de valores no tempo podem ser utilizadas para diversos fins. Um
	 deles é simular como uma conta bancária se comportaria no tempo. Suponha
	 que o salário de uma pessoa é de 500 dinheiros, e cai em sua conta todo
	 dia 1 (por simplicidade, vamos assumir que todos os meses tem 30 dias).
	 No dia 10, ele tem que pagar as contas de agua, luz, etc., no valor de
	 150 Reais. Todos os dias, ele tem um gasto de 10 dinheiros com comida,
	 transporte, etc. Porem, ele eh um excelente investidor e lucra 0.1% ao
	 dia investindo todo o seu dinheiro. Em quantos meses essa pessoa chegara
	 a ter 1.000.000 de Reais?
	 
	 Embora esse problema tenha uma solução exata, calculável, vamos simular
	 todos os parâmetros e deixar que o computador simule a progressão de suas
	 contas. Vamos assumir que hoje é dia 1 de algum mês, e a pessoa não tem
	 qualquer dinheiro.

	 O restante desta lição vai acompanhar o código fonte, para que o código
	 possa ser discutido em maiores detalhes.
*/

#include <stdio.h>

int main() {
	printf("Problema do milionario:\n");
	int contar_dias = 0;
	int dia = 1;
	float conta = 0;
	while (conta < 1000000) {
		if (dia==1) { /* Salario */
			conta = conta + 500;
		}
		if (dia==5) { /* Contas */
			conta = conta - 150;
		}
		conta = conta - 10; /* Gasto diario */
		conta = conta * 1.001; /* Lucro */
		contar_dias = contar_dias + 1; /* Contador geral de dias */
		dia = dia + 1; /* Contador de dia do mes */
		if (dia == 31) { /* Virou o mes */
			dia = 1;
		}
	}
	printf("Em %d dias (%d meses, %d anos) ficarei milionario!\n",
				 contar_dias, contar_dias/30, contar_dias/365);
	printf("----\n");

	/* PROBLEMA 2 - ALGORITMOS MATEMÁTICOS
		 
		 Uma outra classe de problemas que pode ser resolvida já neste
		 ponto do curso envolve uma série de problemas matemáticos. Um
		 exemplo é o cálculo do Maior Divisor Comum (MDC) entre dois números.
		 O procedimento para tal é o seguinte:
		 Sejam dois números inteiros A e B;
		 Repita enquanto A!=B {
		 Se A > B, A recebe A-B;
		 Caso contrário, B recebe B-A;
		 }
		 MDC é A

		 Caso o MDC entre dois números seja 1, eles são ditos "primos entre si".
		 
		 O algoritmo abaixo reproduz, passo a passo, o que foi discutido acima.
	 */
	int A, B;
	A = 5340; B = 7233; /* Supõe-se que A e B são positivos */
	printf("MDC(%d, %d)=", A, B);
	while (A != B) {
		if (A > B) A = A - B;
		else B = B - A; /* Exercício: neste loop, como sabemos que A e B
											 nunca se tornarão nulos ou negativos?
											 Resposta: a condição do loop mostra que A e B
											 são sempre diferentes. Além disso, sempre subtraímos
											 o menor do maior (uma operação positiva). Assim,
											 ambos nunca ficam nulos nem negativos.
										*/
	}
	printf("%d\n", A);
	if (A==1) printf("Primos entre si!\n");
	printf("----\n");

	/* Seguindo uma logica parecida, podemos verificar se um numero A é
		 primo. A condição para isso é que ele não seja divisível por
		 nenhum outro número que não seja ele mesmo ou 1 */
	A = 7; B = 2;
	while ( ((A % B) != 0) &&
					(B < A) ) {
		B = B + 1;
	}
	/* Veja que nosso loop tem duas condições de saída, combinadas por um
		 operador AND lógico. O resto da divisão de A e B deve ser diferente
		 de zero e B deve ser menor que A. Então, se B for igual a A, é porque
		 a condição quebrada foi a segunda, e, portanto, todos os outros
		 números candidatos já foram testados, e, assim, A número é primo.
	*/
	if (B == A) {
		printf("%d eh primo!\n", A);
	} else {
		printf("%d eh divisor de %d\n", B, A);
	}
	printf("----\n");

	/* Um problema interessante que podemos lidar é a inversão dos algarismos
	 de um inteiro. Por exemplo, queremos que a entrada 4325 seja transformada
	em 5234. Um possível algoritmo que faz essa tarefa é:
	1) A variável A conterá o número de origem, a variável B conterá o destino 
	2) A%10 contém o algarismo das unidades de A; A/10 é A sem o algarismo das unidades;
	B * 10 é B com todos os algarismos deslocados para a esquerda.
	3) Então, para cada iteração, fazemos: B = (B*10) + (A%10) e A = A/10
	4) A condição de parada é não restarem algarismos, ou seja, A = 0 */
	A = 4325;
	B = 0;
	printf("Vou inverter %d: ", A);
	while (A > 0) {
		B = (B*10) + (A%10);
		A = A/10;
	}
	printf("%d\n", B);
	printf("----\n");

	return 0;
}

/* Para compilar e executar:
	 ./gcc -oalgoritmos1 algoritmos1.c
	 ./algoritmos1
*/

/* Exercicios

	 1) Escreva uma função que retorna o número de divisores inteiros
	 que um valor inteiro X, recebido como entrada, possui.

	 2) Escreva uma função que calcula N!, para algum N dado.

	 3) A série de Fibonacci é definida da seguinte forma:
	 fibo(1) = 1
	 fibo(2) = 1
	 fibo(n) = fibo(n-1) + fibo(n-2), para n >= 3
	 Escreva uma função que imprime os N primeiros elementos da
	 série de Fibonacci.
*/
