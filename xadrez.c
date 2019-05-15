/* 						
*****************************************************************************************************************
*																												*
*												XADREZ EM C														*	
* 					 Desenvolvido por Anderson Santos, Matheus de Sousa e Jennerson Barbosa                     *
*						Sinta-se livre para ler estudar um pouco da lógica utilizada!							*
*																												*
*****************************************************************************************************************


Última atualização: 15/05 - Organização e documentação.


 --------------------------------------------------------------
 -															  -
 -               >>> Instruções de leitura <<<                -
 -															  -
 --------------------------------------------------------------

-> 1.0 - Funções referentes aos movimentos

 --------------------------------------------------------------

-> 2.0 - Funções referentes a verificação 

 --------------------------------------------------------------

-> 3.0 - Funções de xeque
	
	3.1 - Funções para verificar o xeque
	
	3.2 - Funções ~utilizadas para verificar qual jogada tira o rei de xeque
	
	3.3 - Funções referentes ao xeque-mate
	
 --------------------------------------------------------------
	
-> 4.0 - Funções referentes a movimentos especiais
	
	4.1 - Roque
	
	4.2 - Promove o peão
	
 --------------------------------------------------------------

-> 5.0 - Funções de interface

 ---------------------------------------------------------------

-> 6.0 - Funções de chamadas [ESSENCIAS PARA A FUNÇÃO PRINCIPAL]

 ---------------------------------------------------------------

*****************************************************************************************************************

*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "xadrez.h"

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


// Criação do tabuleiro
char tabuleiro[8][8] = {
    { 'T', 'C', 'B', 'Q', 'K', 'B', 'C', 'T' },
    { 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'p' },
    { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
    { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
    { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
    { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
    { 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p' },
    { 't', 'c', 'b', 'q', 'k', 'b', 'c', 't' },
};



void xadrez(){
    int x1, y1, x2, y2, vez = 1, opt = 0;
    int kingl = 7, kingc = 4, KingL = 0, KingC = 4;
    
    setlocale(LC_ALL, "");

    while(1){
    	
    	interface_jogada(vez);
    	
        exibetabuleiro();
    
        xeque_mate(kingl, kingc, KingL, KingC, vez);

    	
        jogando(&x1, &y1, &x2, &y2);
            
        opt = chama_verificacao(x1-1, y1, x2-1, y2, vez, kingl, kingc, KingL, KingC);

        if(opt) chama_movimento(x1-1, y1, x2-1, y2, vez, opt, &kingl, &kingc, &KingL, &KingC);
        
        system("cls");
        
        if(opt) vez == 1 ? vez++ : vez--;
    }
}



/* 
	***************************************************************************************************************
	*																											  *
	*								1.0 - Funções referentes aos movimentos										  *
	*																											  *
	***************************************************************************************************************
	
*/

//    1.1 Funções relativas ao movimento das peças (usadas para determinar a movimentação da peça)


//Movimentação do rei
int rei(int x1, int y1, int x2, int y2){

    if(((x2 - x1) <= 1 && (x2 - x1) >= -1) && ((y2 - y1) <= 1 && (y2 - y1) >= -1)) return 1;

    return 0;
}


//Movimentação da rainha
int rainha(int x1, int y1, int x2, int y2){

    if(x1 != x2 && y1 != y2){ if(bispo(x1, y1, x2, y2)) return 1; }
    else if((x1 == x2 && y1 != y2) || ((x1 != x2) && y1 == y2)){ if(torre(x1, y1, x2, y2)) return 1; }

    return 0;
}


