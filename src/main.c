#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> 
#include <stdio.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#define SPRITE_HEIGHT 10
#define SPRITE_WIDTH 22

int x = 65, y = 35; // Ponto zero da bola
int incX = 1, incY = 1;

void printBola();
void artPageLost();
void artPageWon();
void readScoresSingle();
void readScoresDual();

typedef struct {
    int x;
    int y;
}Coordenada;

int oddsDefesa(int lado)
{
    // 0 = esquerda baixo, 1 = meio baixo, 2 = direita baixo
    // 3 = esquerda alto,  4 = meio alto,  5 = direita alto

    int x, y, numeros[3];
    if (lado == 212){
      numeros[0] = 0;
    }
    else if(lado == 230){
      numeros[0] = 1;
    }
    else if(lado == 215){
      numeros[0] = 2;
    }
    else if(lado == 216){
      numeros[0] = 3;
    }
    else if(lado == 234){
      numeros[0] = 4;
    }
    else if(lado == 219){
      numeros[0] = 5;
    }
    
    srand(time(NULL));
    for(int i = 1;i<3;i++){
        x = rand() % 6;
        numeros[i]=x;
    }

    int tamanho = sizeof(numeros) / sizeof(numeros[0]);

    srand(time(NULL));

     y = rand() % tamanho;
    int indice_aleatorio = numeros[y];

    return indice_aleatorio;
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
    printBola();

}

void printBola()
{
    printf("⚽");
}

