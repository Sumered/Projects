#include "jungle.h"
pair <int,int> directions[4] = {mp(-1,0),mp(0,-1),mp(0,1),mp(1,0)};
char game::terrain[9][7] = {'.','.','#','*','#','.','.',
'.','.','.','#','.','.','.',
'.','.','.','.','.','.','.',
'.','-','-','.','-','-','.',
'.','-','-','.','-','-','.',
'.','-','-','.','-','-','.',
'.','.','.','.','.','.','.',
'.','.','.','#','.','.','.',
'.','.','#','*','#','.','.'};
rat::rat(char c){name = c;}
cat::cat(char c){name = c;}
dog::dog(char c){name = c;}
wolf::wolf(char c){name = c;}
panther::panther(char c){name = c;}
tiger::tiger(char c){name = c;}
lion::lion(char c){name = c;}
elephant::elephant(char c){name = c;}
empty::empty(char c){name = c;}
rat* rat::clone(){ return new rat(name); }
cat* cat::clone(){ return new cat(name); }
dog* dog::clone(){ return new dog(name); }
wolf* wolf::clone(){ return new wolf(name); }
panther* panther::clone(){ return new panther(name); }
tiger* tiger::clone(){ return new tiger(name); }
lion* lion::clone(){ return new lion(name); }
elephant* elephant::clone(){ return new elephant(name); }
empty* empty::clone(){ return new empty(name); }

bool figure::isWhiteFigure(){
  switch(name){
    case 'r': return true;
    case 'c': return true;
    case 'd': return true;
    case 'w': return true;
    case 'p': return true;
    case 't': return true;
    case 'l': return true;
    case 'e': return true;
  }
  return false;
}

bool figure::isBlackFigure(){
  switch(name){
    case 'R': return true;
    case 'C': return true;
    case 'D': return true;
    case 'W': return true;
    case 'P': return true;
    case 'T': return true;
    case 'L': return true;
    case 'E': return true;
  }
  return false;
}

bool figure::isEmptySpace(){
  return name == '.';
}

int figure::countPower(){
  if(isWhiteFigure()){
    switch(name){
      case 'r': return 1;
      case 'c': return 2;
      case 'd': return 3;
      case 'w': return 4;
      case 'p': return 5;
      case 't': return 6;
      case 'l': return 7;
      case 'e': return 8;
    }
  } else if(isBlackFigure()){
    switch(name){
      case 'R': return 1;
      case 'C': return 2;
      case 'D': return 3;
      case 'W': return 4;
      case 'P': return 5;
      case 'T': return 6;
      case 'L': return 7;
      case 'E': return 8;
    }
  }
  return 0;
}

