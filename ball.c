/****************************************************************************/
/* File Info :                                                              */
/* -----------                                                              */
/* Nome File            : ball.c                                            */
/* Dimensioni           : 2192 bytes                                        */
/* Data Ultima Modifica : Domenica 28 Maggio 2000 - 17:15                   */
/* Autore               : Esposito Gianluca (Matr.Num.056/100858)           */
/* Breve Descrizione    : Valori di colore dei pixel della PALLINA e valori */
/*                        di modifica delle coordinate della PALLINA.       */
/****************************************************************************/

#define MAX_BALLS 3
#define BALL_X 6
#define BALL_Y 6
#define VELOCITA 3
#define MAX_DIREZIONI 12
#define KILLED -100

int xball[MAX_BALLS] = { 118, KILLED, KILLED};
int yball[MAX_BALLS] = { 224, KILLED, KILLED};
int direction[MAX_BALLS] = { 0, 0, 0};
int velocita;

/* ---------------------------------------------------- */
/* Valori dei pixel relativi all'immagine della PALLINA */
/* ---------------------------------------------------- */
int Ball[BALL_Y][BALL_X] = {
  {  0,  2,  4,  4,  2,  0 },
  {  2,  6,  8,  8,  6,  2 },
  {  4,  8, 12, 10,  8,  4 },
  {  4,  8, 10, 10,  8,  4 },
  {  2,  6,  8,  8,  6,  2 },
  {  0,  2,  4,  4,  2,  0 }
};

/* ------------------------------------------------- */   
/* Valori di modifica delle coordinate della pallina */
/* a seconda della velocita' e della direzione.      */
/* ------------------------------------------------- */
struct offset {
  short int passox;
  short int passoy;
} Direzione[VELOCITA][MAX_DIREZIONI] = {
  {
    { 1,-3}, { 2,-2}, { 3,-1}, { 3, 1}, { 2, 2}, { 1, 3}, 
    {-1, 3}, {-2, 2}, {-3, 1}, {-3,-1}, {-2,-2}, {-1,-3}
  },
  {
    { 2,-4}, { 3,-3}, { 4,-2}, { 4, 2}, { 3, 3}, { 2, 4},
    {-2, 4}, {-3, 3}, {-4, 2}, {-4,-2}, {-3,-3}, {-2,-4}
  },
  {
    { 3,-5}, { 4,-4}, { 5,-3}, { 5, 3}, { 4, 4}, { 3, 5},
    {-3, 5}, {-4, 4}, {-5, 3}, {-5,-3}, {-4,-4}, {-3,-5}
  }
};
