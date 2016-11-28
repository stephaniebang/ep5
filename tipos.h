#ifndef __TIPOS_H__
#define __TIPOS_H__


extern int tamanho;   /* Tamanho do tabuleiro */
extern int impressao;   /* Flag para impressao */

typedef struct {
   int x, y;
} posicao;

typedef struct {
   int **m;
   posicao *caminho;
   char cor;
   int topo, max;
} jogador;


#endif
