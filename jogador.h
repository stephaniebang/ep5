/* Stephanie Eun Ji Bang   n.USP 8994414 */

#ifndef __JOGADOR_H__
#define __JOGADOR_H__

#include "tipos.h"


/* A funcao retorna o ponteiro de um jogador com capacidade de n jogadas. */
jogador *cria_jogador(int n);

/* A funcao empilha na pilha de ponteiro p a posicao c. */
void empilha(jogador *p, posicao c);

/* A funcao troca as cores das pecas dos jogadores j1 e j2. */
void troca_jogadores(char *j1, char *j2);

/* A funcao inicializa a matriz m do jogador p de acordo com o estado do
 * tabuleiro t. */
void inicializa_matriz(char **t, jogador *p);

/* A funcao recebe um tabuleiro tab e um jogador jog. Ela retorna 1, se o
 * jogador conseguiu formar um caminho completo, ou retorna 0, caso contrario. */
int caminho_completo(char **tab, jogador *p);

/* A funcao atualiza a matriz m do jogador p de acordo com a ultima jogada
 * realizada e a situacao do tabuleiro t. */
void atualiza_matriz(char **t, jogador *p, posicao jog);

/* A funcao destroi o jogador de ponteiro p. */
void destroi_jogador(jogador *p);


#endif
