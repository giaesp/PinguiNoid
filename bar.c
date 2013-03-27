/****************************************************************************/
/* File Info :                                                              */
/* -----------                                                              */
/* Nome File            : bar.c                                             */
/* Dimensione           : 4067 bytes                                        */
/* Data Ultima Modifica : Mercoledi' 7 Giugno 2000 - 16:44                  */
/* Autore               : Esposito Gianluca (Matr.Num.056/100858)           */
/* Breve Descrizione    : Valori di colore dei pixel relativi alla BARRA e  */
/*                        funzioni ad essa legate.                          */
/****************************************************************************/

#define BAR_X 29
#define BAR_Y 8
 
int xbar = 100;
int ybar = 230;
int barwidth;
int bartype;

/* --------------------------------------------------- */
/* Valori dei pixel per l'immagine relativa alla BARRA */
/* --------------------------------------------------- */
int Bar[BAR_Y][BAR_X] = {
  {129,132,  0,246,245,246,  0,129,134,134,134,134,134,134,134,134,134,
   134,134,134,134,129,  0,246,245,246,  0,132,129},
  {133,135,  0,245,244,245,  0,134,136,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,135,134,  0,246,245,246,  0,135,133},
  {135,137,  0,244,249,244,  0,135,138,  0,117,120,120,120,120,120,120,
   120,117,  0,138,136,  0,244,249,244,  0,137,135},
  {137,140,  0,  0,  0,  0,  0,  0,  0,  0,  0,116,119,119,119,119,119,
   116,  0,  0,  0,  0,  0,  0,  0,  0,  0,140,137},
  {135,137,  0, 97, 99,102,102,104,102,105,  0,  0,116,118,120,118,116,
     0,  0,105,102,104,102,102, 99, 97,  0,137,135},
  {133,135,  0, 97, 99, 99, 99,102,105,106,101,  0,  0,116,117,116,  0,
     0,101,106,105,102, 99, 99, 99, 97,  0,135,133},
  {131,133,  0,  0, 97,104,107,107,107,106,101,101,  0,  0, 97,  0,  0,
   101,101,106,107,107,107,104, 97,  0,  0,133,131},
  {129,132,  0, 99,  0, 99, 99, 99, 99, 99, 99, 99, 97, 97,  0, 97, 97,
    99, 99, 99, 99, 99, 99, 99,  0, 99,  0,132,129}
};

void DrawBar(int x, int y, int mode, int type);

void DrawBar(int x, int y, int mode, int type)
/* Disegna a video alle coordinate x, y la barra in modalita' */
/* mode (OMBRA oppure SOLID) e del tipo specificato da type   */
/* (NORMAL, EXTEND oppure REDUCE).                            */
{
  int i,j,z;
  switch(type) {
    case NORMAL : barwidth = 29;
                  for(j=0;j<BAR_Y;j++) {
                    for(i=0;i<BAR_X;i++) {
                      if(mode == SOLID) vga_setcolor(Bar[j][i]);
                      if(mode == OMBRA) vga_setcolor(0);
                      vga_drawpixel(x+i, y+j);
                    }
                  }
                  break;

    case EXTEND : barwidth = 34;
                  for(j=0;j<BAR_Y;j++) {
                    for(i=0;i<14;i++) {
                      if(mode == SOLID) vga_setcolor(Bar[j][i]);
                      if(mode == OMBRA) vga_setcolor(0);
                      vga_drawpixel(x+i, y+j);
		    }
            	    for(i=14;i<22;i++) {
		      if(mode == SOLID) vga_setcolor(Bar[j][14]);
                      if(mode == OMBRA) vga_setcolor(0);
                      vga_drawpixel(x+i, y+j);
		    }
		    for(i=22;i<BAR_X+6;i++) {
                      if(mode == SOLID) vga_setcolor(Bar[j][i-6]);
                      if(mode == OMBRA) vga_setcolor(0);
                      vga_drawpixel(x+i, y+j);
		    }
                  }
                  break;

    case REDUCE : barwidth = 23;
                  for(j=0;j<BAR_Y;j++) {
                    for(i=0;i<12;i++) {
                      if(mode == SOLID) vga_setcolor(Bar[j][i]);
                      if(mode == OMBRA) vga_setcolor(0);
                      vga_drawpixel(x+i, y+j);
		    }
		    for(i=17;i<BAR_X;i++) {
                      if(mode == SOLID) vga_setcolor(Bar[j][i]);
                      if(mode == OMBRA) vga_setcolor(0);
                      vga_drawpixel(x+i-5, y+j);
		    }
                  }
                  break;
  }
}
