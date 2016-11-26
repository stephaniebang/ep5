/* Stephanie Eun Ji Bang   n.USP 8994414 */

#include <stdlib.h>
#include <stdio.h>
#include "jogador.h"
#include "jogo.h"


int main(int argc, char *argv[]) {
   char peca, **tab;
   coordenadas jogada;
   jogador *adversario;

   /* Inicializando o jogo */
   tab = cria_tabuleiro();
   peca = argv[1][0];
   adversario = cria_jogador(50);

   if (argc == 3 && argv[2][0] == 'd')   impressao = 1;

   /* Realizando a primeira rodada de jogadas */
   if (peca == 'b') {   /* Se for o primeiro jogador */
      adversario->cor = 'p';
      jogada.x = tamanho-3;
      jogada.y = 0;

      faz_jogada(tab, peca, jogada);
   }

   if (peca == 'p') {   /* Se for o segundo jogador */
      adversario->cor = 'b';
      jogada = recebe_jogada(tab, adversario->cor);
   }

   if (pie_rule(tab, jogada, peca))
      troca_jogadores(&peca, &(adversario->cor));

   /* Continuando o jogo ate alguem completar um caminho /
   while (!caminho_completo(tab, peca) && !caminho_completo(tab, adversario->cor)) {
      * Recebendo e guardando a jogada do adversario /
      jogada = recebe_jogada(tab, adversario->cor);

      empilha(adversario, jogada);

      * Escolhendo e realizando a propria jogada *
      jogada = decide_jogada(tab, peca);

      faz_jogada(tab, peca, jogada, impressao);
   }*/

   return 0;
}
