#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <random>
#include <ctime>
#include "Ships.h"
#include "field.h"
#include "functions.h"

using namespace std;
//we read in lines into it
vector<string> t;
//we separate the lines into words by commas
vector<string> vect;

//random computer field
field f1;
//generated player field
field f;

//puts random ships onto the computer board
void genRandom(Ships &s, field &f1)
{
    char dr;

    //generated a random direction for the computer
    int d = rand()%2;

    //checks if the ship is placed
    bool shipP1 = false;

    //generates the direction the ship will be facing
    if(d ==1)
        dr = 'V';
    if(d==0)
        dr ='H';

    //sets that direction
    s.setDir(dr);

    int x;
    int y;


    srand(time(0));  // <- seed with the current time


    //until ship is placed keep on generating a new location for it
    while(!shipP1)
    {
        //generates random x and Y
        x = (rand()%10)+1;
        y = (rand()%10)+1;
        //sets those x and Y
        s.setPlace(x,y);

        //if those x and Y plus size ae bigger than the board then generated new x and y
        if ((s.getX() + s.getSize() > 10) || (s.getY() + s.getSize() > 10))
        {
            //if random direction is H
            if (dr == 'H')
                //then while x plus the size is bigger than the field generate new coordinates
                while(s.getX() + s.getSize() > 10)
                {
                    x = (rand() % 10) + 1;
                    s.setPlace(x, y);
                }
                //if random direction is Y
                else
                {
                    //then while y plus the size is bigger tan field generated new y
                    while(s.getY() + s.getSize() > 10)
                    {
                        y = (rand() % 10) + 1;
                        s.setPlace(x, y);
                    }
                }

                //set the ship placed status equal to true if placed if not try again
            shipP1 = f1.addShip(s);
        } else
        {
            shipP1 = f1.addShip(s);
        }
    }
    s.setPlace(x,y);
    s.setDir(dr);
    //print the field out when the ship is placed
}
//calls the functions to generate the random ships
void ran(Ships &ss1,int &i)
{
    //sets the size for the 5 random ships
    ss1.setSize(i);
    findType(ss1);
    i--;
    findSizeHP(ss1);
    //generates those random ships using the function above
    genRandom(ss1,f1);
}
//reads in ships from a file
bool read()
{
    try {
        // creates the input stream
        ifstream in;

        //makes two strings that will intake the input from files
        string temp, line;

        //opens the file
        in.open("ship_placement3_good.csv");

        //reads in every separate line from the file into a vector
        if (!in) {
            cout << "unable to open the file" << endl;
            return false;
        } else {
            while (in >> temp) {
                t.push_back(temp);
            }
            //splits up the lines into separate parts devided by commas
            for (const auto &i : t) {
                //creates stringstteam and sets it up for the current string in the vector
                stringstream ss(i);

                //while there are parts to left to that line
                while (getline(ss, temp, ',')) {
                    //stuff those individual parts into a new vector
                    vect.push_back(temp);
                }
            }
            //closes the input file
            in.close();
        }
    }
    catch (...)
    {
     cout << "Error Reading the file, The program will now close"<<endl;
     return false;
    }
}
//sets up all of the coordinates of the boats that are read in from the file
void putBoats(Ships &cs1, int &b, bool &status1)
{
    //creates the new ships
    string name;
    char x;
    int y, placeX;

    ///first ship
    //takes in the type of the ship
    cs1.setType(vect[b]);
    b++;
    //uses function find type
    findSizeHP(cs1);

    //sets up a stingstream to devide the coordinates into x and y
    string in = vect[b];
    b++;
    //reads it in and separates everything
    stringstream ss(in);
    ss >> x >> y;


    //sets character x equal to a number on the board using convert function below
    placeX = convert(x);
    cs1.setPlace(placeX,y);

    //takes in the string in the vector converts it to character and puts it int ships direction instructions
    name = vect[b];
    b++;
    cs1.setDir(name[0]);

    //uses function boatsRead to put all of the ships onto the field called cf for the use

    //checks if the ships are placed
    //and if they arent then lets the user input the location himself
    while(status1)
    {
        if(putBoatsRead(cs1,f))
        {
            cout <<cs1.getType() << " Worked!!"<< endl;
            status1 = false;
        }
        else
        {
            cout <<cs1.getType()<<" didn't work" << endl;
            cout <<cs1.getType()<<" please input your own info"<<endl;
            f.print();
            (checkShip(status1,f,cs1));
        }
    }
}
//sets up the read in boats to be put onto the field
bool putBoatsRead(Ships &s, field &f)
{
    //if boats direction is is h
    if (s.getDir() == 'H')
    {
        //if boats x plus size -1 is not outside of the board then proceed putting them on the field
        if (s.getX() + s.getSize() - 1 <= 10)
        {
            //if the boat was put down successfully then
            if (f.addShip(s))
            {
                //print out the field with the boat on it
                //say what boat was put down successfully
                return true;
                //if it wasn't put successfully then say you cannot put your boat there
            } //end of 3rd if
            else
            {
                cout << "You cannot place a ship there, try again" << endl;
                return false;
            }//end of 1st else
        }//end of if x+size
        // if x+size is bigger than 10 it means that its outside of the board, print out you cannot place a boat there
        else
        {
            cout << "You cannot place your " << s.getType()<<" there, its outside of the board" << endl;
            return false;
        }//end 2nd else

    }//end of if with 'H'
    //if boats direction is vertical
    else if(s.getDir() == 'V')
    {
        //if y and its size -1 is on the board
        if (s.getY() + s.getSize() - 1 <= 10)
        {
            //if the boat was placed successfully then print it out and the board
            if (f.addShip(s))
            {
                return true;
            }//end of 3rd if
            //if putting the ship there was unsuccessful then say try again
            else
            {
                cout << "You cannot place a " << s.getType() <<" ship there, try again" << endl;
                return false;
            }//end of 1st else
        } //end of x+size if
        //if the boat is bigger then board the print out you cant place ship there
        else
        {
            cout << "Your " <<s.getType() <<" cannot cannot be placed there" << endl;
            return false;
        }
    }
}
//this function is made for the user to input his own coordinates of the ships
void start(Ships &s1,Ships &s2,Ships &s3,Ships &s4,Ships &s5)
{
    bool ship1=true,ship2=true,ship3=true,ship4=true,ship5 = true;
    char choice;
    bool ships = true;
    cout << "Lets start by placing ships?" << endl;

    //prints out the empty player board
    f.print();

    //while all the ships are not on the field keep on asking about putting the ships down
    while(ships)
    {
        //prints out the ship options
        cout << "Which one would you like to place onto the board" << endl;
        cout << "A. Carrier,  5 in length" << endl <<
                "B. Battleship, 4 in length" << endl <<
                "C. Cruiser, 3 in length" << endl <<
                "D. Submarine, 2 in length" << endl <<
                "E. Destroyer, 1 in length" << endl;

        //takes in user choice
        cin >> choice;
        //menu for the users
        switch (choice)
        {
            case 'A':
            case 'a':
                //if carrier then set size to 5
                //if ship is true
                if(ship1)
                {
                    //set the size and type and try putting the ship onto the board
                    s1.setType("Carrier");
                    findSizeHP(s1);
                    checkShip(ship1,f,s1);
                }
                //if ship is not true then say that you already have the ships placed
                else
                {
                    cout << "You've already placed that ship" << endl;
                }
                break;
            case 'B':
            case 'b':
                //if ships is Battleship then set size to 4
                //if ship is true
                if(ship2)
                {   //sets the size and the type of the ship, checks if u can place the ship onto the board
                    s2.setType("Battleship");
                    findSizeHP(s2);
                    checkShip(ship2,f,s2);
                }
                //if ship is false then the ship is placed
                else
                {
                    cout << "You've already placed that ship" << endl;
                }
                break;
                //etc...
            case 'C':
            case 'c':
                if(ship3)
                {
                    s3.setType("Cruiser");
                    findSizeHP(s3);
                    checkShip(ship3,f,s3);
                }
                else
                {
                    cout << "You've already placed that ship" << endl;
                }
                break;
            case 'D':
            case 'd':
                if(ship4)
                {
                    s4.setType("Submarine");
                    findSizeHP(s4);
                    checkShip(ship4,f,s4);
                }
                else
                {
                    cout << "You've already placed that ship" << endl;
                }
                break;
            case 'E':
            case 'e':
                if(ship5)
                {
                    s5.setType("Destroyer");
                    findSizeHP(s5);
                    checkShip(ship5,f,s5);
                }
                else
                {
                    cout << "You've already placed that ship" << endl;
                }
                break;
            default:
                cout <<"sorry wrong choice" << endl;
        }
        //if all ships equal to false then all the ship have been placed
        if(!ship1 && !ship2 && !ship3 && !ship4 && !ship5)
        {
            cout << "You have placed all of the ships" << endl;
            break;
        }
    }
}
//takes in input from the user to set up the new ship
void checkShip(bool &ship, field &f, Ships &s)
{
    char X, dir;
    int placeX;
    int placeY;
    //if ships is true then continue placing the ships
    if(ship) {
        //takes in user input for x
        cout << "Where would you like to place it?" << endl;
        cout << "X(use letters A-J):" << endl;
        cin >> X;
        //converts x char into int
        placeX = convert(X);

        //takes in user input for y
        string input;
        while (true) {
            cout << "Enter Y(from 1-10): "<<endl;
            cin >> input;

            // This code converts from string to number safely.
            stringstream myStream(input);
            if (myStream >> placeY)
                break;
            cout << "That is not a number, please try again" << endl;
        }
        //sets the x and y of the ship
        s.setPlace(placeX, placeY);

        //takes in direction of the ship
        cout << "In what direction? h/v" << endl;
        cin >> dir;
        s.setDir(dir);

        //if the direction is h and the size and x are not bigger than 10 then proceed to placing the ship
        if (dir == 'h') {
            if (s.getX() + s.getSize() - 1 <= 10) {
                if (f.addShip(s)) {
                    f.print();
                    //if was successful make that ship false and that ship is done
                    ship = false;
                    cout << "Ship added successfully" << endl;
                }
                //if failed to place a ship then you cant place a ship there
                else
                {
                    cout << "You cannot place a ship there, try again" << endl;
                }
            }
            //if the size is bigger then the  board then you cant place a ship there
            else
            {
                cout << "You cannot place a ship there, its outside of the board" << endl;
            }
        }
        //if it direction if the ship is vertical
        else if(dir == 'v')
        {
            //if size and y bigger than 10
            if (s.getY() + s.getSize() - 1 <= 10)
            {
                //if didn't fail then, print out the board and make print equal to false
                if (f.addShip(s)) {
                    f.print();
                    ship = false;
                    cout << "Ship added successfully" << endl;
                }
                //if didnt place then say place ship again
                else
                {
                    cout << "You cannot place a ship there, try again" << endl;
                }
            } else {
                cout << "You cannot place a ship there, its outside of the board" << endl;
            }

        }
    }
    else
            cout << "You've already placed that ship" << endl;
}
//launches the main shooting part of the game
int playGame(Ships s1,Ships s2,Ships s3,Ships s4,Ships s5,
             Ships cs1,Ships cs2,Ships cs3,Ships cs4,Ships cs5)
{
    char x =0;
    int y=0;
    bool playGame = true;
    field shoot;
    int p1=0,p2=0,p3=0,p4=0,p5=0;
    int q1=0,q2=0,q3=0,q4=0,q5=0;

    //variables to memorize the spot that hit the ship for the ai
    int shotX=0;
    int shotY=0;

    bool hit = false;

    bool AIShot= false;
    int added_To_Xplace=0;

    //prints out ready to play and launches game
    cout << endl<<endl<<"You are ready to play!"<<endl;
    //while bool game is true
    while (playGame)
    {
        bool shot = false;

        //prints out both of the user boards
        cout << endl <<"Board thats being shot at"<<endl;
        shoot.print();
        cout << "Player board" << endl;
        f.print();
        //while bool shot is not true keep on shooting
        while(!shot)
        {
            //takes in user input for the location of the shot
            cout << "Enter X(from A-J)(or Q to exit): "<<endl;
            cin >> x;
            //if user puts in q then quit the game
            if((x=='Q') || (x=='q'))
            {
                cout << "Thank you for playing the game!" <<endl;
                cout << "Computer Ships: "<<endl;
                f1.print();
                return 0;
            }
            //convert users character to int to be placed on the board
            int placeX = convert(x);

            //asks for y input
            string input;
            //checks that you really input int for the y
            //found on Stack overflow
            while (true) {
                cout << "Enter Y: "<<endl;
                cin >> input;

                // This code converts from string to number safely.
                stringstream myStream(input);
                if (myStream >> y)
                    break;
                cout << "That is not an int, please try again" << endl;
            }
            //if the user input can fit onto the board then shoot your shot
            if((placeX<=10) && (placeX>=1) && (y<=10) && (y>=1))
            {
                shot = shoot.playerShoot(placeX,y,f1);
            }
            //if its not print ont you've entered the wrong coordinates and ask for input again
            else
            {
                cout << "You have entered the wrong coordinates" << endl;
            }
        }
        //if the ai did not hit then shoot randomly
        if(!hit)
        {
            aIShot(hit, shotX, shotY);
        }
        //if the ai did hit then look for the spots near it
        else
        {
               aIShotHit(shotX,shotY,hit,AIShot,added_To_Xplace);
        }

        //check player hp on his ships
        CountHP(s1,p1,f);
        CountHP(s2,p2,f);
        CountHP(s3,p3,f);
        CountHP(s4,p4,f);
        CountHP(s5,p5,f);

        //check ai hp on its ships
        CountHP(cs1,q1,f1);
        CountHP(cs2,q2,f1);
        CountHP(cs3,q3,f1);
        CountHP(cs4,q4,f1);
        CountHP(cs5,q5,f1);

        //if one of the ai ships doesnt have hp print that out
        checkAIHP(cs1,cs2,cs3,cs4,cs5);

        //print out user hp
        printHP(s1,s2,s3,s4,s5);

        //if all of the users hp for ships are 0 then the user lost
        if((s1.getHP()==0)&&(s2.getHP()==0)&&(s3.getHP()==0)&&(s4.getHP()==0)&&(s5.getHP()==0))
        {
            cout <<"YOU LOST!!!!"<< endl;
            playGame = false;
        }
        //if all of the computer hp are 0 then ai lost
        if((cs1.getHP()==0)&&(cs2.getHP()==0)&&(cs3.getHP()==0)&&(cs4.getHP()==0)&&(cs5.getHP()==0))
        {
            cout <<endl <<"YOU WON!! GOOD JOB!!"<< endl;
            playGame = false;
        }
    }
}