//Movimentação do bispo
int bispo(int x1, int y1, int x2, int y2){
    int i, j;

    if(x1 < x2){
        if(y1 < y2){
            for(i = (x1 + 1), j = (y1 + 1); (i < x2) && (j < y2); i++, j++){
                if(tabuleiro[i][j] != ' ') return 0;
            }
            return 1;
        }
        else if(y1 > y2){
            for(i = (x1 + 1), j = (y1 - 1); (i < x2) && (j > y2); i++, j--){
                if(tabuleiro[i][j] != ' ') return 0;
            }
            return 1;
        }
    }
    else if(x1 > x2){
        if(y1 < y2){
            for(i = (x1 - 1), j = (y1 + 1); (i > x2) && (j < y2); i--, j++) {
                if(tabuleiro[i][j] != ' ') return 0;
            }
            return 1;
        }
        else if(y1 > y2){
            for(i = (x1 - 1), j = (y1 - 1); (i > x2) && (j > y2); i--, j--) {
                if(tabuleiro[i][j] != ' ') return 0;
            }
            return 1;
        }
    }

    return 0;
}


//Movimentação do cavalo
int cavalo(int x1, int y1, int x2, int y2){

    if((y1 + 1) == y2 || (y1 - 1) == y2){
        if((x1 + 2) == x2) return 1;
        else if((x1 - 2) == x2) return 1;
    }
    if((x1 + 1) == x2 || (x1 - 1) == x2){
        if((y1 + 2) == y2) return 1;
        else if((y1 - 2) == y2) return 1;
    }

    return 0;
}


//Movimentação da torre
int torre(int x1, int y1, int x2, int y2){
    int i;

    if(x1 == x2 && y1 != y2){
        if(y1 > y2){
            for(i = y1 - 1; i > y2; i--){ if(tabuleiro[x1][i] != ' ') return 0; }
        }
        else if(y1 < y2){
            for(i = y1 + 1; i < y2; i++){ if(tabuleiro[x1][i] != ' ') return 0; }
        }
    }
    else if(x1 != x2 && y1 == y2){
        if(x1 > x2){
            for(i = x1 - 1; i > x2; i--){ if(tabuleiro[i][y1] != ' ') return 0; }
        }
        else if(x1 < x2){
            for(i = x1 + 1; i < x2; i++){ if(tabuleiro[i][y1] != ' ') return 0; }
        }
    }

    return 1;
}


//Movimentação do peão
int peao(int x1, int y1, int x2, int y2, int vez){
    int um, dois;

    if(vez == 1) um = 1, dois = 2, vez = 2;
    else um = -1, dois = -2, vez = 1;

    if((x1 - um) == x2 && y1 == y2){ if(tabuleiro[x2][y2] == ' ') return 1; }
    else if((x1 - um) == x2 && ((y1 - 1) == y2 || (y1 + 1) == y2)){ if(minhapeca(x2, y2, vez)) return 1; }
    else if((x1 - dois) == x2 && (y1 == y2) && ((x1 == 6) || (x1 == 1))){ if(tabuleiro[x1 - um][y1] == ' ' && tabuleiro[x1 - dois][y1] == ' ') return 1; }

    return 0;
}


// Movimentação efetiva da peça
void movimento(int x1, int y1, int x2, int y2, int ** x, int ** y){

    tabuleiro[x2][y2] = tabuleiro[x1][y1];
    tabuleiro[x1][y1] = ' ';

    if((tabuleiro[x2][y2] == 'p' && x2 == 0) || (tabuleiro[x2][y2] == 'P' && x2 == 7)) promove_peao(x2, y2);

    if(tabuleiro[x2][y2] == 'k') (**x) = x2, (**y) = y2;
    else if(tabuleiro[x2][y2] == 'K') (**x) = x2, (**y) = y2;
}

// Simula um movimento realizado (utilizado no reiemxeque())
void simula_movimento(int x1, int y1, int x2, int y2, char aux, int opcao){

    switch(opcao){
    case 1: //FAZ
        tabuleiro[x2][y2] = tabuleiro[x1][y1];
        tabuleiro[x1][y1] = ' ';
        break;
    case 2: //DESFAZ
        tabuleiro[x1][y1] = tabuleiro[x2][y2];
        tabuleiro[x2][y2] = aux;
        break;
    }
}


