/*******************************************************************/
/*   PINGUINoid!                                                   */
/*   -----------                                                   */
/*   File            : pnoid.c                                     */
/*   Dimensioni      : 33801 bytes                                 */
/*   Ultima modifica : Mercoledi' 7 Giugno 2000 - 16:43            */
/*                                                                 */
/*   N.B. 1) Compilare con : gcc -lvgagl -lvga -opnoid pnoid.c     */
/*        2) L'eseguibile dovra' essere settato da un utente root  */
/*           con permessi 7777, affinche' possa essere usato da    */
/*           utenti con permessi non-root. In caso contrario       */
/*           le SVGAlib genererebbero il messagio di errore        */
/*           "Cannot get I/O permission" causando l'uscita dal     */
/*           programma.                                            */
/*                                                                 */
/*   Realizzato da Gianluca Esposito (Num.Matr.056/100858)         */
/*   Prova di Laboratorio di Informatica I                         */
/*   Prof. M.Tucci                                                 */
/*   Universita' degli Studi di Salerno                            */
/*   Facolta' di Scienze matematiche fisiche e naturali            */
/*   Corso di Laurea in Informatica                                */
/*   Anno Accademico 1999/2000                                     */
/*******************************************************************/
   
#define SOLID 1
#define OMBRA 0

#define TRUE 1
#define FALSE 0

#define ON 1
#define OFF 0

#define NORMAL 0

#include <stdio.h>
#include <stdlib.h>

#include <vga.h>
#include <vgagl.h>
#include <vgakeyboard.h>

#include "256color.c"
#include "bonus.c"
#include "ball.c"
#include "brick.c"
#include "bar.c"
#include "score.c"
#include "logo.c"
#include "lives.c"
#include "stage.c"
#include "text.c"

#define DEFAULT_USLEEP 1000
#define LEFT_LIMIT 10
#define UPPER_LIMIT 10
#define RIGHT_LIMIT 262
#define TILT_LIMIT 50
#define LOCK_TIME 100

/* Variabili Globali */
int speedcounter;
int leftpress;
int rightpress;
int current_stage;
int numlives;
int tilt_counter;
int lock_counter;

void ProgramInfo(void);
void Partita(void);
void DrawBorder(void);
void DrawSfondo(void);
void DrawMap(void);
void Key_Control(void);
void Key_Tilt(void);
void Key_Laser(void);
void BrickContact(int ballid);
void BarContact(int ballid);
void BorderContact(int ballid);
void LoseALife(void);
void BonusContact(int counter);
void MultiBall(void);
void ActiveBall(void);
void BallLock(void);
void Extend(void);
void Reduce(void);
void UpdateCounter(void);
void InitLife(void);
void InitGame(void);
void InitStage(void);
void AssignBonus(void);
void BackupWinCounter(void);
void RestoreWinCounter(void);
void BackupMaps(void);
void RestoreMaps(void);
void KillTouchedBonus(void);
void KillLaser(void);
void KillMultiBall(void);
void ExitProgram(void);

int main(void)
{
  system("clear");
  ProgramInfo();
  vga_disabledriverreport();
  vga_init();
  vga_setmode(G320x240x256);
  gl_setcontextvga(G320x240x256);
  LoadPalette();
  keyboard_init();
  Partita(); 
  return 0;
}

void ProgramInfo(void)
/* Scrive a video una piccola introduzione al programma. */
{ 
  printf("\n\n\n  PINGUINoid\n");
  printf("  ----------\n");
  printf("  Progetto realizzato da\n");
  printf("  ESPOSITO GIANLUCA (Matr.Num. 056/100858)\n");
  printf("  per la Prova di Laboratorio di Informatica I\n");
  printf("  relativa al Corso tenuto dal Prof. M. Tucci\n\n");
  printf("  Universita' degli Studi di Salerno\n");
  printf("  Facolta' di Scienze matematiche fisiche e naturali\n");
  printf("  Corso di Laurea in Informatica\n");
  printf("  Anno Accademico 1999/2000\n\n");
  printf("\n\n\n  Premi INVIO per continuare\n");
  fflush(stdin);
  getchar();
}

void Partita(void)
/* Gestisce l'intera partita aggiornando costantemente i vari flag */
/* ed i vari valori di posizione e gestendo le varie immagini da   */
/* disegnare a video.                                              */
{
  int i;
  InitGame();
  while(TRUE) {
    UpdateCounter();   
    for(i=0;i<MAX_BALLS;i++) {
      keyboard_update();
      if(keyboard_keypressed(SCANCODE_ESCAPE)==KEY_PRESSED) 
        ExitProgram();
      Key_Control();
      Key_Tilt();
      Key_Laser();
      
      if(keyboard_keypressed(SCANCODE_SPACE)==KEY_PRESSED && 
         ball_lock == TRUE) 
        ball_lock = FALSE;
      if(ball_lock == FALSE && xball[i]>=0 && xball[i]<=RIGHT_LIMIT &&
                               yball[i]>=0 && yball[i]<=240) {
        BrickContact(i); 
        BorderContact(i);
        BarContact(i);
        if(xball[i]!=KILLED && yball[i]!=KILLED) {  
          DrawObject(xball[i], yball[i], BALL_X, BALL_Y, Ball, OMBRA); 
          xball[i] += Direzione[velocita][direction[i]].passox;
          yball[i] += Direzione[velocita][direction[i]].passoy;
          DrawObject(xball[i], yball[i], BALL_X, BALL_Y, Ball, SOLID);
        }
        if(laserfired == ON && laserflag == ON) {
          if(ylaser <= 14.0) {
	    DrawObject(xlaser, (int)ylaser, LASER_X, LASER_Y, laser, OMBRA);
            laserfired = OFF;
            xlaser = KILLEDLASER;
            ylaser = (float)KILLEDLASER;
	  } 
        }
        if(yball[i] >= 240) {
          xball[i] = KILLED;
          yball[i] = KILLED;
          ballingame-=1;
        }    
        if(ballingame == 1) KillMultiBall();
        if(ballingame==0) LoseALife();
      }    
    }    
    usleep(DEFAULT_USLEEP);
  }
}

