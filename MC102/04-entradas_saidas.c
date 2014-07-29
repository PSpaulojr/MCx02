/* Entradas e saídas

	 Nesta licao, discutiremos rapidamente como receber entradas do teclado
	 e retomaremos as instrucoes de saida.
	 
	 Na biblioteca stdio.h, estao definidas varias instrucoes de entradas e
	 saídas padrão do sistema. O programa-exemplo mostrará algumas formas
	 básicas de entradas e saídas, que serão utilizadas daqui para frente
	 no curso.

	 printf( ) - escreve mensagem na tela, como ja vimos antes.
	 scanf( ) - le mensagens da entrada padrao

	 Na sintaxe (veja o programa-exemplo):
	 - Use %d para decimais, %f para float e %c para char
	 - As variaveis-alvo vem depois da string inicial
	 - No scanf, preceda cada variavel com o operador & (ele sera discutido em
	 outra licao)
	 - Pode usar multiplas variaveis

	 A biblioteca stdio.h tambem define varias outras funcoes, mas elas nao
	 serao discutidas aqui. Uma referencia para a biblioteca pode ser encontrada
	 em:
	 http://pubs.opengroup.org/onlinepubs/7908799/xsh/stdio.h.html

*/

#include <stdio.h>

int main() {
	int a;
	float b;

	printf("Digite um inteiro e entao ENTER\n");
	scanf("%d", &a);
	printf("%d\n", a);

	printf("Digite um valor e depois um valor em ponto flutuante e ENTER\n");
	scanf("%d %f", &a, &b);
	printf("Voce digitou: %d %f\n", a, b);

	/* Nesse trecho, o que acontece se voce digitar primeiro o valor float
		 e depois o valor int?
	*/

	printf("Controle de saidas formatadas\n");
	b = 1.5;
	a = 15;
	printf("%4d %04d %1d\n", a, a, a);
	printf("%4.5f %04.05f %1.0f\n", b, b, b);

	printf("\nImprimindo em hexadecimal e octal\n");
	printf("%x %2x %04x\n", a, a, a);
	printf("%o %2o %04o\n", a, a, a);

	printf("FIM\n");
	return 0;
}

/* Uma experiencia bem interessante eh verificar o que acontece quando voce
	 digita valores invalidos como entrada para o comando scanf. Tente forcar
	 um scanf a receber valores de ponto flutuante ou mesmo caracteres. O que
	 acontece?
 */

/* Proxima licao: repeticao.c */

/* Exercicios

	 1) O que será impresso na tela no programa a seguir?
	 #include <stdio.h>
	 int i;
	 i = 16;
	 printf("0x%2x\t%5d\t%5d\n", i, i, i/2);

	 2) Escreva um programa que recebe o raio de uma esfera como entrada e
	 escreve, na saida, o volume dessa esfera.

	 3) Escreva um programa que recebe, como entrada, as medidas dos
	 lados de um paralelepipedo e escreve, na saída, o volume desse mesmo
	 paralelepípedo.

*/
