/**
 gcc ./src/*.c -I./include -o penalty
 ./penalty
*/

#include <string.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

int x = 50, y = 30;
int incX = 1, incY = 1;

int esquerdaBaixoX = 30, esquerdaBaixoY = 10;
int meioBaixoX = 50, meioBaixoY = 10;
int direitaBaixoX = 70, direitaBaixoY = 10;

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
//         int x = 0;
//         int y = 0;
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
// W == 119

// Função para desenhar a bola
void chamaNaBola() {
    printf("۝");
}

void printHello(int nextX, int nextY)
{
    screenSetColor(CYAN, DARKGRAY);
    
    screenGotoxy(x, y);
    printf("   "); // LIMPA A ÁREA DA BOLA
    
    x = nextX;
    y = nextY;

    screenGotoxy(x, y);
    chamaNaBola();
}

int main() 
{
    static int ch = 0;

    screenInit(1);
    keyboardInit();
    timerInit(50);

    printHello(x, y);
    screenUpdate();

    while (ch != 10) //enter
    {
        // Handle user input
        if (keyhit()) 
        {
            ch = readch();

            if (ch == 97) {
                printHello(esquerdaBaixoX,esquerdaBaixoY);
                screenUpdate();
            }
            else if (ch == 119) {
                printHello(meioBaixoX,meioBaixoY);
                screenUpdate();
            }
            else if (ch == 100) {
                printHello(direitaBaixoX,direitaBaixoY);
                screenUpdate();

            }
            
        }

        // Update game state (move elements, verify collision, etc)
        
        if (timerTimeOver() == 1)
        {
            int newX = x + incX;
            if (newX >= (MAXX -strlen("Hello World") -1) || newX <= MINX+1) incX = -incX;
            int newY = y + incY;
            if (newY >= MAXY-1 || newY <= MINY+1) incY = -incY;

            printHello(newX, newY);

            screenUpdate();
        }
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}
