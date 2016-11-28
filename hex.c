/* Stephanie Eun Ji Bang   n.USP 8994414 */

#include <stdlib.h>
#include <stdio.h>
#include "jogador.h"
#include "jogo.h"
#include "tipos.h"


int tamanho = 12;
int impressao = 0;

int main(int argc, char *argv[]) {
   char **tab;
   posicao jogada;
   jogador *adversario, *eu;
int i;
   /* Inicializando o jogo */
   tab = cria_tabuleiro();
   eu = cria_jogador(2*tamanho);
   adversario = cria_jogador(2*tamanho);
   eu->cor = argv[1][0];

   if (argc == 3 && argv[2][0] == 'd')   impressao = 1;

   /* Realizando as jogadas iniciais */
   if (eu->cor == 'b') {   /* Se eu for o primeiro jogador */
      adversario->cor = 'p';
      jogada.x = tamanho-3;
      jogada.y = 0;

      faz_jogada(tab, eu->cor, jogada);
   }

   else if (eu->cor == 'p') {   /* Se eu for o segundo jogador */
      adversario->cor = 'b';
      jogada = recebe_jogada(tab, adversario->cor);
   }

   else   return 0;

   /* Aplicando uma possivel pie rule */
   if (pie_rule(tab, jogada, eu->cor))   /* Se houver troca de jogadores */
      troca_jogadores(&(eu->cor), &(adversario->cor));

   inicializa_matriz(tab, eu);
   inicializa_matriz(tab, adversario);

   /* Continuando o jogo ate alguem completar um caminho */
   while (eu->m[eu->caminho[0].x][eu->caminho[0].y]) {
      /* Recebendo a jogada do adversario */
      jogada = recebe_jogada(tab, adversario->cor);

      atualiza_matriz(tab, adversario, jogada);

      if (!adversario->m[adversario->caminho[0].x][adversario->caminho[0].y])
         break;

      /* Decidindo e efetuando a propria jogada */
      jogada = decide_jogada(tab, eu, adversario, jogada);

      faz_jogada(tab, eu->cor, jogada);

      atualiza_matriz(tab, adversario, jogada);
      atualiza_matriz(tab, eu, jogada);

      printf("Meu caminho(%c): ", eu->cor);

      for (i = 0; i < eu->topo; i++)   printf("(%d, %d) ", eu->caminho[i].x, eu->caminho[i].y);

      printf("\nCaminho adv(%c): ", adversario->cor);
      for (i = 0; i < adversario->topo; i++)
         printf("(%d, %d) ", adversario->caminho[i].x, adversario->caminho[i].y);
      printf("\n");
   }

   if (!(eu->m[eu->caminho[0].x][eu->caminho[0].y]))
      printf("%c ganhou\n", eu->cor);

   else   printf("%c ganhou\n", adversario->cor);

   return 0;
}
