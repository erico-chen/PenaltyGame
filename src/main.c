/**
 gcc ./src/*.c -I./include -o penalty
 ./penalty
*/

#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

int x = 50, y = 30; // Ponto zero da bola
int incX = 1, incY = 1;

typedef struct {
    int x;
    int y;
}Coordenada;

int oddsDefesa() {
    // 0 = esquerda baixo
    // 1 = meio baixo
    // 2 = direita baixo
    srand(time(NULL));
    return rand() % 3;
}

void printaBola() {
    printf("⚽");
}

void printaCobrador() {
    printf("    \\O\n");
    printf("    /\\\n");
    printf(" __/\\ `\n");
    printf("`    \\,\n");  

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

void welcome() {
    screenInit(0);

    printf(" ___  ___  ________  ________  ________          ________  ________     \n");
    printf("|\\  \\|\\  \\|\\   __  \\|\\   __  \\|\\   __  \\        |\\   ___ \\\\|\\   __  \\    \n");
    printf("\\ \\  \\\\\\  \\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\|\\  \\       \\ \\  \\_|\\ \\\\ \\  \\|\\  \\   \n");
    printf(" \\ \\   __  \\ \\  \\\\\\  \\ \\   _  _\\\\ \\   __  \\       \\ \\  \\ \\\\ \\\\ \\  \\\\\\  \\  \n");
    printf("  \\ \\  \\ \\  \\ \\  \\\\\\\\  \\ \\  \\\\  \\\\ \\  \\ \\  \\       \\ \\  \\_\\\\ \\\\ \\  \\\\\\  \\ \n");
    printf("   \\ \\__\\ \\__\\ \\_______\\ \\__\\\\ _\\\\ \\__\\ \\__\\       \\ \\_______\\\\ \\_______\\ \n");
    printf("    \\|__|\\|__|\\|_______|\\|__|\\|__|\\|__|\\|__|        \\|_______|\\|_______| \n");
    printf(" ________  ________  ___       ___                                      \n");
    printf("|\\   ____\\|\\   __  \\|\\  \\     |\\  \\                                     \n");
    printf("\\ \\  \\___|\\ \\  \\|\\  \\ \\  \\    \\ \\  \\                                    \n");
    printf(" \\ \\  \\  __\\ \\  \\\\\\  \\ \\  \\    \\ \\  \\                                   \n");
    printf("  \\ \\  \\|\\  \\ \\  \\\\\\  \\ \\  \\____\\ \\__\\                                  \n");
    printf("   \\ \\_______\\ \\_______\\ \\_______\\|__|                                  \n");
    printf("    \\|_______|\\|_______|\\|_______|   ___                                \n");
    printf("                                    |\\__\\                               \n");
    printf("                                    \\|__|                               \n");
    printf("Escolha o modo de jogo:\n1 - Um jogador\n2 - Dois jogadores\n");

}


int main() 
{   
    static int ch = 0;
    int ins, outs;
    int i = 0;
    
    Coordenada esquerdaAlto = {5, 12};
    Coordenada esquerdaBaixo = {30, 12};
    Coordenada meioAlto = {0, 0};
    Coordenada meioBaixo = {50, 12};
    Coordenada diretaAlto = {0, 0};
    Coordenada direitaBaixo = {70, 12};

    screenInit(1); // Com parametro falso, a quadra nao starta
    keyboardInit();
    timerInit(50);
    // welcome();

    movimentaBola(x, y);
    screenUpdate();

    while (ch != 10)
    {

        if (keyhit()) 
        {
            i+=1;
            ch = readch();
            int def = oddsDefesa();

            if (ch == 97 && def != 0) { // A
                ins+=1;
                printf("   Gol[%d]", ins);

                movimentaBola(esquerdaBaixo.x,esquerdaBaixo.y);
                screenUpdate();

            }
            else if (ch == 119) { // W
                if (def == 1) {
                    printf("   Goleiro pegou!");
                }
                movimentaBola(meioBaixo.x,meioBaixo.y);
                screenUpdate();
            }
            else if (ch == 100) { // D
                if (def == 2) {
                    printf("   Goleiro pegou!");
                }
                movimentaBola(direitaBaixo.x,direitaBaixo.y);
                screenUpdate();

            }
            
        }

        // Update game state (move elements, verify collision, etc)
        
        if (timerTimeOver() == 2)
        {
            int newX = x + incX;
            if (newX >= direitaBaixo.x - 1 || newX <= MINX + 1) incX = -incX;
            int newY = y - incY;
            if (newY >= MAXY - 1 || newY <= direitaBaixo.y + 1) incY = -incY;

            movimentaBola(newX, newY);

            screenUpdate();
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
