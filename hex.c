/* Stephanie Eun Ji Bang   n.USP 8994414 */

#include <stdlib.h>
#include <stdio.h>
#include "jogador.h"
#include "jogo.h"
#include "tipos.h"


int tamanho = 14;
int impressao = 0;

int main(int argc, char *argv[]) {
   char **tab;
   posicao jogada;
   jogador *adversario, *eu;

   /* Inicializando o jogo */
   tab = cria_tabuleiro();
   eu = cria_jogador(tamanho);
   adversario = cria_jogador(tamanho);
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
   while (!caminho_completo(tab, eu)) {
      /* Recebendo a jogada do adversario */
      jogada = recebe_jogada(tab, adversario->cor);

      atualiza_matriz(tab, adversario, jogada);

      if (caminho_completo(tab, adversario))
         break;

      /* Decidindo e efetuando a propria jogada */
      jogada = decide_jogada(tab, eu, adversario, jogada);

      faz_jogada(tab, eu->cor, jogada);

      atualiza_matriz(tab, adversario, jogada);
      atualiza_matriz(tab, eu, jogada);
   }

   if (!(eu->m[eu->caminho[0].x][eu->caminho[0].y]))
      printf("%c ganhou\n", eu->cor);

   else   printf("%c ganhou\n", adversario->cor);

   destroi_tabuleiro(tab);
   destroi_jogador(adversario);
   destroi_jogador(eu);

   return 0;
}
