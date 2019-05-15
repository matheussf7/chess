#ifndef XADREZ_H
#define XADREZ_H

extern char tabuleiro[8][8];

//Função principal
void xadrez();

//1.0 - Funções referentes ao movimento
int rei(int x1, int y1, int x2, int y2);
int rainha(int x1, int y1, int x2, int y2);
int bispo(int x1, int y1, int x2, int y2);
int cavalo(int x1, int y1, int x2, int y2);
int torre(int x1, int y1, int x2, int y2);
int peao(int x1, int y1, int x2, int y2, int vez);
void movimento(int x1, int y1, int x2, int y2, int **x, int **y);
void simula_movimento(int x1, int y1, int x2, int y2, char aux, int opcao);

//2.0 - Funções referentes a movimentações
int movimentopossivel(int x1, int y1, int x2, int y2, int vez);
int verifica(int x1, int y1, int x2, int y2, int vez, int x, int y);
int reiemxeque(int x1, int y1, int x2, int y2, int vez, int x, int y);
int minhapeca(int x, int y, int vez);

//3.0 - Funções de xeque
int xequerei(int x, int y, char Rei);
int xequerainha(int x, int y, char Rainha);
int xequebispo(int x, int y, char Bispo);
int xequecavalo(int x, int y, char Cavalo);
int xequetorre(int x, int y, char Torre);
int xequepeao(int x, int y, int vez, char Peao);
int xeque(int x, int y, int vez);
int renderiza_rainha(int i, int j, int x, int y, int vez);
int renderiza_bispo(int i, int j, int l, int c, int vez);
int renderiza_cavalo(int i, int j, int x, int y, int vez);
int renderiza_torre(int i, int j, int l, int c, int vez);
int renderiza_peao(int i, int j, int x, int y, int vez);
int mover_rei(int x, int y, int vez);
int renderiza(int x, int y, int vez);
int mate(int x, int y, int vez);
void xeque_mate(int kingl, int kingc, int KingL, int KingC, int vez);

//4.0 - Funções referentes a movimentos especiais
void movimento_roque(int x1, int y1, int x2, int y2, int **x, int **y);
int verifica_roque(int x1, int y1, int x2, int y2, int vez);
int casas_em_xeque(int x, int y1, int y2, int vez);
int casas_livres(int x, int y1, int y2);
void promove_peao(int x2, int y2);

//5.0 - Funções referentes a exibição da interface
void exibetabuleiro();
void interface_jogada(int vez);
void jogando(int *x1, int *y1, int *x2, int *y2);

//6.0 - Funções de chamada
int chama_verificacao(int x1, int y1, int x2, int y2, int vez, int kingl, int king, int KingL, int KingC);
void chama_movimento(int x1, int y1, int x2, int y2, int vez, int opt, int *kingl, int *kingc, int *KingL, int  *KingC);


#endif
