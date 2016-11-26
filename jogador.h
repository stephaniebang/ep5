/* Stephanie Eun Ji Bang   n.USP 8994414 */

#ifndef __JOGADOR_H__
#define __JOGADOR_H__

#include "jogo.h"


typedef struct {
   coordenadas *jogadas;
   char cor;
   int topo, max;
} jogador;


/* A funcao retorna o ponteiro de um jogador com capacidade de n jogadas. */
jogador *cria_jogador(int n);

/* A funcao realoca o dobro de espaco para o jogador de ponteiro p. */
void realoca(jogador *p);

/* A funcao empilha na pilha de ponteiro p as coordenadas c. */
void empilha(jogador *p, coordenadas c);

/* A funcao troca as cores das pecas dos jogadores j1 e j2. */
void troca_jogadores(char *j1, char *j2);


#endif
