/* Stephanie Eun Ji Bang   n.USP 8994414 */

#include "jogo.h"
#include "jogador.h"
#include <stdlib.h>
#include <stdio.h>


int tamanho = 11;
int impressao = 0;

/***********************
* Funcoes do tabuleiro *
***********************/
char **cria_tabuleiro() {
   char **tab;
   int i, j;

   tab = malloc(tamanho*sizeof(char *));

   for (i = 0; i < tamanho; i++) {
      tab[i] = malloc(tamanho*sizeof(char));

      for (j = 0; j < tamanho; j++)
         tab[i][j] = '-';
   }

   return tab;
}

void imprime_tabuleiro(char **tab) {
   int i, j, k;

   for (i = 0; i < tamanho; i++) {
      for (k = 0; k < i; k++)   printf("  ");

      for (j = 0; j < tamanho; j++)
         printf("%c ", tab[i][j]);

      printf("\n");
   }
}

void faz_jogada(char **tab, char cor, posicao jog) {
   tab[jog.x][jog.y] = cor;

   printf("%d %d\n", jog.x, jog.y);

   if (impressao)   imprime_tabuleiro(tab);
}

int jogada_valida(char **tab, posicao jog) {
   if (jog.x < 0 || jog.x >= tamanho || jog.y < 0 || jog.y >= tamanho)
      return 0;

   if (tab[jog.x][jog.y] != '-')   return 0;

   return 1;
}

posicao recebe_jogada(char **tab, char cor) {
   posicao jog;

   scanf("%d %d", &jog.x, &jog.y);

   while (!jogada_valida(tab, jog)) {
      printf("Jogada invalida. Digite outra jogada.\n");
      scanf("%d %d", &jog.x, &jog.y);
   }

   tab[jog.x][jog.y] = cor;

   return jog;
}


/************************
* Funcoes de estrategia *
************************/
int pie_rule(char **tab, posicao jog, char cor) {
   int troca = 0;

   if (cor == 'b') {   /* Se eu for o jogador branco */
      /* Recebendo a primeira jogada do preto */
      scanf("%d %d", &jog.x, &jog.y);

      while (jog.x < 0 || jog.x >= tamanho || jog.y < 0 || jog.y >= tamanho) {
         printf("Jogada invalida. Digite outra jogada.\n");
         scanf("%d %d", &jog.x, &jog.y);
      }

      if (tab[jog.x][jog.y] == 'b') {
         troca = 1;
         cor = 'p';
      }

      else    tab[jog.x][jog.y] = 'p';

      /* Respondendo a jogada */
      if (jog.x < 3 || jog.y < 3) {
         jog.x = tamanho/2;
         jog.y = tamanho/2;
      }

      else {
         if (tab[jog.x-1][jog.y] == '-')
            jog.x--;

         else   jog.y--;
      }
   }

   else {   /* Se eu for o jogador preto */
      /* Decidindo qual jogada realizar */
      if (jog.x < 2 || jog.x > tamanho-3 || jog.y < 2 || jog.y > tamanho-3) {
         jog.x = tamanho/2;
         jog.y = tamanho/2;
      }

      else {
         cor = 'b';
         troca = 1;
      }
   }

   faz_jogada(tab, cor, jog);

   return troca;
}

int caminho_completo(char **tab, jogador *jog) {
   posicao c;
   int i, j, menor;

   if (jog->cor == 'p') {
      for (i = tamanho-1; i >= 0; i--) {
         menor = 0;

         for (j = 1; j < tamanho; j++)
            if (jog->m[i][j] < jog->m[i][menor])   menor = j;

         c.x = i;
         c.y = menor;

         empilha(jog, c);
      }
   }

   else {
      for (j = 0; j < tamanho; j++) {
         menor = 0;

         for (i = 1; i < tamanho; i++)
            if (jog->m[i][j] < jog->m[menor][j])   menor = i;

         c.x = menor;
         c.y = j;

         empilha(jog, c);
      }
   }

   return jog->topo;
}

posicao posicao_critica(jogador *jog) {
   int i, p1, p2, u1, u2;

   p1 = p2 = u1 = u2 = 0;

   for (i = 1; i < jog->topo; i++)
      if (jog->m[jog->caminho[i].x][jog->caminho[i].y] !=
            jog->m[jog->caminho[u2].x][jog->caminho[u2].y])
         u2++;

      else {
         if (u1-p1 < u2-p2) {
            p1 = p2;;
            u1 = u2;
         }

         p2 = u2 = i;
      }

   return jog->caminho[(p2+u2)/2];
}

posicao decide_jogada(char **tab, jogador *jog, jogador *adv, posicao ultimo) {
   atualiza_matriz(tab, jog, ultimo);

   if (jog->m[jog->caminho[0].x][jog->caminho[0].y] < 4)   return posicao_critica(jog);

   printf("Bloqueio\n");
   return posicao_critica(adv);
}