void printPlacar(int a, int b)
{

  screenSetColor(YELLOW, DARKGRAY);
  screenGotoxy(56, 37);
  printf("Batedor %d X %d Goleiro", a, b);

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
{'|','_','_','_','_','_','_','_','|'},
{'|',' ',' ',' ',' ',' ',' ',' ','|'},
{'|','_','_','_','|','_','_','_','|',},
{' ',' ','|','|',' ','|','|',},
{' ','<','_','|',' ','|','_','>'}
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

void artPageWon()
{
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
}

void artPageLost()
{
  // screenInit(0);
  printf(" __     _____   ____  //\\    ____  _____ ____  ____  _____ _   _ _ \n");
  printf(" \\ \\   / / _ \\ / ___||/_\\|  |  _ \\| ____|  _ \\|  _ \\| ____| | | | |\n");
  printf("  \\ \\ / / | | | |   | ____| | |_) |  _| | |_) | | | |  _| | | | | |\n");
  printf("   \\ V /| |_| | |___|  _|_  |  __/| |___|  _ <| |_| | |___| |_| |_|\n");
  printf("    \\_/  \\___/ \\____|_____| |_|   |_____|_| \\_\\____/|_____|\\___/(_)\n");
}

void artPagePlayerWon()
{
  printf("     _  ___   ____    _    ____   ___  ____  \n");
  printf("    | |/ _ \\ / ___|  / \\  |  _ \\ / _ \\|  _ \\ \n");
  printf(" _  | | | | | |  _  / _ \\ | | | | | | | |_) |\n");
  printf("| |_| | |_| | |_| |/ ___ \\| |_| | |_| |  _ < \n");
  printf("\\____/ \\___/ \\____/_/    \\_\\____/ \\___/|_| \\_\\\n");
  printf("\\ \\   / / ____| \\ | |/ ___| ____| | | | |    \n");
  printf(" \\ \\ / /|  _| |  \\| | |   |  _| | | | | |    \n");
  printf("  \\ V / | |___| |\\  | |___| |___| |_| |_|    \n");
  printf("   \\_/  |_____|_| \\_|\\____|_____|\\___/(_)    \n");

  printf("----------------------------------------------\n");
  printf("                 ___________\n");
  printf("                '._==_==_=_.\n");
  printf("                .-\\:      /-.\n");
  printf("               | (|:.     |) |\n");
  printf("                '-|:.     |-\n");
  printf("                  \\::.    /\n");
  printf("                   '::. .'\n");
  printf("                     ) (\n");
  printf("                   _.' '._\n");
  printf("                  `\"\"\"\"\"\"\"`\n");
  printf("----------------------------------------------\n");
}

void artPageGoalkeeperWon()
{
  printf("  ____  ___  _     _____ ___ ____   ___  \n");
  printf(" / ___|/ _ \\| |   | ____|_ _|  _ \\ / _ \\ \n");
  printf("| |  _| | | | |   |  _|  | || |_) | | | |\n");
  printf("| |_| | |_| | |___| |___ | ||  _ <| |_| |\n");
  printf("\\____|\\___/|_____|_____|___|_| \\_\\\\___/ \n");
  printf("\\ \\   / / ____| \\ | |/ ___| ____| | | | |\n");
  printf(" \\ \\ / /|  _| |  \\| | |   |  _| | | | | |\n");
  printf("  \\ V / | |___| |\\  | |___| |___| |_| |_|\n");
  printf("   \\_/  |_____|_| \\_|\\____|_____|\\___/(_)\n");

  printf("-----------------------------------------\n");
  printf("               ___________\n");
  printf("              '._==_==_=_.\n");
  printf("              .-\\:      /-.\n");
  printf("             | (|:.     |) |\n");
  printf("              '-|:.     |-\n");
  printf("                \\::.    /\n");
  printf("                 '::. .'\n");
  printf("                   ) (\n");
  printf("                 _.' '._\n");
  printf("                `\"\"\"\"\"\"\"`\n");
  printf("-----------------------------------------\n");
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
  printf("\n");

  printf(" [0]   Voltar à tela inicial\n\n");
  printf("________________________________\n");
  printf("________RANK SINGLEPLAYER_______\n\n");
  readScoresSingle();
  printf("________________________________\n");
  printf("________RANK DUALPLAYER_________\n\n");
  readScoresDual();

  
}

void pageScoreRegisterSingle(int direct)
{
  screenInit(0);
  keyboardInit();

  if (direct == 0) { 
    artPageWon();
  } else if (direct == 1) {
    artPageLost();
  }

  printf("\nDigita teu nome, jogador!");
  scanf("");

}

void pageScoreRegisterDual(int direct)

{
  screenInit(0);
  keyboardInit();

  if (direct == 0) {
    artPagePlayerWon();
  } else if (direct == 1) {
    artPageGoalkeeperWon();
  }

  printf("\nDigita teu nome, jogador!");
  scanf("");
  printf("\nDigita teu nome, goleiro!");
  scanf("");

}

void readScoresSingle()
{
  FILE *fptr;
  char nome[100];
  int numero;
  fptr = fopen("scores.txt", "r");

  if (fptr == NULL) {
      perror("Erro ao abrir o arquivo");
      exit(1);
  }

  printf("");
  while (fscanf(fptr, "%s %d", nome, &numero) == 2) {
      printf("Jogador: %s, Gols: %d\n", nome, numero);
  }

  fclose(fptr);
}

void readScoresDual()
{
  FILE *fptr;
  int gols, defs;
  char player[100], goalkeeper[100];

  fptr = fopen("scoreDual.txt", "r");

  if (fptr == NULL) {
      perror("Erro ao abrir o arquivo");
      exit(1);
  }

  while (fscanf(fptr, "[%d] %s vs %s [%d]\n", &gols, player, goalkeeper, &defs) == 4) {
      printf(" [%d] %s vs %s [%d]\n", gols, player, goalkeeper, defs);
  }

  fclose(fptr);
}

int scoreRegisterSingle(int score)
{
  FILE *fptr;
  char *nome;
  int maxLength = 30;

  nome = (char *)malloc(maxLength * sizeof(char));

  scanf("%s", nome);

  fptr = fopen("scoreSingle.txt", "a");

  fprintf(fptr, "%s %d\n", nome, score);
  fclose(fptr);

  free(nome);

  return 0;
}

int scoreRegisterDual(int scorePlayer, int scoreGoalkeeper)
{
  FILE *fptr;
  char *nome_player, *nome_goalkeeper;
  int maxLength = 30;

  nome_player = (char *)malloc(maxLength * sizeof(char));
  nome_goalkeeper = (char *)malloc(maxLength * sizeof(char));

  scanf("%s", nome_player);
  scanf("%s", nome_goalkeeper);


  fptr = fopen("scoreDual.txt", "a");

  fprintf(fptr, "[%d] %s vs %s [%d]\n", scorePlayer, nome_player, nome_goalkeeper, scoreGoalkeeper);
  fclose(fptr);

  free(nome_player);
  free(nome_goalkeeper);

  return 0;
}

void movimentaGoleiro(int def, int alvo_x, int alvo_y)
{
  if (def == 0 || def == 210){
    printSprite(59, 6, cleanGoleiro);
    movimentaBola(alvo_x,alvo_y);
    printSprite(35, 9, goleiroEsquerdaBaixo);
    sleep(1);
    printSprite(35, 9, cleanGoleiroEsquerdaBaixo);
  }
  
  else if (def == 1 || def == 212){
    printSprite(59, 6, cleanGoleiro);
    movimentaBola(alvo_x,alvo_y);
    printSprite(59, 6, goleiro);
    sleep(1);
    printSprite(59, 6, cleanGoleiro);
  }

  else if (def == 2 || def == 213){
    printSprite(59, 6, cleanGoleiro);
    movimentaBola(alvo_x,alvo_y);
    printSprite(82, 9, goleiroDireitaBaixo);
    sleep(1);
    printSprite(82, 9, cleanGoleiroDireitaBaixo);
  }

  else if (def == 3 || def == 221){
    printSprite(59, 6, cleanGoleiro);
    movimentaBola(alvo_x,alvo_y);
    printSprite(36, 7, goleiroEsquerdaAlto);
    sleep(1);
    printSprite(36, 7, cleanGoleiroEsquerdaAlto);
  }
  
  else if (def == 4 || def == 223){
    printSprite(59, 6, cleanGoleiro);
    movimentaBola(alvo_x,alvo_y);
    printSprite(59, 5, goleiroMeioAlto);
    sleep(1);
    printSprite(59, 5, cleanGoleiroMeioAlto);
  }

  else if (def == 5 || def == 224){
    printSprite(59, 6, cleanGoleiro);
    movimentaBola(alvo_x,alvo_y);
    printSprite(80,7,goleiroDireitaAlto);
    sleep(1);
    printSprite(80, 7, cleanGoleiroDireitaAlto);
  }
}

int singlePlayer() 
{
  int chances = 0;
  int batedor_1 = 0, batedor_2 = 0;
  static int ch_batedor = 0, lado_batedor = 0;
  int ins = 0, outs = 0;
  int i = 0;
  int direct;

  Coordenada esquerdaAlto = {40, 7};
  Coordenada esquerdaBaixo = {34, 13};
  Coordenada meioAlto = {65, 5};
  Coordenada meioBaixo = {64, 13};
  Coordenada direitaAlto = {96, 7};
  Coordenada direitaBaixo = {102, 13};

  screenInit(1); // Com parametro falso, a quadra nao starta
  printSprite(59, 6, goleiro);
  keyboardInit();
  timerInit(50);
  movimentaBola(x, y);
  printPlacar(ins,outs);
  screenUpdate();

  while (ch_batedor != 10 && chances<5)
  {
    if (keyhit()) 
    {
      i+=1;
      batedor_1 = readch();
      batedor_2 = readch();

      lado_batedor = batedor_1+batedor_2;

      int def = oddsDefesa(lado_batedor);
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
        movimentaGoleiro(def, alvo_x, alvo_y);
        
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
        movimentaGoleiro(def, alvo_x, alvo_y);

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
        movimentaGoleiro(def, alvo_x, alvo_y);
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
        movimentaGoleiro(def, alvo_x, alvo_y);
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
        movimentaGoleiro(def, alvo_x, alvo_y);
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
        movimentaGoleiro(def, alvo_x, alvo_y);
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
  
  if (ins > outs) {
    direct = 0;

  } else if (ins < outs) {
    direct = 1;

  }

  pageScoreRegisterSingle(direct);
  scoreRegisterSingle(ins);

  return ins;

}

int dualPlayer() {
  int chances = 0;
  int batedor_1 = 0, batedor_2 = 0, goleiro_1 = 0, goleiro_2 = 0;
  static int ch_batedor = 0, lado_batedor = 0, ch_goleiro = 0, lado_goleiro = 0;
  int ins = 0, outs = 0;
  int i = 0;
  int direct;

  Coordenada esquerdaAlto = {40, 7};
  Coordenada esquerdaBaixo = {34, 13};
  Coordenada meioAlto = {65, 5};
  Coordenada meioBaixo = {64, 13};
  Coordenada direitaAlto = {96, 7};
  Coordenada direitaBaixo = {102, 13};

  screenInit(1); // Com parametro falso, a quadra nao starta
  printSprite(59, 6, goleiro);
  keyboardInit();
  timerInit(50);
  movimentaBola(x, y);
  printPlacar(ins,outs);
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
          movimentaGoleiro(lado_goleiro, alvo_x, alvo_y);
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
          movimentaGoleiro(lado_goleiro, alvo_x, alvo_y);
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
          movimentaGoleiro(lado_goleiro, alvo_x, alvo_y);
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
          movimentaGoleiro(lado_goleiro, alvo_x, alvo_y);
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
          movimentaGoleiro(lado_goleiro, alvo_x, alvo_y);
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
          movimentaGoleiro(lado_goleiro, alvo_x, alvo_y);
        }

        else{ //chutou pra fora
            outs+=1;
        }

        // movimentaBola(alvo_x,alvo_y);
        printSprite(59, 6, goleiro);
        printPlacar(ins,outs);
        screenUpdate();

        // sleep(1);
        screenGotoxy(alvo_x,alvo_y);
        printf(" ");
        screenUpdate();
        screenGotoxy(75,45);
        printf("              ");
        movimentaBola(75,45);
        screenUpdate();
        chances +=1;  
      }
  }
  
  keyboardDestroy();
  screenDestroy();
  timerDestroy();

  screenDestroy();

  if (ins > outs) {
    direct = 0;

  } else if (ins < outs) {
    direct = 1;

  }
  pageScoreRegisterDual(direct);
  scoreRegisterDual(ins, outs);
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
        dualPlayer();
      }
      else if (ch == 51) {
        screenDestroy();
        pageManual();
      }
      else if (ch == 52) {
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