void DrawBorder(void)
/* Disegna a video i bordi dell'area giocabile */
{  
  int i;
  for(i=3;i<11;i++) {
    vga_setcolor(i);
    vga_drawline(i-3,0,i-3,240);
    vga_drawline(275-i,0,275-i,240);
    vga_drawline(0,i-3,272,i-3);
  }
} 

void DrawSfondo(void)
/* Disegna a video le componenti informative del gioco quali */
/* il logo, il titolo, l'autore, i tasti, etc.               */ 
{
  DrawBorder();  
  DrawObject(LOGO);
  DrawObject(TITLE);
  DrawObject(AUTHOR);
  DrawObject(KEYS);
  DrawObject(LIVES_TXT);
  DrawObject(SCORE);
  DrawScore();
  DrawLives(numlives);
}

void DrawMap(void)
/* Disegna a video la mappa relativa allo stage corrente (current_stage). */
{
  int i;
  for(i=0;i<MAP_OBJECT;i++) {
    DrawBrick(STD_MAPX+MapXY[i].begx,
              STD_MAPY+MapXY[i].begy,
              MapObj[current_stage][i]);
  }
}

void Key_Control(void)
/* Controlla lo stato dei tasti di controllo (left e right)   */
/* tenendo in considerazione l'avvenuta o meno attivazione    */
/* del flag "reverseflag" che abilita l'inversione dei tasti. */
{
  if(reverseflag == OFF) {
    if(keyboard_keypressed(SCANCODE_CURSORBLOCKLEFT)==KEY_PRESSED) {
      leftpress = TRUE;
      if(xbar >= LEFT_LIMIT+3) {
        xbar -= 2;
        DrawBar(xbar+2, ybar, OMBRA, bartype);
        DrawBar(xbar, ybar, SOLID, bartype);
        if(ball_lock == TRUE) {
          xball[0] -= 2;
          DrawObject(xball[0]+2, yball[0], BALL_X, BALL_Y, Ball, OMBRA);
          DrawObject(xball[0], yball[0], BALL_X, BALL_Y, Ball, SOLID);
        }
      }
    }
    else leftpress = FALSE;

    if(keyboard_keypressed(SCANCODE_CURSORBLOCKRIGHT)==KEY_PRESSED) {
      rightpress = TRUE;
      if(xbar+2+barwidth<RIGHT_LIMIT) {
        xbar+=2;
	DrawBar(xbar-2, ybar, OMBRA, bartype);
	DrawBar(xbar, ybar, SOLID, bartype);
        if(ball_lock == TRUE) {
          xball[0]+=2;
          DrawObject(xball[0]-2, yball[0], BALL_X, BALL_Y, Ball, OMBRA);
          DrawObject(xball[0], yball[0], BALL_X, BALL_Y, Ball, SOLID);
        }
      }
    }
    else rightpress = FALSE;
  }

  else if(reverseflag == ON) {
    if(keyboard_keypressed(SCANCODE_CURSORBLOCKLEFT)==KEY_PRESSED) {
      rightpress = TRUE;
      if(xbar+2+barwidth<RIGHT_LIMIT) {
        xbar+=2;
        DrawBar(xbar-2, ybar, OMBRA, bartype);
        DrawBar(xbar, ybar, SOLID, bartype);
        if(ball_lock == TRUE) {
          xball[0]+=2;
          DrawObject(xball[0]-2, yball[0], BALL_X, BALL_Y, Ball, OMBRA);
          DrawObject(xball[0], yball[0], BALL_X, BALL_Y, Ball, SOLID);
        }
      }
    }
    else rightpress = FALSE;

    if(keyboard_keypressed(SCANCODE_CURSORBLOCKRIGHT)==KEY_PRESSED) {
      leftpress = TRUE;
      if(xbar>=LEFT_LIMIT+3) {
        xbar-=2;
	DrawBar(xbar+2, ybar, OMBRA, bartype);
	DrawBar(xbar, ybar, SOLID, bartype);
        if(ball_lock == TRUE) {
          xball[0]-=2;
          DrawObject(xball[0]+2, yball[0], BALL_X, BALL_Y, Ball, OMBRA);
          DrawObject(xball[0], yball[0], BALL_X, BALL_Y, Ball, SOLID);
        }
      }
    }
    else leftpress = FALSE;
  }
}

