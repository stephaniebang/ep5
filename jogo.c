/* Stephanie Eun Ji Bang   n.USP 8994414 */

#include "jogo.h"
#include "jogador.h"
#include <stdlib.h>
#include <stdio.h>


/*********************
* Funcoes auxiliares *
*********************/
int jogada_valida(char **tab, posicao jog) {
   /* A funcao recebe o tabuleiro tab e a posicao jog e retorna 1, se for
    * possivel realizar essa jogada, ou retorna 0, caso contrario. */
   if (jog.x < 0 || jog.x >= tamanho || jog.y < 0 || jog.y >= tamanho)
      return 0;

   if (tab[jog.x][jog.y] != '-')   return 0;

   return 1;
}

posicao posicao_critica(char **tab, jogador *jog) {
   /* A funcao retorna a posicao da jogada mais importante dentro do vetor
    * caminho do jogador jog, sendo na maioria das vezes uma jogada ainda nao
    * realizada. */
   int i, p1, p2, u1, u2;

   p1 = p2 = u1 = u2 = 0;

   for (i = 1; i < jog->topo; i++)
      if (jog->m[jog->caminho[i].x][jog->caminho[i].y] !=
            jog->m[jog->caminho[u2].x][jog->caminho[u2].y])
         u2++;

      else {
         if (u1-p1 < u2-p2) {
            p1 = p2;
            u1 = u2;
         }

         p2 = u2 = i;
      }

   if (tab[jog->caminho[(p1+u1)/2].x][jog->caminho[(p1+u1)/2].y] == '-')
      return jog->caminho[(p1+u1)/2];

   for (i = 1; i < (u1-p1)/2; i++) {
      if (tab[jog->caminho[i+(p1+u1)/2].x][jog->caminho[i+(p1+u1)/2].y] == '-')
         return jog->caminho[i+(p1+u1)/2];

      if (tab[jog->caminho[-i+(p1+u1)/2].x][jog->caminho[-i+(p1-u1)/2].y] == '-')
         return jog->caminho[-i+(p1+u1)/2];
   }

   return jog->caminho[(p2+u2)/2];
}


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

void destroi_tabuleiro(char **tab) {
   int i;

   for (i = 0; i < tamanho; i++)
      free(tab[i]);

   free(tab);
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

posicao decide_jogada(char **tab, jogador *jog, jogador *adv, posicao ultimo) {
   posicao ret;
   atualiza_matriz(tab, jog, ultimo);

   ret = posicao_critica(tab, adv);

   if (tab[ret.x][ret.y] == '-')   return ret;
      
   ret = posicao_critica(tab, jog);

   if (tab[ret.x][ret.y] != '-') {
      for (ret.x = 0; ret.x < tamanho; ret.x++)
         for (ret.y = 0; ret.y < tamanho; ret.y++)
            if (tab[ret.x][ret.y] == '-')   return ret;
   }

   return ret;
}