/* 
	***************************************************************************************************************
	*																											  *
	*								2.0 - Funções referentes a verificações										  *
	*																											  *
	***************************************************************************************************************
	
*/


//Função se verifica se o movimento feito é possível
int movimentopossivel(int x1, int y1, int x2, int y2, int vez){

    if(tabuleiro[x1][y1] == 'p' || tabuleiro[x1][y1] == 'P') return peao(x1, y1, x2, y2, vez);
    else if(tabuleiro[x1][y1] == 't' || tabuleiro[x1][y1] == 'T') return torre(x1, y1, x2, y2);
    else if(tabuleiro[x1][y1] == 'c' || tabuleiro[x1][y1] == 'C') return cavalo(x1, y1, x2, y2);
    else if(tabuleiro[x1][y1] == 'b' || tabuleiro[x1][y1] == 'B') return bispo(x1, y1, x2, y2);
    else if(tabuleiro[x1][y1] == 'q' || tabuleiro[x1][y1] == 'Q') return rainha(x1, y1, x2, y2);
    else if(tabuleiro[x1][y1] == 'k' || tabuleiro[x1][y1] == 'K') return rei(x1, y1, x2, y2);

    return 0;
}


//Função generalizada, vê se todas as verificações foram validadas
int verifica(int x1, int y1, int x2, int y2, int vez, int x, int y){

    if((x1 >= 0 && x1 < 8) && (y1 >= 0 && y1 < 8)){
        if((x2 >= 0 && x2 < 8) && (y2 >= 0 && y2 < 8)){
            if(minhapeca(x1, y1, vez)){
                if(minhapeca(x2, y2, vez) == 0){
                    if(movimentopossivel(x1, y1, x2, y2, vez)){
                        if(reiemxeque(x1, y1, x2, y2, vez, x, y) == 0){
                            return 1;
                        }
                    }
                }
            }
        }
    }
    if((x1 == x2) && ((y2 == y1 + 3) || (y2 == y1 - 4))){
        if((tabuleiro[x1][y1] == 'k' && tabuleiro[x2][y2] == 't' && (vez == 1)) || (tabuleiro[x1][y1] == 'K' && tabuleiro[x2][y2] == 'T' && (vez == 2))){
            if(verifica_roque(x1, y1, x2, y2, vez)){
                return 2;
            }
        }
    }

    return 0;
}


//Verifica se o rei vai ficar em xeque caso a jogada seja feita
int reiemxeque(int x1, int y1, int x2, int y2, int vez, int x, int y){
    char aux;

    aux = tabuleiro[x2][y2];

    simula_movimento(x1, y1, x2, y2, aux, 1);

    if(tabuleiro[x2][y2] == 'k' || tabuleiro[x2][y2] == 'K'){ x = x2, y = y2; }

    if(xeque(x, y, vez)){
        simula_movimento(x1, y1, x2, y2, aux, 2);
        return 1;
    }

    simula_movimento(x1, y1, x2, y2, aux, 2);

    return 0;
}


//Função que verifica qual peça o jogador escolheu
int minhapeca(int x, int y, int vez){
    char letra = (vez == 1 ? 98 : 66);

    if(tabuleiro[x][y] == letra) return 1; letra+=1;
    if(tabuleiro[x][y] == letra) return 1; letra+=8;
    if(tabuleiro[x][y] == letra) return 1; letra+=5;
    if(tabuleiro[x][y] == letra) return 1; letra+=1;
    if(tabuleiro[x][y] == letra) return 1; letra+=3;
    if(tabuleiro[x][y] == letra) return 1;

    return 0;
}


/* 
	***************************************************************************************************************
	*																											  *
	*										3.0 - Funções de xeque												  *
	*																											  *
	***************************************************************************************************************
	
*/


//    3.1 Funções para verificar se o rei está em xeque