void Key_Tilt(void)
/* Controlla i tasti-tilt: se premuti questi generano un effetto */
/* "flipper" ovvero simulano una spinta al monitor, con relativo */
/* spostamento anomalo della pallina.                            */
/* Controlla il tilt-counter: se premuti troppe volte, generano  */
/* il "tilt" del gioco, causando cosi' la perdita di un credit.  */
{ 
   if(keyboard_keypressed(SCANCODE_LEFTSHIFT)==KEY_PRESSED) {
     tilt_counter += 1;
     if(xball[0] != KILLED && 
        xball[0]>=LEFT_LIMIT+3 && xball[0]<=RIGHT_LIMIT-7){
       DrawObject(xball[0], yball[0], BALL_X, BALL_Y, Ball, OMBRA);
       xball[0]+=1;
     }
     if(xball[1] != KILLED && 
        xball[1]>=LEFT_LIMIT+3 && xball[1]<=RIGHT_LIMIT-7) {
       DrawObject(xball[1], yball[1], BALL_X, BALL_Y, Ball, OMBRA);
       xball[1]+=1; 
     }
     if(xball[2] != KILLED && 
        xball[2]>=LEFT_LIMIT+3 && xball[2]<=RIGHT_LIMIT-7) {
       DrawObject(xball[2], yball[2], BALL_X, BALL_Y, Ball, OMBRA);
       xball[2]+=1;
     }
   }

   if(keyboard_keypressed(SCANCODE_RIGHTSHIFT)==KEY_PRESSED) {
     tilt_counter += 1;
     if(xball[0] != KILLED && 
        xball[0]>=LEFT_LIMIT+3 && xball[0]<=RIGHT_LIMIT-7) {
       DrawObject(xball[0], yball[0], BALL_X, BALL_Y, Ball, OMBRA);
       xball[0] -= 1;
     }
     if(xball[1] != KILLED && 
        xball[1]>=LEFT_LIMIT+3 && xball[1]<=RIGHT_LIMIT-7) {
       DrawObject(xball[1], yball[1], BALL_X, BALL_Y, Ball, OMBRA);
       xball[1] -= 1;
     }
     if(xball[2] != KILLED && 
        xball[2]>=LEFT_LIMIT+3 && xball[2]<=RIGHT_LIMIT-7) {
       DrawObject(xball[2], yball[2], BALL_X, BALL_Y, Ball, OMBRA);
       xball[2] -= 1;
     }  
   }

   if(tilt_counter>=TILT_LIMIT) {
     DrawObject(TILT_ON);
     LoseALife();
     sleep(2);
     DrawBar( xbar, ybar, OMBRA, bartype);
     InitLife();
   }
}
    
void Key_Laser(void)
/* Controlla i tasti relativi allo sparo di un laser (se questo e' */
/* abilitato.                                                      */
{
  if(keyboard_keypressed(SCANCODE_SPACE)==KEY_PRESSED &&
     laserflag == ON && laserfired != ON) {
    laserfired = ON;
    if(xlaser == KILLEDLASER) xlaser = xbar + 13;
    if((int)ylaser == KILLEDLASER) ylaser = (float)(ybar - 6);
  }
 
  if(laserflag == ON && laserfired == ON) {
    DrawObject(xlaser, (int)ylaser, LASER_X, LASER_Y, laser, OMBRA);
    ylaser -= 2.0;
    if(ylaser != (float)KILLEDLASER) 
      DrawObject(xlaser, (int)ylaser, LASER_X, LASER_Y, laser, SOLID);
  }
}

