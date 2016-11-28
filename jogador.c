/* Stephanie Eun Ji Bang   n.USP 8994414 */

#include "jogador.h"
#include <stdlib.h>
#include <stdio.h>

jogador *cria_jogador(int n) {
   int i, j;
   jogador *p;

   p = malloc(sizeof(jogador));
   p->m = malloc(tamanho*sizeof(int *));
   p->caminho = malloc(n*sizeof(posicao));
   p->topo = 0;
   p->max = n;

   for (i = 0; i < tamanho; i++)
      p->m[i] = malloc(tamanho*sizeof(int));

   return p;
}

void realoca(jogador *p) {
   posicao *novo;
   int i;

   novo = malloc(2*p->max*sizeof(posicao));

   for (i = 0; i < p->topo; i++)   novo[i] = p->caminho[i];

   free(p->caminho);

   p->caminho = novo;
   p->max *= 2;
}

void empilha(jogador *p, posicao c) {
   if (p->topo == p->max)   realoca(p);

   p->caminho[p->topo] = c;
   p->topo++;
}

void troca_jogadores(char *j1, char *j2) {
   char copia_j1 = *j1;

   *j1 = *j2;
   *j2 = copia_j1;
}

void imprime_caminhos(jogador *p) {
   int i;

   printf("caminho %c\n", p->cor);
   for (i = 0; i < p->topo; i++)   printf("(%d, %d) ", p->caminho[i].x, p->caminho[i].y);

   printf("\n");
}

void imprime_matriz(int **m) {
   int i, j, k;

   for (i = 0; i < tamanho; i++) {
      for (k = 0; k < i; k++)   printf("  ");

      for (j = 0; j < tamanho; j++)
         printf("%d ", m[i][j]);

      printf("\n");
   }
}

int menor_anterior(int **m, int lin, int col, char cor) {
   if (cor == 'p') {
      if (lin+1 < tamanho && m[lin][col-1] > m[lin+1][col-1])
         return m[lin+1][col-1];

      return m[lin][col-1];
   }

   if (col+1 < tamanho && m[lin-1][col] > m[lin-1][col+1])
      return m[lin-1][col+1];

   return m[lin-1][col];
}

int menor_caminho(jogador *p) {
   posicao c;
   int i, j, menor;

   zera_caminho(p);

   if (p->cor == 'p') {
      j = tamanho-1;
      menor = 0;

      for (i = 1; i < tamanho; i++) {
         if (p->m[i][j] < p->m[menor][j])   menor = i;

         else if (p->m[i][j] == p->m[menor][j])
            if (menor_anterior(p->m, i, j, p->cor) < menor_anterior(p->m, menor, j, p->cor))
               menor = i;
      }

      c.x = menor;
      c.y = j;

      empilha(p, c);

      while (j > 0) {
         if (menor+1 < tamanho && p->m[menor][j-1] > p->m[menor+1][j-1])
            menor++;

         c.x = menor;
         c.y = j-1;

         empilha(p, c);

         j--;
      }
   }

   else {
      i = tamanho-1;
      menor = 0;

      for (j = 1; j < tamanho; j++) {
         if (p->m[i][j] < p->m[i][menor])   menor = j;

         else if (p->m[i][j] == p->m[i][menor])
            if (menor_anterior(p->m, i, j, p->cor) < menor_anterior(p->m, i, menor, p->cor))
               menor = j;
      }

      c.x = i;
      c.y = menor;

      empilha(p, c);
   
      while (i > 0) {
         if (menor+1 < tamanho && p->m[i-1][menor] > p->m[i-1][menor+1])
            menor++;

         c.x = i-1;
         c.y = menor;

         empilha(p, c);

         i--;
      }
   }

   imprime_caminhos(p);

   return p->m[p->caminho[0].x][p->caminho[0].y];
}

void inicializa_matriz(char **t, jogador *p) {
   int i, j, menor;

   if (p->cor == 'p') {
      for (i = 0; i < tamanho; i++)
         if (t[i][0] == 'p')   p->m[i][0] = 0;

         else if (t[i][0] == 'b')   p->m[i][0] = tamanho+1;

         else   p->m[i][0] = 1;

      for (j = 1; j < tamanho; j++) {
         for (i = 0; i < tamanho; i++) {
            menor = menor_anterior(p->m, i, j, 'p');

            if (t[i][j] == 'p')   p->m[i][j] = menor;

            else if (t[i][j] == 'b')   p->m[i][j] = tamanho+1;

            else   p->m[i][j] = menor+1;
         }
      }
   }

   else {
      for (j = 0; j < tamanho; j++)
         if (t[0][j] == 'b')   p->m[0][j] = 0;

         else if (t[0][j] == 'p')   p->m[0][j] = tamanho+1;

         else   p->m[0][j] = 1;

      for (i = 1; i < tamanho; i++) {
         for (j = 0; j < tamanho; j++) {
            menor = menor_anterior(p->m, i, j, 'b');

            if (t[i][j] == 'b')   p->m[i][j] = menor;

            else if(t[i][j] == 'p')   p->m[i][j] = tamanho+1;

            else   p->m[i][j] = menor+1;
         }
      }
   }

   menor_caminho(p);
}

void atualiza_matriz(char **t, jogador *p, posicao jog) {
   int i, j, menor, cont = 1;

   if (p->cor == 'p') {
      if (jog.y == 0) {
         if (t[jog.x][0] == 'b')   p->m[jog.x][0] = tamanho+1;

         else   p->m[jog.x][0] = 0;

         jog.y++;
         cont++;
      }

      for (j = jog.y; j < tamanho; j++) {
         for (i = 0; i < cont && jog.x-i >= 0; i++) {
            menor = menor_anterior(p->m, jog.x-i, j, 'p');

            if (t[jog.x-i][j] == 'p')   p->m[jog.x-i][j] = menor;

            else if (t[jog.x-i][j] == 'b')   p->m[jog.x-i][j] = tamanho+1;

            else   p->m[jog.x-i][j] = menor+1;
         }

         cont++;
      }
   }

   else {
      if (jog.x == 0) {
         if (t[0][jog.y] == 'p')   p->m[0][jog.y] = tamanho+1;

         else   p->m[0][jog.y] = 0;

         jog.x++;
         cont++;
      }

      for (i = jog.x; i < tamanho; i++) {
         for (j = 0; j < cont && jog.y-j >= 0; j++) {
            menor = menor_anterior(p->m, i, jog.y-j, 'b');

            if (t[i][jog.y-j] == 'b')   p->m[i][jog.y-j] = menor;

            else if (t[i][jog.y-j] == 'p')   p->m[i][jog.y-j] = tamanho+1;

            else   p->m[i][jog.y-j] = menor+1;
         }

         cont++;
      }
   }

   printf("foi\n");

   menor_caminho(p);
}

void zera_caminho(jogador *p) {
   free(p->caminho);

   p->caminho = malloc(p->max*sizeof(posicao));
   p->topo = 0;
}