//Verifica se o rei inimigo realiza xeque
int xequerei(int x, int y, char Rei){

    if(tabuleiro[x + 1][y] == Rei) return 1;
    else if(tabuleiro[x - 1][y] == Rei) return 1;
    else if(tabuleiro[x + 1][y + 1] == Rei) return 1;
    else if(tabuleiro[x + 1][y - 1] == Rei) return 1;
    else if(tabuleiro[x - 1][y - 1] == Rei) return 1;
    else if(tabuleiro[x - 1][y + 1] == Rei) return 1;
    else if(tabuleiro[x][y - 1] == Rei) return 1;
    else if(tabuleiro[x][y + 1] == Rei) return 1;

    return 0;
}


//Verifica se a rainha inimiga realiza xeque
int xequerainha(int x, int y, char Rainha){

    if(xequetorre(x, y, Rainha)) return 1;
    else if(xequebispo(x, y, Rainha)) return 1;

    return 0;
}


//Verifica se o bispo inimigo realiza xeque
int xequebispo(int x, int y, char Bispo){
    int i, j;

    for(i = (x + 1), j = (y + 1); (i <= 7) && (j <= 7); i++, j++){
        if(tabuleiro[i][j] == Bispo) return 1;
        else if(tabuleiro[i][j] != ' ') break;
    }
    for(i = (x + 1), j = (y - 1); (i <= 7) && (j >= 0); i++, j--){
        if(tabuleiro[i][j] == Bispo) return 1;
        else if(tabuleiro[i][j] != ' ') break;
    }
    for(i = (x - 1), j = (y - 1); (i >= 0) && (j >= 0); i--, j--){
        if(tabuleiro[i][j] == Bispo) return 1;
        else if(tabuleiro[i][j] != ' ') break;
    }
    for(i = (x - 1), j = (y + 1); (i >= 0) && (j <= 7); i--, j++){
        if(tabuleiro[i][j] == Bispo) return 1;
        else if(tabuleiro[i][j] != ' ') break;
    }

    return 0;
}


//Verifica se o cavalo inimigo realiza xeque
int xequecavalo(int x, int y, char Cavalo){

    if(tabuleiro[x + 2][y + 1] == Cavalo) return 1;
    else if(tabuleiro[x + 2][y - 1] == Cavalo) return 1;
    else if(tabuleiro[x - 2][y + 1] == Cavalo) return 1;
    else if(tabuleiro[x - 2][y - 1] == Cavalo) return 1;
    else if(tabuleiro[x + 1][y + 2] == Cavalo) return 1;
    else if(tabuleiro[x + 1][y - 2] == Cavalo) return 1;
    else if(tabuleiro[x - 1][y - 2] == Cavalo) return 1;
    else if(tabuleiro[x - 1][y + 2] == Cavalo) return 1;

    return 0;
}


//Verifica se a torre inimiga realiza xeque
int xequetorre(int x, int y, char Torre){
    int i;

    for(i = (x + 1); i <= 7; i++){
        if(tabuleiro[i][y] == Torre) return 1;
        else if(tabuleiro[i][y] != ' ') break;
    }
    for(i = (x - 1); i >= 0; i--){
        if(tabuleiro[i][y] == Torre) return 1;
        else if(tabuleiro[i][y] != ' ') break;
    }
    for(i = (y + 1); i <= 7; i++){
        if(tabuleiro[x][i] == Torre) return 1;
        else if(tabuleiro[x][i] != ' ') break;
    }
    for(i = (y - 1); i >= 0; i--){
        if(tabuleiro[x][i] == Torre) return 1;
        else if(tabuleiro[x][i] != ' ') break;
    }

    return 0;
}


//Verifica se o peão inimigo realiza xeque
int xequepeao(int x, int y, int vez, char Peao){

    switch(vez){
    case 1:
        if(tabuleiro[x-1][y+1] == Peao) return 1;
        else if(tabuleiro[x-1][y-1] == Peao) return 1;
        break;
    case 2:
        if(tabuleiro[x+1][y+1] == Peao) return 1;
        else if(tabuleiro[x+1][y-1] == Peao) return 1;
        break;
    }

    return 0;
}


