/*****************************************************************************/
/* File Info :                                                               */
/* -----------                                                               */
/* Nome File            : text.c                                             */
/* Dimensioni           : 11180 bytes                                        */
/* Data Ultima Modifica : Domenica 28 Maggio 2000 - 17:25                    */
/* Autore               : Esposito Gianluca (Matr.Num.056/100858)            */
/* Breve Descrizione    : Definizioni dei valori di colore dei pixel per i   */
/*                        testi (trattati come oggetti/disegni).             */
/*****************************************************************************/
 
#define Y_SCORE 9
#define X_SCORE 36
#define Y_TITLE 13
#define X_TITLE 24
#define Y_KEYS 23
#define X_KEYS 30
#define Y_LIVES_TXT 5
#define X_LIVES_TXT 18
#define X_STAGE_CLEAR 27
#define Y_STAGE_CLEAR 15
#define X_AUTHOR 47
#define Y_AUTHOR 17
#define X_TILT 24
#define Y_TILT 7
#define X_GAME_OVER 18
#define Y_GAME_OVER 11

int txt_score[Y_SCORE][X_SCORE] = {
  { 0,15,15,15,15,15, 0, 0,15,15,15,15,15, 0, 0,15,15,15,15,15, 0, 0,15,
   15,15,15,15,15, 0, 0,15,15,15,15,15, 0},
  {15,15, 0, 0, 0, 0, 0,15,15, 0, 0, 0, 0, 0,15,15, 0, 0, 0,15,15, 0,15,
   15, 0, 0, 0,15,15, 0,15,15, 0, 0, 0, 0}, 
  {15,15, 0, 0, 0, 0, 0,15,15, 0, 0, 0, 0, 0,15,15, 0, 0, 0,15,15, 0,15,
   15, 0, 0, 0,15,15, 0,15,15, 0, 0, 0, 0}, 
  {15,15, 0, 0, 0, 0, 0,15,15, 0, 0, 0, 0, 0,15,15, 0, 0, 0,15,15, 0,15,
   15, 0, 0, 0,15,15, 0,15,15, 0, 0, 0, 0}, 
  { 0,15,15,15,15, 0, 0,15,15, 0, 0, 0, 0, 0,15,15, 0, 0, 0,15,15, 0,15,
   15,15,15,15,15, 0, 0,15,15,15,15, 0, 0},
  { 0, 0, 0, 0,15,15, 0,15,15, 0, 0, 0, 0, 0,15,15, 0, 0, 0,15,15, 0,15,
   15, 0, 0,15,15, 0, 0,15,15, 0, 0, 0, 0},
  { 0, 0, 0, 0,15,15, 0,15,15, 0, 0, 0, 0, 0,15,15, 0, 0, 0,15,15, 0,15,
   15, 0, 0, 0,15,15, 0,15,15, 0, 0, 0, 0},
  { 0, 0, 0, 0,15,15, 0,15,15, 0, 0, 0, 0, 0,15,15, 0, 0, 0,15,15, 0,15,
   15, 0, 0, 0,15,15, 0,15,15, 0, 0, 0, 0},
  {15,15,15,15,15, 0, 0, 0,15,15,15,15,15, 0, 0,15,15,15,15,15, 0, 0,15,
   15, 0, 0, 0,15,15, 0,15,15,15,15,15,15}
};

int title[Y_TITLE][X_TITLE] = {
  {15,15,15, 0, 0, 0, 0,15, 0, 0, 0,15, 0, 0,15,15,15, 0,15, 0, 0,15, 0, 0},
  {15, 0, 0,15, 0,15, 0,15,15, 0, 0,15, 0,15, 0, 0, 0, 0,15, 0, 0,15, 0,15},
  {15, 0, 0,15, 0, 0, 0,15, 0,15, 0,15, 0,15, 0, 0, 0, 0,15, 0, 0,15, 0, 0},
  {15,15,15, 0, 0,15, 0,15, 0,15, 0,15, 0,15, 0,15,15, 0,15, 0, 0,15, 0,15},
  {15, 0, 0, 0, 0,15, 0,15, 0, 0,15,15, 0,15, 0, 0,15, 0,15, 0, 0,15, 0,15},
  {15, 0, 0, 0, 0,15, 0,15, 0, 0, 0,15, 0, 0,15,15,15, 0, 0,15,15, 0, 0,15},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0,15, 0, 0, 0,15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,15, 0, 0, 0, 0, 0},
  { 0, 0, 0,15,15, 0, 0,15, 0, 0, 0, 0, 0,15, 0, 0, 0, 0,15, 0, 0, 0, 0, 0},
  { 0, 0, 0,15, 0,15, 0,15, 0, 0,15, 0, 0, 0, 0, 0,15, 0,15, 0, 0, 0, 0 ,0},
  { 0, 0, 0,15, 0,15, 0,15, 0,15, 0,15, 0,15, 0,15, 0,15,15, 0, 0, 0, 0, 0},
  { 0, 0, 0,15, 0, 0,15,15, 0,15, 0,15, 0,15, 0,15, 0,15,15, 0, 0, 0, 0, 0},
  { 0, 0, 0,15, 0, 0, 0,15, 0, 0,15, 0, 0,15, 0, 0,15, 0,15, 0, 0, 0, 0, 0}
};      

