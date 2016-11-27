/* Stephanie Eun Ji Bang   n.USP 8994414 */

#include "jogo.h"
#include <stdlib.h>
#include <stdio.h>


int tamanho = 11;   /* Tamanho do tabuleiro */
int impressao = 0;   /* Flag para impressao */


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


/************************
* Funcoes de estrategia *
************************/
int pie_rule(char **tab, coordenadas jog, char cor) {
   int troca = 0;

   if (cor == 'p') {
      if (jog.x < 2 || jog.x > tamanho-3 || jog.y < 2 || jog.y > tamanho-3) {
         jog.x = tamanho/2;
         jog.y = tamanho/2;
      }

      else {
         cor = 'b';
         troca = 1;
      }

      faz_jogada(tab, cor, jog);
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

int caminho_completo(char **tab, char cor) {
   int i, j, menor, **m, k;

   m = malloc(tamanho*sizeof(int *));

   for (i = 0; i < tamanho; i++)
      m[i] = malloc(tamanho*sizeof(int));

   printf("\nImpressao da matriz de caminho da peca %c\n", cor);

   if (cor == 'p') {
      for (i = 0; i < tamanho; i++)
         if (tab[i][0] == 'p')   m[i][0] = 0;

         else   m[i][0] = 1;

      for (j = 1; j < tamanho; j++) {
         for (i = 0; i < tamanho; i++) {
            menor = menor_anterior(m, i , j, 'p');
           
            if (tab[i][j] == 'p')   m[i][j] = menor;

            else   m[i][j] = menor+1;
         }
      }

      menor = m[0][tamanho-1];

      for (i = 1; i < tamanho; i++)
         if (menor > m[i][tamanho-1])   menor = m[i][tamanho-1];
   }

   else {
      for (j = 0; j < tamanho; j++)
         if (tab[0][j] == 'b')   m[0][j] = 0;

         else   m[0][j] = 1;

      for (i = 1; i < tamanho; i++) {
         for (j = 0; j < tamanho; j++) {
            menor = menor_anterior(m, i, j, 'b');

            if (tab[i][j] == cor)   m[i][j] = menor;

            else   m[i][j] = menor+1;
         }
      }

      menor = m[tamanho-1][0];

      for (j = 1; j < tamanho; j++)
         if (menor > m[tamanho-1][j]);
   }

   for (i = 0; i < tamanho; i++) {
      for (k = 0; k < i; k++)   printf("  ");

      for (j = 0; j < tamanho; j++)
         printf("%d ", m[i][j]);

      printf("\n");
   }

   for (i = 0; i < tamanho; i++)   free(m[i]);
   
   free(m);

   return menor;
}

int absoluto(int x) {
   if (x < 0)   return -x;

   return x;
}

int uma_borda(coordenadas c1, coordenadas c2) {
   if (absoluto(c1.x-c2.x) == 1)
      if (absoluto(c1.y-c2.y) == 1 || absoluto(c1.y-c2.y) == 2)   return 1;

   if (absoluto(c1.x-c2.x) == 2 && absoluto(c1.y-c2.y) == 1)   return 1;

   return 0;
}

int duas_bordas(coordenadas c1, coordenadas c2) {
   if (absoluto(c1.x-c2.x) == 1)
      if (absoluto(c1.y-c2.y) == 2 || absoluto(c1.y-c2.y) == 3)   return 1;

   if (absoluto(c1.x-c2.x) == 2)
      if (absoluto(c1.y-c2.y) == 1 || absoluto(c1.y-c2.y) == 3)   return 1;

   if (absoluto(c1.x-c2.x) == 3)
      if (absoluto(c1.y-c2.y) == 1 || absoluto(c1.y-c2.y) == 2)   return 1;

   return 0;
}

int tres_bordas(coordenadas c1, coordenadas c2) {
   if (absoluto(c1.x-c2.x) == 1)
      if (absoluto(c1.y-c2.y) == 3 || absoluto(c1.y-c2.y) == 4)   return 1;

   if (absoluto(c1.x-c2.x) == 2)
      if (absoluto(c1.y-c2.y) == 2 || absoluto(c1.y-c2.y) == 4)   return 1;

   if (absoluto(c1.x-c2.x) == 3)
      if (absoluto(c1.y-c2.y) == 1 || absoluto(c1.y-c2.y) == 4)   return 1;

   if (absoluto(c1.x-c2.x) == 4)
      if (absoluto(c1.y-c2.y) < 0 && absoluto(c1.y-c2.y) > 4)   return 1;

   return 0;
}

int um_entre(coordenadas c1, coordenadas c2) {
   if (absoluto(c1.x-c2.x) == 1)
      if (absoluto(c1.y-c2.y) == 1 || absoluto(c1.y-c2.y) == 2)
         return 1;

   if (absoluto(c1.x-c2.y) == 2 && absoluto(c1.y-c2.y) == 1)
      return 1;

   return 0;
}

int dois_entre(coordenadas c1, coordenadas c2) {
   if (absoluto(c1.x-c2.x) == 3)
      if (c1.y == c2.y || absoluto(c1.y-c2.y) == 3)   return 1;

   if (absoluto(c1.y-c2.y) == 3)
      if (c1.x == c2.x || absoluto(c1.x-c2.x) == 3)   return 1;

   return 0;
}

int tres_entre(coordenadas c1, coordenadas c2) {
    if (absoluto(c1.x-c2.x) == 4)
      if (c1.y == c2.y || absoluto(c1.y-c2.y) == 4)   return 1;

   if (absoluto(c1.y-c2.y) == 4)
      if (c1.x == c2.x || absoluto(c1.x-c2.x) == 4)   return 1;

   return 0;  
}

coordenadas decide_jogada(char **tab, char cor, coordenadas novo, coordenadas ant) {
   coordenadas r;

   for (r.x = 0; r.x < tamanho; r.x++)
      for (r.y = 0; r.y < tamanho; r.y++)
         if (tab[r.x][r.y] == '-')   return r;
/*   if (um_entre(novo, ant)) ;*/
}