//Função generalista que inclui todas as outras funções apresentadas previamente nesta seção e verificam se o xeque acontece
int xeque(int x, int y, int vez){

    switch(vez){
    case 1:
        if(xequepeao(x, y, vez, 'P')) return 1;
        else if(xequetorre(x, y, 'T')) return 1;
        else if(xequecavalo(x, y, 'C')) return 1;
        else if(xequebispo(x, y, 'B')) return 1;
        else if(xequerainha(x, y, 'Q')) return 1;
        else if(xequerei(x, y, 'K')) return 1;
        break;
    case 2:
        if(xequepeao(x, y, vez, 'p')) return 1;
        else if(xequetorre(x, y, 't')) return 1;
        else if(xequecavalo(x, y, 'c')) return 1;
        else if(xequebispo(x, y, 'b')) return 1;
        else if(xequerainha(x, y, 'q')) return 1;
        else if(xequerei(x, y, 'k')) return 1;
        break;
    }

    return 0;
}


//    3.2 Funções que verificam se alguma peça tira o rei de xeque


//Renderiza todas as possibilidades possíveis para a rainha
int renderiza_rainha(int i, int j, int x, int y, int vez){

    if(renderiza_bispo(i, j, x, y, vez)) return 1;
    else if(renderiza_torre(i, j, x, y, vez)) return 1;

    return 0;
}


//Renderiza todas as possibilidades possíveis para o bispo
int renderiza_bispo(int i, int j, int l, int c, int vez){
    int x, y;

    for(x = (i+1), y = (j+1); x <= 7 && y <= 7; x++, y++){ if(verifica(i, j, x, y, vez, l, c)) return 1; }
    for(x = (i+1), y = (j-1); x <= 7 && y >= 0; x++, y--){ if(verifica(i, j, x, y, vez, l, c)) return 1; }
    for(x = (i-1), y = (j-1); x >= 0 && y >= 0; x--, y--){ if(verifica(i, j, x, y, vez, l, c)) return 1; }
    for(x = (i-1), y = (j+1); x >= 0 && y <= 7; x--, y++){ if(verifica(i, j, x, y, vez, l, c)) return 1; }

    return 0;
}


//Renderiza todas as possibilidades possíveis para o cavalo
int renderiza_cavalo(int i, int j, int x, int y, int vez){

    if(verifica(i, j, (i+2), (j+1), vez, x, y)) return 1;
    else if(verifica(i, j, (i+2), (j-1), vez, x, y)) return 1;
    else if(verifica(i, j, (i+1), (j+2), vez, x, y)) return 1;
    else if(verifica(i, j, (i+1), (j-2), vez, x, y)) return 1;
    else if(verifica(i, j, (i-1), (j-2), vez, x, y)) return 1;
    else if(verifica(i, j, (i-1), (j+2), vez, x, y)) return 1;
    else if(verifica(i, j, (i-2), (j-1), vez, x, y)) return 1;
    else if(verifica(i, j, (i-2), (j+1), vez, x, y)) return 1;

    return 0;
}


//Renderiza todas as possibilidades possíveis para a torre
int renderiza_torre(int i, int j, int l, int c, int vez){
    int x, y;

    for(x = (i + 1); x <= 7; x++) if(verifica(i, j, x, j, vez, l, c)) return 1;
    for(x = (i - 1); x >= 0; x--) if(verifica(i, j, x, j, vez, l, c)) return 1;
    for(y = (j + 1); y <= 7; y++) if(verifica(i, j, i, y, vez, l, c)) return 1;
    for(y = (j - 1); y >= 0; y--) if(verifica(i, j, i, y, vez, l, c)) return 1;

    return 0;
}


