#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> 
#include <stdio.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#define SPRITE_HEIGHT 10
#define SPRITE_WIDTH 21

int x = 65, y = 35; // Ponto zero da bola
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

void printGoalKeeper()
{
    printf("       🤓\n");
    printf("   _ _/  \\_ _\n");
    printf("  / _      _ \\\n");
    printf(" / / |    | \\ \\\n");
    printf("|||  |____|  |||\n");
    printf("     |	  |\n");
    printf("     |_ |_|\n");
    printf("      || ||\n");
    printf("     <_| |_>\n");
}

void printSprite(int x, int y, char sprite[SPRITE_HEIGHT][SPRITE_WIDTH + 1])
{
    for (int i = 0; i < SPRITE_HEIGHT; i++)
    {
        screenGotoxy(x, y + i);
        printf("%s", sprite[i]);
    }
    screenUpdate();
}

char cleanBola[SPRITE_HEIGHT][SPRITE_WIDTH + 1] = {
{' '}
};

char cleanGoleiro[SPRITE_HEIGHT][SPRITE_WIDTH + 1] = {
{' ',' ',' ',' ',' ',' ',' ',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', ' ', ' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
};

char cleanGoleiroMeioAlto[SPRITE_HEIGHT][SPRITE_WIDTH + 1] = {
  {' ',' ',' ',' ',' ',' ',' ',' '},
  {' ',' ',' ',' ',' ',' ',' ',' ',' '},
  {' ',' ',' ',' ',' ',' ',' ',' ',' '},
  {' ',' ',' ',' ',' ',' ',' ',' ',' '},
  {' ',' ',' ',' ',' ',' ',' ',' ',' '},
  {' ',' ',' ',' ',' ',' ',' ',' ',' '},
  {' ',' ',' ',' ',' ',' ',' ',' ',' '},
  {' ',' ',' ',' ',' ',' ',' ',' ',' ',},
  {' ',' ',' ',' ',' ',' ',' ',},
  {' ',' ',' ',' ',' ',' ',' ',' '}
};

char cleanGoleiroEsquerdaBaixo[SPRITE_HEIGHT][SPRITE_WIDTH + 1] = {
  {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
  {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
  {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
  {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
  {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
};

char cleanGoleiroEsquerdaAlto[SPRITE_HEIGHT][SPRITE_WIDTH + 1] = {
  {' ',' ',' ',' ',' '},
  {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
  {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
  {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
  {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
  {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
};

char cleanGoleiroDireitaBaixo[SPRITE_HEIGHT][SPRITE_WIDTH + 1] = {
  {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
  {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
  {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
  {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
  {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
};

char cleanGoleiroDireitaAlto[SPRITE_HEIGHT][SPRITE_WIDTH + 1] = {
  {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
  {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
  {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
  {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
  {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
  {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
};

char goleiro[SPRITE_HEIGHT][SPRITE_WIDTH + 1] = {
{' ',' ',' ',' ',' ',' ',' ','@'},
{' ',' ',' ','_',' ','_','/',' ','\\','_',' ','_'},
{' ',' ','/',' ','_',' ',' ',' ',' ',' ',' ','_', ' ', '\\'},
{' ','/',' ','/',' ','|',' ',' ',' ',' ','|',' ','\\',' ','\\',' ',' '},
{'|','|','|',' ',' ','|','_','_','_','_','|',' ',' ','|','|','|'},
{' ',' ',' ',' ',' ','|',' ',' ',' ',' ','|'},
{' ',' ',' ',' ',' ','|','_',' ','|','_','|',},
{' ',' ',' ',' ',' ',' ','|','|',' ','|','|',},
{' ',' ',' ',' ',' ','<','_','|',' ','|','_','>'}
};

char goleiroMeioAlto[SPRITE_HEIGHT][SPRITE_WIDTH + 1] = {
{' ',' ','E',' ',' ',' ',' ','>'},
{'/',' ','/',' ','@',' ','|',' ','\\'},
{'|',' ','\\','/',' ','\\','/',' ','|'},
{'|',' ',' ',' ',' ',' ',' ',' ','|'},
{'|',' ',' ',' ',' ',' ',' ',' ','|'},
{'|',' ',' ',' ',' ',' ',' ','_','|'},
{'|',' ',' ',' ',' ',' ',' ',' ','|'},
{'|',' ',' ',' ','|',' ',' ',' ','|',},
{' ',' ','|','|',' ','|','|',},
{' ','<',' ','|',' ','|',' ','>'}
};

char goleiroEsquerdaBaixo[SPRITE_HEIGHT][SPRITE_WIDTH + 1] = {
{' ','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_'},
{'>','_','_','_','_',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ','|','-','-','-','-','>'},
{' ',' ',' ','@','/',' ',' ',' ',' ',' ','|',' ',' ',' ','_','_','|'},
{' ','_','_','_','\\',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ','|','-','-','-','-','>'},
{'>','_','_','_','_','_','_','_','_','_','|','_','_','_','_','_','|'},
};

char goleiroEsquerdaAlto[SPRITE_HEIGHT][SPRITE_WIDTH + 1] = {
{' ',' ',' ',' ','V'},
{' ',' ',' ',' ','\\',' ','\\','_','_','_','_','_','_','_','_','_'},
{' ',' ',' ',' ','\\',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ','|','-','-','-','-','>'},
{' ',' ',' ','@','/',' ',' ',' ',' ',' ','|',' ',' ',' ','_','_','|'},
{' ','_','_','_','\\',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ','|','-','-','-','-','>'},
{'>','_','_','_','_','_','_','_','_','_','|','_','_','_','_','_','|'},
};

char goleiroDireitaBaixo[SPRITE_HEIGHT][SPRITE_WIDTH + 1] = {
{' ',' ',' ',' ',' ',' ','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_'},
{'<','-','-','-','-','|',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ','_','_','_','_','<'},
{' ',' ',' ',' ',' ','|','_','_',' ',' ',' ','|',' ',' ',' ',' ',' ','\\','@'},
{'<','-','-','-','-','|',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ','/','_','_','_',},
{' ',' ',' ',' ',' ','|','_','_','_','_','_','|','_','_','_','_','_','_','_','_','_','<'},
};

char goleiroDireitaAlto[SPRITE_HEIGHT][SPRITE_WIDTH + 1] = {
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','V'},
{' ',' ',' ',' ',' ',' ','_','_','_','_','_','_','_','_','_','/',' ','/'},
{'<','-','-','-','-','|',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ','/'},
{' ',' ',' ',' ',' ','|','_','_',' ',' ',' ','|',' ',' ',' ',' ',' ','\\','@'},
{'<','-','-','-','-','|',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ','/','_','_','_',},
{' ',' ',' ',' ',' ','|','_','_','_','_','_','|','_','_','_','_','_','_','_','_','_','<'},
};

void printPlacar(int a, int b)
{

    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(64, 37);
    printf("Batedor %d X %d Goleiro", a, b);

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

void pageManual()
{

    screenInit(0);

    printf("  ____                            _                        \n");
    printf(" / ___|___  _ __ ___   ___       | | ___   __ _  __ _ _ __ \n");
    printf("| |   / _ \\| '_ ` _ \\ / _ \\   _  | |/ _ \\ / _` |/ _` | '__|\n");
    printf("| |__| (_) | | | | | | (_) | | |_| | (_) | (_| | (_| | |   \n");
    printf(" \\____\\___/|_| |_| |_|\\___/   \\___/ \\___/ \\__, |\\__,_|_|   \n");
    printf("                                          |___/            \n");

    printf("\nModo Um Jogador (Cobrador de Penalti):\n");
    printf("\nUse as teclas A, W, S e D para cobrar o pênalti.\n");
    printf("Você terá 5 chances de fazer gol. Caso a sua pontuação seja superior à do goleiro, você vence.\n\n");
    printf("  A + S ➡️ chuta para a esquerda e baixo\n  S + S ➡️ chuta para o meio e baixo\n  D + S ➡️ chuta para a direita e baixo\n  A + W ➡️ chuta para a esquerda e alto\n  S + W ➡️ chuta para o meio e alto\n  D + W ➡️ chuta para a direita e alto\n\n");
    printf("\nModo Dois Jogadores (Cobrador de Penalti e Goleiro):\n");
    printf("\nUse as teclas H, U, J e K para defender o pênalti.\n");
    printf("Você terá 5 chances de para defender o penalti. Caso a sua pontuação seja superior à do cobrador, você vence.\n\n");
    printf("\nOs comandos para o cobrador de penalti seguem a do Modo Um Jogador.\n");
    printf("  H + J ➡️ pula para a esquerda e baixo\n  J + J ➡️ pula para o meio e baixo\n  K + J ➡️ pula para a direita e baixo\n  H + U ➡️ pula para a esquerda e alto\n  J + U ➡️ pula para o meio e alto\n  K + U ➡️ pula para a direita e alto\n\n");
    printf(" [0]   Voltar à tela inicial\n [1]   Iniciar o jogo - Modo Um Jogador\n [2]   Iniciar o jogo - Modo Dois Jogadores\n");
}

void pageScores()
{
    
    screenInit(0);

    printf(" ____                          \n");
    printf("/ ___|  ___ ___  _ __ ___  ___ \n");
    printf("\\___ \\ / __/ _ \\| '__/ _ \\/ __|\n");
    printf(" ___) | (_| (_) | | |  __/\\__ \\\n");
    printf("|____/ \\___\\___/|_|  \\___||___/\n");


}



void pageScoreRegister()
{
  screenInit(0);
  keyboardInit();

  printf("__     _____   ____  //\\   __     _______ _   _  ____ _____ _   _ _\n");
  printf("\\ \\   / / _ \\ / ___||/_%c|  \\ \\   / / ____| \\ | |/ ___| ____| | | | |\n", '\\');
  printf(" \\ \\ / / | | | |   | ____|  \\ \\ / /|  _| |  \\| | |   |  _| | | | | |\n");
  printf("  \\ V /| |_| | |___|  _|_    \\ V / | |___| |\\  | |___| |___| |_| |_|\n");
  printf("   \\_/  \\___/ \\____|_____|    \\_/  |_____|_| \\_|\\____|_____|\\___/(_)\n");

  printf("--------------------------------------------------------------------\n");
  printf("                               ___________\n");
  printf("                              '._==_==_=_.\n");
  printf("                              .-\\:      /-.\n");
  printf("                             | (|:.     |) |\n");
  printf("                              '-|:.     |-\n");
  printf("                                \\::.    /\n");
  printf("                                 '::. .'\n");
  printf("                                   ) (\n");
  printf("                                 _.' '._\n");
  printf("                                `\"\"\"\"\"\"\"`\n");
  printf("---------------------------------------------------------------------\n");

  // screenGotoxy(x, y);
  printf("\nDigita teu nome, jogador!");
  scanf("");

}

int scoreRegister(int score)
{
    FILE *fptr;
    char *nome;
    int maxLength = 30;

    nome = (char *)malloc(maxLength * sizeof(char));

    scanf("%s", nome);

    fptr = fopen("scores.txt", "a");

    fprintf(fptr, "%s %d\n", nome, score);
    fclose(fptr);

    free(nome);

    return 0;
}

void movimentaGoleiroDualPlayer(int def, int alvo_x, int alvo_y)
{
  switch(def) {
    case 0:
      printSprite(59, 6, cleanGoleiro);
      movimentaBola(alvo_x,alvo_y);
      // printSprite(alvo_x, alvo_y, cleanBola);
      printSprite(35, 9, goleiroEsquerdaBaixo);
      sleep(1);
      printSprite(35, 9, cleanGoleiroEsquerdaBaixo);
      break;
    case 1:
      printSprite(59, 6, cleanGoleiro);
      movimentaBola(alvo_x,alvo_y);
      printSprite(35, 9, goleiro);
      sleep(1);
      printSprite(35, 9, cleanGoleiro);
      break;
    case 2:
      printSprite(59, 6, cleanGoleiro);
      movimentaBola(alvo_x,alvo_y);
      printSprite(82, 9, goleiroDireitaBaixo);
      sleep(1);
      printSprite(82, 9, cleanGoleiroDireitaBaixo);
      break;
    case 3:
      printSprite(59, 6, cleanGoleiro);
      movimentaBola(alvo_x,alvo_y);
      printSprite(36, 7, goleiroEsquerdaAlto);
      sleep(1);
      printSprite(36, 7, cleanGoleiroEsquerdaAlto);	
      break;
    case 4:
      printSprite(59, 6, cleanGoleiro);
      movimentaBola(alvo_x,alvo_y);
      printSprite(59, 5, goleiroMeioAlto);
      sleep(1);
      printSprite(59, 5, cleanGoleiroMeioAlto);
      break;
    case 5:
      printSprite(59, 6, cleanGoleiro);
      movimentaBola(alvo_x,alvo_y);
      printSprite(80,7,goleiroDireitaAlto);
      sleep(1);
      printSprite(80, 7, cleanGoleiroDireitaAlto);
      break;
  }
}

int singlePlayer() 
{
    int chances = 0;
    int batedor_1 = 0, batedor_2 = 0;
    static int ch_batedor = 0, lado_batedor = 0;
    int ins = 0, outs = 0;
    int i = 0;

    Coordenada esquerdaAlto = {40, 7};
    Coordenada esquerdaBaixo = {34, 13};
    Coordenada meioAlto = {65, 5};
    Coordenada meioBaixo = {64, 13};
    Coordenada direitaAlto = {96, 7};
    Coordenada direitaBaixo = {102, 13};

    screenInit(1); // Com parametro falso, a quadra nao starta
    // printGoalKeeper();
    printSprite(59, 6, goleiro);
    keyboardInit();
    timerInit(50);
    // printaCobrador();
    movimentaBola(x, y);
    screenUpdate();

    while (ch_batedor != 10 && chances<5)
    {

        if (keyhit()) 
        {
            i+=1;
            batedor_1 = readch();
            batedor_2 = readch();

            lado_batedor = batedor_1+batedor_2;

            int def = oddsDefesa();
            int alvo_x = 0, alvo_y = 0;
            
            if (lado_batedor == 212) { // A+S
	            if (def != 0) {
		            ins+=1;
	            }
	            else {
		            outs+=1;
	            }
	            alvo_x = esquerdaBaixo.x;
	            alvo_y = esquerdaBaixo.y;
              movimentaGoleiroDualPlayer(def, alvo_x, alvo_y);
              
            }

            else if (lado_batedor == 230) { // S+S 
	            if (def != 1) {
		            ins+=1;
	            }
	            else {
		            outs+=1;
	            }

	            alvo_x = meioBaixo.x;
	            alvo_y = meioBaixo.y;
              movimentaGoleiroDualPlayer(def, alvo_x, alvo_y);

            }

            else if (lado_batedor == 215) { // D+S
	            if (def != 2) {
		            ins+=1;
	            }
	            else {
		            outs+=1;
	            }
	            alvo_x = direitaBaixo.x;
	            alvo_y = direitaBaixo.y;
              movimentaGoleiroDualPlayer(def, alvo_x, alvo_y);
            }

            else if (lado_batedor == 216) { // A+W
	            if (def != 3) {
		            ins+=1;
	            }
	            else {
		            outs+=1;
	            }
	            alvo_x = esquerdaAlto.x;
	            alvo_y = esquerdaAlto.y;
              movimentaGoleiroDualPlayer(def, alvo_x, alvo_y);
            }

            else if (lado_batedor == 234) { // W+S
	            if (def != 4) {
		            ins+=1;
	            }
	            else {
		            outs+=1;
	            }
	            alvo_x = meioAlto.x;
	            alvo_y = meioAlto.y;
              movimentaGoleiroDualPlayer(def, alvo_x, alvo_y);
            }

            else if (lado_batedor == 219) { // D+W
	            if (def != 5) {
		            ins+=1;
	            }
	            else {
		            outs+=1;
	            }
	            alvo_x = direitaAlto.x;
	            alvo_y = direitaAlto.y;
              movimentaGoleiroDualPlayer(def, alvo_x, alvo_y);
            }

            else{ //chutou pra fora
                outs+=1;
            }
            printSprite(59, 6, goleiro);
            printPlacar(ins,outs);
	        screenUpdate();

            // sleep(1);
            screenGotoxy(alvo_x,alvo_y);
            printf(" ");
            screenUpdate();
            screenGotoxy(65,35);
            printf("              ");
            movimentaBola(65,35);
            screenUpdate();
            chances +=1;

            
        }
        
    }
    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    screenDestroy();
    pageScoreRegister();
    scoreRegister(ins);

    return ins;
}

int dualPlayer() {
    int chances = 0;
    int batedor_1 = 0, batedor_2 = 0, goleiro_1 = 0, goleiro_2 = 0;
    static int ch_batedor = 0, lado_batedor = 0, ch_goleiro = 0, lado_goleiro = 0;
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
    // printaCobrador();
    movimentaBola(x, y);
    screenUpdate();

    while (ch_batedor != 10 && chances<5)
    {

        if (keyhit()) 
        {
            i+=1;
            batedor_1 = readch();
            batedor_2 = readch();
            goleiro_1 = readch();
            goleiro_2 = readch();

            lado_batedor = batedor_1+batedor_2;
            lado_goleiro = goleiro_1+goleiro_2;

            int def = oddsDefesa();
            int alvo_x = 0, alvo_y = 0;
            
            if (lado_batedor == 212) { // A+S
	            if (lado_goleiro != 210) { //H+J
		            ins+=1;
	            }
	            else {
		            outs+=1;
	            }

	            alvo_x = esquerdaBaixo.x;
	            alvo_y = esquerdaBaixo.y;
            }

            else if (lado_batedor == 230) { // S+S
	            if (lado_goleiro != 212){ //J+J
		            ins+=1;
	            }
	            else {
		            outs+=1;
	            }

	            alvo_x = meioBaixo.x;
	            alvo_y = meioBaixo.y;
            }

            else if (lado_batedor == 215) { // D+S
	            if (lado_goleiro != 213){ // J+K
		            ins+=1;
	            }
	            else {
		            outs+=1;
	            }

	            alvo_x = direitaBaixo.x;
	            alvo_y = direitaBaixo.y;
            }

            else if (lado_batedor == 216) { // A+W
	            if (lado_goleiro != 221){ //H+U
		            ins+=1;
	            }
	            else {
		            outs+=1;
	            }

	            alvo_x = esquerdaAlto.x;
	            alvo_y = esquerdaAlto.y;
            }

            else if (lado_batedor == 234) { // S+W
	            if (lado_goleiro != 223){ //J+U
		            ins+=1;
	            }
	            else {
		            outs+=1;
	            }

	            alvo_x = meioAlto.x;
	            alvo_y = meioAlto.y;
            }

            else if (lado_batedor == 219) { // D+W
	            if (lado_goleiro != 224){ // K+U
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
        
        // if (timerTimeOver() == 1)
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

    screenDestroy();
    pageScoreRegister();
    scoreRegister(ins);

    return ins;
}

int main() 
{   
    static int ch = 0;
    pageWelcome();
    keyboardInit();
    
    while (ch!=10) {

        if (keyhit()) {
            ch = readch();

            if (ch == 48) {
                screenDestroy();
                pageWelcome();
            }

            else if (ch == 49) {
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
            }
            else if (ch == 51) {// TODO : ler arquivo
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