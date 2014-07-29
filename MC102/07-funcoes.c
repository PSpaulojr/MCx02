/* Funções e procedimentos

	 Em determinadas tarefas, há instruções que se aplicam a
	 diversas partes. Um exemplo na vida cotidian é engatar
	 marchas em um carro: executa-se o mesmo procedimento,
	 variando-se a marcha que será engatada; apesar disso,
	 "trocar para a marcha N" envolve um conjunto único
	 de instruções. Se desejarmos sistematizar outros processsos
	 cotidianos, poderemos reduzi-lo a diferentes níveis de
	 abstração: "chutar uma bola para um alvo" significa "escolher
	 o alvo, mirar, verificar posição da bola, estimar força e 
	 executar o chute", o que, por sua vez, pode ser explicado
	 como uma série de ajustes musculares e avaliações da imagem
	 que vemos nos olhos, que pode ser explicado como um
	 intrínseco processo químico, e assim por diante.

	 Na linguagem C, esse processo de abstração é realizado através
	 do uso de funções e procedimentos.

	 Um procedimento, como já explicado, é um conjunto de instruções
	 que pode ser executado como um bloco. Pode ser que, em diferentes
	 situações, desejemos imprimir uma certa mensagem na tela. Em C, o
	 código-fonte para declarar esse procedimento é como segue:
	 ---
	 void procedimento () {
		 printf("Ola, mundo! Eu funciono!\n");
	 }
	 ---
	 Esse código deve aparecer ANTES da declaração de int main(), e então,
	 sempre que o comando:
	 procedimento();
	 for chamado, as instruções relacionadas são executadas, e a mensagem
	 será impressa.

	 Fica aqui evidenciada a primeira utilidade de um procedimento: o re-uso de
	 código. Se quisermos trocar a mensagem que será exibida, não será necessário
	 varrer todo o código-fonte buscando por pontos em que ela é impressa: basta
	 encontrar o procedimento que a imprime e mudar apenas uma linha do código.

	 Um procedimento pode receber, como entrada, um conjunto de valores. Eles são
	 chamados de parâmetros. Eles permitem que um procedimento execute conjuntos
	 de instruções cujos detalhes serão explicados pelos parâmetros. Os parâmetros
	 são variáveis com tipos determinados, explicitadas no cabeçalho da declaração
	 na forma:
	 void procedimento2(int n, float f) {
	   ... código ...
	 }
	 Nesse caso, o procedimento2 recebe como entrada um int e um float.

	 O procedimento "enxerga" somente as variáveis que lhe são passadas como
	 parâmetros e as que são declaradas em seu interior. Assim, se uma variável
	 é declarada num procedimento, aquela declaração "só vale" para aquele
	 trecho de código. Isso se chama "escopo" de variáveis, e permite que
	 uma variável (por exemplo int i) seja declarada no interior de um
	 procedimento, mesmo que haja um int i rodando na função principal.

	 Ao fim da execução da sub-rotina (função ou procedimento), a memória alocada
	 é devolvida ao sistema. Assim, os dados armazenados em variáveis declaradas
	 no interior da sub-rotina são perdidos. Essa propriedade também faz parte da
	 definição de "escopo".

	 Porém, pode ser que queiramos utilizar algum cálculo realizado durante
	 o procedimento - por exemplo, o cálculo de um MMC. Um procedimento
	 que retorna um valor é chamado de função, e é declarado substituindo
	 o "void" pelo tipo de valor que será retornado - por exemplo, int
	 ou float. Ao fim da função, deve haver uma chamada para a instrução
	 return [algo]; que indica o que será retornado pela função.
	 
	 Assim, podemos escrever:
	 int dobro(int i) {
	   return i*2;
	 }
	 
	 Sempre que dobro(i) for chamado, o programa calcula i*2 e retorna esse
	 valor. Note que a função poderá ser chamada em qualquer lugar que
	 um int poderia ter sido empregado (o programa-exemplo traz uma
	 aplicação disso).

	 Fica, assim, claro que main() é uma função, definida conforme as regras
	 de sintaxe do C. Também, é importante perceber que um
	 procedimento é somente uma função que não retorna nada (ou seja, retorna
	 void).

	 Por fim, é importante discutir o conceito de passagem por valor e passagem
	 por referencia. Quando um parâmetro é passado a uma função, o programa
	 cria uma cópia desse parâmetro, que será visto pela função, de forma que
	 modificar a cópia não causa modificação na variável original. A isso, se chama
	 passagem por valor.

	 É possivel, porém, que se deseje alterar as variáveis que foram
	 passadas como parâmetro. Nesse caso, devemos passar uma referência à
	 variável - que nada mais é que um valor que indica a posição da memória
	 onde a variável está contida. Para isso, precisamos conhecer os seguintes
	 modificadores:

	 Ponteiro:
	 int *i;
	 Nesse caso, i é um ponteiro para uma posição de memória onde estará um int.
	 Ao utilizar (*i), modifica-se o que quer que esteja naquela posição de
	 memória.

	 Endereço:
	 int &i;
	 Nesse caso, i é o endereço de uma posição de memória, que pode ser usado
	 para descobrir qual é o ponteiro que deve ser usado para encontra a variável
	 i.

	 Assim, temos que o programa:
	 --
	 int i;
	 int *j;
	 j = &i;
	 (*j) = 5;
	 printf("%d\n", i);
	 --
	 imprimirá "5" na tela.

	 O uso de referências permite que um procedimento ou função modifique o
	 parâmetro no escopo do programa principal. Daí, podemos ter um procedimento
	 que incrementa diretamente um inteiro:
	 ---
	 void incrementa(int *i) {
	  (*i) = (*i) + 1;
	 }
	 ---
	 A diferença de comportamento do programa para passagens por valor e 
	 passagens por referência fica evidenciada no programa-exemplo.

	 Uma importante função que tem passagem por valor é o operador ++, que
	 incrementa uma variável. Porém, dependendo da precedência do operador,
	 um valor diferente é retornado pela função:
	 i++   =>  retorna o valor de i e depois incrementa a variável
	 ++i   =>  incrementa a variável e então retorna o novo valor
	 Assim, temos:
	 int a, b, c;
	 a = 0;
	 b = a++;
	 c = ++a;
	 Ao fim dessa execução, a==2, b==0 e c==2.

*/

