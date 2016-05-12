/* Sistemas
 *
 * Um sistema eh um conceito abstrato usado para representar elementos do mundo
 * real. Um sistema possui um estado interno, e realiza operacoes baseadas em
 * seu estado interno e em entradas. Neste programa, vou utilizar ponteiros e
 * variaveis do tipo struct para implementar um filtro de media movel
 * exponencial */

#include <stdio.h>
#include <stdlib.h>

typedef float real;

typedef struct {
  real yn1;
  real alpha;
} EMeanFilter;

EMeanFilter *EMeanFilter_Create(real alpha); /* Cria novo filtro */

real EMeanFilter_Insert(EMeanFilter *E, real x); /* Aplica filtro
                                                    em uma nova amostra */

EMeanFilter *EMeanFilter_Create(real alpha)
{
  EMeanFilter *E;
  E = (EMeanFilter*) malloc(sizeof(EMeanFilter));
  E->yn1 = 0;
  E->alpha = alpha;
  return E;
}

real EMeanFilter_Insert(EMeanFilter *E, real x)
{
  real y;
  y = ((E->alpha) * x) + ((1 - (E->alpha)) * (E->yn1));
  E->yn1 = y;
  return y;
}


int main()
{
  unsigned int N;
  unsigned int n;
  real alpha;

  real y;
  real x;
  EMeanFilter *E;

  /* Ler os parametros da filtragem */
  scanf("%d %f", &N, &alpha);

  E = EMeanFilter_Create(alpha);
  printf("Receiving samples...\n");
  for (n=0; n<N; n++) {
    scanf("%f", &x);
    y = EMeanFilter_Insert(E, x);
    printf("[%d]\t%f\n", n, y);
  }

  free(E);
  return 0;

}

/* Exercicios
 *
 * 1) Programe um sistema que gera ruido gaussiano branco com media zero e
 * variancia definida no momento da criacao do sistema.
 *
 * 2) Utilize o filtro de media movel exponencial para filtrar um sinal de
 * entrada que eh uma onda quadrada na qual foi adicionada ruido gaussiano
 * branco. Variando o valor de alpha, verifique o que acontece como sinal de
 * saida, considerando:
 *   a) A rejeicao ao ruido que foi adicionado
 *   b) O tempo que o filtro leva para convergir a cada semi-ciclo do sinal de
 *   entrada
 *
 * 3) Programe um sistema que eh um filtro que simula uma versao discretizada de
 * um circuito passa-baixas RC. Compare a resposta do filtro digital a resposta
 * do seu equivalente analogico (use um osciloscopio e um gerador de sinais para
 * capturar essa resposta).
 *
 */

