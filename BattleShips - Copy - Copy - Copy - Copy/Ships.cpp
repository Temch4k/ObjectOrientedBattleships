#include "Ships.h"
#include <iostream>

//lets u set type of the ship
void Ships::setType(string t)
{
    type = t;
}
//lets you change size of the ship
void Ships::setSize(int s)
{
    size = s;
}
//set ship location
void Ships::setPlace(int x, int y)
{
    placeX = x;
    placeY = y;
}
//set direction of the ship
void Ships::setDir(char d)
{
    dir = d;
}
//sets shipsHP
void Ships::setHP(int h)
{
    HP = h;
}
//lets you get ships type
string Ships::getType()
{
    return type;
}
//lets you get ship direction
char Ships::getDir()
{
    return dir;
}
//lets you get ship size
int Ships::getSize()
{
    return size;
}
//lets you get ship x
int Ships::getX()
{
    return placeX;
}
//lets you get ship y
char Ships::getY()
{
    return placeY;
}
//gets ships health
int Ships::getHP()
{
    return HP;
}
