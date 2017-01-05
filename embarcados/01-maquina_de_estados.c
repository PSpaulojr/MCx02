/** \page "Maquinas de Estados"
 *
 * Uma maquina de estados eh um conceito abstrato. Trata-se de um dispositivo
 * que sempre assume um, e apenas um, estado discreto entre um conjunto de
 * estados possiveis. Essa abstracao matematica pode ser usada para modelar
 * diversos fenomenos.
 *
 * Um exemplo de fenomeno que eh modelavel por uma maquina de estados eh o tempo
 * de um local. Poderiamos associar um estado que indica se estamos em um dia de
 * Sol, e outro estado para indicar se o dia eh chuvoso. Essa informacao eh
 * relevante para alguns sistemas, em especial de climatizacao: provavelmente,
 * um sistema de resfriamento agira mais intensamente em dias de Sol; outra
 * possibilidade eh que um sistema de agendamento preveja atrasos maiores em
 * dias de chuva.
 *
 * Uma maquina de estados se baseia em dois componentes:
 * 1) Um registro do numero do estado em que estamos neste momento
 * 2) Uma tabela de transicoes de estado
 *
 * O registro do estado atual pode ser realizado usando uma variavel inteira. A
 * tabela de transicoes de estado, por sua vez, pode ser:
 * a) Implicita (se estamos falando de um contador, entao nao eh preciso guardar
 * uma tabela explicitamente, ja que basta somar 1 ao estado a cada nova
 * contagem)
 * b) Explicita por meio de estruturas if-then-else
 * c) Explicita por meio de um vetor
 *
 * Para usar uma maquina de estados, deve ser possivel, no minimo, ativar a
 * mudanca de estado. Opcionalmente, pode ser possivel reiniciar a maquina ou
 * forcar que ela assuma algum estado.
 *
 * Tambem, podemos associar acoes (saidas) a estados. Assim como no caso da
 * tabela de proximo estado, eh possivel fazer isso implicitamente, ou por meio
 * de estruturas if-then-else ou na definicao de um vetor.
*/

#define N_ESTADOS 4

unsigned int estado = 0; /**< Numero do estado atual */
unsigned int tabela_estado[N_ESTADOS] = {1, 3, 0, 2}; /**< Tabela de transicao */
unsigned int saidas[N_ESTADOS] = {0, 2, 1, 2}; /**< Saidas para cada estado */


/** Avanca uma maquina para o proximo estado
 *
 * A passagem dos parametros por referencia permite que a mesma funcao seja
 * usada para operar sobre varias maquinas de estado, inclusive as que tem
 * escopo local, desde que sejam definidas de forma compativel com a definicao
 * da maquina deixada como exemplo.
 * */
void proximo_estado(unsigned int *registrador_de_estado, /**< [in,out] Ponteiro para o registrador de estado */
    unsigned int *tabela_de_transicao /**< [in] Ponteiro para tabela de transicao*/ )
{
  (*registrador_de_estado) = tabela_de_transicao[(*registrador_de_estado)];
}


/** Calcula a saida de uma maquina de estados */
unsigned int saida(unsigned int *registrador_de_estado, /**< [in] Ponteiro para o registrador de estado */
    unsigned int *tabela_de_saidas /**< [in] Ponteiro para tabela de saidas */ )
{
  return tabela_de_saidas[(*registrador_de_estado)];
}


#include <stdio.h>

/** Programa exemplo */
int main() {
  int i;
  for (i=0; i<10; i++) {
    printf("%02d\tEstado: %02d\tSaida: %02d\n", i, estado, saida(&estado, saidas));
    proximo_estado(&estado, tabela_estado);
  }
  return 0;
}

/* Compilar: gcc -ofsm 01-maquina_de_estados.c
 * Executar: ./fsm
 * */

