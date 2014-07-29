/* Arquivos

	 O computador, como vimos, lida com dados que
	 estão armazenados em sua memória principal (RAM). 
	 Essa memória, porém, é limitada (por ser cara) e
	 volátil, ou seja, é perdida se o computador for
	 desligado. Assim, é preciso utilizar dispositivos
	 de memória secundária, capazes de armazenar mais dados
	 e de forma persistente.

	 Tais dispositivos, hoje, são implementados principalmente
	 na forma de discos rígidos (Hard Disks - HDs), que têm 
	 algumas características importantes que devem ser consideradas:
	 - O acesso a dados é mais lento que na memória RAM
	 - Os dados gravados são persistentes
	 - Sua capacidade de armazenamento é maior

	 Sempre que nos referimos a arquivos, estamos nos referindo a
	 dados armazenados na memória secundária.

	 Arquivos são acessados, no sistema operacional, através de nomes,
	 que usualmente contém uma extensão (.txt, .c, .exe) que caracteriza
	 a informação que lá estará contida. De forma geral, os arquivos
	 podem ser divididos em dois tipos:
	 1) Arquivos binários, que são uma sequência de bits que será interpretada
	 por um outro programa de computador, e
	 2) Arquivos texto, ou ascii, que contém apenas caracteres ascii e podem
	 ser lidos tanto por seres humanos quanto por programas.
	 
	 No sistema operacional, arquivos são organizados em diretórios, ou pastas,
	 e podem ser referidos por seu caminho absoluto:
	 /users/eu/arquivo.c
	 /users/eu/diretorio1/leiame.txt
	 /users/outro/foto.jpg
	 ou por seu caminho relativo:
	 ./arquivo.c
	 ./diretorio1/leiame.txt
	 ../outro/foto.jpg
	 
	 Em C, as funções para lidar com arquivo estão na biblioteca <stdio.h>
*/

#include <stdio.h>

/* Um arquivo é acessado, em C, através de um ponteiro para arquivo:
	 FILE *p;

	 Depois de declarar o ponteiro, deve-se informar ao sistema que um
	 arquivo será aberto. Para isso, utiliza-se a função fopen:
	 p = fopen("nome_do_arquivo.txt", "r");

	 o identificador "r" determina os modos de acesso permitidos ao
	 arquivo, conforme a tabela abaixo:
	 "r" - Leitura. O arquivo deve existir, caso contrário o sistema retorna erro.
	 "w" - Gravação. Apaga os conteúdos do arquivo ou cria um novo arquivo.
	 "a" - Adição. Adiciona conteúdo ao fim do arquivo ou cria um novo arquivo.
	 "r+" - Leitura e gravação. O arquivo deve existir.
	 "w+" - Leitura e gravação. Apaga conteúdos do arquivo ou cria um novo.
	 "a+" - Adição e gravação. Cria um novo arquivo caso seja necessário.

	 Após o uso, o arquivo deve ser fechado.

	 Para lidar com arquivos-texto, podem ser utilizadas as funções fscanf (para leitura)
	 e fprintf, cujo uso é bastante semelhante ao scanf e ao printf:

	 FILE *p;
	 int i;
	 p = fopen("nome_do_arquivo.txt", "w");
	 fprintf(p, "%d", 2000);
	 fclose(p);

	 p = fopen("nome_do_arquivo.txt", "r");
	 fscanf(p, "%d", &i);
	 fclose(p);
	 printf("%d\n", i);

	 É importante perceber que um arquivo é acessado como um vetor sobre o qual
	 são realizadas leituras. A cada leitura, há um ponteiro para uma posição
	 desse arquivo, que avança sequencialmente. Podemos querer mover, explicitamente,
	 o ponteiro do arquivo de uma determinada quantidade:
	 FILE *p;
	 p = fopen("teste.txt", "a+");
	 fprintf(p, "%06d", 345678);
	 fseek(p, -8);
	 fscanf(p, "%d", &i);
	 fclose(p);
	 printf("%d\n", i);

	 Também é possível usar a função rewind(p), que retorna o ponteiro de leitura para
	 a posição inicial (zero).

	 Temos, agora, um problema. Uma variável do tipo int ocupa (em nosso sistema atual)
	 4 bytes. Porém, em nosso arquivo, ela foi representada em 6 bytes, o que significa
	 um incremento de 50%. Pode não parecer muito, mas um incremento desse tipo pode
	 significar que um CD contendo 80 minutos de música passaria a conter apenas 53 minutos,
	 ou ainda, que uma transmissão de arquivo que leva uma hora passaria a levar uma hora
	 e meia.
	 
	 Nossa solução, então, é gravar diretamente nosso número inteiro no arquivo, usando
	 a representação que o sistema achar mais adequada para isso. Nesse caso, utilizaremos
	 as funções fwrite e fread:

	 fwrite(ponteiro_para_comeco_dos_dados, tamanho_dos_dados, numero_de_registros_para_escrever, arquivo);
	 fread(ponteiro_para_comeco_dos_dados, tamanho_dos_dados, numero_de_registro_para_ler, arquivo);

	 E, assim, temos o código:
	 FILE *p;
	 int i;
	 int j;
	 i = 50;

	 p = fopen("teste.dat", "a+");
	 fwrite(&i, sizeof(int), 1, p);
	 rewind(p);
	 fread(&j, sizeof(int), 1, p);
	 fclose(p);

	 printf("i=%d, j=%d\n", i, j);

	 Assim, poderíamos utilizar o seguite comando para gravar um vetor em disco:
	 int meu_vetor[500];
	 fwrite(meu_vetor, sizeof(int), 500, p);
*/

