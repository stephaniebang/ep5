/* Stephanie Eun Ji Bang   n.USP 8994414 */

#ifndef __JOGO_H__
#define __JOGO_H__

#include "tipos.h"


/* A funcao retorna o ponteiro de uma matriz de char, quadrada de dimensao
 * tamanho, preenchida por '-'. */
char **cria_tabuleiro();

/* A funcao imprime o conteudo de uma matriz de char, quadrada de dimensao
 * tamanho no stderr. */
void imprime_tabuleiro(char **tab);

/* A funcao recebe um tabuleiro tab, o char cor do jogador e a posicao jog de 
 * sua jogada. Ela realiza em tab a jogada e imprime a jog e, se necesssario, o
 * tabuleiro tambem. */
void faz_jogada(char **tab, char cor, posicao jog);

/* A funcao recebe o tabuleiro tab e a cor de um jogador e recebe pela entrada 
 * padrao a posicao de sua jogada, a realiza em tab e a retorna. */
posicao recebe_jogada(char **tab, char cor);

/* A funcao recebeo tabuleiro tab, a posicao jog de uma jogada realizada e a cor
 * do jogador. Se o jogador for o preto, ela retorna 1, se a jog for repetida, 
 * ou 0, se outra jogada foi realizada. Se ele for branco, ela recebe a jogada
 * adversaria e retorna 1, se ela for repetida, ou 0, caso contrario. */
int pie_rule(char **tab, posicao jog, char cor);

/* A funcao recebe um tabuleiro tab e um jogador jog e retorna a posicao da
 * jogada a ser realizada por esse jogador. */
posicao decide_jogada(char **tab, jogador *jog, jogador *adv, posicao ultimo);

/* A funcao destroi o tabuleiro de ponteiro tab. */
void destroi_tabuleiro(char **tab);


#endif
