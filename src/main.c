/**
 gcc ./src/*.c -I./include -o penalty
 ./penalty
*/

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> 

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

int x = 75, y = 45; // Ponto zero da bola
int incX = 1, incY = 1;

typedef struct {
    int x;
    int y;
}Coordenada;

int oddsDefesa()
{
    // 0 = esquerda baixo
    // 1 = meio baixo
    // 2 = direita baixo
    // 3 = esquerda alto
    // 4 = meio alto
    // 5 = direita alto
    int x;
    srand(time(NULL));
    x = rand() % 6;
    return x;
}

void printaBola()
{
    printf("⚽");
}

void printaCobrador()
{
    printf("    \\O\n");
    printf("    /\\\n");
    printf(" __/\\ `\n");
    printf("`    \\,\n");  

}

void printPlacar(int a, int b) {

    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(74, 48);
    printf("%d X %d", a, b);

}


void movimentaBola(int nextX, int nextY)
{
    screenSetColor(CYAN, DARKGRAY);
    
    // LIMPA A ÁREA DA BOLA
    screenGotoxy(x, y); 
    printf("   "); 

    
    x = nextX;
    y = nextY;

    screenGotoxy(x, y);
    printaBola();

}

void pageWelcome()
{

    screenInit(0);

    printf(" ____                  _ _            ____                      \n");
    printf("|  _ \\ ___ _ __   __ _| | |_ _   _   / ___| __ _ _ __ ___   ___ \n");
    printf("| |_) / _ \\ '_ \\ / _` | | __| | | | | |  _ / _` | '_ ` _ \\ / _ \\\n");
    printf("|  __/  __/ | | | (_| | | |_| |_| | | |_| | (_| | | | | | |  __/\n");
    printf("|_|   \\___|_| |_|\\__,_|_|\\__|\\__, |  \\____|\\__,_|_| |_| |_|\\___|\n");
    printf("                             |___/                               \n");

    printf("\nDigite o número da opção escolhida:\n\n");
    printf(" [1]   Modo um jogador\n [2]   Modo dois jogadores\n [3]   Como jogar\n [4]   Pontuações salvas\n");

}

void pageManual(){

    screenInit(0);

    printf("  ____                            _                        \n");
    printf(" / ___|___  _ __ ___   ___       | | ___   __ _  __ _ _ __ \n");
    printf("| |   / _ \\| '_ ` _ \\ / _ \\   _  | |/ _ \\ / _` |/ _` | '__|\n");
    printf("| |__| (_) | | | | | | (_) | | |_| | (_) | (_| | (_| | |   \n");
    printf(" \\____\\___/|_| |_| |_|\\___/   \\___/ \\___/ \\__, |\\__,_|_|   \n");
    printf("                                          |___/            \n");

    printf("\nUse as teclas A, W e D para cobrar o pênalti.\n");
    printf("\nVocê terá 5 chances de fazer gol. Caso a sua pontuação seja superior à do goleiro, você vence.\n\n");
    printf("  A ➡️ chuta para a esquerda\n  W ➡️ chuta para o meio\n  D ➡️ chuta para a direita\n\n");
    printf(" [1]   Iniciar o jogo\n [0]   Voltar à tela inicial\n");
}

void pageScores() {
    
    screenInit(0);

    printf(" ____                          \n");
    printf("/ ___|  ___ ___  _ __ ___  ___ \n");
    printf("\\___ \\ / __/ _ \\| '__/ _ \\/ __|\n");
    printf(" ___) | (_| (_) | | |  __/\\__ \\\n");
    printf("|____/ \\___\\___/|_|  \\___||___/\n");


}

void printGoalKeeper(){
    printf("       @\n");
    printf("   _ _/  \\_ _\n");
    printf("  / _      _ \\\n");
    printf(" / / |    | \\ \\\n");
    printf("|||  |____|  |||\n");
    printf("     |	  |\n");
    printf("     |_ |_|\n");
    printf("      || ||\n");
    printf("     <_| |_>\n");
}

