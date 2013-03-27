/*****************************************************************************/
/* File Info :                                                               */
/* -----------                                                               */
/* Nome File            : score.c                                            */
/* Dimensioni           : 5216 bytes                                         */
/* Data Ultima Modifica : Domenica 28 Maggio 2000 - 17:17                    */
/* Autore               : Esposito Gianluca (Matr.Num.056/100858)            */
/* Breve Descrizione    : Contiene le funzioni relative ai grafici del       */
/*                        punteggio in modo da disegnarlo simile ad un       */
/*                        display digitale.                                  */
/*****************************************************************************/

#define OFF_COLOR 3
#define ON_COLOR 25
#define MAX_CIFRE 6

int score;
int pointstring[MAX_CIFRE];

void DrawDigitalNumber(int x, int y, int num);
void Led(int x, int y, int numled);
void DrawScore(void);
void int2string(void);

void DrawDigitalNumber(int x, int y, int num) 
/* Disegna a video alle coordinate x, y, il numero num. */ 
{
  switch(num) {
  case 0 : vga_setcolor(ON_COLOR);
           Led(x,y,0);
           Led(x,y,1);
           Led(x,y,2); 
           Led(x,y,3);
           Led(x,y,4);
           Led(x,y,5);
           vga_setcolor(OFF_COLOR);
           Led(x,y,6);
           break;

  case 1 : vga_setcolor(ON_COLOR);
           Led(x,y,1);
           Led(x,y,2);
           vga_setcolor(OFF_COLOR);
           Led(x,y,0); 
           Led(x,y,3);
           Led(x,y,4);
           Led(x,y,5);
           Led(x,y,6);
           break;

  case 2 : vga_setcolor(ON_COLOR);
           Led(x,y,0);
           Led(x,y,1);
           Led(x,y,3);
           Led(x,y,4);
           Led(x,y,6);
           vga_setcolor(OFF_COLOR);
           Led(x,y,2);
           Led(x,y,5);
           break;

  case 3 : vga_setcolor(ON_COLOR);
           Led(x,y,0);
           Led(x,y,1);
           Led(x,y,2);
           Led(x,y,3);
           Led(x,y,6);
           vga_setcolor(OFF_COLOR);
           Led(x,y,4);
           Led(x,y,5);
           break;

  case 4 : vga_setcolor(ON_COLOR);
           Led(x,y,1);
           Led(x,y,2);
           Led(x,y,5);
           Led(x,y,6);
           vga_setcolor(OFF_COLOR);
           Led(x,y,0);
           Led(x,y,3);
           Led(x,y,4);
           break;

  case 5 : vga_setcolor(ON_COLOR);
           Led(x,y,0);
           Led(x,y,2);
           Led(x,y,3);
           Led(x,y,5);
           Led(x,y,6);
           vga_setcolor(OFF_COLOR);
           Led(x,y,1);
           Led(x,y,4);
           break;

  case 6 : vga_setcolor(ON_COLOR);
           Led(x,y,0);
           Led(x,y,2);
           Led(x,y,3); 
           Led(x,y,4);
           Led(x,y,5);
           Led(x,y,6);
           vga_setcolor(OFF_COLOR);
           Led(x,y,1);
           break;

  case 7 : vga_setcolor(ON_COLOR);
           Led(x,y,0);
           Led(x,y,1);
           Led(x,y,2);
           Led(x,y,5);
           vga_setcolor(OFF_COLOR);
           Led(x,y,3);
           Led(x,y,4);
           Led(x,y,6);
           break;

  case 8 : vga_setcolor(ON_COLOR);
           Led(x,y,0);
           Led(x,y,1);
           Led(x,y,2);
           Led(x,y,3);
           Led(x,y,4);
           Led(x,y,5);
           Led(x,y,6);    
           break;

  case 9 : vga_setcolor(ON_COLOR);
           Led(x,y,0);
           Led(x,y,1);
           Led(x,y,2);
           Led(x,y,3);
           Led(x,y,5);
           Led(x,y,6);
           vga_setcolor(OFF_COLOR);
           Led(x,y,4);
           break;
  }
}

void Led(int x, int y, int numled)
/* Attiva/Disattiva il LED specificato da numled */
{
  switch(numled) {
    case 0 : vga_drawline(x+1, y+0, x+5, y+0);
             vga_drawline(x+2, y+1, x+4, y+1);
             break;
    case 1 : vga_drawline(x+5, y+2, x+5, y+4);
             vga_drawline(x+6, y+1, x+6, y+5);
             break;
    case 2 : vga_drawline(x+5, y+8, x+5, y+10);
             vga_drawline(x+6, y+7, x+6, y+11);
             break;
    case 3 : vga_drawline(x+2, y+11,x+4, y+11);
             vga_drawline(x+1, y+12,x+5, y+12);
             break;
    case 4 : vga_drawline(x+0, y+7, x+0, y+11);
             vga_drawline(x+1, y+8, x+1, y+10);
             break;
    case 5 : vga_drawline(x+0, y+1, x+0, y+5);
             vga_drawline(x+1, y+2, x+1, y+4);
             break;
    case 6 : vga_drawline(x+2, y+5, x+4, y+5);
             vga_drawline(x+1, y+6, x+5, y+6);
             vga_drawline(x+2, y+7, x+4, y+7);
             break;
  }
}

void DrawScore(void)
{
  int2string();
  DrawDigitalNumber(273,20,pointstring[0]);
  DrawDigitalNumber(281,20,pointstring[1]);
  DrawDigitalNumber(289,20,pointstring[2]);
  DrawDigitalNumber(297,20,pointstring[3]);
  DrawDigitalNumber(305,20,pointstring[4]);
  DrawDigitalNumber(313,20,pointstring[5]);
}

void int2string(void)
{
  int i;
  int temp = 0, divisore = 100000;
  for(i=0;i<MAX_CIFRE;i++) {
    pointstring[i] = (int)(score-temp)/divisore;
    temp+=pointstring[i]*divisore;
    divisore = divisore/10; 
  }
}





