#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <gtk/gtk.h>
//Structures
struct pool {
  int x,y;
  char name;
  GtkWidget *grid;
};
struct pair {
  int x,y;
};
//SHARED FUNCS
void initGTK();
void checkWhichFigureIsIt(char chessboard[9][9],int x,int y,struct pair possibleMovesCordinates[107]);
void checkAndSendData(int x,int y,struct pool ChoosenFigure,struct pair additionalChange[2],char name);
void transformPawn(int x,int y,bool color);
void checkPromotion(struct pool ChoosenFigure,int x,int y);
