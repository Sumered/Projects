#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "coreFuncs.h"
static struct pair KnightMoves[8] = {1,2,-1,2,1,-2,-1,-2,2,1,2,-1,-2,1,-2,-1};
static struct pair KingMoves[8] = {1,0,1,1,0,1,-1,1,-1,0,-1,-1,0,-1,1,-1};
static struct pair EnPassant = {0,0},KingHasMoved = {0,0},WhiteRookHasMoved = {0,0},BlackRookHasMoved = {0,0};
int counter = 0;
static bool ifOutOfChessboard(int x,int y){
  if(x>0 && x<9 && y>0 && y<9){ return true; }
  return false;
}
static bool isWhiteFigure(char c){
  char biale[6] = {'P','W','S','G','H','K'};
  for(int i=0;i<6;i++){
    if(biale[i] == c){ return true; }
  }
  return false;
}
static bool isBlackFigure(char c){
  char czarne[6] = {'p','w','s','g','h','k'};
  for(int i=0;i<6;i++){
    if(czarne[i] == c){ return true; }
  }
  return false;
}
static int BlackFigureCheckingHelper(char fakeChessboard[9][9],int x,int y){
  if(ifOutOfChessboard(x,y)){
    if(isBlackFigure(fakeChessboard[x][y])){ return 1; }
    if(isWhiteFigure(fakeChessboard[x][y])){
      if(fakeChessboard[x][y]=='K'){ return 2; }
      return 1;
    }
  }
  return 0;
}
static int WhiteFigureCheckingHelper(char fakeChessboard[9][9],int x,int y){
  if(ifOutOfChessboard(x,y)){
    if(isWhiteFigure(fakeChessboard[x][y])){ return 1; }
    if(isBlackFigure(fakeChessboard[x][y])){
      if(fakeChessboard[x][y]=='k'){ return 2; }
      return 1;
    }
  }
  return 0;
}
static bool BlackPawnChecking(char fakeChessboard[9][9],int x,int y){
  if(ifOutOfChessboard(x+1,y+1)){
    if(fakeChessboard[x+1][y+1] == 'K'){ return true; }
  }
  if(ifOutOfChessboard(x-1,y+1)){
    if(fakeChessboard[x-1][y+1] == 'K'){ return true; }
  }
  return false;
}
static bool BlackRookChecking(char fakeChessboard[9][9],int x,int y){
  for(int i=1;i<=8;i++){
    if(BlackFigureCheckingHelper(fakeChessboard,x+i,y) == 1){ break; }
    else if(BlackFigureCheckingHelper(fakeChessboard,x+i,y) == 2){ return true; }
  }
  for(int i=1;i<=8;i++){
    if(BlackFigureCheckingHelper(fakeChessboard,x,y+i) == 1){ break; }
    else if(BlackFigureCheckingHelper(fakeChessboard,x,y+i) == 2){ return true; }
  }
  for(int i=1;i<=8;i++){
    if(BlackFigureCheckingHelper(fakeChessboard,x-i,y) == 1){ break; }
    else if(BlackFigureCheckingHelper(fakeChessboard,x-i,y) == 2){ return true; }
  }
  for(int i=1;i<=8;i++){
    if(BlackFigureCheckingHelper(fakeChessboard,x,y-i) == 1){ break; }
    else if(BlackFigureCheckingHelper(fakeChessboard,x,y-i) == 2){ return true; }
  }
  return false;
}
static bool BlackKnightChecking(char fakeChessboard[9][9],int x,int y){
  for(int i=0;i<8;i++){
    if(BlackFigureCheckingHelper(fakeChessboard,x+KnightMoves[i].x,y+KnightMoves[i].y) == 2){ return true; }
  }
  return false;
}
static bool BlackBishopChecking(char fakeChessboard[9][9],int x,int y){
  for(int i=1;i<=8;i++){
    if(BlackFigureCheckingHelper(fakeChessboard,x+i,y+i) == 1){ break; }
    else if(BlackFigureCheckingHelper(fakeChessboard,x+i,y+i) == 2){ return true; }
  }
  for(int i=1;i<=8;i++){
    if(BlackFigureCheckingHelper(fakeChessboard,x+i,y-i) == 1){ break; }
    else if(BlackFigureCheckingHelper(fakeChessboard,x+i,y-i) == 2){ return true; }
  }
  for(int i=1;i<=8;i++){
    if(BlackFigureCheckingHelper(fakeChessboard,x-i,y-i) == 1){ break; }
    else if(BlackFigureCheckingHelper(fakeChessboard,x-i,y-i) == 2){ return true; }
  }
  for(int i=1;i<=8;i++){
    if(BlackFigureCheckingHelper(fakeChessboard,x-i,y+i) == 1){ break; }
    else if(BlackFigureCheckingHelper(fakeChessboard,x-i,y+i) == 2){ return true; }
  }
  return false;
}
static bool BlackQueenChecking(char fakeChessboard[9][9],int x,int y){
  return BlackBishopChecking(fakeChessboard,x,y) || BlackRookChecking(fakeChessboard,x,y);
}
static bool BlackKingChecking(char fakeChessboard[9][9],int x,int y){
  for(int i=0;i<8;i++){
    if(BlackFigureCheckingHelper(fakeChessboard,x+KnightMoves[i].x,y+KnightMoves[i].y) == 2){ return true; }
  }
  return false;
}
static bool WhitePawnChecking(char fakeChessboard[9][9],int x,int y){
  if(ifOutOfChessboard(x+1,y-1)){
    if(fakeChessboard[x+1][y-1] == 'k'){ return true; }
  }
  if(ifOutOfChessboard(x-1,y-1)){
    if(fakeChessboard[x-1][y-1] == 'k'){ return true; }
  }
  return false;
}
static bool WhiteRookChecking(char fakeChessboard[9][9],int x,int y){
  for(int i=1;i<=8;i++){
    if(WhiteFigureCheckingHelper(fakeChessboard,x+i,y) == 1){ break; }
    else if(WhiteFigureCheckingHelper(fakeChessboard,x+i,y) == 2){ return true; }
  }
  for(int i=1;i<=8;i++){
    if(WhiteFigureCheckingHelper(fakeChessboard,x,y+i) == 1){ break; }
    else if(WhiteFigureCheckingHelper(fakeChessboard,x,y+i) == 2){ return true; }
  }
  for(int i=1;i<=8;i++){
    if(WhiteFigureCheckingHelper(fakeChessboard,x-i,y) == 1){ break; }
    else if(WhiteFigureCheckingHelper(fakeChessboard,x-i,y) == 2){ return true; }
  }
  for(int i=1;i<=8;i++){
    if(WhiteFigureCheckingHelper(fakeChessboard,x,y-i) == 1){ break; }
    else if(WhiteFigureCheckingHelper(fakeChessboard,x,y-i) == 2){ return true; }
  }
  return false;
}
static bool WhiteKnightChecking(char fakeChessboard[9][9],int x,int y){
  for(int i=0;i<8;i++){
    if(WhiteFigureCheckingHelper(fakeChessboard,x+KnightMoves[i].x,y+KnightMoves[i].y) == 2){ return true; }
  }
  return false;
}
static bool WhiteBishopChecking(char fakeChessboard[9][9],int x,int y){
  for(int i=1;i<=8;i++){
    if(WhiteFigureCheckingHelper(fakeChessboard,x+i,y+i) == 1){ break; }
    else if(WhiteFigureCheckingHelper(fakeChessboard,x+i,y+i) == 2){ return true; }
  }
  for(int i=1;i<=8;i++){
    if(WhiteFigureCheckingHelper(fakeChessboard,x+i,y-i) == 1){ break; }
    else if(WhiteFigureCheckingHelper(fakeChessboard,x+i,y-i) == 2){ return true; }
  }
  for(int i=1;i<=8;i++){
    if(WhiteFigureCheckingHelper(fakeChessboard,x-i,y-i) == 1){ break; }
    else if(WhiteFigureCheckingHelper(fakeChessboard,x-i,y-i) == 2){ return true; }
  }
  for(int i=1;i<=8;i++){
    if(WhiteFigureCheckingHelper(fakeChessboard,x-i,y+i) == 1){ break; }
    else if(WhiteFigureCheckingHelper(fakeChessboard,x-i,y+i) == 2){ return true; }
  }
  return false;
}
static bool WhiteQueenChecking(char fakeChessboard[9][9],int x,int y){
  return WhiteBishopChecking(fakeChessboard,x,y) || WhiteRookChecking(fakeChessboard,x,y);
}
static bool WhiteKingChecking(char fakeChessboard[9][9],int x,int y){
  for(int i=0;i<8;i++){
    if(WhiteFigureCheckingHelper(fakeChessboard,x+KnightMoves[i].x,y+KnightMoves[i].y) == 2){ return true; }
  }
  return false;
}
static bool ifBlackFigure(char fakeChessboard[9][9],int x,int y){
  switch (fakeChessboard[x][y]){
    case 'p':
      return BlackPawnChecking(fakeChessboard,x,y);
    case 'w':
      return BlackRookChecking(fakeChessboard,x,y);
    case 's':
      return BlackKnightChecking(fakeChessboard,x,y);
    case 'g':
      return BlackBishopChecking(fakeChessboard,x,y);
    case 'h':
      return BlackQueenChecking(fakeChessboard,x,y);
    case 'k':
      return BlackKingChecking(fakeChessboard,x,y);
    default :
      return false;
  }
}
static bool ifWhiteFigure(char fakeChessboard[9][9],int x,int y){
  switch (fakeChessboard[x][y]){
    case 'P':
      return WhitePawnChecking(fakeChessboard,x,y);
    case 'W':
      return WhiteRookChecking(fakeChessboard,x,y);
    case 'S':
      return WhiteKnightChecking(fakeChessboard,x,y);
    case 'G':
      return WhiteBishopChecking(fakeChessboard,x,y);
    case 'H':
      return WhiteQueenChecking(fakeChessboard,x,y);
    case 'K':
      return WhiteKingChecking(fakeChessboard,x,y);
    default :
      return false;
  }
}
static bool ifIsInCheck(bool whiteTurn,char copiedChessboard[9][9]){
  if(whiteTurn == true){
    for(int i=1;i<=8;i++){
      for(int j=1;j<=8;j++){
        if(ifBlackFigure(copiedChessboard,i,j)){ return true; }
      }
    }
  } else {
    for(int i=1;i<=8;i++){
      for(int j=1;j<=8;j++){
        if(ifWhiteFigure(copiedChessboard,i,j)){ return true; }
      }
    }
  }
  return false;
}
static void createFakeChessboard(int x,int y,int x2,int y2,char fakeChessboard[9][9],char chessboard[9][9]){
  for(int i=1;i<=8;i++){
    for(int j=1;j<=8;j++){
      fakeChessboard[i][j]=chessboard[i][j];
    }
  }
  fakeChessboard[x2][y2] = chessboard[x][y]; fakeChessboard[x][y] = ' ';
}
static bool BlackFigureHelper(char chessboard[9][9],int xo,int yo,int x,int y,struct pair possibleMovesCordinates[107]){
  if(ifOutOfChessboard(x,y)){
    if(isBlackFigure(chessboard[x][y])){
      return true;
    } else if(isWhiteFigure(chessboard[x][y])){
      char fakeChessboard[9][9];
      createFakeChessboard(xo,yo,x,y,fakeChessboard,chessboard);
      if(!ifIsInCheck(0,fakeChessboard)){
        possibleMovesCordinates[counter].x = x;
        possibleMovesCordinates[counter].y = y;
        counter++;
      }
      return true;
    } else {
      char fakeChessboard[9][9];
      createFakeChessboard(xo,yo,x,y,fakeChessboard,chessboard);
      if(!ifIsInCheck(0,fakeChessboard)){
        possibleMovesCordinates[counter].x = x;
        possibleMovesCordinates[counter].y = y;
        counter++;
      }
      return false;
    }
  }
  return true;
}
static bool WhiteFigureHelper(char chessboard[9][9],int xo,int yo,int x,int y,struct pair possibleMovesCordinates[107]){
  if(ifOutOfChessboard(x,y)){
    if(isWhiteFigure(chessboard[x][y])){
      return true;
    } else if(isBlackFigure(chessboard[x][y])){
      char fakeChessboard[9][9];
      createFakeChessboard(xo,yo,x,y,fakeChessboard,chessboard);
      if(!ifIsInCheck(1,fakeChessboard)){
        possibleMovesCordinates[counter].x = x;
        possibleMovesCordinates[counter].y = y;
        counter++;
      }
      return true;
    } else {
      char fakeChessboard[9][9];
      createFakeChessboard(xo,yo,x,y,fakeChessboard,chessboard);
      if(!ifIsInCheck(1,fakeChessboard)){
        possibleMovesCordinates[counter].x = x;
        possibleMovesCordinates[counter].y = y;
        counter++;
      }
      return false;
    }
  }
  return true;
}
static void WhiteKing(char chessboard[9][9],int x,int y,struct pair possibleMovesCordinates[107]){
  for(int i=0;i<8;i++){
    WhiteFigureHelper(chessboard,x,y,x+KingMoves[i].x,y+KingMoves[i].y,possibleMovesCordinates);
  }
  if(KingHasMoved.x == 0){
    if(chessboard[8][8] == 'W'){
      if(WhiteRookHasMoved.y == 0 && chessboard[x+1][y] == ' ' && chessboard[x+2][y] == ' '){
        char fakeChessboard[9][9],fakeChessboard2[9][9];
        createFakeChessboard(x,y,x+1,y,fakeChessboard,chessboard);
        createFakeChessboard(x,y,x+2,y,fakeChessboard,chessboard);
        if(!ifIsInCheck(1,fakeChessboard) && !ifIsInCheck(1,fakeChessboard2)){
          possibleMovesCordinates[counter].x = x+2;
          possibleMovesCordinates[counter].y = y;
          counter++;
        }
      }
    }
    if(chessboard[1][8] == 'W'){
      if(WhiteRookHasMoved.x == 0 && chessboard[x-1][y] == ' ' && chessboard[x-2][y] == ' '){
        char fakeChessboard[9][9],fakeChessboard2[9][9];
        createFakeChessboard(x,y,x-1,y,fakeChessboard,chessboard);
        createFakeChessboard(x,y,x-2,y,fakeChessboard,chessboard);
        if(!ifIsInCheck(1,fakeChessboard) && !ifIsInCheck(1,fakeChessboard2)){
          possibleMovesCordinates[counter].x = x-2;
          possibleMovesCordinates[counter].y = y;
          counter++;
        }
      }
    }
  }
}
static void WhitePawn(char chessboard[9][9],int x,int y,struct pair possibleMovesCordinates[107]){
  if(y==7){
    if(ifOutOfChessboard(x,y-2)){
      if(!isWhiteFigure(chessboard[x][y-2]) && !isBlackFigure(chessboard[x][y-2])){
        char fakeChessboard[9][9];
        createFakeChessboard(x,y,x,y-2,fakeChessboard,chessboard);
        if(!ifIsInCheck(1,fakeChessboard)){
          possibleMovesCordinates[counter].x = x;
          possibleMovesCordinates[counter].y = y-2;
          counter++;
        }
      }
    }
  }
  if(ifOutOfChessboard(x,y-1)){
    if(!isWhiteFigure(chessboard[x][y-1]) && !isBlackFigure(chessboard[x][y-1])){
      char fakeChessboard[9][9];
      createFakeChessboard(x,y,x,y-1,fakeChessboard,chessboard);
      if(!ifIsInCheck(1,fakeChessboard)){
        possibleMovesCordinates[counter].x = x;
        possibleMovesCordinates[counter].y = y-1;
        counter++;
      }
    }
  }
  if(ifOutOfChessboard(x-1,y-1)){
    if(isBlackFigure(chessboard[x-1][y-1])){
      char fakeChessboard[9][9];
      createFakeChessboard(x,y,x-1,y-1,fakeChessboard,chessboard);
      if(!ifIsInCheck(1,fakeChessboard)){
        possibleMovesCordinates[counter].x = x-1;
        possibleMovesCordinates[counter].y = y-1;
        counter++;
      }
    }
  }
  if(ifOutOfChessboard(x+1,y-1)){
    if(isBlackFigure(chessboard[x+1][y-1])){
      char fakeChessboard[9][9];
      createFakeChessboard(x,y,x+1,y-1,fakeChessboard,chessboard);
      if(!ifIsInCheck(1,fakeChessboard)){
        possibleMovesCordinates[counter].x = x+1;
        possibleMovesCordinates[counter].y = y-1;
        counter++;
      }
    }
  }
  //BICIE W PRZELOCIE
  //g_print("ENPASSANT: %d %d",EnPassant.x,EnPassant.y);
  if(EnPassant.y == y && EnPassant.x == x-1){
    char fakeChessboard[9][9];
    createFakeChessboard(x,y,x-1,y-1,fakeChessboard,chessboard);
    if(!ifIsInCheck(1,fakeChessboard)){
      possibleMovesCordinates[counter].x = x-1;
      possibleMovesCordinates[counter].y = y-1;
      counter++;
    }
  }
  if(EnPassant.y == y && EnPassant.x == x+1){
    char fakeChessboard[9][9];
    createFakeChessboard(x,y,x+1,y-1,fakeChessboard,chessboard);
    if(!ifIsInCheck(1,fakeChessboard)){
      possibleMovesCordinates[counter].x = x+1;
      possibleMovesCordinates[counter].y = y-1;
      counter++;
    }
  }
}
static void WhiteBishop(char chessboard[9][9],int x,int y,struct pair possibleMovesCordinates[107]){
  for(int i=1;i<=8;i++){
    if(WhiteFigureHelper(chessboard,x,y,x+i,y+i,possibleMovesCordinates)){
      break;
    }
  }
  for(int i=1;i<=8;i++){
    if(WhiteFigureHelper(chessboard,x,y,x-i,y+i,possibleMovesCordinates)){
      break;
    }
  }
  for(int i=1;i<=8;i++){
    if(WhiteFigureHelper(chessboard,x,y,x+i,y-i,possibleMovesCordinates)){
      break;
    }
  }
  for(int i=1;i<=8;i++){
    if(WhiteFigureHelper(chessboard,x,y,x-i,y-i,possibleMovesCordinates)){
      break;
    }
  }
}
static void WhiteKnight(char chessboard[9][9],int x,int y,struct pair possibleMovesCordinates[107]){
  for(int i=0;i<8;i++){
    WhiteFigureHelper(chessboard,x,y,x+KnightMoves[i].x,y+KnightMoves[i].y,possibleMovesCordinates);
  }
}
static void WhiteRook(char chessboard[9][9],int x,int y,struct pair possibleMovesCordinates[107]){
  for(int i=x+1;i<=8;i++){
    if(WhiteFigureHelper(chessboard,x,y,i,y,possibleMovesCordinates)){
      break;
    }
  }
  for(int i=x-1;i>=1;i--){
    if(WhiteFigureHelper(chessboard,x,y,i,y,possibleMovesCordinates)){
      break;
    }
  }
  for(int i=y+1;i<=8;i++){
    if(WhiteFigureHelper(chessboard,x,y,x,i,possibleMovesCordinates)){
      break;
    }
  }
  for(int i=y-1;i>=1;i--){
    if(WhiteFigureHelper(chessboard,x,y,x,i,possibleMovesCordinates)){
      break;
    }
  }
}
static void WhiteQueen(char chessboard[9][9],int x,int y,struct pair possibleMovesCordinates[107]){
  WhiteBishop(chessboard,x,y,possibleMovesCordinates);
  WhiteRook(chessboard,x,y,possibleMovesCordinates);
}
static void BlackKing(char chessboard[9][9],int x,int y,struct pair possibleMovesCordinates[107]){
  for(int i=0;i<8;i++){
    BlackFigureHelper(chessboard,x,y,x+KingMoves[i].x,y+KingMoves[i].y,possibleMovesCordinates);
  }
  if(KingHasMoved.y == 0){
    if(chessboard[8][1] == 'w'){
      if(BlackRookHasMoved.y == 0 && chessboard[x+1][y] == ' ' && chessboard[x+2][y] == ' '){
        char fakeChessboard[9][9],fakeChessboard2[9][9];
        createFakeChessboard(x,y,x+1,y,fakeChessboard,chessboard);
        createFakeChessboard(x,y,x+2,y,fakeChessboard,chessboard);
        if(!ifIsInCheck(0,fakeChessboard) && !ifIsInCheck(0,fakeChessboard2)){
          possibleMovesCordinates[counter].x = x+2;
          possibleMovesCordinates[counter].y = y;
          counter++;
        }
      }
    }
    if(chessboard[1][1] == 'w'){
      if(BlackRookHasMoved.x == 0 && chessboard[x-1][y] == ' ' && chessboard[x-2][y] == ' '){
        char fakeChessboard[9][9],fakeChessboard2[9][9];
        createFakeChessboard(x,y,x-1,y,fakeChessboard,chessboard);
        createFakeChessboard(x,y,x-2,y,fakeChessboard,chessboard);
        if(!ifIsInCheck(0,fakeChessboard) && !ifIsInCheck(0,fakeChessboard2)){
          possibleMovesCordinates[counter].x = x-2;
          possibleMovesCordinates[counter].y = y;
          counter++;
        }
      }
    }
  }
}
static void BlackPawn(char chessboard[9][9],int x,int y,struct pair possibleMovesCordinates[107]){
  if(y==2){
    if(ifOutOfChessboard(x,y+2)){
      if(!isWhiteFigure(chessboard[x][y+2]) && !isBlackFigure(chessboard[x][y+2])){
        char fakeChessboard[9][9];
        createFakeChessboard(x,y,x,y+2,fakeChessboard,chessboard);
        if(!ifIsInCheck(0,fakeChessboard)){
          possibleMovesCordinates[counter].x = x;
          possibleMovesCordinates[counter].y = y+2;
          counter++;
        }
      }
    }
  }
  if(ifOutOfChessboard(x,y+1)){
    if(!isWhiteFigure(chessboard[x][y+1]) && !isBlackFigure(chessboard[x][y+1])){
      char fakeChessboard[9][9];
      createFakeChessboard(x,y,x,y+1,fakeChessboard,chessboard);
      if(!ifIsInCheck(0,fakeChessboard)){
        possibleMovesCordinates[counter].x = x;
        possibleMovesCordinates[counter].y = y+1;
        counter++;
      }
    }
  }
  if(ifOutOfChessboard(x-1,y+1)){
    if(isWhiteFigure(chessboard[x-1][y+1])){
      char fakeChessboard[9][9];
      createFakeChessboard(x,y,x-1,y+1,fakeChessboard,chessboard);
      if(!ifIsInCheck(0,fakeChessboard)){
        possibleMovesCordinates[counter].x = x-1;
        possibleMovesCordinates[counter].y = y+1;
        counter++;
      }
    }
  }
  if(ifOutOfChessboard(x+1,y+1)){
    if(isWhiteFigure(chessboard[x+1][y+1])){
      char fakeChessboard[9][9];
      createFakeChessboard(x,y,x+1,y+1,fakeChessboard,chessboard);
      if(!ifIsInCheck(0,fakeChessboard)){
        possibleMovesCordinates[counter].x = x+1;
        possibleMovesCordinates[counter].y = y+1;
        counter++;
      }
    }
  }
  //BICIE W PRZELOCIE
  if(EnPassant.y == y && EnPassant.x == x-1){
    char fakeChessboard[9][9];
    createFakeChessboard(x,y,x-1,y+1,fakeChessboard,chessboard);
    if(!ifIsInCheck(0,fakeChessboard)){
      possibleMovesCordinates[counter].x = x-1;
      possibleMovesCordinates[counter].y = y+1;
      counter++;
    }
  }
  if(EnPassant.y == y && EnPassant.x == x+1){
    char fakeChessboard[9][9];
    createFakeChessboard(x,y,x+1,y+1,fakeChessboard,chessboard);
    if(!ifIsInCheck(0,fakeChessboard)){
      possibleMovesCordinates[counter].x = x+1;
      possibleMovesCordinates[counter].y = y+1;
      counter++;
    }
  }
}
static void BlackBishop(char chessboard[9][9],int x,int y,struct pair possibleMovesCordinates[107]){
  for(int i=1;i<=8;i++){
    if(BlackFigureHelper(chessboard,x,y,x+i,y+i,possibleMovesCordinates)){
      break;
    }
  }
  for(int i=1;i<=8;i++){
    if(BlackFigureHelper(chessboard,x,y,x-i,y+i,possibleMovesCordinates)){
      break;
    }
  }
  for(int i=1;i<=8;i++){
    if(BlackFigureHelper(chessboard,x,y,x+i,y-i,possibleMovesCordinates)){
      break;
    }
  }
  for(int i=1;i<=8;i++){
    if(BlackFigureHelper(chessboard,x,y,x-i,y-i,possibleMovesCordinates)){
      break;
    }
  }
}
static void BlackKnight(char chessboard[9][9],int x,int y,struct pair possibleMovesCordinates[107]){
  for(int i=0;i<8;i++){
    BlackFigureHelper(chessboard,x,y,x+KnightMoves[i].x,y+KnightMoves[i].y,possibleMovesCordinates);
  }
}
static void BlackRook(char chessboard[9][9],int x,int y,struct pair possibleMovesCordinates[107]){
  for(int i=x+1;i<=8;i++){
    if(BlackFigureHelper(chessboard,x,y,i,y,possibleMovesCordinates)){
      break;
    }
  }
  for(int i=x-1;i>=1;i--){
    if(BlackFigureHelper(chessboard,x,y,i,y,possibleMovesCordinates)){
      break;
    }
  }
  for(int i=y+1;i<=8;i++){
    if(BlackFigureHelper(chessboard,x,y,x,i,possibleMovesCordinates)){
      break;
    }
  }
  for(int i=y-1;i>=1;i--){
    if(BlackFigureHelper(chessboard,x,y,x,i,possibleMovesCordinates)){
      break;
    }
  }
}
static void BlackQueen(char chessboard[9][9],int x,int y,struct pair possibleMovesCordinates[107]){
  BlackRook(chessboard,x,y,possibleMovesCordinates);
  BlackBishop(chessboard,x,y,possibleMovesCordinates);
}
void checkWhichFigureIsIt(char chessboard[9][9],int x,int y,struct pair possibleMovesCordinates[107]){
  counter = 0;
  switch (chessboard[x][y]){
    case 'K':
      return WhiteKing(chessboard,x,y,possibleMovesCordinates);
    case 'H':
      return WhiteQueen(chessboard,x,y,possibleMovesCordinates);
    case 'W':
      return WhiteRook(chessboard,x,y,possibleMovesCordinates);
    case 'G':
      return WhiteBishop(chessboard,x,y,possibleMovesCordinates);
    case 'P':
      return WhitePawn(chessboard,x,y,possibleMovesCordinates);
    case 'S':
      return WhiteKnight(chessboard,x,y,possibleMovesCordinates);
    case 'k':
      return BlackKing(chessboard,x,y,possibleMovesCordinates);
    case 'h':
      return BlackQueen(chessboard,x,y,possibleMovesCordinates);
    case 'w':
      return BlackRook(chessboard,x,y,possibleMovesCordinates);
    case 'g':
      return BlackBishop(chessboard,x,y,possibleMovesCordinates);
    case 'p':
      return BlackPawn(chessboard,x,y,possibleMovesCordinates);
    case 's':
      return BlackKnight(chessboard,x,y,possibleMovesCordinates);
  }
}
static void UpdateEnPassant(int x,int y){
  EnPassant.x = x;
  EnPassant.y = y;
}
static void UpdateKingHasMoved(int x,int y){
  if(x == 1){ KingHasMoved.x = x; }
  if(y == 1){ KingHasMoved.y = y; }
}
static void UpdateWhiteRookHasMoved(int x,int y){
  if(x == 1){ WhiteRookHasMoved.x = x; }
  if(y == 1){ WhiteRookHasMoved.y = y; }
}
static void UpdateBlackRookHasMoved(int x,int y){
  if(x == 1){ BlackRookHasMoved.x = x; }
  if(y == 1){ BlackRookHasMoved.y = y; }
}
static void checkEnPassant(int x,int y,struct pool ChoosenFigure){
  if(ChoosenFigure.name == 'p'){
    if(ChoosenFigure.y == 2){
      if(y==4){
        UpdateEnPassant(x,y);
      }
    }
  } else if(ChoosenFigure.name == 'P'){
    if(ChoosenFigure.y == 7){
      if(y==5){
        UpdateEnPassant(x,y);
      }
    }
  } else {
    UpdateEnPassant(0,0);
  }
}
void checkAndSendData(int x,int y,struct pool ChoosenFigure,struct pair additionalChange[2],char name){
  checkEnPassant(x,y,ChoosenFigure);
  if(ChoosenFigure.name == 'k'){ UpdateKingHasMoved(0,1); }
  if(ChoosenFigure.name == 'K'){ UpdateKingHasMoved(1,0); }
  if(ChoosenFigure.name == 'W'){
    if(ChoosenFigure.x == 1){
      UpdateWhiteRookHasMoved(1,0);
    }
    if(ChoosenFigure.x == 8){
      UpdateWhiteRookHasMoved(0,1);
    }
  }
  if(ChoosenFigure.name == 'w'){
    if(ChoosenFigure.x == 1){
      UpdateBlackRookHasMoved(1,0);
    }
    if(ChoosenFigure.x == 8){
      UpdateBlackRookHasMoved(0,1);
    }
  }
  if(ChoosenFigure.name == 'k'){
    if(ChoosenFigure.x - x == 2){
      additionalChange[0].x = 1;additionalChange[0].y = 1;additionalChange[1].x = x+1;additionalChange[1].y = 1;
    }
    if(ChoosenFigure.x - x == -2){
      additionalChange[0].x = 8;additionalChange[0].y = 1;additionalChange[1].x = x-1;additionalChange[1].y = 1;
    }
  }
  if(ChoosenFigure.name == 'K'){
    if(ChoosenFigure.x - x == 2){
      additionalChange[0].x = 1;additionalChange[0].y = 8;additionalChange[1].x = x+1;additionalChange[1].y = 8;
    }
    if(ChoosenFigure.x - x == -2){
      additionalChange[0].x = 8;additionalChange[0].y = 8;additionalChange[1].x = x-1;additionalChange[1].y = 8;
    }
  }
  if(ChoosenFigure.name == 'p' || ChoosenFigure.name == 'P'){
    if(x == ChoosenFigure.x+1 && name == ' '){
      additionalChange[0].x = ChoosenFigure.x+1;additionalChange[0].y = ChoosenFigure.y;
      additionalChange[1].x = 0;additionalChange[1].y = 0;
    }
    if(x == ChoosenFigure.x-1 && name == ' '){
      additionalChange[0].x = ChoosenFigure.x-1;additionalChange[0].y = ChoosenFigure.y;
      additionalChange[1].x = 0;additionalChange[1].y = 0;
    }
  }
}
void checkPromotion(struct pool ChoosenFigure,int x,int y){
  if(ChoosenFigure.name == 'p' && y == 8){
    transformPawn(x,y,0);
  }
  if(ChoosenFigure.name == 'P' && y == 1){
    transformPawn(x,y,1);
  }
}
