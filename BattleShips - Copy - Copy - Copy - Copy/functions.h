#ifndef BattleShips_functions_H
#define BattleShips_functions_H

#include <vector>

using namespace std;
bool read();
void start(Ships &s1,Ships &s2,Ships &s3,Ships &s4,Ships &s5);
int convert(char i);
void checkShip(bool &ship, field &f, Ships &s);
void putBoats(Ships &cs1, int &b, bool &status1);
void findSizeHP(Ships &s);
bool putBoatsRead(Ships &s, field &f);
void genRandom(Ships &s, field &f1);
void ran(Ships &ss1,int &i);
int playGame(Ships s1,Ships s2,Ships s3,Ships s4,Ships s5,
             Ships cs1,Ships cs2,Ships cs3,Ships cs4,Ships cs5);
void aIShotHit(int &shotX, int &shotY, bool &hit, bool &AIShot,int &added_To_Xplace);
void printHP(Ships s,Ships s2,Ships s3,Ships s4, Ships s5);
void CountHP(Ships &s1, int &p1,field f);
void aIShot(bool &hit,int &shotX,int &shotY);
void checkAIHP(Ships s,Ships s2,Ships s3,Ships s4, Ships s5);
void findType(Ships &s);

#endif