/**
 * screen.c
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
*/

#include "screen.h"

void screenDrawBorders() 
{
    char hbc = BOX_HLINE;
    char vbc = BOX_VLINE;
    
    screenClear();
    screenBoxEnable();
    
    screenGotoxy(BARRA_MIN_X, MINY);
    printf("%c", BOX_UPLEFT);

    for (int i=BARRA_MIN_X+1; i<BARRA_MAX_X; i++)
    {
        screenGotoxy(i, MINY);
        printf("%c", hbc);
    }
    screenGotoxy(BARRA_MAX_X, MINY);
    printf("%c", BOX_UPRIGHT);

    for (int i=MINY+1; i<BARRA_MAX_Y; i++)
    {
        screenGotoxy(BARRA_MIN_X, i);
        printf("%c", vbc);
        screenGotoxy(BARRA_MAX_X, i);
        printf("%c", vbc);
    }
    
     for (int i=MINX; i<MAXX; i++)
    {
        screenGotoxy(i, BARRA_MAX_Y);
        if(i == BARRA_MIN_X){
            printf("%c", BOX_DWNLEFT);
        }
        else if(i == BARRA_MAX_X){
            printf("%c", BOX_DWNRIGHT);
        }
        else{
        printf("%c", hbc);
        }
    }

    screenGotoxy(MINX, LINHA_DOIS_Y);
     for (int i=MINX; i<MAXX; i++)
    {
        printf("%c", hbc);
    }

    screenBoxDisable();
    
}

void screenInit(int drawBorders)
{
    screenClear();
    if (drawBorders) screenDrawBorders();
    screenHomeCursor();
    screenHideCursor();
}

void screenDestroy()
{
    printf("%s[0;39;49m", ESC); // Reset colors
    screenSetNormal();
    screenClear();
    screenHomeCursor();
    screenShowCursor();
}

void screenGotoxy(int x, int y)
{
    x = ( x<0 ? 0 : x>=MAXX ? MAXX-1 : x);
    y = ( y<0 ? 0 : y>MAXY ? MAXY : y);
    
    printf("%s[f%s[%dB%s[%dC", ESC, ESC, y, ESC, x);
}

void screenSetColor( screenColor fg, screenColor bg)
{
    char atr[] = "[0;";

    if ( fg > LIGHTGRAY )
    {
        atr[1] = '1';
		fg -= 8;
    }

    printf("%s%s%d;%dm", ESC, atr, fg+30, bg+40);
}