//Renderiza todas as possibilidades possíveis para o peão
int renderiza_peao(int i, int j, int x, int y, int vez){

    switch(vez){
    case 1:
        if(verifica(i, j, (i-1), j, vez, x, y)) return 1;
        if(verifica(i, j, (i-1), (j+1), vez, x, y)) return 1;
        if(verifica(i, j, (i-1), (j-1), vez, x, y)) return 1;
        if(verifica(i, j, (i-2), j, vez, x, y)) return 1;
        break;
    case 2:
        if(verifica(i, j, (i+1), j, vez, x, y)) return 1;
        if(verifica(i, j, (i+1), (j+1), vez, x, y)) return 1;
        if(verifica(i, j, (i-1), (j-1), vez, x, y)) return 1;
	    if(verifica(i, j, (i+2), j, vez, x, y)) return 1;
	    break;
	}
	return 0;
}


//Renderiza todas as possibilidades possíveis para o rei
int mover_rei(int x, int y, int vez){

    if(verifica(x, y, (x + 1), y, vez, x, y)) return 1;
    else if(verifica(x, y, (x + 1), (y + 1), vez, x, y)) return 1;
    else if(verifica(x, y, (x + 1), (y - 1), vez, x, y)) return 1;
    else if(verifica(x, y, (x - 1), (y + 1), vez, x, y)) return 1;
    else if(verifica(x, y, (x - 1), (y - 1), vez, x, y)) return 1;
    else if(verifica(x, y, (x - 1), y, vez, x, y)) return 1;
    else if(verifica(x, y, x, (y + 1), vez, x, y)) return 1;
    else if(verifica(x, y, x, (y - 1), vez, x, y)) return 1;

    return 0;
}
	

//Função generalista que inclui todas as outras funções apresentadas previamente nesta seção e verificam se o alguma peça pode tirar o rei de xeque
int renderiza(int x, int y, int vez){
	int i, j;
	
	if(vez == 1){
	    for(i = 0; i <= 7; i++){
	        for(j = 0; j <= 7; j++){
	            if(tabuleiro[i][j] != ' '){
	                if(tabuleiro[i][j] == 'p'){ if(renderiza_peao(i, j, x, y, vez)) return 1; }
	                if(tabuleiro[i][j] == 't'){ if(renderiza_torre(i, j, x, y, vez)) return 1; }
	                if(tabuleiro[i][j] == 'c'){ if(renderiza_cavalo(i, j, x, y, vez)) return 1; }
	                if(tabuleiro[i][j] == 'b'){ if(renderiza_bispo(i, j, x, y, vez)) return 1; }
	                if(tabuleiro[i][j] == 'q'){ if(renderiza_rainha(i, j, x, y, vez)) return 1; }
	            }
	        }
	    }
	}
	else if(vez == 2){
	    for(i = 0; i <= 7; i++){
	        for(j = 0; j <= 7; j++){
	            if(tabuleiro[i][j] != ' '){
	                if(tabuleiro[i][j] == 'P'){ if(renderiza_peao(i, j, x, y, vez)) return 1; }
	                if(tabuleiro[i][j] == 'T'){ if(renderiza_torre(i, j, x, y, vez)) return 1; }
	                if(tabuleiro[i][j] == 'C'){ if(renderiza_cavalo(i, j, x, y, vez)) return 1; }
	                if(tabuleiro[i][j] == 'B'){ if(renderiza_bispo(i, j, x, y, vez)) return 1; }
	                if(tabuleiro[i][j] == 'Q'){ if(renderiza_rainha(i, j, x, y, vez)) return 1; }
	            }
	        }
	    }
	}	
	return 0;
}


//    3.3 - Funções utilizadas para verificar o xeque-mate


//Função utilizada para chamar a mover rei e verificar se é xeque-mate
int mate(int x, int y, int vez){
    if(mover_rei(x, y, vez)) return 0;
    else if(renderiza(x, y, vez)) return 0;

    return 1;
}