void figure::basicGenerateAllPossibleMovesCordinates(vector <pair <int,int> > &result,pair <int,int> pos, shared_ptr<figure> board[9][7]) {
  for(int i=0;i<4;i++){
    if(isInsideBoard(mp(pos.f+directions[i].f,pos.s+directions[i].s))){
      if(board[pos.f+directions[i].f][pos.s+directions[i].s]->isWhiteFigure() && isBlackFigure()){
        if(board[pos.f+directions[i].f][pos.s+directions[i].s]->countPower() <= countPower()){
          result.pb(mp(pos.f+directions[i].f,pos.s+directions[i].s));
        } else if(game::terrain[pos.f+directions[i].f][pos.s+directions[i].s] == '#'){
          result.pb(mp(pos.f+directions[i].f,pos.s+directions[i].s));
        }
      }
      if(board[pos.f+directions[i].f][pos.s+directions[i].s]->isBlackFigure() && isWhiteFigure()){
        if(board[pos.f+directions[i].f][pos.s+directions[i].s]->countPower() <= countPower()){
          result.pb(mp(pos.f+directions[i].f,pos.s+directions[i].s));
        } else if(game::terrain[pos.f+directions[i].f][pos.s+directions[i].s] == '#'){
          result.pb(mp(pos.f+directions[i].f,pos.s+directions[i].s));
        }
      }
      if(board[pos.f+directions[i].f][pos.s+directions[i].s]->isEmptySpace() && game::terrain[pos.f+directions[i].f][pos.s+directions[i].s] != '-'){
        result.pb(mp(pos.f+directions[i].f,pos.s+directions[i].s));
      }
    }
  }
}
void empty::generateAllPossibleMovesCordinates(vector <pair <int,int> > &result,pair <int,int> pos, shared_ptr<figure> board[9][7]){return;}
void rat::generateAllPossibleMovesCordinates(vector <pair <int,int> > &result,pair <int,int> pos, shared_ptr<figure> board[9][7]){
  for(int i=0;i<4;i++){
    if(isInsideBoard(mp(pos.f+directions[i].f,pos.s+directions[i].s))){
      if(board[pos.f+directions[i].f][pos.s+directions[i].s]->isWhiteFigure() && isBlackFigure()){
        if((board[pos.f+directions[i].f][pos.s+directions[i].s]->countPower() == 1 || board[pos.f+directions[i].f][pos.s+directions[i].s]->countPower() == 8) && game::terrain[pos.f][pos.s] != '-'){
          result.pb(mp(pos.f+directions[i].f,pos.s+directions[i].s));
        } else if(game::terrain[pos.f+directions[i].f][pos.s+directions[i].s] == '#'){
          result.pb(mp(pos.f+directions[i].f,pos.s+directions[i].s));
        }
      }
      if(board[pos.f+directions[i].f][pos.s+directions[i].s]->isBlackFigure() && isWhiteFigure()){
        if((board[pos.f+directions[i].f][pos.s+directions[i].s]->countPower() == 1 || board[pos.f+directions[i].f][pos.s+directions[i].s]->countPower() == 8) && game::terrain[pos.f][pos.s] != '-'){
          result.pb(mp(pos.f+directions[i].f,pos.s+directions[i].s));
        } else if(game::terrain[pos.f+directions[i].f][pos.s+directions[i].s] == '#'){
          result.pb(mp(pos.f+directions[i].f,pos.s+directions[i].s));
        }
      }
      if(board[pos.f+directions[i].f][pos.s+directions[i].s]->isEmptySpace()){
        result.pb(mp(pos.f+directions[i].f,pos.s+directions[i].s));
      }
    }
  }
}
void cat::generateAllPossibleMovesCordinates(vector <pair <int,int> > &result,pair <int,int> pos, shared_ptr<figure> board[9][7]){
  basicGenerateAllPossibleMovesCordinates(result,pos,board);
}

void dog::generateAllPossibleMovesCordinates(vector <pair <int,int> > &result,pair <int,int> pos, shared_ptr<figure> board[9][7]){
  basicGenerateAllPossibleMovesCordinates(result,pos,board);
}

void wolf::generateAllPossibleMovesCordinates(vector <pair <int,int> > &result,pair <int,int> pos, shared_ptr<figure> board[9][7]){
  basicGenerateAllPossibleMovesCordinates(result,pos,board);
}

void panther::generateAllPossibleMovesCordinates(vector <pair <int,int> > &result,pair <int,int> pos, shared_ptr<figure> board[9][7]){
  basicGenerateAllPossibleMovesCordinates(result,pos,board);
}

void tiger::generateAllPossibleMovesCordinates(vector <pair <int,int> > &result,pair <int,int> pos, shared_ptr<figure> board[9][7]){
  basicGenerateAllPossibleMovesCordinates(result,pos,board);
  for(int i=0;i<4;i++){
    if(isInsideBoard(mp(pos.f+directions[i].f,pos.s+directions[i].s))){
      if(board[pos.f+directions[i].f][pos.s+directions[i].s]->isEmptySpace() && game::terrain[pos.f+directions[i].f][pos.s+directions[i].s] == '-'){
        pair <int,int> start = pos;
        start.f += directions[i].f; start.s += directions[i].s;
        bool canJump = true;
        while(game::terrain[start.f][start.s] == '-'){
          if(!board[start.f][start.s]->isEmptySpace()){
            canJump = false;
            break;
          }
          start.f += directions[i].f;
          start.s += directions[i].s;
        }
        if(canJump == false){continue;}
        if(board[start.f][start.s]->isWhiteFigure() && isBlackFigure()){
          if(board[start.f][start.s]->countPower() <= countPower()){
            result.pb(start);
          }
        }
        if(board[start.f][start.s]->isBlackFigure() && isWhiteFigure()){
          if(board[start.f][start.s]->countPower() <= countPower()){
            result.pb(start);
          }
        }
        if(board[start.f][start.s]->isEmptySpace()){
          result.pb(start);
        }
      }
    }
  }
}

