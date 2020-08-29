#include <fstream>
#include "jungle.h"
using namespace std;
int main(){
  int loops = 0;
  while(loops < 100){
    //init
    AI population[28];
    vector < pair <int,int> > wins;
    game jungle = game();
    for(int i = 0;i<28;i++){
      wins.pb(mp(0,i));
      population[i] = AI(&jungle);
      string name = "heur";
      name += to_string(i);
      ifstream file;
      file.open(name);
      for(int j=0;j<9;j++){
        for(int k=0;k<7;k++){
          int value;
          file >> value;
          population[i].posBonus[j][k] = value;
        }
      }
      for(int j=0;j<8;j++){
        int value;
        file >> value;
        population[i].figureValues[j] = value;
      }
      file >> population[i].agressionBonus;
    }
    //ai arena
    int counter = 0;
    for(int i=0;i<28;i++){
      for(int j=i+1;j<28;j++){
        game jungleBoard = game();
        population[i].actualGame = &jungleBoard;
        population[j].actualGame = &jungleBoard;
        int moves = 100;
        while(true){
          population[i].MinMax(1);
          jungleBoard.printState();
          if(jungleBoard.ended()){cout << "WINS AI: " << i << "\n"; wins[i].f += 1; break;}
          population[j].MinMax(0);
          jungleBoard.printState();
          if(jungleBoard.ended()){cout << "WINS AI: " << j << "\n"; wins[j].f += 1; break;}
          moves--;
          if(moves == 0){break;}
        }
        counter++;
        cout << counter << " : " << 28*14 << "\n";
      }
    }
    ofstream result;
    result.open("result.txt");
    for(int i=0;i<28;i++){
      result << i << "\n";
      result << wins[i].f << " " << wins[i].s << "\n";
    }
    result << loops << "\n";
    result.close();
    //ai evolution
    int cnt = 0;
    sort(wins.begin(),wins.end());
    for(int i=0;i<14;i+=2){
      AI father = population[wins[i].s];
      AI mother = population[wins[i+1].s];
      for(int j=0;j<4;j++){
        string name = "heur";
        name += to_string(cnt);
        cnt++;
        ofstream file;
        file.open(name);
        for(int k=0;k<9;k++){
          for(int l=0;l<7;l++){
            int chance = rand()%100+1;
            if(chance == 1 || chance == 2){
              file << rand()%10000 << " ";
              continue;
            } else if(chance <= 51){
              file << mother.posBonus[k][l] << " ";
            } else if(chance > 51){
              file << father.posBonus[k][l] << " ";
            }
          }
          file << "\n";
        }
        for(int k=0;k<8;k++){
          int chance = rand()%100+1;
          if(chance == 1 || chance == 2){
            file << rand()%50000 + 10000 << "\n";
            continue;
          } else if(chance <= 51){
            file << mother.figureValues[k] << "\n";
          } else if(chance > 51){
            file << father.figureValues[k] << "\n";
          }
        }
        int chance = rand()%100+1;
        if(chance == 1 || chance == 2){
          file << rand()%20000 << "\n";
        } else if(chance <= 51){
          file << mother.agressionBonus << "\n";
        } else if(chance > 51){
          file << father.agressionBonus << "\n";
        }
      }
    }
    loops++;
  }
}
