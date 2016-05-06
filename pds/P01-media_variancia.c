
/* Este programa recebe como entrada uma sequencia de numeros separados por
 * espaco. O primeiro numero eh um inteiro N que indica o numero de amostras que
 * serao guardadas. Apos, ele recebe N valores inteiros e os armazena num vetor.
 * O programa, entao, calcula a media e o desvio padrao dos numeros recebidos.
 * Por ultimo, imprime a media e o desvio padrao na tela. */

#include <stdio.h>

#define TAM_MAX_ENTRADA 100

typedef float real;


int main() {
  real x[TAM_MAX_ENTRADA];
  real media;
  real std_dev;

  int N;
  int n;

  /* Receber numeros */
  scanf("%d", &N);

  for (n=0; n<N; n++) {
    scanf("%f", &(x[n]));
  }


  /* Calcular media */
  media = 0;
  for (n=0; n<N; n++) {
    media = media + x[n];
  }
  media = media / (float)N;

  /* Calcular desvio padrao */
  std_dev = 0;
  for (n=0; n<N; n++) {
    std_dev = std_dev + ((x[n]-media) * (x[n]-media));
  }
  std_dev = std_dev / (float)N;

  printf("Media: %f\nDesvio Padrao: %f\n", media, std_dev);

  return 0;
}
