/* Matrizes

	 Matrizes são utilizadas para relacionar duas dimensões diferentes a
	 valores. Figuras, por exemplo, relacionam a posição (i,j) de cada
	 pixel a uma cor correspondente. Em C, uma matriz é representada como
	 um vetor de vetores:
*/

#define LINHAS 3
#define COLUNAS 3
#define DIM COLUNAS

int matriz_1[LINHAS][COLUNAS];
int matrix_2[LINHAS][COLUNAS];

/* De forma análoga a um vetor, podemos ler valores de nossa entrada-padrão
	 e colocá-las em uma matriz:
*/

#include <stdio.h>

void ler_matriz(int matriz[][COLUNAS], int linhas, int colunas) {
	int i;
	int j;
	for (i=0; i<linhas; i++) { /* Para cada linha */
		for (j=0; j<colunas; j++) { /* Para cada coluna */
			scanf("%d", &(matriz[i][j]));
		}
	}
}

/* Além disso, podemos imprimir todos os elementos de nossa matriz: */

void imprimir_matriz(int matriz[][COLUNAS], int linhas, int colunas) {
	int i;
	int j;
	for (i=0; i<linhas; i++) {
		for (j=0; j<colunas; j++) {
			printf("%d\t", matriz[i][j]);
		}
		printf("\n");
	}
}

/* As matrizes nos permitem realizar operações matriciais, como a soma de
	 matrizes, em funções simples como: */

void somar_matrizes(int matriz1[][COLUNAS], int matriz2[][COLUNAS], int resposta[][COLUNAS], int linhas, int colunas) {
	int i;
	int j;
	for (i=0; i<linhas; i++)
		for (j=0; j<colunas; j++)
			resposta[i][j] = matriz1[i][j] + matriz2[i][j];
}

/* É possível declarar vetores de vetores de vetores, e assim por diante, de forma
	 a relacionar dados em muitas dimensões. Um vídeo, por exemplo, pode ser
	 representado como um vetor de quadros, sendo que cada quadro é uma matriz de
	 inteiros representando cada pixel - algo como video[quadro][linha][coluna].
	 Isso pode ajudar a representar dados multi-dimensionais.

	 Voltemos, porém, ao conceito de vetores. Um vetor é um espaço contínuo onde
	 podem ser representados N elementos de um certo tipo. Assim, um vetor de M 
	 vetores de tamanho N é um espaço contínuo em que podem ser representados
	 N*M elementos desse mesmo tipo. Isso significa que podemos acessar matrizes
	 como se fossem vetores, nos quais cada linha está localizada num espaço 
	 contínuo de vetores.

	 Assim, uma outra função para imprimir matrizes pode assumir a forma:
*/

void imprimir_matriz_2(int matriz[], int linhas, int colunas) {
	int i;
	int j;
	for (i=0; i<linhas; i++) {
		for (j=0; j<colunas; j++)
			printf("%d\t", matriz[i*colunas + j]);
		printf("\n");
	}
}

/* A linearização de índices é interessante quando queremos realizar, sobre
	 matrizes, operações que são típicas de vetores, como a busca por um
	 máximo valor, a ordenação ou o cálculo da soma total dos valores armazenados.
	 Para nosso programa-exemplo, definiremos uma função que imprime todos
	 os valores de um vetor, e o utilizaremos para verificar nosso procedimento
	 de linearização de índices.
*/
void imprimir_vetor(int vetor[], int tamanho) {
	int i;
	for (i=0; i<tamanho; i++)
		printf("%d\t", vetor[i]);
	printf("\n");
}

/* Note que, ao se utilizar a ideia de linearizacao de indices, tornou-se
	 automaticamente desnecessario informar ao compilador, previamente, o numero
	 de colunas de sua matriz. Esse comportamento eh de grande valia para tornar
	 programas mais flexiveis à entrada, embora tenha o custo de aumentar
	 (um pouco) a complexidade do código. Como a maior parte dos parâmetros, em
	 computação, essa decisão vai depender de um compromisso que levará em
	 consideração o problema que está sendo abordado. */

int main() {
	int matriz[DIM][DIM] = { {5, 4, 3}, {2, 3, 1}, {9, 9, 0} }; /* Inicializando a matriz */
	/*ler_matriz(matriz, DIM, DIM);*/
	printf("\n");
	imprimir_matriz(matriz, DIM, DIM);
	printf("\n");
	imprimir_matriz_2(&(matriz[0][0]), DIM, DIM);
	printf("\n");
	imprimir_vetor(&(matriz[0][0]), DIM*DIM);
	printf("\n");
	somar_matrizes(matriz, matriz, matriz, DIM, DIM);
	imprimir_matriz(matriz, DIM, DIM);
	printf("\n");
	return 0;
}

/* Exercícios
	 1) Escreva um programa que lê uma matriz quadrada de dimensão 50
	 e verifica que essa matriz é a matriz identidade ou não.

	 2) Uma matriz contém as notas de alunos numa prova de MC000.
	 Cada uma das cinco colunas contém a nota de uma questão, e cada
	 linha contém as notas de um aluno. Escreva um programa que:
	 a) Calcula a nota de cada aluno, sabendo que o peso
	 de cada questão é igual.
	 b) Encontra qual é a questão na qual mais alunos tiraram nota
	 abaixo de 5.
	 c) Encontra qual é a questão que mais alunos tiraram 10.

	 3) Escreva um programa que recebe como entrada:
	 - Dois números, respectivamente, o número de linhas
	 e colunas de uma matriz;
	 - A matriz propriamente dita, contendo números inteiros
	 O programa deve processar a matriz recebida de forma que:
	 a) A[i+1][j] > A[i][j] para todo i e j
	 b) A[i][j+1] > A[i][j] para todo i e j

	 4) Escreva uma função cujo cabeçalho é:
	 void transpoe(int matriz A[], int *linhas, int *colunas).
	 Ao fim da execução da função, a matriz A deve estar transposta
	 e os valores de linhas e colunas devem estar atualizados, 
	 considerando a matriz transposta.

	 5 (bônus)) Analizando as notas da matriz 
	 recebida no exercício 1, proponha e aplique um algoritmo que
	 detecta possíveis colas entre alunos.
*/
