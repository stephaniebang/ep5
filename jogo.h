/* Stephanie Eun Ji Bang   n.USP 8994414 */

#ifndef __JOGO_H__
#define __JOGO_H__


typedef struct {
   int x, y;
} coordenadas;


extern int tamanho;
extern int impressao;

/* A funcao retorna o ponteiro de uma matriz de char, quadrada de dimensao
 * tamanho, preenchida por '-'. */
char **cria_tabuleiro();

/* A funcao imprime o conteudo de uma matriz de char, quadrada de dimensao
 * tamanho no stderr. */
void imprime_tabuleiro(char **tab);

/* A funcao recebe um tabuleiro tab, o char cor do jogador e as coordenadas jog
 * de sua jogada. Ela realiza em tab a jogada e imprime a jog e, se necesssario,
 * o tabuleiro tambem. */
void faz_jogada(char **tab, char cor, coordenadas jog);

/* A funcao recebe o tabuleiro tab e as coordenadas jog e retorna 1, se for
 * possivel realizar essa jogada, ou retorna 0, caso contrario. */
int jogada_valida(char **tab, coordenadas jog);

/* A funcao recebe o tabuleiro tab e a cor de um jogador e recebe pela entrada 
 * padrao as coordenadas de sua jogada, as realiza em tab e as retorna. */
coordenadas recebe_jogada(char **tab, char cor);

/* A funcao recebeo tabuleiro tab, as coordenadas jog de uma jogada realizada e a
 * cor do jogador. Se o jogador for o preto, ela retorna 1, se a jog for
 * repetida, ou 0, se outra jogada foi realizada. Se ele for branco, ela recebe
 * a jogada adversaria e retorna 1, se ela for repetida, ou 0, caso contrario. */
int pie_rule(char **tab, coordenadas jog, char cor);

coordenadas proximo(char **tab, char cor, coordenadas inicio);

/* A funcao recebe uma matriz m e um char c com a cor de um jogador. Ela
 * retorna 1, se ele conseguiu formar um caminho completo, ou retorna 0, caso
 * contrario. */
int caminho_completo(char **tab, char cor);

coordenadas decide_jogada(char **tab, char cor);


#endif
