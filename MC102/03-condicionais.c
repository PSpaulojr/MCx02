/* Comandos condicionais

	 Um comando condicional, ou expressão condicional, ou estrutura condicional,
	 é aquela que causa no fluxo de execução de um programa um desvio que depende
	 de uma condição específica. Essa condição, de forma geral, é escrita na
	 forma: se acontece algo, então faça x, caso contrário faça y. Comandos
	 condicionais permitem que o programa avalie condições e reaja a elas de forma
	 apropriada.
	 fonte: http://en.wikipedia.org/wiki/Conditional_(computer_programming)

	 Uma condição é sempre apresentada na forma de uma *expressão Booleana*. Uma
	 expressão desse tipo, ao ser computada, resulta sempre em valores verdadeiro
	 (true) ou falso (false). Apesar disso, os operandos que constituem uma
	 expressão Booleana não precisam assumir somente esses valores.
	 fonte:http://en.wikipedia.org/wiki/Boolean_expression

	 Os operadores que podem ser utilizados em uma expressão Booleana são
	 definidos em uma tabela-verdade. Os principais estão mostrados abaixo:
	 EXPRESSÃO    |    RESULTADO É TRUE SE...
   ----------------------------------------------------------------
	 A == B       |    A é igual a B
	 A != B       |    A é diferente de B
   A && B       |    A e B são verdadeiros (AND lógico)
   A || B       |    A é verdadeiro e/ou B é verdadeiro (OR lógico)
	 !A           |    A é false
   A >  B       |    A é maior que B
   A <  A       |    A é menor que B
   A >= B       |    A é maior ou igual a B
   A <= B       |    A é menor ou igual a B
   ------------------------------------------------------------------
	 fonte: http://en.wikipedia.org/wiki/Operators_in_C_and_C%2B%2B

	 Em C, a forma mais usual de se escrever um comando condicional é através
	 do comando if, cuja sintaxe é a seguinte:
	 if (condição) {
	   comandos_se_condição_é_true;
	 }
	 Opcionalmente, é possível explicitar um bloco else {}, que contém comandos
	 que serão executados se a condição for false. Se esse bloco não for
	 explicitado, o programa simplesmente "pula" o bloco if {} caso a condição
	 não seja avaliada como verdadeira.

	 Para se considerar muitas possibilidades de condições, é comum utilizar-se
	 o comando switch. Os dois blocos abaixo executarão os mesmos comandos:
	 POSSIBILIDADE 1:
	 if (a == 1) {
	   comando1
	 }
	 if (a == 2) {
	   comando2
	 } 
	 if (a == 3) {
	   comando3
	 }
	 POSSIBILIDADE 2:
	 switch (a) {
	   case 1:
		   comando1;
			 break;
	   case 2:
		   comando2;
			 break;
	   case 3:
		   comando3;
			 break;
	 }

	 O comando break; é utilizado porque, em C, a instrução "switch" é
	 implementada na forma de fall-through, ou seja, o programa pula para
	 a linha correspondente à condição true e então executa todas as instruções
	 daí por diante. O comando "break" força o fluxo de execução do programa
	 a sair do laço atual.

	 O switch também oferece suporte a um comando padrão que será executado
	 se nenhuma das condições for confirmada. Para isso, utiliza-se a instrução
	 default, como mostrado abaixo:
	 switch (a) {
	   case 1:
		   comando1;
			 break;
	   case 2:
		   comando2;
			 break;
	   default:
		   comando_default;
			 break;
	 }

*/


/* O programa abaixo demonstra varios condicionais. Antes de executa-lo, 
	 leia o codigo-fonte e tente descobrir o que sera impresso na tela.
*/

#include <stdio.h>

