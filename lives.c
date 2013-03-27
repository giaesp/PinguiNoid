/*****************************************************************************/
/* File Info :                                                               */
/* -----------                                                               */
/* Nome File            : lives.c                                            */
/* Dimensione           : 3020 bytes                                         */
/* Data Ultima Modifica : Domenica 28 Maggio 2000 - 17:18                    */
/* Autore               : Esposito Gianluca (Matr.Num.056/100858)            */
/* Breve Descrizione    : Contiene i valori di colore dei pixel del          */
/*                        grafico LIVES (relativo alla gestione dei credits) */
/*****************************************************************************/

#define LIVES_X 11
#define LIVES_Y 10

/* --------------------------------------------- */
/* Pixel Map : LIVES                             */
/* Dimensione in byte : 220 byte                 */
/* --------------------------------------------- */
int lives[LIVES_Y][LIVES_X] = {
  { 0, 0,52,52, 0, 0, 0,52,52, 0, 0},
  { 0,52,55,55,55,52,55,55,55,52, 0},
  {52,55,55,55,55,55,55,59,55,55,52},
  {55,55,55,55,55,55,55,55,59,55,55},
  {55,55,55,55,55,55,55,55,59,55,55},
  {52,55,55,55,55,55,55,55,55,55,52},
  { 0,52,55,55,55,55,55,55,55,52, 0},
  { 0, 0,52,55,55,55,55,55,52, 0, 0},
  { 0, 0, 0,52,55,55,55,52, 0, 0, 0},
  { 0, 0, 0, 0,52,55,52, 0, 0, 0, 0}
};


void DrawLives(int num_lives); 

void DrawLives(int num_lives)
/* Disegna a video il numero di credits rimanenti */
{
  switch(num_lives) {
  case 1 : DrawObject(273, 226, LIVES_X, LIVES_Y, lives, OMBRA);
           DrawObject(285, 226, LIVES_X, LIVES_Y, lives, OMBRA);
           DrawObject(297, 226, LIVES_X, LIVES_Y, lives, OMBRA);
           DrawObject(309, 226, LIVES_X, LIVES_Y, lives, OMBRA);
           break;    
  case 2 : DrawObject(273, 226, LIVES_X, LIVES_Y, lives, SOLID);
           DrawObject(285, 226, LIVES_X, LIVES_Y, lives, OMBRA);
           DrawObject(297, 226, LIVES_X, LIVES_Y, lives, OMBRA);
           DrawObject(309, 226, LIVES_X, LIVES_Y, lives, OMBRA);
           break;    
  case 3 : DrawObject(273, 226, LIVES_X, LIVES_Y, lives, SOLID);
           DrawObject(285, 226, LIVES_X, LIVES_Y, lives, SOLID);
           DrawObject(297, 226, LIVES_X, LIVES_Y, lives, OMBRA);
           DrawObject(309, 226, LIVES_X, LIVES_Y, lives, OMBRA);
           break;    
  case 4 : DrawObject(273, 226, LIVES_X, LIVES_Y, lives, SOLID);
           DrawObject(285, 226, LIVES_X, LIVES_Y, lives, SOLID);
           DrawObject(297, 226, LIVES_X, LIVES_Y, lives, SOLID);
           DrawObject(309, 226, LIVES_X, LIVES_Y, lives, OMBRA);
           break;    
  case 5 : DrawObject(273, 226, LIVES_X, LIVES_Y, lives, SOLID);
           DrawObject(285, 226, LIVES_X, LIVES_Y, lives, SOLID);
           DrawObject(297, 226, LIVES_X, LIVES_Y, lives, SOLID);
           DrawObject(309, 226, LIVES_X, LIVES_Y, lives, SOLID);
           break;    
  }
}
