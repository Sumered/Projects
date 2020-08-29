#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <map>
using namespace std;
#define mp make_pair
#define f first
#define s second
#define pb push_back

class figure {
public:
  virtual ~figure(){};
  shared_ptr<figure> clones(){
    return shared_ptr<figure>(this->clone());
  };
  virtual figure* clone() = 0;
  char name;
  bool isWhiteFigure();
  bool isBlackFigure();
  bool isEmptySpace();
  int countPower();
  virtual void generateAllPossibleMovesCordinates(vector <pair <int,int> > &result,pair <int,int> pos, shared_ptr<figure> board[9][7]) = 0;
  void basicGenerateAllPossibleMovesCordinates(vector <pair <int,int> > &result,pair <int,int> pos, shared_ptr<figure> board[9][7]);
};

class game {
public:
  game();
  //~game();
  game(shared_ptr<figure> b[9][7]);
  shared_ptr <figure> board[9][7]; //shared_ptr
  static char terrain[9][7];
  void generateAllPossibleMovesCordinates(bool who,vector <pair <pair <int,int>,pair <int,int> > > &result);
  bool ended();
  void makeMove(pair <pair <int,int>,pair <int,int> > move);
  void makeRandomMove(bool who);
  void printState();
  string toString();
};

class empty: public figure {
public:
  empty(char c);
  empty* clone();
  void generateAllPossibleMovesCordinates(vector <pair <int,int> > &result,pair <int,int> pos, shared_ptr<figure> board[9][7]);
};
class rat: public figure {
public:
  rat(char c);
  rat* clone();
  void generateAllPossibleMovesCordinates(vector <pair <int,int> > &result,pair <int,int> pos, shared_ptr<figure> board[9][7]);
};
class cat: public figure {
public:
  cat(char c);
  cat* clone();
  void generateAllPossibleMovesCordinates(vector <pair <int,int> > &result,pair <int,int> pos, shared_ptr<figure> board[9][7]);
};
class dog: public figure {
public:
  dog(char c);
  dog* clone();
  void generateAllPossibleMovesCordinates(vector <pair <int,int> > &result,pair <int,int> pos, shared_ptr<figure> board[9][7]);
};
class wolf: public figure {
public:
  wolf(char c);
  wolf* clone();
  void generateAllPossibleMovesCordinates(vector <pair <int,int> > &result,pair <int,int> pos, shared_ptr<figure> board[9][7]);
};
class panther: public figure {
public:
  panther(char c);
  panther* clone();
  void generateAllPossibleMovesCordinates(vector <pair <int,int> > &result,pair <int,int> pos, shared_ptr<figure> board[9][7]);
};
class tiger: public figure {
public:
  tiger(char c);
  tiger* clone();
  void generateAllPossibleMovesCordinates(vector <pair <int,int> > &result,pair <int,int> pos, shared_ptr<figure> board[9][7]);
};
class lion: public figure {
public:
  lion(char c);
  lion* clone();
  void generateAllPossibleMovesCordinates(vector <pair <int,int> > &result,pair <int,int> pos, shared_ptr<figure> board[9][7]);
};
class elephant: public figure {
public:
  elephant(char c);
  elephant* clone();
  void generateAllPossibleMovesCordinates(vector <pair <int,int> > &result,pair <int,int> pos, shared_ptr<figure> board[9][7]);
};

class AI {
public:
  int posBonus[9][7];
  int figureValues[8];
  int agressionBonus;
  AI(game* g);
  AI();
  //STANDARD HEURESTIC
  int countScore(game situation);
  int countValue(char c);
  void chooseBestMove(int who); //flat MCTS algorithm
  void MinMax(bool who); //min max with alfabeta prunning
  int AlfaBeta(game situation,bool who,int deepLimit,int alfa,int beta);
  pair <int,int> doRngGame(game fakeGame,int who); //week oponent
  void MCTS();
  game* actualGame;
};

bool isInsideBoard(pair <int,int> pos);