void lion::generateAllPossibleMovesCordinates(vector <pair <int,int> > &result,pair <int,int> pos, shared_ptr<figure> board[9][7]){
  basicGenerateAllPossibleMovesCordinates(result,pos,board);
  for(int i=0;i<4;i++){
    if(isInsideBoard(mp(pos.f+directions[i].f,pos.s+directions[i].s))){
      if(board[pos.f+directions[i].f][pos.s+directions[i].s]->isEmptySpace() && game::terrain[pos.f+directions[i].f][pos.s+directions[i].s] == '-'){
        pair <int,int> start = pos;
        start.f += directions[i].f; start.s += directions[i].s;
        bool canJump = true;
        while(game::terrain[start.f][start.s] == '-'){
          if(!board[start.f][start.s]->isEmptySpace()){
            canJump = false;
            break;
          }
          start.f += directions[i].f;
          start.s += directions[i].s;
        }
        if(canJump == false){continue;}
        if(board[start.f][start.s]->isWhiteFigure() && isBlackFigure()){
          if(board[start.f][start.s]->countPower() <= countPower()){
            result.pb(start);
          }
        }
        if(board[start.f][start.s]->isBlackFigure() && isWhiteFigure()){
          if(board[start.f][start.s]->countPower() <= countPower()){
            result.pb(start);
          }
        }
        if(board[start.f][start.s]->isEmptySpace()){
          result.pb(start);
        }
      }
    }
  }
}

void elephant::generateAllPossibleMovesCordinates(vector <pair <int,int> > &result,pair <int,int> pos, shared_ptr<figure> board[9][7]){
  basicGenerateAllPossibleMovesCordinates(result,pos,board);
}

string game::toString(){
  string coded = "";
  for(int i=0;i<9;i++){
    for(int j=0;j<7;j++){
      coded += board[i][j]->name;
    }
  }
  return coded;
}
void game::generateAllPossibleMovesCordinates(bool who,vector <pair <pair <int,int>,pair <int,int> > > &result){
  vector <pair <int,int> > smallMoves;
  for(int i=0;i<9;i++){
    for(int j=0;j<7;j++){
      smallMoves.clear();
      if(who == 1 && board[i][j]->isWhiteFigure()){
        board[i][j]->generateAllPossibleMovesCordinates(smallMoves,mp(i,j),board);
        for(int k=0;k<smallMoves.size();k++){
          if(smallMoves[k].f == 8 && smallMoves[k].s == 3){continue;}
          result.pb(mp(mp(i,j),smallMoves[k]));
        }
      }else if(who == 0 && board[i][j]->isBlackFigure()){
        board[i][j]->generateAllPossibleMovesCordinates(smallMoves,mp(i,j),board);
        for(int k=0;k<smallMoves.size();k++){
          if(smallMoves[k].f == 0 && smallMoves[k].s == 3){continue;}
          result.pb(mp(mp(i,j),smallMoves[k]));
        }
      }
    }
  }
}
bool game::ended(){
  int numberOfBlack = 0,numberOfWhite = 0;
  if(board[0][3]->isWhiteFigure()){return true;}
  if(board[8][3]->isBlackFigure()){return true;}
  for(int i=0;i<9;i++){
    for(int j=0;j<7;j++){
      if(board[i][j]->isBlackFigure()){numberOfBlack++;}
      else if(board[i][j]->isWhiteFigure()){numberOfWhite++;}
    }
  }
  if(numberOfBlack == 0 || numberOfWhite == 0){return true;}
  return false;
}

void game::makeRandomMove(bool who){
  vector <pair <pair <int,int>,pair <int,int> > > possibleMoves;
  generateAllPossibleMovesCordinates(who,possibleMoves);
  int choosen = rand()%possibleMoves.size();
  //delete board[possibleMoves[choosen].s.f][possibleMoves[choosen].s.s];
  board[possibleMoves[choosen].s.f][possibleMoves[choosen].s.s] = board[possibleMoves[choosen].f.f][possibleMoves[choosen].f.s];
  board[possibleMoves[choosen].f.f][possibleMoves[choosen].f.s] = shared_ptr<empty>(new empty('.'));
}

void game::makeMove(pair <pair <int,int>,pair <int,int> > move){
  //delete board[move.s.f][move.s.s];
  board[move.s.f][move.s.s] = board[move.f.f][move.f.s];
  board[move.f.f][move.f.s] = shared_ptr<empty>(new empty('.'));
}

