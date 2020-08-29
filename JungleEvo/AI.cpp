#include "jungle.h"

AI::AI(game* g){
  actualGame = g;
}
AI::AI(){}
//RNG AI
//!!!!!!
//!!!!!!

void AI::chooseBestMove(int who){
  vector <pair <pair <int,int>,pair <int,int> > > V;
  actualGame->generateAllPossibleMovesCordinates(who,V);
  int movesMade = 0;
  pair <int,int> StatisticGames[V.size()];
  for(int i=0;i<V.size();i++){ StatisticGames[i] = mp(0,0); }
  for(int i=0;i<V.size();i++){
    for(int j=0;j<(1000/(V.size()));j++){
      game fakeGame = game(actualGame->board);
      fakeGame.makeMove(V[i]);
      pair <int,int> result = doRngGame(fakeGame,who);
      movesMade += result.s;
      StatisticGames[i].f += result.f; StatisticGames[i].s++;
      if(movesMade>=20000){break;}
    }
  }
  int bestMove;
  double bestScore = 0.0;
  for(int i=0;i<V.size();i++){
    double score = ((1.0*StatisticGames[i].f)/StatisticGames[i].s);
    if(bestScore < score){
      bestScore = score;
      bestMove = i;
    }
  }
  actualGame->makeMove(V[bestMove]);
}

pair <int,int> AI::doRngGame(game fakeGame,int who){
  vector <pair <pair <int,int>,pair <int,int> > > V;
  int cnt = 0;
  while(true){
    fakeGame.generateAllPossibleMovesCordinates(who,V);
    fakeGame.makeRandomMove(who);
    cnt++;
    if(fakeGame.ended()){return mp(1,cnt);}
    V.clear();
    fakeGame.generateAllPossibleMovesCordinates((who+1)%2,V);
    fakeGame.makeRandomMove((who+1)%2);
    cnt++;
    if(fakeGame.ended()){return mp(0,cnt);}
  }
}

//HEUR AI
//!!!!!!!
//!!!!!!!

int AI::countValue(char c){
  switch(c){
    case 'r': return figureValues[0];
    case 'c': return figureValues[1];
    case 'd': return figureValues[2];
    case 'w': return figureValues[3];
    case 'p': return figureValues[4];
    case 't': return figureValues[5];
    case 'l': return figureValues[6];
    case 'e': return figureValues[7];
    case 'R': return figureValues[0];
    case 'C': return figureValues[1];
    case 'D': return figureValues[2];
    case 'W': return figureValues[3];
    case 'P': return figureValues[4];
    case 'T': return figureValues[5];
    case 'L': return figureValues[6];
    case 'E': return figureValues[7];
    default: return 0;
  }
}

int AI::countScore(game situation){ //standard Heurestic
  int whiteScore = 0,blackScore = 0;
  for(int i=0;i<9;i++){
    for(int j=0;j<7;j++){
      shared_ptr <figure> actual = situation.board[i][j];
      if(actual->isWhiteFigure()){
        whiteScore += countValue(actual->name);
        whiteScore += posBonus[i][j];
        if(i == 0 && j == 3){ whiteScore += 1e8; }
        else { whiteScore += 12.0/(i+abs(3-j)) * (double)agressionBonus; }
        //whiteScore += actual->countPower();// + positionBonus[i][j];
      } else if(actual->isBlackFigure()){
        blackScore += countValue(actual->name);
        blackScore += posBonus[8-i][6-j];
        if(i == 8 && j == 3){ blackScore += 1e8; }
        else { blackScore += 12.0/(8-i+abs(3-j)) * (double)agressionBonus; }
        //blackScore += actual->countPower();// + positionBonus[8-i][6-j];
      }
    }
  }
  return whiteScore-blackScore;
}

void AI::MinMax(bool who){//MinMax AI with alfabeta prunning
  vector <pair <pair <int,int>,pair <int,int> > > V;
  actualGame->generateAllPossibleMovesCordinates(who,V);
  int best;
  if(who == 1){
    best = -1e9;
  } else {
    best = 1e9;
  }
  int choosedMove;
  for(int i=0;i<V.size();i++){
    game fakeGame = game(actualGame->board);
    fakeGame.makeMove(V[i]);
    int moveScore = AlfaBeta(fakeGame,!who,2,-1e9,1e9);
    //cout << moveScore << " " << V[i].f.f << " " << V[i].f.s << " " << V[i].s.f << " " << V[i].s.s << "\n";
    if(who == 1){
      if(moveScore > best){
        best = moveScore;
        choosedMove = i;
      }
    } else {
      if(moveScore < best){
        best = moveScore;
        choosedMove = i;
      }
    }
  }
  actualGame->makeMove(V[choosedMove]);
}

int AI::AlfaBeta(game situation,bool who,int deepLimit,int alfa,int beta){
  if(situation.ended()){
    if(who == 0){
      return 1e8*(deepLimit+1);
    } else {
      return -1e8*(deepLimit+1);
    }
  }
  if(deepLimit == 0){
    return countScore(situation);
  }
  vector <pair <pair <int,int>,pair <int,int> > > V;
  situation.generateAllPossibleMovesCordinates(who,V);
  if(who == 0){
    for(int i=0;i<V.size();i++){
      game fakeGame = game(situation.board);
      fakeGame.makeMove(V[i]);
      beta = min(beta,AlfaBeta(fakeGame,1,deepLimit-1,alfa,beta));
      if(alfa>=beta){
        break;
      }
    }
    return beta;
  } else {
    for(int i=0;i<V.size();i++){
      game fakeGame = game(situation.board);
      fakeGame.makeMove(V[i]);
      alfa = max(alfa,AlfaBeta(fakeGame,0,deepLimit-1,alfa,beta));
      if(alfa>=beta){
        break;
      }
    }
    return alfa;
  }
}
