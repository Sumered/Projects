#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;
int main(){
  srand(time(NULL));
  string name = "heur";
  for(int i=0;i<28;i++){
    string num = to_string(i);
    name += num;
    ofstream file;
    file.open(name.c_str());
    for(int j=0;j<9;j++){
      for(int k=0;k<7;k++){
        file << rand()%10000 << " ";
      }
      file << "\n";
    }
    for(int j=0;j<8;j++){
      file << rand()%50000 + 10000 << "\n";
    }
    file << rand()%20000+5000 << "\n";
    if(i>9){name.pop_back();}
    name.pop_back();
  }
}
