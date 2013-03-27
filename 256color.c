/*****************************************************************************/
/* File Info :                                                               */
/* -----------                                                               */
/* Nome File            : 256color.c                                         */
/* Dimensioni           : 1751 bytes                                         */
/* Data Ultima Modifica : Domenica 28 Maggio 2000 - 17:14                    */
/* Autore               : Esposito Gianluca (Matr.Num.056/100858)            */
/* Breve Descrizione    : Contiene le definizioni dei valori RGB per la      */
/*                        palette e la funzione per caricarle in memoria.    */
/*****************************************************************************/

#define NUM_COLOR 256
#define PALETTE_FILE "256color.pal"

struct color {
  int r;         /* Percentuale di ROSSO (red)   */
  int g;         /* Percentuale di VERDE (green) */
  int b;         /* Precentuale di BLU   (blue)  */
} Color;

void LoadPalette(void);

void LoadPalette(void)
/* Apre il file 256color.pal e carica i valori RGB usati per la palette */
/* assegnandoli a valori compresi tra 0 e 255 tramite la funzione       */
/* gl_setpalettecolor(int num_color, int r, int g, int b);              */
{
  int i;
  FILE *file_pointer;
  file_pointer = fopen(PALETTE_FILE, "rb");
  if(file_pointer == NULL) { 
    printf(" Si e' verificato un errore durante l'apertura del file :\n");
    printf(" 256color.pal\n");
    exit(0);
  }
  for(i=0;i<NUM_COLOR;i++) {
    fseek(file_pointer, i*sizeof(struct color), SEEK_SET);
    fread(&Color, sizeof(struct color), 1, file_pointer);
    gl_setpalettecolor(i, Color.r, Color.g, Color.b);
  }
}