/* Em nosso programa-exemplo, vamos definir vetor de tamanho 500 contendo números
	 sequenciais, gravar esse vetor em disco e então lê-lo posteriormente */

int main() {
	int vetor1[500];
	int vetor2[500];
	int i;
	FILE *p;

	for (i=0; i<500; i++)
		vetor1[i] = i;

	p = fopen("teste.dat", "w+");
	rewind(p);
	fwrite(vetor1, sizeof(int), 500, p);
	rewind(p);
	fread(vetor2, sizeof(int), 500, p);
	fclose(p);

	for (i=0; i<500; i++) {
		if (vetor1[i] != vetor2[i]) {
			printf("Algo deu errado!\n");
			break;
		}
	}
	if (i == 500) {
		printf("Teste de leitura e escrita foi bem sucedido!\nVeja o que há no teste.dat!\n");
	}
	return 0;
}
/* Para executar:
	 gcc -oarquivos 15-arquivos.c
	 ./arquivos

	 Verifique o tamanho (em bytes) do teste.dat em linux utilizando o comando wc.
	 Verifique o conteúdo do teste.dat em linux utilizando o comando cat.
*/

/* Exercícios

	 1) Implemente um programa que, de forma semelhante ao comando
	 cat de linux, lê um arquivo de texto e imprime seu conteúdo
	 na tela. Dica: o comando fscanf retorna EOF (uma constante especial)
	 quando o fim do arquivo foi atingido.

	 2) Num arquivo de texto, estão salvos diversos valores separados
	 por vírgula, que correspondem a medições de temperatura de um sensor.
	 a) Implemente um programa que lê todos esses valores para um vetor
	 do tipo float
	 b) Verifique quanto espaço de armazenamento seria economizado se os valores
	 fossem gravados em formato binário

	 3) Proponha um sistema simples de armazenamento de dados no
	 qual rótulos de aeroportos (que podem ser representados por um char[3]) são
	 associados ao número de vôos que esse aeroporto já recebeu. Você não pode
	 manter na memória principal mais que um único registro de aeroporto. Implemente
	 as seguintes funções:
	 void adicionar_voo(const char[3] aeroporto, FILE *db); que adiciona um vôo ao aeroporto 
	                                                        recebido como entrada.
	 int verificar_voos(const_char[3] aeroporto, FILE *db); que retorna o número de vôos do
	                                                        aeroporto recebido como entrada.
   Para este sistema, é recomendável utilizar registros tipo struct. O sistema deve
	 suportar adições de vôos em aeroportos sem que todos os aeroportos tenham que ser
	 registrados previamente, ou seja, ao adicionar um vôo a um aeroporto inexistente,
	 um novo registro deve ser criado.
*/
