/** Maquina de estados
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
const unsigned int proximo_estado[N_ESTADOS] = {1, 2, 3, 0}; /**< Tabela de transicao */
const unsigned int saidas[N_ESTADOS] = {0, 2, 1, 2}; /**< Saidas para cada estado */





