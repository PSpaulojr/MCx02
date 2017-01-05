/** \page "Buffer circular" Buffer circular
 *
 * # Como usar um buffer circular
 *
 * Considere o seguinte problema. Estamos em 1992, filmando a final do
 * Campeonato Mundial Interclubes de Futebol. De repente, o goleiro Zetti
 * espalma uma bola, dando seguimento ao lance. O defensor do Sao Paulo pega o
 * rebote e comeca um contra-ataque. Surge entao um problema: queremos mostrar o
 * replay do lance ao mesmo tempo que queremos continuar gravando o restante do
 * jogo.
 *
 * Uma possivel solucao para isso (lembrando que em 1992 as gravacoes nao eram
 * digitais!), que foi adotada durante algum tempo, eh usar um tambor de fita
 * circular. Ele eh capaz de armazenar ate, digamos, 2 minutos de video. A
 * cabeca de gravacao avanca constantemente sobre ele, mas a cabeca de leitura
 * pode ser regulada. Assim, podemos usar essa estrutura para mostrar o video
 * correspondente a alguns segundos no passado sem interromper a aquisicao de
 * novas imagens.
 *
 * A versao computacional dessa fita circular se chama ``buffer circular''.
 * Trata-se de um vetor ao qual associamos um ponteiro de leitura e um ponteiro
 * de gravacao.
 *
 * \image html buffer_circular.jpg width=400
 *
 * O buffer circular eh interessante para os casos em que desejamos gravar dados
 * e utiliza-los numa taxa diferente. Neste exemplo, seremos capazes de guardar
 * ate 5 elementos em nosso buffer circular, e poderemos ler esses elementos a
 * medida que forem sendo processados.
 *
 * Alem de aplicacoes em replay de video, buffers circulares aparecem em
 * filtragem de sinais (para implementar o atraso de amostras) e em sistemas de
 * comunicacao (para armazenar um comando inteiro antes que ele seja
 * processado).
 * */

#define TAM_BUFFER 5

/** Estrutura para buffer circular
 *
 * Como ha muitos parametros relacionados a um buffer circular, convem definir
 * uma estrutura que agregue todos eles. */
typedef struct buffer_circular {
  unsigned int n_elementos;
  char dados[TAM_BUFFER];
  unsigned int pont_gravacao;
  unsigned int pont_leitura;
} buffer_circular;

/** Inicializar buffer circular
 *
 * Reinicia a cabeca de gravacao e de leitura */
void reiniciar_buffer(buffer_circular *c /**< [in,out] Buffer que sera reinicializado */) {
  c->n_elementos=0;
  c->pont_gravacao=0;
  c->pont_leitura=0;
}

/** Gravar dado no buffer
 *
 *  \return 1 se o dado foi gravado, 0 caso contrario (buffer cheio)
 * */
int gravar_dado(buffer_circular *c, /**< [in,out] Buffer onde gravaremos dados */
                char dado /**< [in] Dado a ser gravado */) {
  if (c->n_elementos < TAM_BUFFER) {
    c->dados[c->pont_gravacao] = dado;
    c->pont_gravacao = ((c->pont_gravacao)+1)%TAM_BUFFER;
    c->n_elementos += 1;
    return 1;
  } else return 0;
}

/** Recuperar dado no buffer
 *
 * \return 1 se o dado foi recuperado, 0 caso contrario (buffer vazio)
 * */
int recuperar_dado(buffer_circular *c, /**< [in,out] Buffer com dados */
                   char *dado /**< [out] Ponteiro para variavel onde dado sera gravado */)
{
  if (c->n_elementos > 0) {
    (*dado) = c->dados[c->pont_leitura];
    c->pont_leitura = ((c->pont_leitura)+1)%TAM_BUFFER;
    c->n_elementos -= 1;
    return 1;
  } else return 0;
}

#include <stdio.h>
int main() {
  buffer_circular bc;
  char c;
  reiniciar_buffer(&bc);
  gravar_dado(&bc, 'a');
  gravar_dado(&bc, 'b');
  gravar_dado(&bc, 'c');
  recuperar_dado(&bc, &c);
  printf("%c\n", c);
  recuperar_dado(&bc, &c);
  printf("%c\n", c);
  recuperar_dado(&bc, &c);
  printf("%c\n", c);
  gravar_dado(&bc, 'd');
  gravar_dado(&bc, 'e');
  gravar_dado(&bc, 'f');
  recuperar_dado(&bc, &c);
  printf("%c\n", c);
  recuperar_dado(&bc, &c);
  printf("%c\n", c);
  recuperar_dado(&bc, &c);
  printf("%c\n", c);
}