int keys[Y_KEYS][X_KEYS] = {
  { 0, 0, 0,15, 0,15, 0,15,15,15, 0,15, 0,15, 0, 0,15,15,15, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0},
  { 0, 0, 0,15, 0,15, 0,15, 0, 0, 0,15, 0,15, 0,15, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0},
  { 0, 0, 0,15,15, 0, 0,15,15, 0, 0,15, 0,15, 0, 0,15,15, 0, 0,15, 0, 0, 0, 0,
    0, 0, 0, 0 ,0},
  { 0, 0, 0,15, 0,15, 0,15, 0, 0, 0, 0,15, 0, 0, 0, 0, 0,15, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0},
  { 0, 0, 0,15, 0,15, 0,15,15,15, 0, 0,15, 0, 0,15,15,15, 0, 0,15, 0, 0, 0, 0,
    0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0, 0,
    0, 0, 0, 0, 0},
  { 0, 0,15, 0, 0, 0, 0, 0, 0, 0, 0, 0,15, 0, 0, 0,15,15,15, 0,15,15,15, 0,15,
   15,15, 0, 0, 0},
  { 0,15,15,15,15,15,15,15, 0, 0, 0, 0,15, 0, 0, 0,15, 0, 0, 0,15, 0, 0, 0, 0,
   15, 0, 0, 0, 0},
  {15,15,15,15,15,15,15,15, 0,15,15, 0,15, 0, 0, 0,15,15, 0, 0,15,15, 0, 0, 0,
   15, 0, 0, 0, 0},
  { 0,15,15,15,15,15,15,15, 0, 0, 0, 0,15, 0, 0, 0,15, 0, 0, 0,15, 0, 0, 0, 0,
   15, 0, 0, 0, 0},
  { 0, 0,15, 0, 0, 0, 0, 0, 0, 0, 0, 0,15,15,15, 0,15,15,15, 0,15, 0, 0, 0, 0,
   15, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0,15, 0, 0, 0, 0, 0, 0,15,15, 0, 0,15, 0, 0,15,15,15, 0,15, 0,
   15, 0,15,15,15},
  {15,15,15,15,15,15,15, 0, 0, 0, 0, 0,15, 0,15, 0, 0, 0,15, 0, 0, 0, 0,15, 0,
   15, 0, 0,15, 0},
  {15,15,15,15,15,15,15,15, 0,15,15, 0,15,15, 0, 0,15, 0,15, 0,15,15, 0,15,15,
   15, 0, 0,15, 0},
  {15,15,15,15,15,15,15, 0, 0, 0, 0, 0,15, 0,15, 0,15, 0,15, 0, 0,15, 0,15, 0,
   15, 0, 0,15, 0},
  { 0, 0, 0, 0, 0,15, 0, 0, 0, 0, 0, 0,15, 0,15, 0,15, 0, 0,15,15,15, 0,15, 0,
   15, 0, 0,15, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0},
  {15,15,15, 0, 0,15,15,15, 0, 0,15,15, 0, 0, 0, 0,15,15,15, 0,15, 0,15, 0,15,
    0,15,15,15, 0},
  {15, 0, 0, 0,15, 0, 0, 0, 0,15, 0, 0, 0, 0, 0, 0,15, 0, 0, 0,15, 0,15, 0, 0, 
    0, 0,15, 0, 0},
  {15,15, 0, 0, 0,15,15, 0, 0,15, 0, 0, 0,15,15, 0,15,15, 0, 0, 0,15, 0, 0,15,
    0, 0,15, 0, 0},
  {15, 0, 0, 0, 0, 0, 0,15, 0,15, 0, 0, 0, 0, 0, 0,15, 0, 0, 0,15, 0,15, 0,15, 
    0, 0,15, 0, 0},
  {15,15,15, 0,15,15,15, 0, 0, 0,15,15, 0, 0, 0, 0,15,15,15, 0,15, 0,15, 0,15,
    0, 0,15, 0, 0} 
};

