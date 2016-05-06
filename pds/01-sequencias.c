/* Sequencias
 *
 * Sequencias de numeros podem ser representados por vetores em C. Para isso,
 * usualmente eh necessario reservar memoria em quantidade adequada. Para
 * representar numeros reais, utilizaremos o tipo float, sabendo de suas
 * limitacoes de representacao (overflow / underflow, por exemplo)
 * */

typedef float real;


/* Eventualmente, sera preciso ler e armazenar sequencias em disco, ou
 * recebe-las atraves da linha de comando, ou escreve-las na tela. Para tal,
 * utilizaremos a biblioteca stdio.h
 * */

#include <stdio.h>

/* Escreveremos um programa que parte de uma sequencia de numeros e executa uma
 * serie de operacoes sobre ela. */

int main() {
  int n; /* Contador que sera usado mais adiante */

  real x[6] = {0.1, 0.4, -2, 5, 0.3, 5};

  /* Operacao 1: Iterar por todas as amostras e escreve-las na tela */
  printf("Amostras: ");
  for (n=0; n<6; n++)
    printf("%02.02f ", x[n]);
  printf("\n");

  /* Operacao 2: Atraso de 1 amostra */
  real y[7];
  y[0] = 0;
  for (n=1; n<7; n++)
    y[n] = x[n-1];

  /* Escrever as amostras atrasadas na tela: */
  printf("Amostras: ");
  for (n=0; n<7; n++)
    printf("%02.02f ", y[n]);
  printf("\n");

  /* Perceba que, implicitamente, assumimos que as amostras nao-representadas
   * sao assumidas como iguais a zero */


  /* Operacao 3: Executar uma operacao matematica sobre as amostras */
  real z[6];
  for (n=0; n<6; n++)
    z[n] = x[n] * 3;

  /* Escrever as amostras atrasadas na tela: */
  printf("Amostras: ");
  for (n=0; n<6; n++)
    printf("%02.02f ", z[n]);
  printf("\n");


  return 0;
}


/* Para executar:
 * gcc -o01-sequencias 01-sequencias.c
 * ./01-sequencias
 *
 * */

/* Exercicios:
 * 1) Suponha uma sequencia x[n] com N amostras. Crie um programa que calcula a
 * sequencia y[n] = x[n-N].
 *
 * 2) Qual eh a eficiencia assintotica do calculo de z[n] = 5*x[n]+10? Use a
 * notacao Big-O.
 *
 * 3) Quantas posicoes de memoria sao necessarias para armazenar os dados
 * metereologicos lidos em uma estacao durante o periodo de 100 anos, assumindo
 * que existe uma leitura de maxima temperatura e
 * uma leitura de minima temperatura a cada:
 *   a) Ano
 *   b) Mes
 *   c) Semana
 *   d) Dia
 *   e) Hora
 *   f) Minuto
 *   g) Segundo
 *
 * 4) Defenda uma das frequencias de leitura acima, considerando o compromisso
 * entre a memoria utilizada e a quantidade de informacao armazenada.
 *
 */


