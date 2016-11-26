/* Stephanie Eun Ji Bang   n.USP 8994414 */

#include "jogo.h"
#include <stdlib.h>
#include <stdio.h>


int tamanho = 14;   /* Tamanho do tabuleiro */
int impressao = 0;   /* Flag para impressao */

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
   int i, j;

   for (i = 0; i < tamanho; i++) {
      for (j = 0; j < tamanho; j++)
         printf("%c ", tab[i][j]);

      printf("\n");
   }
}

void faz_jogada(char **tab, char cor, coordenadas jog) {
   tab[jog.x][jog.y] = cor;

   printf("%d %d\n", jog.x, jog.y);

   if (impressao)   imprime_tabuleiro(tab);
}

int jogada_valida(char **tab, coordenadas jog) {
   if (jog.x < 0 || jog.x >= tamanho || jog.y < 0 || jog.y >= tamanho)
      return 0;

   if (tab[jog.x][jog.y] != '-')   return 0;

   return 1;
}

coordenadas recebe_jogada(char **tab, char cor) {
   coordenadas jog;

   scanf("%d %d", &jog.x, &jog.y);

   while (!jogada_valida(tab, jog)) {
      printf("Jogada invalida. Digite outra jogada.\n");
      scanf("%d %d", &jog.x, &jog.y);
   }

   tab[jog.x][jog.y] = cor;

   return jog;
}

int pie_rule(char **tab, coordenadas jog, char cor) {
   int troca = 0;

   if (cor == 'p') {
      if (jog.x < 2 || jog.x > tamanho-3 || jog.y < 2 || jog.y > tamanho-3) {
         jog.x = tamanho/2;
         jog.y = tamanho/2;
      }

      else   troca = 1;

      faz_jogada(tab, 'p', jog);
   }

   else {
      scanf("%d %d", &jog.x, &jog.y);

      while (jog.x < 0 || jog.x >= tamanho || jog.y < 0 || jog.y >= tamanho) {
         printf("Jogada invalida. Digite outra jogada.\n");
         scanf("%d %d", &jog.x, &jog.y);
      }

      if (tab[jog.x][jog.y] == 'p')   troca = 1;

      tab[jog.x][jog.y] = 'b';
   }

   return troca;
}

coordenadas proximo(char **tab, char cor, coordenadas inicio);

int caminho_completo(char **tab, char cor);

coordenadas decide_jogada(char **tab, char cor);
