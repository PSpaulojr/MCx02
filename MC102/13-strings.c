/* Cadeias de caracteres

	 Cadeias de caracteres, ou strings, nada mais são que
	 vetores de elementos do tipo char. Em C, cadeias de caracteres
	 são finalizadas por um caractere de terminação nulo (\0). Assim, podemos
	 definir uma função que imprime cadeias de caracteres sem que
	 seu tamanho seja explicitamente passado como parametro:
*/

#include <stdio.h>

void imprime_string(char *c) {
	/* Esta função é semelhante a printf("%s", c); */
	int i;
	i = 0;
	while (c[i] != '\0') {
		printf("%c", c[i]);
		i++;
	}
}

/* Quando colocamos o valor de uma atribuição do tipo char
	 entre aspas simples, o compilador transforma esse valor utilizando
	 uma tabela chamada ASCII (American Standard Code for Information
	 Interchange). Essa tabela relaciona caracteres legíveis
	 com valores numéricos, sendo que os códigos relacionados
	 aos caracteres a-z estão em um bloco, A-Z estão em outro bloco
	 e 0-9 em outro bloco. Podemos utilizar a seguinte função para imprimir
	 a tabela ASCII:
*/

void imprime_tabela_ascii() {
	unsigned char i;
	for (i = 0; i < 255; i++)
		printf("%d\t%c\n", i, i);
}

/* É importante que fique claro que um char nada mais é que um 
	 inteiro sem sinal representado por um byte. Isso significa que
	 operações comuns a inteiros podem ser realizadas com variáveis
	 tipo char, como a subtração, a adição e a comparação por maior
	 ou menor. Utilizaremos isso para criar funções que verificam se
	 um caractere é maiúsculo ou minúsculo:
*/

int maiusculo_ou_minusculo(char c) {
	/* Retorna 1 se c é maiúsculo, retorna 0 caso seja minúsculo e -1
		 caso não seja uma letra */
	if ( ('A' <= c) && (c <= 'Z') ) return 1;
	if ( ('a' <= c) && (c <= 'z') ) return 0;
	return -1;
}

/* Podemos utilizar o mesmo tipo de aritmetica para converter
	 caracteres para maiúscula, na forma: */
char para_maiuscula(char c) {
	if ( maiusculo_ou_minusculo(c) == 0 )
		return (c-'a')+'A';
	else return c;
}

void string_para_maiuscula(char *c) {
	int i;
	i = 0;
	while (c[i] != '\0') {
		c[i] = para_maiuscula(c[i]);
		i++;
	}
}

/* As strings (cadeias de caracteres) são tão importantes que
	 a própria biblioteca padrão do C já vem com um conjunto
	 de funções para lidar com strings. Elas estão no arquivo <string.h>,
	 e contém diversas utilidades para lidar com strings, com
	 operações como concatenar, dividir ou copiar strings, entre
	 outras.

	 Uma importante funcionalidade relacionada a strings é converter
	 uma cadeia de caracteres para um número decimal. Assim, se
	 recebemos a string "1050", devemos converte-la para o número
	 inteiro 1050. Um possível algoritmo para converter strings
	 para inteiros é como segue:
*/
int string_para_inteiro(char *c) {
	int i;
	int acumulador;
	i = 0;
	acumulador = 0;
	while (c[i] != '\0') { 
		acumulador *= 10;
		acumulador += (c[i]-'0');
		i++;
	}
	return acumulador;
}


int main() {
	char meu_texto[] = "Vai, minha tristeza, e diz a ela que sem ela nao pode ser...";
	/*imprime_tabela_ascii();*/
	imprime_string(meu_texto);
	printf("\n%s\n", meu_texto);
	string_para_maiuscula(meu_texto);
	printf("%s\n", meu_texto);
	printf("%d\n", string_para_inteiro("0001050"));

	return 0;
}

/* Exercícios

	 1) Escreva uma função que detecta se uma string recebida
	 como entrada é palíndroma ou não.

	 2) Escreva uma função que conta as palavras de uma string
	 recebida como entrada.

	 3) Escreva uma função que recebe uma string contendo um número
	 em formato ponto flutuante e o converte para tipo float.

	 4) Uma string contém diversos números inteiros, escritos
	 em formato decimal. Escreva uma função que calcula a soma
	 de todos esses números.

	 5) CamelCase é o nome dado a um tipo de grafia no qual
	 várias palavras são escritas sem espaço entre elas, sendo
	 que cada nova palavra começa com letra maiúscula. Assim,
	 pode-se escrever RioDeJaneiro, por exemplo. O CamelCase é
	 usado como convenção de grafia de nomes em vários grupos
	 de programadores. Uma outra forma de escrever nomes é
	 utilizando todas as letras minúsculas, separando palavras
	 por um caractere underline ('_'). Nesse caso, a grafia se
	 parece mais com rio_de_janeiro. Escreva funções que permitam
	 converter entre uma convenção de nomes e outra.
*/
