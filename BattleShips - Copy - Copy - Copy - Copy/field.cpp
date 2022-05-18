#include "field.h"
#include <iostream>
using namespace std;
field::field()
{

}
field::~field()
{
}
//prints out the current form of the board
void field::print() {
    cout << endl;
    int n = 1;

    cout << " \t A B C D E F G H I J " << endl;
    for (int i = 0; i < 10; i++) {
        cout << n << "\t";
        n++;
        cout << "|";

        for (int k = 0; k < 10; k++)
        {
            if(grid[i][k]==0)
            {
                cout <<" |";
            }
            else
            {
                cout << grid[i][k] << "|";
            }
        }
        cout << endl;
    }
}

//adds ship onto the
bool field::addShip(Ships s)
{
    //checks if the is is outside of the boards borders
    if((s.getY() <= 10) && (s.getY() >= 1) && (s.getX() <= 10) && (s.getX() >= 1))
    {
        //if ships direction is horizontal
        if(s.getDir()=='H' || s.getDir()=='h')
        {
            //then check of there is no ships located in its spot already
            for(int i = s.getX()-1;i<s.getSize()+s.getX()-1; i++)
            {
                if(grid[s.getY()-1][i] == 'V' || grid[s.getY()-1][i]== 'H')
                {
                    //if there is a ship there then return false and go back
                    return false;
                }
            }
            //if there is no ship the print it out on the field
            for(int i = s.getX()-1;i<s.getSize()+s.getX()-1; i++)
            {
                grid[s.getY()-1][i] = 'H';
            }
            return true;
        }
        //if ships direction is vertical
        else if(s.getDir()=='V' || s.getDir()=='v')
        {
            //check if there are any ships located in its way
            for(int i = s.getY()-1;i<s.getSize()+s.getY()-1; i++)
            {
                if(grid[i][s.getX()-1] == 'V' || grid[i][s.getX()-1]== 'H')
                {
                    // if there is then return false and go back
                    return false;
                }
            }
            //if there is no ship then print the ship onto the board
            for(int i = s.getY()-1;i<s.getSize()+s.getY()-1; i++)
            {
                grid[i][s.getX()-1] = 'V';
            }
            return true;
        }
    }
    //if the ship is outside of the boards borders then return false
    else
        cout << "Sorry your ship os not on the board" << endl;
        return false;
}
//lets the player shoot onto the board
bool field::playerShoot(int x, int y, field &f)
{
    //if players chosen spot on the board is H or V then player hit
    if((f.getItem(x,y) == 'H')||(f.getItem(x,y) == 'V'))
    {
        //sets that spot to the X
        grid[y-1][x-1] = 'X';
        f.setField(x,y,'X');
        //prints out target hit
        cout <<"Target Hit!"<<endl<<endl;
        return true;
    }
    //if players chosen spot is X or o then player already shot there
    else if((f.getItem(x,y) == 'X')||(f.getItem(x,y) == 'o'))
    {
        cout <<"You've already shot there, try again"<<endl;
        return false;
    }
    //if that spots is 0 then put an o in there
    else if(f.getItem(x,y) == 0)
    {
        //sets the player spot == o
        grid[y-1][x-1] = 'o';
        f.setField(x,y,'o');
        //prints out you missed
        cout <<"You missed" <<endl << endl;
        return true;
    }
}
//checks if the computer hit players ship
int field::checkIfHit(Ships s)
{
    //if the ships gets hit then make hit ++
    // that is the way to controll player ships and computer ships ship hp
    int hit = 0;
    if((s.getDir()== 'H') || (s.getDir() == 'h'))
    {
        for(int i = s.getX()-1;i<s.getX() - 1 + s.getSize();i++)
        {
            if(grid[s.getY()-1][i]=='X')
            {
                hit++;
            }
        }
        return hit;
    }
    else if((s.getDir()=='V') || (s.getDir() == 'v'))
    {
        for(int i = s.getY() - 1;i < s.getY() - 1 + s.getSize();i ++)
        {
            if(grid[i][s.getX()-1]=='X')
            {
                hit++;
            }
        }
        return hit;
    }
}

//lets the ai shoot using its randomly generated coordinates
bool field::AIShoot(int x, int y,bool &hit)
{
    // if that spot equals to H or V then hit!
    if((grid[y][x]=='H')||(grid[y][x]=='V'))
    {
        //set up that player board equal to X
        grid[y][x] = 'X';
        hit = true;
        return false;
    }
    //if that spot equals to X or o
    else if((grid[y][x]=='X')||(grid[y][x]=='o'))
    {
        //then the ai already shot there before
        hit = false;
        return true;
    }
    //if that spot equal to zero then its empty
    else if(grid[y][x] == 0)
    {
        grid[y][x] = 'o';
        hit = false;
        return false;
    }
}