int livestxt[Y_LIVES_TXT][X_LIVES_TXT] = {
  {15, 0, 0, 0,15, 0,15, 0,15, 0,15,15,15, 0, 0,15,15,15},
  {15, 0, 0, 0, 0, 0,15, 0,15, 0,15, 0, 0, 0,15, 0, 0, 0},
  {15, 0, 0, 0,15, 0,15, 0,15, 0,15,15, 0, 0, 0,15,15, 0},
  {15, 0, 0, 0,15, 0,15, 0,15, 0,15, 0, 0, 0, 0, 0, 0,15},
  {15,15,15, 0,15, 0, 0,15, 0, 0,15,15,15, 0,15,15,15, 0}
};
 
int stage_clear[Y_STAGE_CLEAR][X_STAGE_CLEAR] = {
  { 0,15,15,15,15, 0,15,15,15,15,15, 0, 0,15, 0, 0, 0, 0,15,15,15, 0, 0,15,15,
   15,15},
  {15, 0, 0, 0, 0, 0, 0, 0,15, 0, 0, 0,15, 0,15, 0, 0,15, 0, 0, 0, 0, 0,15, 0,
    0, 0},
  {15, 0, 0, 0, 0, 0, 0, 0,15, 0, 0,15, 0, 0, 0,15, 0,15, 0, 0, 0, 0, 0,15, 0,
    0, 0},
  { 0,15,15,15,15, 0, 0, 0,15, 0, 0,15, 0, 0, 0,15, 0,15, 0,15,15,15, 0,15,15,
   15, 0},
  { 0, 0, 0, 0, 0,15, 0, 0,15, 0, 0,15,15,15,15,15, 0,15, 0, 0, 0,15, 0,15, 0,
    0, 0},
  { 0, 0, 0, 0, 0,15, 0, 0,15, 0, 0,15, 0, 0, 0,15, 0,15, 0, 0, 0,15, 0,15, 0,
    0, 0},
  { 0,15,15,15,15, 0, 0, 0,15, 0, 0,15, 0, 0, 0,15, 0, 0,15,15,15, 0, 0,15,15,
   15,15},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0},
  { 0,15,15,15,15, 0,15, 0, 0, 0, 0,15,15,15,15, 0, 0, 0,15, 0, 0, 0,15,15,15,
    15, 0},
  {15, 0, 0, 0, 0, 0,15, 0, 0, 0, 0,15, 0, 0, 0, 0, 0,15, 0,15, 0, 0,15, 0, 0,
    0,15},
  {15, 0, 0, 0, 0, 0,15, 0, 0, 0, 0,15, 0, 0, 0, 0,15, 0, 0, 0,15, 0,15, 0, 0,
    0,15},
  {15, 0, 0, 0, 0, 0,15, 0, 0, 0, 0,15,15,15, 0, 0,15, 0, 0, 0,15, 0,15,15,15,
   15, 0},
  {15, 0, 0, 0, 0, 0,15, 0, 0, 0, 0,15, 0, 0, 0, 0,15,15,15,15,15, 0,15, 0, 0,
    0,15},
  {15, 0, 0, 0, 0, 0,15, 0, 0, 0, 0,15, 0, 0, 0, 0,15, 0, 0, 0,15, 0,15, 0, 0,
    0,15},
  { 0,15,15,15,15, 0,15,15,15,15, 0,15,15,15,15, 0,15, 0, 0, 0,15, 0,15, 0, 0,
    0,15}
};

