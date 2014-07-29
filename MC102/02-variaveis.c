/* Variaveis e atribuicoes

	 Em diversos processos, eh preciso que alguns dados sejam
	 armazenados para uso posterior. Quando fazemos uma conta
	 de adicao, por exemplo, eh preciso anotar as parcelas e
	 tambem eventuais processos de "vai um". Ao planejar uma
	 compra, eh interessante anotar as vantagens e custo de
	 cada uma das opcoes candidatas, e assim por diante.

	 No computador, a pratica comum de programacao eh pedir ao
	 sistema que nos reserve uma certa quantidade de memoria.
	 Esse "pedido" eh importante porque, como ja vimos, a memoria
	 eh um dispositivo fisico compartilhado por todos os programas
	 que rodam no computador, e eh importante que um programa
	 nao interfira no funcionamento de outro programa. Isso pode
	 ser comparado a varias pessoas compartilhando a mesma lousa
	 para fazer contas - se elas nao se organizarem de alguma forma,
	 uma vai atrapalhar bastante a outra.

	 A quantidade de memoria que sera reservada depende do tipo de
	 dados que sera armazenado na memoria. Em C, temos quatro tipos
	 de dados basicos:
	 char: armazena caracteres
	 int: armazena numeros inteiros
	 float: armazena numeros no formato ponto flutuante
	 double: armazena numeros no formato ponto flutuante com precisao dupla
	 (fonte: http://en.wikipedia.org/wiki/C_data_types)

	 Ao declarar a necessidade por um espaco em memoria, estamos
	 declarando uma variavel. A sintaxe para isso eh:
	 tipo nome_da_variavel;
	 por exemplo:
	 int contador;
	 que quer dizer:
	 preciso de um espaco em memoria para armazenar um int e vou me referir a
	 esse espaco com o rotulo "contador".

	 A partir dai, podemos atribuir valores as variaveis usando o operador =:
	 int a;
	 a = 20;
	 Ao atribuir um novo valor a uma variavel, o valor anterior estara perdido
	 para sempre:
	 a = 40;

	 Os tipos de dados definem quanto espaco uma variavel ocupa e tambem 
	 como serao representados os dados contidos nela. A seguir, vamos discutir
	 cada uma delas.

	 char
	 Esse tipo ocupa somente um byte (8 bits) na memoria. Eh utilizado para
	 armazenar caracteres, em geral seguindo a representacao de uma tabela
	 ascii. Um char, na verdade, eh um numero inteiro representado em 8 bits,
	 e segue a aritmetica de numeros inteiros.

	 int
	 A quantidade de espaco que int ocupa depende da maquina utilizada. Nesta
	 explicacao, vamos supor que sao 8 bits, mas isso nao eh uma regra geral
	 (maquinas modernas podem usar 16, 32, 64 ou mais bits).
	 Sabemos que existem 2^8 numeros que podem ser representados em 8 bits.
	 Dai, temos que o numero representado eh igual a:
	 (2^7)*bit7 + (2^6)*bit6 + ... + (2^0)*bit0
	 
	 Nessa representacao, uma soma eh feita normalmente usando o procedimento
	 em base 2.

	 Se utilizarmos um bit para representar o sinal do nosso inteiro, sobram
	 15 bits. Em nossa representacao, queremos que a soma de N com -N seja igual
	 a zero, por isso eh empregada uma representacao chamada 'complemento de 2'.
	 Nela, para obter o numero -N, invertemos todos os bits e somamos 1 ao
	 resultado. Como exemplo, vamos tomar a representacao do numero 5, em 4 bits:
	 0 1 0 1
	 Ao inverter todos os bits, temos:
	 1 0 1 0
	 E, somando 1:
	 1 0 1 1
	 Somando em binario 5 e -5 temos:
	 0 0 0 0
	 que eh o resultado que gostariamos de ter.
	 (fonte: http://en.wikipedia.org/wiki/Two's_complement)

	 A representacao inteira tem um efeito colateral chamado "overflow". Ele
	 ocorre quando o resultado de uma operacao aritmetica eh muito grande para
	 ser armazenado. Em nosso exemplo de 4 bits, por exemplo, o maximo valor
	 inteiro que pode ser armazenado eh (2^3)-1, ou seja, 7. Ao somar 5 com 3,
	 obtemos o seguinte comportamento:
	 0 1 0 1 +
   0 0 1 1
   -------
	 1 0 0 0
	 Assim, 5+3 resulta em -8.

	 Se necessario, eh possivel utilizar modificadores para especificar variaveis,
	 de forma a modificar seu comportamento. A sintaxe para isso eh:
	 [modificador] [tipo] [nome da variavel].
	 Alguns modificadores comuns sao:
	 unsigned: Especifica que a variavel nunca eh negativa. Isso permite que o bit
	 de sinal seja utilizado para representar numeros. Em nosso exemplo de
	 overflow acima, o resultado passaria a representar o numero 8, que eh o
	 resultado correto. Importante lembrar que isso nao torna a variavel
	 imune ao overflow nem aumenta sua capacidade de armazenamento, apenas
	 modifica os numeros que podem ser representados por ela.
	 short, long: Especifica que menos memoria ou mais memoria sera utilizada para
	 representar aquela variavel int especifica. A quantidade de memoria a mais ou
	 a menos empregada depende da maquina utilizada.

	 float e double (ver: http://en.wikipedia.org/wiki/IEEE_floating_point)
	 Numeros reais podem ser representados utilizando float e double. Nesta
	 representacao, o numero eh representado por uma mantissa e um expoente,
	 numa notacao semelhante a:
	 numero representado = mantissa * base^expoente
	 A base eh definida na maquina, e, geralmente, eh 2. A mantissa e o expoente
	 sao representados como inteiros com sinal.
	 Essa representacao leva a erros: numeros com muitos digitos significativos,
	 por exemplo, serao obrigatoriamente truncados e aproximados. Em casos
	 extremos, um numero pode ser representado como estritamente igual a zero,
	 num fenomeno chamado de underflow.

	 Numa soma com ponto flutuante, as mantissas das parcelas sao modificadas
	 de forma que o expoente se torne o mesmo, e entao a soma procede normalmente.
	 Isso pode levar a erros devidos a perda de digitos significativos em
	 numeros muito pequenos somados a numeros muito grandes.

	 Existem, hoje, diversos algoritmos para realizar essa soma de forma
	 eficiente e para corrigir erros de aproximacao (soma ordenada, soma
	 compensada, etc.), mas eles nao serao discutidos aqui.

	 Em operacoes entre tipos diferentes de dados, os tipos mais simples
	 sao implicitamente convertidos para tipos mais complexos, seguindo a
	 ordem char->int->float->double. Para tornar essa conversao de dados
	 explicita, utilizamos o cast:
	 int a, b;
	 float c;
	 a = (int)c/b;

	 É importante ressaltar que o operador = não significa igualdade, mas
	 sim atribuição. Isso quer dizer que o comando: 
	 a = b;
	 não faz a tornar-se igual a b, mas sim toma o valor de b e atribui a a.
	 Assim, são válidos os comandos:
	 a = a + 1;
	 a = a + b;
	 a = 2 * a;
	 

	 Na verdade, atribuições que tomam por base o valor atual da variável são
	 tão comuns que podem ser condensados. Assim, temos algumas equivalências:
	 a = a + b    |    a += b
	 a = a * b    |    a *= b
	 a = a - b    |    a -= b
	 a = a / b    |    a /= b
   a = a + 1    |    a++, ++a (abordaremos a diferença entre eles mais adiante)

*/