void BrickContact(int ballid)
/* Controlla l'eventuale contatto tra la palla ballid e uno dei */
/* mattoni dello stage. In caso di contatto elimina il mattone  */
/* e, se presente, lascia cadere un bonus, oltra al cambio      */
/* direzionale della pallina. In caso contrario la pallina      */
/* continua il suo tragitto.                                    */
/* Controlla anche un eventuale contatto tra laser e mattone.   */
{
  int i;
  for(i=0;i<MAP_OBJECT;i++) {
    if(MapObj[current_stage][i]!= FALSE) {

      /* Contatto con la parte inferiore del mattone (Laser)  */
      if(laserfired == ON && laserflag == ON     &&
         xlaser >= STD_MAPX+MapXY[i].begx-4      &&
         xlaser <= STD_MAPX+MapXY[i].begx+20     &&
         (int)ylaser >= STD_MAPY+MapXY[i].begy+6 &&
         (int)ylaser <= STD_MAPY+MapXY[i].begy+11) {
        DrawObject(xlaser, (int)ylaser, LASER_X, LASER_Y, laser, OMBRA);
        laserfired = OFF;
        xlaser = KILLEDLASER;
        ylaser = (float)KILLEDLASER;
        score+=5;
        DrawScore();
        if(MapObj[current_stage][i] == GRAY1)
          DrawBrick(STD_MAPX+MapXY[i].begx, STD_MAPY+MapXY[i].begy, GRAY1);
        else {
          MapObj[current_stage][i] = OMBRA;
          DrawBrick(STD_MAPX+MapXY[i].begx, STD_MAPY+MapXY[i].begy,OMBRA);
          wincounter[current_stage] -= 1;
          Bonus[i].touched = TRUE;
        }
      }

      /* Contatto con la parte superiore del mattone */
      if(xball[ballid]   >= STD_MAPX+MapXY[i].begx-5   &&
         xball[ballid]+2 <= STD_MAPX+MapXY[i].begx+15  &&
         yball[ballid]+5 >= STD_MAPY+MapXY[i].begy-3   &&
         yball[ballid]+5 <= STD_MAPY+MapXY[i].begy+3) {
        score += 5;
        DrawScore();
        if(MapObj[current_stage][i]==GRAY1)
          DrawBrick(STD_MAPX+MapXY[i].begx,STD_MAPY+MapXY[i].begy, GRAY1);
        else {
          MapObj[current_stage][i] = OMBRA;
          DrawBrick(STD_MAPX+MapXY[i].begx,STD_MAPY+MapXY[i].begy,OMBRA);
          wincounter[current_stage] -= 1;
	  Bonus[i].touched = TRUE;
        }
        switch(direction[ballid]) {
	  case  0 : direction[ballid] = 11; break;
	  case  1 : direction[ballid] =  0; break;
	  case  2 : direction[ballid] =  1; break;
	  case  3 : direction[ballid] =  2; break;
	  case  4 : direction[ballid] =  1; break;
	  case  5 : direction[ballid] =  0; break;
	  case  6 : direction[ballid] = 11; break;
	  case  7 : direction[ballid] = 10; break;
	  case  8 : direction[ballid] =  9; break;
   	  case  9 : direction[ballid] = 10; break;
	  case 11 : direction[ballid] =  0; break;
	}
      }

      /* Contatto con la parte inferiore del mattone */
      else if(xball[ballid]+3 >= STD_MAPX+MapXY[i].begx-4   &&
              xball[ballid]+2 <= STD_MAPX+MapXY[i].begx+15  &&
              yball[ballid]   >= STD_MAPY+MapXY[i].begy+4   &&
              yball[ballid]   <= STD_MAPY+MapXY[i].begy+10) {
        score+=5;
        DrawScore();
        if(MapObj[current_stage][i]==GRAY1)
	  DrawBrick(STD_MAPX+MapXY[i].begx,STD_MAPY+MapXY[i].begy, GRAY1);
        else {
          MapObj[current_stage][i] =OMBRA;
          DrawBrick(STD_MAPX+MapXY[i].begx,STD_MAPY+MapXY[i].begy,OMBRA);
          wincounter[current_stage] -= 1;
	  Bonus[i].touched = TRUE;
        }
        switch(direction[ballid]) {
	  case  0 : direction[ballid] = 5; break;
 	  case  1 : direction[ballid] = 4; break;
	  case  2 : direction[ballid] = 3; break;
	  case  3 : direction[ballid] = 4; break;
	  case  4 : direction[ballid] = 5; break;
	  case  5 : direction[ballid] = 6; break;
	  case  6 : direction[ballid] = 7; break;
	  case  7 : direction[ballid] = 4; break;
	  case  8 : direction[ballid] = 6; break;
	  case  9 : direction[ballid] = 8; break;
	  case 10 : direction[ballid] = 7; break;
	  case 11 : direction[ballid] = 6; break;
	}
      }

      /* Contatto con la parte sinistra del mattone */
      else if(xball[ballid]+5>=STD_MAPX+MapXY[i].begx-3 &&
              xball[ballid]+5<=STD_MAPX+MapXY[i].begx+7 &&
              yball[ballid]+3>=STD_MAPY+MapXY[i].begy   &&
              yball[ballid]+2<=STD_MAPY+MapXY[i].begy+8) {
        score+=5;
        DrawScore();
        if(MapObj[current_stage][i]==GRAY1)
          DrawBrick(STD_MAPX+MapXY[i].begx,STD_MAPY+MapXY[i].begy, GRAY1);
        else {
          MapObj[current_stage][i] = OMBRA;
          DrawBrick(STD_MAPX+MapXY[i].begx,STD_MAPY+MapXY[i].begy,OMBRA);
	  wincounter[current_stage] -= 1;
          Bonus[i].touched = TRUE;
        }
        switch(direction[ballid]) {
          case  0 : direction[ballid] = 11; break;
	  case  1 : direction[ballid] = 10; break;
	  case  2 : direction[ballid] =  9; break;
	  case  3 : direction[ballid] =  8; break;
	  case  4 : direction[ballid] =  7; break;
	  case  5 : direction[ballid] =  6; break;
	  case  6 : direction[ballid] =  7; break;
   	  case  7 : direction[ballid] =  8; break;
	  case  8 : direction[ballid] =  9; break;
  	  case  9 : direction[ballid] =  8; break;
	  case 10 : direction[ballid] =  9; break;
	  case 11 : direction[ballid] = 10; break;
	}
      }

     /* Contatto con la parte destra del mattone */
     else if(xball[ballid]   >= STD_MAPX+MapXY[i].begx+8  &&
             xball[ballid]   <= STD_MAPX+MapXY[i].begx+18 &&
             yball[ballid]+3 >= STD_MAPY+MapXY[i].begy    &&
             yball[ballid]+2 <= STD_MAPY+MapXY[i].begy+8) {
       score += 5;
	DrawScore();
        if(MapObj[current_stage][i]==GRAY1)
	  DrawBrick(STD_MAPX+MapXY[i].begx,STD_MAPY+MapXY[i].begy, GRAY1);
        else {
          MapObj[current_stage][i] = OMBRA;
          DrawBrick(STD_MAPX+MapXY[i].begx,STD_MAPY+MapXY[i].begy, OMBRA);
	  wincounter[current_stage] -= 1;
	  Bonus[i].touched = TRUE;
        }
        switch(direction[ballid]) {
	  case  0 : direction[ballid] = 1; break;
	  case  1 : direction[ballid] = 2; break;
	  case  2 : direction[ballid] = 3; break;
	  case  3 : direction[ballid] = 0; break;
	  case  4 : direction[ballid] = 2; break;
	  case  5 : direction[ballid] = 1; break;
	  case  6 : direction[ballid] = 5; break;
	  case  7 : direction[ballid] = 4; break;
	  case  8 : direction[ballid] = 3; break;
	  case  9 : direction[ballid] = 2; break;
	  case 10 : direction[ballid] = 1; break;
	  case 11 : direction[ballid] = 0; break;
	}
      }
    }    
    BonusContact(i);
  } 
}