#include <stdio.h>

void procedimento() {
	printf("Ola, mundo! Eu sou um procedimento!\n");
}

void procedimentoN(int N) {
	printf("Ola, mundo! Eu sou o procedimento %d!\n", N);
}

void procedimentoEscopo(int N) {
	int i;
	i = N + 1;
	printf("Sucessor de %d: %d\n", N, i);
}

int dobro(int i) {
	return (i*2);
}

void procedimento_ref(int *N, int M) {
	(*N) = (*N) + 1;
	M = M + 1;
}

int main() {
	int i, j;
	printf("Procedimentos:\n");
	procedimento();
	procedimentoN(2);
	i = 3;
	procedimentoN(i);
	printf("----\n");
	printf("Escopo:\n");
	printf("i=%d (main)\n", i);
	procedimentoEscopo(i);
	printf("i=%d (main)\n", i);
	printf("----\n");
	printf("Funcoes:\n");
	printf("i=%d, dobro=%d\n", i, dobro(i));
	i = dobro(i);
	printf("i=%d, dobro=%d\n", i, dobro(i));
	printf("----\n");
	i = 0;
	j = 0;
	printf("Passagem por referência:\n");
	printf("i=%d, j=%d\n", i, j);
	procedimento_ref(&i, j);
	printf("i=%d, j=%d\n", i, j);

	return 0;
}

/* Para rodar:
	 gcc -ofuncoes funcoes.c
	 ./funcoes
*/

/* Por uma questão de segurança, a maior parte dos sistemas operacionais mantém
	 uma "lista" das posições de memória que cada programa é autorizado a
	 acessar. Se um programa tenta acessar uma posição não-autorizada, o sistema
	 pára sua execução, alegando "falha de segmentação" (segmentation fault). No
	 Windows, esse tipo de erro dá origem ao "esse programa executou uma operação
	 ilegal e será fechado".
 */