#include <stdio.h>

int main() {
	/* Neste programa, declararemos algumas variaveis:*/
	char c0, c1, c2, c3; /* C permite a declaracao de varias variaveis
													numa unica sequencia */
	int i0, i1, i2, i3;
	float f0, f1, f2, f3;

	/* Vamos atribuir alguns valores e escreve-los na tela */
	c0 = 'd';
	i0 = 50;
	f0 = 50.0;

	/* Atencao a sintaxe do printf para escrever variaveis na tela!
		 coloque um %c, %d ou %f para marcar, na string, as posicoes em que as
		 variaveis serao escritas; apos, declare quais serao essas variaveis que
		 serao escritas - na ordem que aparecem na string! */
	printf("Atribui os valores %c, %d e %f as minhas variaveis!\n", c0, i0, f0);
	
	/* Teste de aritmetica */
	printf("Aritmetica com int (+ - * / 3): %d, %d, %d, %d\n", i0+3, i0-3, i0*3, i0/3);
	printf("Aritmetica com float (+ - * / 3): %f, %f, %f, %f\n", f0+3, f0-3, f0*3, f0/3);
	printf("Aritmetica com char (+ - * / 3): %c, %c, %c, %c\n", c0+3, c0-3, c0*3, c0/3);

	/* Mas, lembre que char eh um tipo inteiro! Entao, o codigo seguinte eh valido: */
	printf("Aritmetica com char (+ - * / 3): %d, %d, %d, %d\n", c0+3, c0-3, c0*3, c0/3);

	/* Teste com tipos de dados diferentes */
	i0 = 163;
	f1 = i0/f0;
	i1 = i0/f0;
	f2 = i0/(int)f0;
	i2 = (float)i0/f0;
	f3 = 3*i0/f0;
	i3 = 3*i0/f0;
	printf("Teste de conversao de tipos de dados: %f, %d, %f, %d, %f, %d\n", f1, i1, f2, i2, f3, i3);
	
	/* Um operador importante em C e o resto da divisao: */
	printf("Tesde de divisao inteira de %d por 7: quociente=%d, resto=%d\n", i0, i0/7, i0%7);
	
	return 0;
}

/* Para rodar o programa:
> gcc -ovariaveis variaveis.c
> ./variaveis
*/

/* Algumas linguagens de programacao requerem tipagem  "forte",
	 ou seja, como em C, o tipo de dado a ser armazenado na variavel
	 eh explicitamente declarado pelo programador. Outras possuem
	 a caracteristica de tipagem "fraca", ou seja, o proprio programa
	 determina seu tipo de dado. Isso pode levar a estilos de codigo
	 diferentes: a tipagem forte permite otimizacoes em tempo de
	 compilacao, e a tipagem fraca pode tornar o programa mais robusto
	 a determinados erros
*/

/* Exercicios

	 1) Qual o valor das variaveis x, y, z e w apos o programa abaixo
	 ser executado?

	 int a;
	 int b;
	 float c;
	 int x;
	 int y;
	 float z;
	 float w;

	 a = 1;
	 b = 5;
	 c = 5.0;

	 x = a/b;
	 y = a/c;
	 z = a/b;
	 w = a/c;

*/


/* Proxima licao: condicionais.c */