void BarContact(int ballid)
/* Controlla l'eventuale contatto tra la pallina (ballid) e       */
/* la barra usata dall'utente per ribatterla. In caso di contatto */
/* la palla viene respinta, cambiando quindi direzione.           */
/* Il cambio direzionale e' influenzato diversamente se la barra  */
/* e' immobile oppure in movimento, rendendo cosi' piu' vario     */
/* il tipo di risposta della pallina al contatto con la barra.    */
{
  if(xball[ballid]>=xbar          &&
     xball[ballid]<=xbar+barwidth &&
     yball[ballid]>=ybar-7        &&
     yball[ballid]<=240) {
    DrawBar(xbar,ybar,SOLID, bartype); 
    if(leftpress == TRUE) {
      switch(direction[ballid]) {
	case 3 : direction[ballid] =  1; break;
        case 4 : direction[ballid] =  2; break;
        case 5 : direction[ballid] =  2; break;
	case 6 : direction[ballid] = 10; break;
	case 7 : direction[ballid] =  9; break;
	case 8 : direction[ballid] = 11; break;
      }
    }
    if(rightpress == TRUE) {
      switch(direction[ballid]) {
	case 3 : direction[ballid] =  0; break;
	case 4 : direction[ballid] =  2; break;
	case 5 : direction[ballid] =  1; break;
	case 6 : direction[ballid] = 10; break;
	case 7 : direction[ballid] =  9; break;
	case 8 : direction[ballid] =  9; break;
      }
    }
    if(leftpress == FALSE && rightpress == FALSE) {
      switch(direction[ballid]) {
	case 3 : direction[ballid] =  2; break;
	case 4 : direction[ballid] =  1; break;
	case 5 : direction[ballid] =  0; break;
	case 6 : direction[ballid] = 11; break;
        case 7 : direction[ballid] = 10; break;
	case 8 : direction[ballid] =  9; break;
      }
    }
  }
}

void BorderContact(int ballid)
/* Controlla il contatto della pallina (ballid) con i bordi */
/* gestendo il cambio direzionale.                          */
{
  /* Contatto con il bordo sinistro */
  if(xball[ballid]<=LEFT_LIMIT+3) {
    switch(direction[ballid]) {
      case  6 : direction[ballid] = 5; break;
      case  7 : direction[ballid] = 4; break;
      case  8 : direction[ballid] = 3; break;
      case  9 : direction[ballid] = 2; break;
      case 10 : direction[ballid] = 1; break;
      case 11 : direction[ballid] = 0; break;
    }
  }

  /* Contatto con il bordo destro */
  if(xball[ballid]>=RIGHT_LIMIT-7) {
    switch(direction[ballid]) {
      case 0 : direction[ballid] = 11; break;
      case 1 : direction[ballid] = 10; break;
      case 2 : direction[ballid] =  9; break;
      case 3 : direction[ballid] =  8; break;
      case 4 : direction[ballid] =  7; break;
      case 5 : direction[ballid] =  6; break;
    }
  }      

  /* Contatto con la parte superiore */
  if(yball[ballid]<=UPPER_LIMIT+3) {
    switch(direction[ballid]) {
      case  0 : direction[ballid] = 5; break;
      case  1 : direction[ballid] = 4; break;
      case  2 : direction[ballid] = 3; break;
      case  9 : direction[ballid] = 8; break;
      case 10 : direction[ballid] = 7; break;
      case 11 : direction[ballid] = 6; break;
    }
  }
}

