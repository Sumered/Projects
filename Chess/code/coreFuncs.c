#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <gtk/gtk.h>
#include "coreFuncs.h"
//Global Variables
static bool ChoosedFigure = false;
static bool WhiteTurn = true;
static struct pool ChoosenFigure;
static FILE *gameRecord;
static struct pair possibleMovesCordinates[107];
static struct pool chessboard[9][9];
static GtkWidget *mainWindow;
static GtkWidget *selectImageFromChar(char c,int pos,int rzad){
  GtkWidget *image;
  switch (c){
    case ' ':
    if((pos%2 == 1 && rzad%2 == 1) || (pos%2==0 && rzad%2 == 0)){ return image = gtk_image_new_from_file("WhiteBg.jpg"); }
    else { return image = gtk_image_new_from_file("BlackBg.jpg"); }
    case 'p':
      if((pos%2 == 1 && rzad%2 == 1) || (pos%2==0 && rzad%2 == 0)){ return image = gtk_image_new_from_file("BlackPawnWhiteBg.jpg"); }
      else { return image = gtk_image_new_from_file("BlackPawnBlackBg.jpg"); }
    case 'w':
      if((pos%2 == 1 && rzad%2 == 1) || (pos%2==0 && rzad%2 == 0)){ return image = gtk_image_new_from_file("BlackRookWhiteBg.jpg"); }
      else { return image = gtk_image_new_from_file("BlackRookBlackBg.jpg"); }
    case 's':
      if((pos%2 == 1 && rzad%2 == 1) || (pos%2==0 && rzad%2 == 0)){ return image = gtk_image_new_from_file("BlackKnightWhiteBg.jpg"); }
      else { return image = gtk_image_new_from_file("BlackKnightBlackBg.jpg"); }
    case 'g':
      if((pos%2 == 1 && rzad%2 == 1) || (pos%2==0 && rzad%2 == 0)){ return image = gtk_image_new_from_file("BlackBishopWhiteBg.jpg"); }
      else { return image = gtk_image_new_from_file("BlackBishopBlackBg.jpg"); }
    case 'h':
      if((pos%2 == 1 && rzad%2 == 1) || (pos%2==0 && rzad%2 == 0)){ return image = gtk_image_new_from_file("BlackQueenWhiteBg.jpg"); }
      else { return image = gtk_image_new_from_file("BlackQueenBlackBg.jpg"); }
    case 'k':
      if((pos%2 == 1 && rzad%2 == 1) || (pos%2==0 && rzad%2 == 0)){ return image = gtk_image_new_from_file("BlackKingWhiteBg.jpg"); }
      else { return image = gtk_image_new_from_file("BlackKingBlackBg.jpg"); }
    case 'P':
      if((pos%2 == 1 && rzad%2 == 1) || (pos%2==0 && rzad%2 == 0)){ return image = gtk_image_new_from_file("WhitePawnWhiteBg.jpg"); }
      else { return image = gtk_image_new_from_file("WhitePawnBlackBg.jpg"); }
    case 'W':
      if((pos%2 == 1 && rzad%2 == 1) || (pos%2==0 && rzad%2 == 0)){ return image = gtk_image_new_from_file("WhiteRookWhiteBg.jpg"); }
      else { return image = gtk_image_new_from_file("WhiteRookBlackBg.jpg"); }
    case 'S':
      if((pos%2 == 1 && rzad%2 == 1) || (pos%2==0 && rzad%2 == 0)){ return image = gtk_image_new_from_file("WhiteKnightWhiteBg.jpg"); }
      else { return image = gtk_image_new_from_file("WhiteKnightBlackBg.jpg"); }
    case 'G':
      if((pos%2 == 1 && rzad%2 == 1) || (pos%2==0 && rzad%2 == 0)){ return image = gtk_image_new_from_file("WhiteBishopWhiteBg.jpg"); }
      else { return image = gtk_image_new_from_file("WhiteBishopBlackBg.jpg"); }
    case 'H':
      if((pos%2 == 1 && rzad%2 == 1) || (pos%2==0 && rzad%2 == 0)){ return image = gtk_image_new_from_file("WhiteQueenWhiteBg.jpg"); }
      else { return image = gtk_image_new_from_file("WhiteQueenBlackBg.jpg"); }
    case 'K':
      if((pos%2 == 1 && rzad%2 == 1) || (pos%2==0 && rzad%2 == 0)){ return image = gtk_image_new_from_file("WhiteKingWhiteBg.jpg"); }
      else { return image = gtk_image_new_from_file("WhiteKingBlackBg.jpg"); }
    default:
      return image = gtk_image_new_from_file("WhitePawnWhiteBg.jpg");
  }
}
static GtkWidget *selectRightHighlight(char c){
  GtkWidget *image;
  switch (c){
    case ' ': return image = gtk_image_new_from_file("Possible.png");
    case 'p': return image = gtk_image_new_from_file("BlackPawnPossible.png");
    case 'w': return image = gtk_image_new_from_file("BlackRookPossible.png");
    case 's': return image = gtk_image_new_from_file("BlackKnightPossible.png");
    case 'g': return image = gtk_image_new_from_file("BlackBishopPossible.png");
    case 'h': return image = gtk_image_new_from_file("BlackQueenPossible.png");
    case 'k': return image = gtk_image_new_from_file("BlackKingPossible.png");
    case 'P': return image = gtk_image_new_from_file("WhitePawnPossible.png");
    case 'W': return image = gtk_image_new_from_file("WhiteRookPossible.png");
    case 'S': return image = gtk_image_new_from_file("WhiteKnightPossible.png");
    case 'G': return image = gtk_image_new_from_file("WhiteBishopPossible.png");
    case 'H': return image = gtk_image_new_from_file("WhiteQueenPossible.png");
    case 'K': return image = gtk_image_new_from_file("WhiteKingPossible.png");
  }
}
void transformPawn(int x,int y,bool color){
  if(color == 1){
    chessboard[x][y].name = 'H';
    gtk_button_set_image(GTK_BUTTON(chessboard[x][y].grid),selectImageFromChar('H',(x-1)+(y-1)*8,y));
  } else {
    chessboard[x][y].name = 'h';
    gtk_button_set_image(GTK_BUTTON(chessboard[x][y].grid),selectImageFromChar('h',(x-1)+(y-1)*8,y));
  }
}
static void changeButtonLabel(int x,int y){
  chessboard[x][y].name = chessboard[ChoosenFigure.x][ChoosenFigure.y].name;
  GtkWidget *image = selectImageFromChar(chessboard[x][y].name,(x-1)+(y-1)*8,y);
  gtk_button_set_image(GTK_BUTTON(chessboard[x][y].grid),image);
  chessboard[ChoosenFigure.x][ChoosenFigure.y].name=' ';
  image = selectImageFromChar(chessboard[ChoosenFigure.x][ChoosenFigure.y].name,ChoosenFigure.x-1+(ChoosenFigure.y-1)*8,ChoosenFigure.y);
  gtk_button_set_image(GTK_BUTTON(chessboard[ChoosenFigure.x][ChoosenFigure.y].grid),image);
}
static void extraChangeButtonLabel(struct pair additionalChange[2]){
  if(additionalChange[0].x == -1 && additionalChange[0].y == -1){ return; }
  if(additionalChange[1].x == 0 && additionalChange[1].y == 0){
    chessboard[additionalChange[0].x][additionalChange[0].y].name = ' ';
    GtkWidget *image = selectImageFromChar(' ',additionalChange[0].x-1+(additionalChange[0].y-1)*8,additionalChange[0].y);
    gtk_button_set_image(GTK_BUTTON(chessboard[additionalChange[0].x][additionalChange[0].y].grid),image);
    return;
  }
  gchar c[20],c2[20];
  GtkWidget *image = selectImageFromChar(' ',additionalChange[0].x-1+(additionalChange[0].y-1)*8,additionalChange[0].y);
  GtkWidget *image2 = selectImageFromChar(chessboard[additionalChange[0].x][additionalChange[0].y].name,additionalChange[1].x-1+(additionalChange[1].y-1)*8,additionalChange[1].y);
  sprintf(c," ");
  sprintf(c2,"%c",chessboard[additionalChange[0].x][additionalChange[0].y].name);
  chessboard[additionalChange[1].x][additionalChange[1].y].name = chessboard[additionalChange[0].x][additionalChange[0].y].name;
  chessboard[additionalChange[0].x][additionalChange[0].y].name = ' ';
  gtk_button_set_image(GTK_BUTTON(chessboard[additionalChange[0].x][additionalChange[0].y].grid),image);
  gtk_button_set_image(GTK_BUTTON(chessboard[additionalChange[1].x][additionalChange[1].y].grid),image2);
}
static void highlightPossibeMoveCordinates(int x,int y){
  gtk_button_set_image(GTK_BUTTON(chessboard[x][y].grid),selectRightHighlight(chessboard[x][y].name));
  int i=0;
  while(possibleMovesCordinates[i].x != -1){
    int a = possibleMovesCordinates[i].x;
    int b = possibleMovesCordinates[i].y;
    gtk_button_set_image(GTK_BUTTON(chessboard[a][b].grid),selectRightHighlight(chessboard[a][b].name));
    i++;
  }
}
static void returnButtonsToNormalState(int x,int y){
  gtk_button_set_image(GTK_BUTTON(chessboard[x][y].grid),selectImageFromChar(chessboard[x][y].name,(x-1)+(y-1)*8,y));
  int i=0;
  while(possibleMovesCordinates[i].x != -1){
    int a = possibleMovesCordinates[i].x;
    int b = possibleMovesCordinates[i].y;
    gtk_button_set_image(GTK_BUTTON(chessboard[a][b].grid),selectImageFromChar(chessboard[a][b].name,(a-1)+(b-1)*8,b));
    i++;
  }
}
static void displayPossibleMoves(int x,int y){
  char normalChessboard[9][9];
  for(int i=1;i<=8;i++){
    for(int j=1;j<=8;j++){
      normalChessboard[i][j]=chessboard[i][j].name;
    }
  }
  checkWhichFigureIsIt(normalChessboard,x,y,possibleMovesCordinates);
  highlightPossibeMoveCordinates(x,y);
}
static bool checkIfRightChoose(int x,int y){
  int i=0;
  while(possibleMovesCordinates[i].x!=-1){
    if(possibleMovesCordinates[i].x==x && possibleMovesCordinates[i].y==y){
      return true;
    }
    i++;
  }
  return false;
}
static void cancelMove(GtkWidget *button,gpointer *nothing){
  ChoosedFigure = false;
  returnButtonsToNormalState(ChoosenFigure.x,ChoosenFigure.y);
  for(int i=0;i<100;i++){
    possibleMovesCordinates[i].x = -1;
    possibleMovesCordinates[i].y = -1;
  }
}
static void newGame(GtkWidget *button,gpointer *nothing){
  gtk_window_close(GTK_WINDOW(mainWindow));
  ChoosedFigure = false;
  WhiteTurn = true;
  initGTK();
}
static void endGame(GtkWidget *button,gpointer *nothing){
  gtk_window_close(GTK_WINDOW(mainWindow));
  fclose(gameRecord);
  exit(0);
}
static void movecheck(GtkWidget *button,gpointer *place){
  struct pool *placer = (struct pool*) place;
  if(ChoosedFigure == false){
    if(chessboard[placer->x][placer->y].name==' '){return;}
    char c = chessboard[placer->x][placer->y].name;
    int a = c;
    if(WhiteTurn == true && a>=97){return;}
    if(WhiteTurn == false && a<97){return;}
    ChoosedFigure = true;
    ChoosenFigure = (*placer);
    displayPossibleMoves(placer->x,placer->y);
  } else {
    if(checkIfRightChoose(placer->x,placer->y)){
      char letters[8] = {'A','B','C','D','E','F','G','H'};
      fprintf(gameRecord, "%c%d-%c%d\n",letters[ChoosenFigure.x],ChoosenFigure.y,letters[placer->x],placer->y);
      returnButtonsToNormalState(ChoosenFigure.x,ChoosenFigure.y);
      for(int i=0;i<100;i++){
        possibleMovesCordinates[i].x = -1;
        possibleMovesCordinates[i].y = -1;
      }
      struct pair additionalChange[2] = {-1,-1,-1,-1};
      checkAndSendData(placer->x,placer->y,ChoosenFigure,additionalChange,chessboard[placer->x][placer->y].name);
      changeButtonLabel(placer->x,placer->y);
      checkPromotion(ChoosenFigure,placer->x,placer->y);
      extraChangeButtonLabel(additionalChange);
      if(WhiteTurn==true){WhiteTurn=false;}
      else{WhiteTurn=true;}
      ChoosedFigure = false;
    }
  }
}
void initGTK(){
  gtk_init(NULL,NULL);
  gameRecord = fopen("gameRecord.txt","w");
  char startingNames[64] = {
  'w','s','g','h','k','g','s','w',
  'p','p','p','p','p','p','p','p',
  ' ',' ',' ',' ',' ',' ',' ',' ',
  ' ',' ',' ',' ',' ',' ',' ',' ',
  ' ',' ',' ',' ',' ',' ',' ',' ',
  ' ',' ',' ',' ',' ',' ',' ',' ',
  'P','P','P','P','P','P','P','P',
  'W','S','G','H','K','G','S','W'};
  for(int i=0;i<100;i++){
    possibleMovesCordinates[i].x = -1;
    possibleMovesCordinates[i].y = -1;
  }
	GtkWidget *window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
  mainWindow = window;
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(window),"Chessboard");
	gtk_container_set_border_width(GTK_CONTAINER(window),0);
	GtkWidget *grid=gtk_grid_new();
	gtk_grid_set_row_spacing(GTK_GRID(grid),0);
	gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
	gtk_grid_set_column_spacing(GTK_GRID(grid), 0);
	gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	gtk_container_add(GTK_CONTAINER(window),grid);
  for(int i=1;i<=8;i++){
    for(int j=1;j<=8;j++){
      GtkWidget *button = gtk_button_new();
      GtkWidget *image = selectImageFromChar(startingNames[(i-1)+(j-1)*8],(i-1)+(j-1)*8,j);
      gtk_button_set_image(GTK_BUTTON(button),image);
      chessboard[i][j].x = i; chessboard[i][j].y = j; chessboard[i][j].name = startingNames[(i-1)+(j-1)*8]; chessboard[i][j].grid = button;
      g_signal_connect(G_OBJECT(button),"pressed",G_CALLBACK(movecheck),&chessboard[i][j]);
      gtk_grid_attach(GTK_GRID(grid),button,i,j,1,1);
    }
  }
  char letters[8] = {'A','B','C','D','E','F','G','H'};
  for(int i=1;i<=8;i++){
    gchar c[20];
    sprintf(c,"%d",i);
    GtkWidget *label = gtk_label_new(c);
    gtk_widget_modify_font(label,pango_font_description_from_string("Helvetica 20"));
    gtk_grid_attach(GTK_GRID(grid),label,0,8-i+1,1,1);
    sprintf(c,"%c",letters[i-1]);
    GtkWidget *label2 = gtk_label_new(c);
    gtk_widget_modify_font(label2,pango_font_description_from_string("Helvetica 20"));
    gtk_grid_attach(GTK_GRID(grid),label2,i,9,1,1);
  }
  gchar c[20];
  sprintf(c,"Cancel Move");
  GtkWidget *cancelButton = gtk_button_new_with_label(c);
  gtk_widget_modify_font(cancelButton,pango_font_description_from_string("Helvetica 20"));
  g_signal_connect(G_OBJECT(cancelButton),"pressed",G_CALLBACK(cancelMove),NULL);
  sprintf(c,"New Game");
  GtkWidget *newGameButton = gtk_button_new_with_label(c);
  gtk_widget_modify_font(newGameButton,pango_font_description_from_string("Helvetica 20"));
  g_signal_connect(G_OBJECT(newGameButton),"pressed",G_CALLBACK(newGame),NULL);
  gtk_grid_attach(GTK_GRID(grid),newGameButton,5,10,4,1);
  gtk_grid_attach(GTK_GRID(grid),cancelButton,1,10,4,1);
  sprintf(c,"X");
  GtkWidget *endGameButton = gtk_button_new_with_label(c);
  gtk_widget_modify_font(endGameButton,pango_font_description_from_string("Helvetica 20"));
  g_signal_connect(G_OBJECT(endGameButton),"pressed",G_CALLBACK(endGame),NULL);
  gtk_grid_attach(GTK_GRID(grid),endGameButton,0,9,1,2);
  gtk_widget_show_all(window);
  gtk_main();
}
