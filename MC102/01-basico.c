/* Estrutura basica de um programa em C.
   O texto entre barra-estrela e estrela-barra eh chamado
   comentario. Comentarios sao ignorados pelo compilador,
   mas podem ser importantes para a compreensao do codigo-fonte
   por outro humano.
   Neste codigo-fonte, mostrarei a estrutura basica de um programa
   em C e como utilizar o comando printf, que serve para imprimir
   textos na tela.
*/

/* O comando printf nao faz parte da linguagem C padrao, entao eh preciso
   adicionar ao nosso programa a biblioteca onde printf esta localizado.
   Para isso, utilizamos o #include. Ao indicar o caminho da biblioteca entre
   chaves, como esta abaixo, estamos informado ao compilador que a biblioteca
   esta no caminho de sistema. Se utilizarmos a forma #include "arquivo.h", eh
   preciso incluir o caminho (completo ou relativo) para o arquivo (util no caso
	 de bibliotecas proprias), e, caso o compilador nao encontre esse arquivo, 
	 passa a procurar no caminho do sistema. Entao, por convencao, use <> para
	 bibliotecas padrao e aspas para bibliotecas proprias.
Fonte: http://stackoverflow.com/questions/3162030/difference-between-angle-bracket-and-double-quotes-while-including-heade
*/
#include <stdio.h>

/* Todo programa em C tem a estrutura:
int main() {
  [programa]
  return 0;
}

Isso sera discutido mais tarde, em outra licao.
*/

int main() {
	/* printf("coisa a imprimir") imprime algo na tela.
		 Alguns caracteres especiais podem ser uteis para formatacao:
		 \n (newline) representa o fim de uma linha.
		 \t (tabulation) representa uma tabulacao.
		 \\ (barra invertida) imprime uma barra invertida.
	*/

	printf("Estou funcionando!\n");
	return 0;
}

/* Para executar este programa:
> gcc -obasico basico.c
> ./basico
 */

/* Proxima licao: variaveis.c */