int singlePlayer() 
{
    int chances = 0;
    int t_1 = 0, t_2 = 0;
    static int lado = 0;
    static int ch = 0;
    int ins = 0, outs = 0;
    int i = 0;

    Coordenada esquerdaAlto = {40, 12};
    Coordenada esquerdaBaixo = {40, 20};
    Coordenada meioAlto = {75, 12};
    Coordenada meioBaixo = {75, 20};
    Coordenada direitaAlto = {110, 12};
    Coordenada direitaBaixo = {110, 20};

    screenInit(1); // Com parametro falso, a quadra nao starta
    printGoalKeeper();
    keyboardInit();
    timerInit(50);
    printaCobrador();
    movimentaBola(x, y);
    screenUpdate();

    while (ch != 10 && chances<5)
    {

        if (keyhit()) 
        {
            i+=1;
            t_1 = readch();
            t_2 = readch();
            lado = t_1+t_2;
            int def = oddsDefesa();
            int alvo_x = 0, alvo_y = 0;
            
            if (lado == 212) { // A+S
	            if (def != 0) {
		            ins+=1;
	            }
	            else {
		            outs+=1;
	            }

	            alvo_x = esquerdaBaixo.x;
	            alvo_y = esquerdaBaixo.y;
            }

            else if (lado == 230) { // W+S
	            if (def != 1) {
		            ins+=1;
	            }
	            else {
		            outs+=1;
	            }

	            alvo_x = meioBaixo.x;
	            alvo_y = meioBaixo.y;
            }

            else if (lado == 215) { // D+S
	            if (def != 2) {
		            ins+=1;
	            }
	            else {
		            outs+=1;
	            }

	            alvo_x = direitaBaixo.x;
	            alvo_y = direitaBaixo.y;
            }

            else if (lado == 216) { // A+W
	            if (def != 3) {
		            ins+=1;
	            }
	            else {
		            outs+=1;
	            }

	            alvo_x = esquerdaAlto.x;
	            alvo_y = esquerdaAlto.y;
            }

            else if (lado == 234) { // W+W
	            if (def != 4) {
		            ins+=1;
	            }
	            else {
		            outs+=1;
	            }

	            alvo_x = meioAlto.x;
	            alvo_y = meioAlto.y;
            }

            else if (lado == 219) { // D+W
	            if (def != 5) {
		            ins+=1;
	            }
	            else {
		            outs+=1;
	            }

	            alvo_x = direitaAlto.x;
	            alvo_y = direitaAlto.y;
            }

            else{ //chutou pra fora
                outs+=1;
            }

            movimentaBola(alvo_x,alvo_y);
            printPlacar(ins,outs);
	        screenUpdate();

            sleep(1);
            screenGotoxy(alvo_x,alvo_y);
            printf(" ");
            screenUpdate();
            screenGotoxy(75,45);
            printf("              ");
            movimentaBola(75,45);
            screenUpdate();
            chances +=1;
            
        }

        // Update game state (move elements, verify collision, etc)
        
        // if (timerTimeOver() == 2)
        // {
        //     int newX = x + incX;
        //     if (newX >= direitaBaixo.x - 1 || newX <= MINX + 1) incX = -incX;
        //     int newY = y - incY;
        //     if (newY >= MAXY - 1 || newY <= direitaBaixo.y + 1) incY = -incY;

        //     movimentaBola(newX, newY);

        //     screenUpdate();
        // }
        
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}

int dualPlayer() {
    printGoalKeeper();
    return 0;
}

int main() 
{   
    static int ch = 0, ch_m = 0;
    pageWelcome();
    keyboardInit();
    
    while (ch!=10) {

        if (keyhit()) {
            ch = readch();

            if (ch == 49) {
                screenUpdate();
                singlePlayer();
            }
            else if (ch == 50) {
                screenDestroy();
                dualPlayer(); // TODO: dualPlayer()
            }
            else if (ch == 51) {
                screenDestroy();
                pageManual();
                if (keyhit()) {
                    ch_m = readch();
                    if (ch_m == 48) {
                        pageWelcome();
                    }
                }
            }
            else if (ch == 51) {
                screenDestroy();
                pageScores();
            }
        }

    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}


// Essa será a coordenada 0 da bola
// Ponto zero: 50,30
// Meio do gol: 50, 10
// Lado esquerdo gol: 30, 10
// Lado direito gol: 70, 10