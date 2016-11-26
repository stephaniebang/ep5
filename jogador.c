/* Stephanie Eun Ji Bang   n.USP 8994414 */

#include "jogador.h"
#include <stdlib.h>


jogador *cria_jogador(int n) {
   jogador *p;

   p = malloc(sizeof(jogador));
   p->jogadas = malloc(n*sizeof(coordenadas));
   p->topo = 0;
   p->max = n;

   return p;
}

void realoca(jogador *p) {
   coordenadas *novo;
   int i;

   novo = malloc(2*p->max*sizeof(coordenadas));

   for (i = 0; i < p->topo; i++)   novo[i] = p->jogadas[i];

   free(p->jogadas);

   p->jogadas = novo;
   p->max *= 2;
}

void empilha(jogador *p, coordenadas c) {
   if (p->topo == p->max)   realoca(p);

   p->jogadas[p->topo] = c;
   p->topo++;
}

void troca_jogadores(char *j1, char *j2) {
   char copia_j1 = *j1;

   *j1 = *j2;
   *j2 = copia_j1;
}