void LoseALife(void)
/* Gestisce la perdita di un credit controllando anche il numero di   */
/* credit restanti e generando cosi' soluzioni diverse per ogni caso. */
{
  if(numlives>=1) {
    numlives -= 1;
    DrawLives(numlives);
    sleep(2);
    DrawBar(xbar, ybar, OMBRA, bartype);
    InitLife();
  } 

  if(numlives == 0) {
    DrawObject(GAME_OVER_ON); 
    sleep(2);
    keyboard_waitforupdate();
    RestoreMaps();
    RestoreWinCounter();
    InitGame();
  }
}


void BonusContact(int counter)
/* Gestisce la caduta dei bonus.                               */
/* Controlla eventuali conflitti tra bonus in caduta e mattoni */
/* non ancora toccati dalla pallina, ridisegnando il mattone   */
/* in conflitto che altrimenti sarebbe sovrascritto dal bonus, */
/* ma rimarebbe attivo e non visto dall'utente.                */ 
/* Controlla se il bonus in caduta viene "catturato" dalla     */
/* barra dell'utente, generando cosi' le conseguenze relative  */
/* a quel tipo di bonus.                                       */
{
  int i;

  /* Gestione dei conflitti tra mattoni e bonus in caduta */
  for(i=counter;i<MAP_OBJECT;i+=16) {
    if(Bonus[counter].touched==TRUE && Bonus[counter].type!=NB &&
       ((int)(Bonus[counter].y+8.0) >= MapXY[i].begy+STD_MAPY  ||
        (int)Bonus[counter].y   <= MapXY[i].begy+STD_MAPY+8)   &&
        (int)Bonus[counter].y   <= MapXY[MAP_OBJECT-1].begy+8  &&
        MapObj[current_stage][i] != OMBRA)
    DrawBrick(MapXY[i].begx+STD_MAPX,
              MapXY[i].begy+STD_MAPY,
              MapObj[current_stage][i]);
  }

  /* Gestione dello scrolling dei bonus */
  if(Bonus[counter].touched==TRUE && Bonus[counter].type!=NB &&
     (int)Bonus[counter].y<=240 && Bonus[counter].permission==TRUE) {
    switch(ballingame) {
      case 1 : Bonus[counter].y += 1.0; break;
      case 2 : Bonus[counter].y += 0.5; break;
      case 3 : Bonus[counter].y += 0.34; break;
    } 
    DrawBonus(Bonus[counter].x,(int)Bonus[counter].y-1,
	      Bonus[counter].type,OMBRA); 
    DrawBonus(Bonus[counter].x,(int)Bonus[counter].y,
              Bonus[counter].type,SOLID);
  } 

  /* Contatto Barra/Bonus e relative conseguenze */
  if((int)Bonus[counter].y+8  >= ybar && (int)Bonus[counter].y<=ybar+8  &&
     Bonus[counter].x+16 >= xbar && Bonus[counter].x<=xbar+barwidth     &&
     Bonus[counter].permission == TRUE) {
    Bonus[counter].permission = FALSE;
    DrawBonus(Bonus[counter].x, (int)Bonus[counter].y,
              Bonus[counter].type, OMBRA);
    DrawBar(xbar, ybar, SOLID, bartype);
    switch(Bonus[counter].type) {
      case EXTEND     : if(laserflag == ON) laserflag = OFF;
                        Extend();
                        score += 25;
                        break;
      case REDUCE     : if(laserflag == ON) laserflag = OFF;
                        Reduce();
                        score += 25;
                        break;
      case LIVES      : if(numlives < 5) numlives+=1;
                        DrawLives(numlives);
                        score += 100;
                        break;
      case BALL_LOCK  : BallLock(); 
                        score += 20;
                        break;
      case MULTI_BALL : if(multiball==OFF) {
                          ballingame = 3;
                          multiball = ON;
                          MultiBall();
                        };
                        score += 20;
                        break;
      case SPEED_DOWN : if(velocita > 0 ) velocita -= 1;
                        score += 15;
                        break;
      case LASER      : DrawBar(xbar, ybar, OMBRA, bartype);
                        bartype = NORMAL;
                        DrawBar(xbar, ybar, SOLID, bartype);
                        lasercounter = LASER_TIME;
                        laserflag = ON;
                        score += 25;
                        break;
      case REVERSE    : reversecounter = REVERSE_TIME;
                        reverseflag = ON;
                        score += 10;
                        break;
    }
    DrawScore();
  }
}


void MultiBall(void)
{ 
  xball[1] = xball[0];
  yball[1] = yball[0];
  xball[2] = xball[0];
  yball[2] = yball[0];

  switch(direction[0]) {
    case  0 : direction[1] = 11;
              direction[2] =  1;
              break;
    case  1 : direction[1] =  0;
              direction[2] =  2;
              break;
    case  2 : direction[1] =  1;
              direction[2] =  3;
              break;
    case  3 : direction[1] =  2;
              direction[2] =  4;
              break;
    case  4 : direction[1] =  3;
              direction[2] =  5;
              break;
    case  5 : direction[1] =  4;
              direction[2] =  6;
              break;
    case  6 : direction[1] =  5;
              direction[2] =  7;
              break;
    case  7 : direction[1] =  6;
              direction[2] =  8;
              break;
    case  8 : direction[1] =  7;
              direction[2] =  9;
              break;
    case  9 : direction[1] =  8;
              direction[2] = 10;
              break;
    case 10 : direction[1] =  9;
              direction[2] = 11;
              break;
    case 11 : direction[1] = 10;
              direction[2] =  0;
              break;
  }
}