//randomly takes a shot at the board
void aIShot(bool &hit,int &shotX,int &shotY)
{
    int x=0;
    int y=0;
    bool ai = true;
    //untill you have a solid shot keep on shooting
    while(ai)
    {
        //randomizes x and y that are used to shoot
        x=rand()%10+1;
        y=rand()%10+1;
        //shoots
        ai=f.AIShoot(x-1,y-1,hit);
    }
    //if the ai hit a ship store that ship coordinate
    if(hit)
    {
        shotX = x;
        shotY = y;
    }
}

//if the ai hit a ship then this function is called next and is the one that continues shooting and looking for
    //more ships
    //right now only the right and the left side for that woorks
void aIShotHit(int &shotX, int &shotY, bool &hit, bool &AIShot,int &added_To_Xplace)
{
    //if the saved coordinates are on the board, and the next coordinate to the right has not been shot yet
        if (((shotX - 1 < 10) && (f.getItem(shotY-1, shotX) != 'X') && (f.getItem(shotY-1, shotX) != 'o')) ||
                ((shotX - 2 > 0) && (f.getItem(shotY-1, shotX-2) != 'X') && (f.getItem(shotY-1, shotX - 2) != 'o')))
        {
            //if you cannot shoot right then try shooting left
            if ((shotX - 2 > 0) && (f.getItem(shotY, shotX - 2) != 'X') && (f.getItem(shotY, shotX - 2) != 'o') && (AIShot))
            {
                AIShot = f.AIShoot(shotX - 2, shotY - 1, hit);
                //same as the x+1
                if (hit) {
                    shotX = shotX - 1;
                }
                //if you cannot shoot left either then shoot randomly onto the board
                else if(AIShot)
                {
                    aIShot(hit,shotX,shotY);
                    added_To_Xplace =0;
                }
            }
            else//then shoot that coordinate
            {
                AIShot = f.AIShoot(shotX, shotY - 1, hit);
                //if that coordinate was hit, then make x bigger to shot at the nxt spot
                if (hit) {
                    shotX = shotX + 1;
                    added_To_Xplace++;
                }
            }
        }
        //if the coordinates are outside of the board or you cannot shoot there, then shoot randomly onto the board
        else
        {
            hit = false;
            aIShot(hit,shotX,shotY);
        }
}
//prints out player Ship Health Percentage
void printHP(Ships s,Ships s2,Ships s3,Ships s4, Ships s5)
{
    //if ships hp is not 0 then print out how much hp it has
    if(s.getHP()<=0)
    {
        cout <<s.getType()<<" is destroyed! ";
    }
    //if ships hp is zero, then print its name and say that is destroyed
    else
        cout << s.getType()<< ": "<<s.getHP()<<"/"<<s.getSize()<<", ";
    //same for the rest of the lines in this function
    if(s2.getHP()<=0)
    {
        cout <<s2.getType()<<" is destroyed! ";
    }
    else
        cout << s2.getType()<< ": "<<s2.getHP()<<"/"<<s2.getSize()<< ", ";
    if(s3.getHP()<=0)
    {
        cout <<s3.getType()<<" is destroyed! ";
    }
    else
        cout << s3.getType()<< ": "<<s3.getHP()<<"/"<<s3.getSize() << ", ";
    if(s4.getHP()<=0)
    {
        cout <<s4.getType()<<" is destroyed! ";
    }
    else
        cout << s4.getType()<< ": "<<s4.getHP()<<"/"<<s4.getSize()<<", ";
    if(s5.getHP()<=0)
    {
        cout <<s5.getType()<<" is destroyed! ";
    }
    else
        cout << s5.getType()<< ": "<<s5.getHP()<<"/"<<s5.getSize()<< " ";
}