game::game(){
  board[0][0] = shared_ptr<lion> (new lion('L')); board[0][1] = shared_ptr<empty>(new empty('.')); board[0][2] = shared_ptr<empty>(new empty('.')); board[0][3] = shared_ptr<empty>(new empty('.')); board[0][4] = shared_ptr<empty>(new empty('.')); board[0][5] = shared_ptr<empty>(new empty('.')); board[0][6] = shared_ptr<tiger>(new tiger('T'));
  board[1][0] = shared_ptr<empty>(new empty('.')); board[1][1] = shared_ptr<dog>(new dog('D')); board[1][2] = shared_ptr<empty>(new empty('.')); board[1][3] = shared_ptr<empty>(new empty('.')); board[1][4] = shared_ptr<empty>(new empty('.')); board[1][5] = shared_ptr<cat>(new cat('C')); board[1][6] = shared_ptr<empty>(new empty('.'));
  board[2][0] = shared_ptr<rat>(new rat('R')); board[2][1] = shared_ptr<empty>(new empty('.')); board[2][2] = shared_ptr<wolf>(new wolf('W')); board[2][3] = shared_ptr<empty>(new empty('.')); board[2][4] = shared_ptr<panther>(new panther('P')); board[2][5] = shared_ptr<empty>(new empty('.')); board[2][6] = shared_ptr<elephant>(new elephant('E'));
  board[3][0] = shared_ptr<empty>(new empty('.')); board[3][1] = shared_ptr<empty>(new empty('.')); board[3][2] = shared_ptr<empty>(new empty('.')); board[3][3] = shared_ptr<empty>(new empty('.')); board[3][4] = shared_ptr<empty>(new empty('.')); board[3][5] = shared_ptr<empty>(new empty('.')); board[3][6] = shared_ptr<empty>(new empty('.'));
  board[4][0] = shared_ptr<empty>(new empty('.')); board[4][1] = shared_ptr<empty>(new empty('.')); board[4][2] = shared_ptr<empty>(new empty('.')); board[4][3] = shared_ptr<empty>(new empty('.')); board[4][4] = shared_ptr<empty>(new empty('.')); board[4][5] = shared_ptr<empty>(new empty('.')); board[4][6] = shared_ptr<empty>(new empty('.'));
  board[5][0] = shared_ptr<empty>(new empty('.')); board[5][1] = shared_ptr<empty>(new empty('.')); board[5][2] = shared_ptr<empty>(new empty('.')); board[5][3] = shared_ptr<empty>(new empty('.')); board[5][4] = shared_ptr<empty>(new empty('.')); board[5][5] = shared_ptr<empty>(new empty('.')); board[5][6] = shared_ptr<empty>(new empty('.'));
  board[6][0] = shared_ptr<elephant>(new elephant('e')); board[6][1] = shared_ptr<empty>(new empty('.')); board[6][2] = shared_ptr<panther>(new panther('p')); board[6][3] = shared_ptr<empty>(new empty('.')); board[6][4] = shared_ptr<wolf>(new wolf('w')); board[6][5] = shared_ptr<empty>(new empty('.')); board[6][6] = shared_ptr<rat>(new rat('r'));
  board[7][0] = shared_ptr<empty>(new empty('.')); board[7][1] = shared_ptr<cat>(new cat('c')); board[7][2] = shared_ptr<empty>(new empty('.')); board[7][3] = shared_ptr<empty>(new empty('.')); board[7][4] = shared_ptr<empty>(new empty('.')); board[7][5] = shared_ptr<dog>(new dog('d')); board[7][6] = shared_ptr<empty>(new empty('.'));
  board[8][0] = shared_ptr<tiger>(new tiger('t')); board[8][1] = shared_ptr<empty>(new empty('.')); board[8][2] = shared_ptr<empty>(new empty('.')); board[8][3] = shared_ptr<empty>(new empty('.')); board[8][4] = shared_ptr<empty>(new empty('.')); board[8][5] = shared_ptr<empty>(new empty('.')); board[8][6] = shared_ptr<lion>(new lion('l'));
}

// game::~game(){
//   cout << "enters destructor\n";
//   cout << board[0][0] << "\n";
//   for(int i=0;i<9;i++){
//     for(int j=0;j<7;j++){
//       delete board[i][j];
//     }
//   }
// }

game::game(shared_ptr<figure> b[9][7]){
  for(int i=0;i<9;i++){
    for(int j=0;j<7;j++){
      board[i][j] = b[i][j]->clones();
    }
  }
}
void game::printState(){
  for(int i=0;i<9;i++){
    for(int j=0;j<7;j++){
      cout << board[i][j]->name << " ";
    }
    cout << "\n";
  }
  cout << "\n";
}

bool isInsideBoard(pair <int,int> pos){
  return pos.f >= 0 && pos.f < 9 && pos.s >= 0 && pos.s < 7;
}