void ActiveBall(void)
{
  int i;
  for(i=0;i<MAX_BALLS;i++) {
    if(xball[i]!=KILLED && yball[i]!=KILLED) {
      xball[0] = xball[i];
      yball[0] = yball[i];
      direction[0] = direction[i];
    }
  }
}

void BallLock(void)
/* Gestisce le conseguenze del bonus BallLock (Blocco della Palla). */
{
  int i;
  DrawBorder();
  KillLaser();
  KillTouchedBonus();
  for(i=0;i<MAX_BALLS;i++) 
    DrawObject(xball[i],yball[i],BALL_X,BALL_Y,Ball,OMBRA);
  DrawBar( xbar, ybar, OMBRA, bartype);
  DrawMap(); 
  InitLife();
}

void Extend(void)
/* Estende la barra-utente controllando che non sia troppo vicina    */
/* al bordo destro. In questo caso la sposta un po' piu' a sinistra. */
/* Se non fosse spostata accadrebbe che l'estensione della barra     */
/* sovrascriverebbe il bordo destro.                                 */
{
  KillLaser();
  DrawBar(xbar, ybar, OMBRA, bartype);
  if(xbar >= 232) xbar = 232-5; 
  bartype = EXTEND;
  DrawBar(xbar, ybar, SOLID, bartype);
}

void Reduce(void)
/* Riduce la barra-utente. Non ha bisogno di controlli di posizione */
/* come nel caso dell'estensione.                                   */
{
  KillLaser();
  DrawBar(xbar, ybar, OMBRA, bartype);
  bartype = REDUCE;
  DrawBar(xbar, ybar, SOLID, bartype);
}

void UpdateCounter(void)
/* Aggiorna i contatori di validita' dei bonus ed il contatore         */
/* di fine-stage, controllando il raggiungimento dei rispettivi limiti */
/* imposti e generandone le conseguenze.                               */
{
  if(ball_lock == TRUE) lock_counter -= 1;
  if(lock_counter == 0) ball_lock = FALSE;
  
  if(laserflag == ON) lasercounter -= 1;
  if(lasercounter == 0) {
    KillLaser();
  }
    
  if(reverseflag == ON) reversecounter -= 1;
  if(reversecounter == 0) reverseflag = OFF;

  speedcounter += 1;
  if(speedcounter == INT_LIMIT - 1) speedcounter = 0;
  if(speedcounter >= SPEED_CHANGE && velocita < VELOCITA) {
    speedcounter = 0;
    velocita += 1;
  } 
 
  if(wincounter[current_stage] == 0) {
    sleep(2);
    if(current_stage < STAGE_ID) current_stage += 1;
    if(current_stage == STAGE_ID) {
      system("clear");
      printf("\n\n COMPLIMENTI! Hai portato a termine la tua missione\n");
      printf(" totalizzando %d punti\n", score);
      exit(0);
    }
    DrawBar(xbar, ybar, SOLID, bartype);
    InitStage();
  }
}

void InitGame(void)
{
  current_stage = 0;
  numlives = 3;
  score = 0;
  BackupMaps();
  BackupWinCounter();
  DrawObject(GAME_OVER_OFF);
  InitLife();
  InitStage();
}
  
void InitLife(void)
{
  xbar = 100;
  ybar = 230;
  xball[0] = 118;
  yball[0] = 224;
  xball[1] = KILLED;
  yball[1] = KILLED;
  xball[2] = KILLED;
  yball[2] = KILLED;
  direction[0] = 0;
  direction[1] = 0;
  direction[2] = 0;
  ballingame = 1;
  multiball = OFF;  
  ball_lock = TRUE;
  leftpress = FALSE;
  rightpress = FALSE;
  velocita = 0;
  bartype = NORMAL;
  laserflag = OFF;
  lasercounter = 0;
  laserfired = OFF;
  reverseflag = OFF;
  reversecounter = 0;  
  speedcounter = 0;
  tilt_counter = 0;
  lock_counter = LOCK_TIME;
  KillTouchedBonus();
  DrawBorder();
  DrawObject(TILT_OFF);
  DrawBar(xbar, ybar, SOLID, NORMAL);
  DrawObject(xball[0],yball[0],BALL_X, BALL_Y, Ball, SOLID);
}

void InitStage(void)
{
  int i;
  KillTouchedBonus();
  InitBonus();
  AssignBonus();
  for(i=0;i<MAX_BALLS;i++) 
    DrawObject(xball[i], yball[i], BALL_X, BALL_Y, Ball, OMBRA);
  DrawObject(xlaser, (int)ylaser, LASER_X, LASER_Y, laser, OMBRA);
  DrawBar(xbar, ybar, OMBRA, bartype); 
  DrawMap();
  DrawSfondo();
  InitLife();
}