//Função que sinaliza o xeque mate
void xeque_mate(int kingl, int kingc, int KingL, int KingC, int vez){

    if(vez == 1){
        if(xeque(kingl, kingc, vez)){
            printf("XEQUE ");
            if(mate(kingl, kingc, 1)){
                printf("- MATE!!");
                exit(0);
            }
        }
    }
    else{
        if(xeque(KingL, KingC, vez)){
            printf("XEQUE ");
            if(mate(KingL, KingC, 2)){
                printf("- MATE!!");
                exit(0);
            }
        }
    }
}


/* 
	***************************************************************************************************************
	*																											  *
	*						4.0 - Funções referentes a movimentos especiais										  *
	*																											  *
	***************************************************************************************************************
	
*/


//    4.1 - Movimento do roque


//Realiza o movimento do roque
void movimento_roque(int x1, int y1, int x2, int y2, int ** x, int ** y){

    (**x) = x1, (**y) = y1;

    if(y1 > y2){
        tabuleiro[x1][y1 - 2] = tabuleiro[x1][y1];
        tabuleiro[x1][y2 + 3] = tabuleiro[x1][y2];
        tabuleiro[x1][y1] = ' ';
        tabuleiro[x1][y2] = ' ';
    }
    else if(y1 < y2){
        tabuleiro[x1][y1 + 2] = tabuleiro[x1][y1];
        tabuleiro[x1][y2 - 2] = tabuleiro[x1][y2];
        tabuleiro[x1][y1] = ' ';
        tabuleiro[x1][y2] = ' ';
    }
}


//Verifica se o movimento do roque é possível
int verifica_roque(int x1, int y1, int x2, int y2, int vez){

    if(xeque(x1, y1, vez) == 0){
        if(casas_livres(x1, y1, y2)){
            if(xeque(x1, y2 > y1 ? (y1+2) : (y1-2), vez) == 0){ system("pause");
                if(casas_em_xeque(x1, y1, y2, vez)){
                    return 1;
                }
            }
        }
    }

    return 0;
}

//Verifica se alguma das casas da movimentação do roque deixa o rei em xeque
int casas_em_xeque(int x, int y1, int y2, int vez){
    int j;

    if(y2 > y1){
        for(j = (y1 + 1); j < y2; j++){
            if(xeque(x, j, vez)) return 0;
        }
    }
    else if(y2 < y1){
        for(j = (y1 - 1); j > y2; j--){
            if(xeque(x, j, vez)) return 0;
        }
    }

    return 1;
}


//Verifica se todas as casas ao lado do rei estão livres para que a movimentação do roque seja efetiva 
int casas_livres(int x, int y1, int y2){
    int j;

    if(y1 < y2){
        for(j = (y1 + 1); j < y2; j++){
            if(tabuleiro[x][j] != ' ') return 0;
        }
    }
    else if(y1 > y2){
        for(j = (y1 - 1); j > y2; j--){
            if(tabuleiro[x][j] != ' ') return 0;
        }
    }

    return 1;
}


//    4.1 - Movimento da promoção do peão


// Promover o peão
void promove_peao(int x2, int y2){
    int aux, repete = 1;

    while(repete){
        puts("\n>> ");
        puts("Qual peça você deseja promover?: ");
        puts(" -- 1. Rainha");
        puts(" -- 2. Bispo");
        puts(" -- 3. Cavalo");
        puts(" -- 4. Torre");
        printf(" -> ");
        scanf("%d", &aux);
        switch(x2){
        case 0:
            if(aux == 1) tabuleiro[x2][y2] = 'q', repete = 0;
            else if(aux == 2) tabuleiro[x2][y2] = 'b', repete = 0;
            else if(aux == 3) tabuleiro[x2][y2] = 'c', repete = 0;
            else if(aux == 4) tabuleiro[x2][y2] = 't', repete = 0;
            break;
        case 7:
            if(aux == 1) tabuleiro[x2][y2] = 'Q';
            else if(aux == 2) tabuleiro[x2][y2] = 'B', repete = 0;
            else if(aux == 3) tabuleiro[x2][y2] = 'C', repete = 0;
            else if(aux == 4) tabuleiro[x2][y2] = 'T', repete = 0;
            break;
        }
    }
    system("cls");
}


