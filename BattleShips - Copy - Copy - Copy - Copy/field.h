#ifndef BattleShips_field_H
#define BattleShips_field_H
#include <iostream>
#include "Ships.h"

using namespace std;
class field : public Ships
{
private:
    //the infamous battleships grid
    char grid[10][10] = { 0 };
public:
    field();
    ~field();
    void print();
    bool addShip(Ships s);
    char getItem(int x, int y)
    {
        return grid[y-1][x-1];
    }
    char setField(int x, int y,char c)
    {
        grid[y-1][x-1] = c;
    }
    bool playerShoot(int x, int y, field &f);
    bool AIShoot(int x, int y,bool &hit);
    int checkIfHit(Ships s);


};
#endif // Included_NameModel_H
