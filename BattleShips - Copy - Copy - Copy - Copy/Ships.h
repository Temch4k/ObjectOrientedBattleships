#ifndef BattleShips_SHIPS_H
#define BattleShips_SHIPS_H
#include<string>
using namespace std;
class Ships
{
private:
    string type;
    int size;
    int placeX;
    int placeY;
    char dir;
    int HP ;
public:
    Ships()
    {
        type = "";
        size = 0;
        placeX =0;
        placeY =0;
        dir =0;
    }
    void setType(string t);
    void setSize(int s);
    void setPlace(int x, int y);
    void setDir(char d);
    string getType();
    char getDir();
    int getSize();
    int getX();
    char getY();
    void setHP(int h);
    int getHP();
};
#endif