int author[Y_AUTHOR][X_AUTHOR] = {
  {15,15, 0, 0,15,15,15, 0, 0,15, 0, 0,15, 0, 0, 0,15, 0,15,15,15, 0,15,15,15,
    0, 0,15, 0, 0,15,15,15, 0, 0,15,15, 0, 0, 0,15,15, 0, 0, 0,15, 0},
  {15, 0,15, 0,15, 0, 0, 0,15, 0,15, 0,15, 0, 0, 0, 0, 0, 0, 0,15, 0, 0, 0,15,
    0,15, 0,15, 0, 0,15, 0, 0,15, 0, 0,15, 0, 0,15, 0,15, 0,15, 0,15},
  {15,15, 0, 0,15,15, 0, 0,15, 0,15, 0,15, 0, 0, 0,15, 0, 0,15, 0, 0, 0,15, 0,
    0,15, 0,15, 0, 0,15, 0, 0,15, 0, 0,15, 0, 0,15, 0,15, 0,15, 0,15},
  {15, 0,15, 0,15, 0, 0, 0,15,15,15, 0,15, 0, 0, 0,15, 0,15, 0, 0, 0,15, 0, 0,
    0,15,15,15, 0, 0,15, 0, 0,15, 0, 0,15, 0, 0,15, 0,15, 0,15,15,15},
  {15, 0,15, 0,15,15,15, 0,15, 0,15, 0,15,15,15, 0,15, 0,15,15,15, 0,15,15,15,
    0,15, 0,15, 0, 0,15, 0, 0, 0,15,15, 0, 0, 0,15,15, 0, 0,15, 0,15},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {15,15,15, 0, 0,15,15,15, 0,15,15, 0, 0, 0,15, 0, 0, 0,15,15,15, 0,15, 0,15,
   15,15, 0, 0,15,15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {15, 0, 0, 0,15, 0, 0, 0, 0,15, 0,15, 0,15, 0,15, 0,15, 0, 0, 0, 0, 0, 0, 0,
   15, 0, 0,15, 0, 0,15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {15,15, 0, 0, 0,15,15, 0, 0,15,15, 0, 0,15, 0,15, 0, 0,15,15, 0, 0,15, 0, 0,
   15, 0, 0,15, 0, 0,15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {15, 0, 0, 0, 0, 0, 0,15, 0,15, 0, 0, 0,15, 0,15, 0, 0, 0, 0,15, 0,15, 0, 0,
   15, 0, 0,15, 0, 0,15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {15,15,15, 0,15,15,15, 0, 0,15, 0, 0, 0, 0,15, 0, 0,15,15,15, 0, 0,15, 0, 0,
   15, 0, 0, 0,15,15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,15,15,15, 0,15, 0, 0,15, 0, 0,
   15, 0, 0, 0,15, 0,15, 0, 0, 0,15, 0, 0,15, 0, 0,15,15, 0, 0,15, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,15, 0, 0, 0, 0, 0, 0,15, 0,15, 0,
   15,15, 0, 0,15, 0,15, 0, 0, 0,15, 0, 0,15, 0,15, 0, 0, 0,15, 0,15},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,15, 0,15,15, 0,15, 0,15, 0,15, 0,
   15, 0,15, 0,15, 0,15, 0, 0, 0,15, 0, 0,15, 0,15, 0, 0, 0,15, 0,15},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,15, 0, 0,15, 0,15, 0,15,15,15, 0,
   15, 0, 0,15,15, 0,15, 0, 0, 0,15, 0, 0,15, 0,15, 0, 0, 0,15,15,15},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,15,15,15, 0,15, 0,15, 0,15, 0,
   15, 0, 0, 0,15, 0,15,15,15, 0, 0,15,15, 0, 0, 0,15,15, 0,15, 0,15}
};

int tilt[Y_TILT][X_TILT] = {
  {15,15,15,15,15,15, 0,15,15, 0,15,15, 0, 0, 0,15,15,15,15,15,15, 0,15,15},
  {15,15,15,15,15,15, 0,15,15, 0,15,15, 0, 0, 0,15,15,15,15,15,15, 0,15,15},
  { 0, 0,15,15, 0, 0, 0, 0, 0, 0,15,15, 0, 0, 0, 0, 0,15,15, 0, 0, 0,15,15},
  { 0, 0,15,15, 0, 0, 0,15,15, 0,15,15, 0, 0, 0, 0, 0,15,15, 0, 0, 0,15,15},
  { 0, 0,15,15, 0, 0, 0,15,15, 0,15,15, 0, 0, 0, 0, 0,15,15, 0, 0, 0, 0, 0},
  { 0, 0,15,15, 0, 0, 0,15,15, 0,15,15,15,15, 0, 0, 0,15,15, 0, 0, 0,15,15},
  { 0, 0,15,15, 0, 0, 0,15,15, 0,15,15,15,15, 0, 0, 0,15,15, 0, 0, 0,15,15}
};

int game_over[Y_GAME_OVER][X_GAME_OVER] = {
  { 0,15,15,15, 0, 0,15, 0, 0,15, 0, 0, 0,15, 0,15,15,15},
  {15, 0, 0, 0, 0,15, 0,15, 0,15,15, 0,15,15, 0,15, 0, 0},
  {15, 0,15,15, 0,15, 0,15, 0,15, 0,15, 0,15, 0,15,15, 0},
  {15, 0, 0,15, 0,15,15,15, 0,15, 0, 0, 0,15, 0,15, 0, 0},
  { 0,15,15,15, 0,15, 0,15, 0,15, 0, 0, 0,15, 0,15,15,15},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0,15,15, 0, 0,15, 0,15, 0,15,15,15, 0,15,15,15, 0, 0},
  {15, 0, 0,15, 0,15, 0,15, 0,15, 0, 0, 0,15, 0, 0,15, 0},
  {15, 0, 0,15, 0,15, 0,15, 0,15,15, 0, 0,15,15,15, 0, 0},
  {15, 0, 0,15, 0,15, 0,15, 0,15, 0, 0, 0,15, 0, 0,15, 0},
  { 0,15,15, 0, 0, 0,15, 0, 0,15,15,15, 0,15, 0, 0,15, 0}
};

