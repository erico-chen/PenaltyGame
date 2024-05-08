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

int defesa() {
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

int main() 
{
    static int ch = 0;
    
    Coordenada esquerdaAlto = {5, 12};
    Coordenada esquerdaBaixo = {30, 12};
    Coordenada meioBaixo = {50, 12};
    Coordenada direitaBaixo = {70, 12};

    screenInit(1);
    keyboardInit();
    timerInit(50);

    movimentaBola(x, y);
    screenUpdate();

    while (ch != 10)
    {

        if (keyhit()) 
        {
            ch = readch();
            int def = defesa();
            
            if (ch == 97) { // A
                if (def == 0) {
                    printf("   Goleiro pegou!");
                }
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
            if (newX >= (MAXX -strlen("Hello World") -1) || newX <= MINX+1) incX = -incX;
            int newY = y + incY;
            if (newY >= MAXY-1 || newY <= MINY+1) incY = -incY;

            movimentaBola(newX, newY);

            screenUpdate();
        }
        

    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}


// struct coordenadas {
//     struct pontoZero {
//         int x = 50;
//         int y = 30;
//     };
//     struct meioBaixo {
//         int x = 50;
//         int y = 10;
//     };
//     struct meioAlto {
//         int x = 0;
//         int y = 0;
//     };
//     struct esquerdaBaixo {
//         int x = 30;
//         int y = 10;
//     }; 
//     struct esquerdaAlto {
//         int x = 5;
//         int y = 10;
//     };
//     struct direitaBaixo {
//         int x = 70;
//         int y = 10;
//     };
//     struct direitaAlto {
//         int x = 0;
//         int y = 0;
//     };
// };


// Essa será a coordenada 0 da bola
// Ponto zero: 50,30
// Meio do gol: 50, 10
// Lado esquerdo gol: 30, 10
// Lado direito gol: 70, 10