/* 
	***************************************************************************************************************
	*																											  *
	*						5.0 - Funções referentes a exibição da interface									  *
	*																											  *
	***************************************************************************************************************
	
*/


// Funções referente a exibição do tabuleiro
void exibetabuleiro(){
    int i, j;
    
    for(i = 0; i < 8; i++){
    	printf("%d ", i+1);
        for(j = 0; j < 8; j++){
            printf("%c ", tabuleiro[i][j]);
        }
        putchar('\n');
    }
    printf("  ");
    for(i=65;i<73;i++) printf("%c ", i);
    putchar('\n');
}


void interface_jogada(int vez){
	if(vez == 1) printf("    JOGADOR 1\n");
    else printf("   JOGADOR 2\n");
    putchar('\n');
}


void jogando(int * x1, int * y1, int * x2, int * y2){
	char posicaotemp1, posicaotemp2;
    printf(">> Insira a coordenada da peça você quer jogar: ");
    scanf("%c %d", &posicaotemp1, x1);
    getchar();
    switch(posicaotemp1){
    	case 'a':
    		*y1 = 0;
    		break;
    	case 'b':
    		*y1 = 1; 
    		break;
    	case 'c':
    		*y1 = 2; 
    		break;
    	case 'd':
    		*y1 = 3; 
    		break;
    	case 'e':
    		*y1 = 4; 
    		break;
    	case 'f':
    		*y1 = 5; 
    		break;
    	case 'g':
    		*y1 = 6; 
    		break;
    	case 'h':
    		*y1 = 7; 
    		break;
	}
    
    printf(">> Insira a coordenada do lugar em que você quer jogar:  ");
    scanf("%c %d", &posicaotemp2, x2);
    getchar();
    switch(posicaotemp2){
    	case 'a':
    		*y2 = 0;
    		break;
    	case 'b':
    		*y2 = 1; 
    		break;
    	case 'c':
    		*y2 = 2; 
    		break;
    	case 'd':
    		*y2 = 3; 
    		break;
    	case 'e':
    		*y2 = 4; 
    		break;
    	case 'f':
    		*y2 = 5; 
    		break;
    	case 'g':
    		*y2 = 6; 
    		break;
    	case 'h':
    		*y2 = 7; 
    		break;
	}
}


/* 
	***************************************************************************************************************
	*																											  *
	*						6.0 - Funções de chamadas [ESSENCIAS PARA A FUNÇÃO PRINCIPAL] 						  *
	*																											  *
	***************************************************************************************************************
	
*/


//Funções que chama a verificação de peças
int chama_verificacao(int x1, int y1, int x2, int y2, int vez, int  kingl, int  kingc, int  KingL, int  KingC){

    switch(vez){
    case 1:
        return (verifica(x1, y1, x2, y2, vez, kingl, kingc));
        break;
    case 2:
        return (verifica(x1, y1, x2, y2, vez, KingL, KingC));
        break;
    }

    return 0;
}


//Função que chama os movimentos e as funções necessárias para o movimento
void chama_movimento(int x1, int y1, int x2, int y2, int vez, int opt, int * kingl, int * kingc, int * KingL, int * KingC){

    switch(vez){
    case 1:
        if(opt == 1){
            movimento(x1, y1, x2, y2, &kingl, &kingc);
        }
        else if(opt == 2){
            movimento_roque(x1, y1, x2, y2, &kingl, &kingc);
        }
        break;

    case 2:
        if(opt == 1){
            movimento(x1, y1, x2, y2, &KingL, &KingC);
        }
        else if(opt == 2){
            movimento_roque(x1, y1, x2, y2, &KingL, &KingC);
        }
        break;
    }
}