//SMALLER FUNCTIONS

//tells the user what ships they have destroyed on the ai's side
void checkAIHP(Ships s,Ships s2,Ships s3,Ships s4, Ships s5)
{
    cout <<"You Destroyed: ";
    if(s.getHP()<=0)
        cout <<" |"<<s.getType()<<"|";
    if(s2.getHP()<=0)
        cout <<" |"<<s2.getType()<<"|";
    if(s3.getHP()<=0)
        cout <<" |"<<s3.getType()<<"|";
    if(s4.getHP()<=0)
        cout <<" |"<<s4.getType()<<"|";
    if(s5.getHP()<=0)
        cout <<" |"<<s5.getType()<<"|";
    cout << endl;
}
//converts user X char into int
int convert(char i)
{
    if((i == 'a')||(i == 'A')) //a
        i = 1;
    if((i == 'b')||(i=='B')) //b
        i = 2;
    if((i == 'c')||(i=='C')) //c
        i = 3;
    if((i == 'd')||(i=='D')) //d
        i = 4;
    if((i == 'e')||(i=='E')) //e
        i = 5;
    if((i == 'f')||(i=='F')) //f
        i = 6;
    if((i == 'g')||(i=='G')) //g
        i = 7;
    if((i == 'h')||(i=='H')) //h
        i = 8;
    if((i == 'i')||(i=='I')) //i
        i = 9;
    if((i == 'j')||(i=='J')) //j
        i = 10;
    return i;
}
//finds the size of the boat depending on its type, and sets up its hit points
void findSizeHP(Ships &s)
{
    if(s.getType()=="Carrier")
    {
        s.setSize(5);
        s.setHP(5);
    }
    else if(s.getType()=="Battleship") {
        s.setSize(4);
        s.setHP(4);
    }
    else if(s.getType()=="Cruiser") {
        s.setSize(3);
        s.setHP(3);
    }
    else if(s.getType()=="Submarine") {
        s.setSize(2);
        s.setHP(2);
    }
    else if(s.getType()=="Destroyer") {
        s.setSize(1);
        s.setHP(1);
    }
}
//finds the type of the boat depending on its size
void findType(Ships &s)
{
    if(s.getSize()==5) {
        s.setType("Carrier");
    }
    if(s.getSize()==4) {
        s.setType("Battleship");
    }
    if(s.getSize()==3) {
        s.setType("Cruiser");
    }
    if(s.getSize()==2) {
        s.setType("Submarine");
    }
    if(s.getSize()==1) {
        s.setType("Destroyer");
    }
}
//calls the function ro check if the ship was it
// if it was hit --ShipHp
void CountHP(Ships &s1, int &p1, field o)
{
    if(o.checkIfHit(s1)>p1)
    {
        p1 = o.checkIfHit(s1);
        s1.setHP(s1.getHP()-1);
    }
}