int main() {
	int a, b, c; /* Vamos utilizar estas variaveis para fazer testes */
	float x, y, z; /* Tambem vamos testar coisas com estas variaveis */

	printf("Comparacao - int com int\n");
	a = 0;
	if (0 == 0) printf("0 == 0\n");
	if (a == 0) printf("a == 0\n");
	if (a == 1) printf("a == 1\n");
	printf("\n");

	printf("Comparacao - int com float\n");
	x = 0.0;
	y = 0.5;
	if (0.0 == 0.0) printf("0.0 == 0.0\n");
	if (x == 0.0) printf("x == 0.0\n");
	if (a == x) printf("0 == 0.0\n");
	if (a == y) printf("0 == 0.5\n");
	printf("\n");

	printf("Operadores unarios\n");
	b = 1;
	c = 2;
	z = 2.0;
	if (a) printf("a avalia true\n");
	if (b) printf("b avalia true\n");
	if (c) printf("c avalia true\n");
	if (x) printf("y avalia true\n");
	if (y) printf("y avalia true\n");
	if (z) printf("z avalia true\n");

	if (!a) printf("!a avalia true\n");
	if (!b) printf("!b avalia true\n");
	if (!b) printf("!c avalia true\n");
	if (!x) printf("!x avalia true\n");
	if (!y) printf("!y avalia true\n");
	if (!z) printf("!z avalia true\n");
	printf("\n");

	printf("Multiplas condicoes\n");
	if ( (a == b) || (x < y) ) printf("Teste 1\n");
	if ( (a == b) && (x < y) ) printf("Teste 2\n");


	printf("Switch - demonstrando o fall-through\n");
	printf("Sem break:\n");
	switch (a) {
	case 0:
		printf("Case a==0\n");
	case 1:
		printf("Case a==1\n");
	case 2:
		printf("Case a==2\n");
	default:
		printf("Caso contrario\n");
	}
	printf("Com break:\n");
	switch (a) {
	case 0:
		printf("Case a==0\n");
		break;
	case 1:
		printf("Case a==1\n");
		break;
	case 2:
		printf("Case a==2\n");
		break;
	default:
		printf("Caso contrario\n");
		break;
	}

	printf("\n");
	printf("Operador ?\n");
	/* Uma outra forma de expressar condicoes eh atraves do operador ?, 
	 que, por ser um operador, pode ser usado dentro de expressoes. O
	 operador eh usado da seguinte forma:
	 condicao?caso_sim:caso_nao;
	*/

	(a==0) ? printf("a==0\n") : printf("a!=0\n");

	/* Desafio: o que sera impresso na tela? */
  printf("Resultado: %d\n", (a == 1) ? 20: 30 );

	return 0;
}

/* Para rodar o programa:
> gcc -ocondicionais condicionais.c
> ./condicionais
*/

/* Da execucao desse programa, podemos verificar que:
1) Qualquer expressao numerica diferente de zero avalia para true
2) Ao avaliar comparacoes, int se converte para float
3) A instrucao switch eh bastante util, embora possa ser mais dificil de usar
4) Operadores logicos sao uteis para avaliar diferentes condicoes ao mesmo tempo
*/

/* Proxima licao: entradas_saidas.c */

/* Exercícios

	 1) O que será impresso na tela no programa abaixo?
	 #include <stdio.h>
	 if (50 == 50.0) printf("Cond 1\n");
	 if (50 == (int)50.8) printf("Cond 2\n");
	 if (50 > 0.50) printf("Cond 3\n");
	 if ((0 && 1) == 0) printf("Cond 4\n");
	 if ((0 || 1) == 1) printf("Cond 5\n");

	 2) Escreva um programa que lê um número na entrada
	 e imprime, na saída padrão, se esse número é par ou
	 ímpar.

	 3) Um sistema de alarme avisa se o nível de água
	 de um reservatório está abaixo de um determinado nível.
	 Escreva um programa que recebe, na entrada, um número inteiro
	 entre 0 e 100 que representa o nível de água do reservatório
	 e implementa os seguintes alarmes:
	 a) Emergência de seca, caso o nível esteja abaixo de 5%,
	 b) Alerta de seca, caso o nível esteja abaixo de 15%,
	 c) Alerta de transbordar, caso o nível esteja acima de 90%
	 d) Emergência de transbordar, caso o nível esteja acima de 95%
	 e) Nível OK, caso nenhum outro alarme seja disparado
	 Lembre-se que apenas o alarme mais forte deve ser disparado a
	 cada caso.
*/
