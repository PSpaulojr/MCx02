
/* Convolucao entre dois sinais
 *
 * Y[n] = sum from m = -infty to + infty of x1[n-m]*x2[m]
 */

#include <stdio.h>

typedef float real;

int min(i, j) {
  if (i<j) return i;
  else return j;
}

int max(i, j) {
  if (i>j) return i;
  else return j;
}

void convolution(real *x1, real *x2, real *y, unsigned int N1, unsigned int N2)
{
  unsigned int n;
  unsigned int m;

  for (n=0; n<(N1+N2-1); n++) {
    y[n] = 0;
    for (m=max(0, n-N1+1); (m<N2) && (m<(n+1)); m++) {
        y[n] += x1[n-m] * x2[m];
    }
  }
}

int main()
{
  real x1[5] = {1, 1, 1, 1, 1};
  real x2[3] = {1, 1, 1};
  real x3[3] = {0, 1, 0};

  real y[7];
  real y2[9];

  int i;

  printf("-----1\n");
  convolution(x1, x2, y, 5, 3);
  for (i=0; i<7; i++)
    printf("%f\n", y[i]);

  printf("-----2\n");
  convolution(x2, x1, y, 3, 5);
  for (i=0; i<7; i++)
    printf("%f\n", y[i]);

  printf("-----3\n");
  convolution(x3, y, y2, 3, 7);
  for (i=0; i<9; i++)
    printf("%f\n", y2[i]);



  return 0;
}