void AssignBonus(void)
/* Assegna a ciascun mattone, che non sia indistruttibile (cond. GRAY1)  */
/* o inconsistente (cond. OMBRA), un bonus di tipo diverso a seconda     */
/* del risultato generato dalla funzione rand(), collegata alla funzione */
/* srand().	                                                         */
{
  int i, val, stime;
  long ltime;
  ltime = time(NULL);   
  stime = (unsigned)ltime/2;
  srand(stime);               /* Uso di srand() per variare continuamente */
                              /* i risultati delle chiamate a rand().     */
  for(i=0;i<MAP_OBJECT;i++) {
    if(MapObj[current_stage][i]!=OMBRA ||
       MapObj[current_stage][i]!=GRAY1) {
      val = 1+(int)(100.0*rand()/(RAND_MAX+1.0));
      if(val>=99 && val <=100) Bonus[i].type = LIVES;
      if(val>=97 && val <  99) Bonus[i].type = REVERSE;
      if(val>=94 && val <  97) Bonus[i].type = LASER;
      if(val>=91 && val <  94) Bonus[i].type = BALL_LOCK;
      if(val>=88 && val <  91) Bonus[i].type = MULTI_BALL;
      if(val>=85 && val <  88) Bonus[i].type = EXTEND;
      if(val>=82 && val <  85) Bonus[i].type = REDUCE;
      if(val>=79 && val <  82) Bonus[i].type = SPEED_DOWN;
      if(val>=0  && val <  79) Bonus[i].type = NB;
      Bonus[i].touched = FALSE;
      Bonus[i].permission = TRUE;
      if(Bonus[i].type!=NB) {
        Bonus[i].x = MapXY[i].begx + STD_MAPX;
        Bonus[i].y = (float)(MapXY[i].begy + STD_MAPY);
      }
    }
  }
}

/* ----------------------------------------------------------------------- */
/* Le seguenti funzioni di BackUp e Restore sono utilizzate per            */
/* sdoppiare in memoria i dati relativi alle mappe degli stage             */
/* ed ai win-counter (contatori-vittoria) in modo che, i valori modificati */
/* durante una partita, possano essere ripristinati per eseguire una nuova */
/* partita.                                                                */
/* ----------------------------------------------------------------------- */
void BackupWinCounter(void)
{
  int i; 
  for(i=0;i<STAGE_ID;i++) 
    wincountbackup[i] = wincounter[i];
}

void RestoreWinCounter(void)
{
  int i;
  for(i=0;i<STAGE_ID;i++)
    wincounter[i] = wincountbackup[i];
}

void BackupMaps(void)
{
  int i,j;
  for(j=0;j<STAGE_ID;j++) {
    for(i=0;i<MAP_OBJECT;i++) {
      MapBackup[j][i] = MapObj[j][i];
    }
  }
}

void RestoreMaps(void)
{
  int i,j;
  for(j=0;j<STAGE_ID;j++) {
    for(i=0;i<MAP_OBJECT;i++) {
      MapObj[j][i] = MapBackup[j][i];
    }
  }
}


void KillTouchedBonus(void)
/* Elimina eventuali bonus in caduta che vanno persi in alcuni casi, */
/* ad esempio, con la perdita di un credit, con l'inizio di un nuovo */
/* stage, etc.                                                       */
{
  int i;
  for(i=0;i<MAP_OBJECT;i++) {
    if(Bonus[i].permission == TRUE && Bonus[i].touched == TRUE) {
      Bonus[i].permission = FALSE;
      DrawBonus(Bonus[i].x, (int)Bonus[i].y, Bonus[i].type, OMBRA);
    }
  } 
} 

void KillLaser(void)
/* Elimina eventuali laser "vaganti" per le stesse ragioni descritte */
/* nella funzione KillTouchedBonus().                                */ 
{
  DrawObject(xlaser,(int)ylaser,LASER_X, LASER_Y, laser, OMBRA);
  laserflag = OFF;
  laserfired = OFF;
  xlaser = KILLEDLASER;
  ylaser = (float)KILLEDLASER;
}

void KillMultiBall(void)
/* "Uccide" la pallina 1 e la pallina 2 in modo da tenere in gioco    */
/* sempre e solo la pallina 0, necessaria per eventuali altre catture */
/* del bonus Multi Ball.                                              */
{  
  int activeball;
  multiball = OFF;
  if(xball[0] == KILLED && xball[1] == KILLED) activeball = 2;
  else if(xball[0] == KILLED && xball[2] == KILLED) activeball = 1;
  else if(xball[1] == KILLED && xball[2] == KILLED) activeball = 0;
  switch(activeball) {
  case 0 : break;
  case 1 : xball[0] = xball[1];
           xball[1] = KILLED;
           yball[0] = yball[1];
           yball[1] = KILLED;
           direction[0] = direction[1];
           direction[1] = 0;
           break;
  case 2 : xball[0] = xball[2];
           xball[2] = KILLED;
           yball[0] = yball[2];
           yball[2] = KILLED;
           direction[0] = direction[2];
           direction[2] = 0;
           break;
  }
}

void ExitProgram(void)
{
  system("clear");
  printf(" PiNGUINoid: Programma terminato\n");
  printf(" Grazie per aver giocato!\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
  exit(0);
}




