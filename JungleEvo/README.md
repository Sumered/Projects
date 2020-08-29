To run code write in terminal following lines:\
g++ heurValuesGenerator.cpp -o generator\
./generator\
g++ —std=c++11 AI.cpp jungle.cpp jungleEvolution.cpp -o evo\
./evo

Whole project was done before I even had any contact with evolutionary algorithms, so this part of project
is not so great. But implementing whole game (without UI) and some basic AI methods for it in c++ was pretty fun
and challenging.

This project tries to somehow learn heuristic values for deciding which board situation is better and which is worse.
It creates few AI's with different values for figures, board place etc. which are playing against each other,
after tournament the best ones are crossed with each other to create new AI's. 
