//Artsiom Skarakhod
//4/8/2019
//Extra Credit
#include "field.h"
#include "functions.h"
#include "Ships.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
int main() {
        bool menu = true;
        bool menu2 = true;
        char choice;
        char choice2;
        Ships s1, s2, s3, s4, s5, cs1, cs2, cs3, cs4, cs5;
        bool status1 = true, status2 = true, status3 = true, status4 = true, status5 = true;
        int boat = 0;
        int i = 5;

        //while menu is true
        while (menu) {
            //print out the options and take in user's choice
            cout << "Welcome to the battleships!" << endl;
            cout << "A. Start game" << endl;
            cout << "B. quit game" << endl;

            try {
            cin >> choice;
                switch (choice) {
                    case 'A':
                    case 'a':
                        //choice a starts game an launches 2nd menu
                        while (menu2) {
                            cout << "A. pick your own positions" << endl;
                            cout << "B. read in from a file" << endl;
                            cout << "C. exit " << endl;
                            cin >> choice2;
                            //if picked a you pick ships locations yourself
                            //if pick be read it ship info from a file
                            //if pick c exit
                            switch (choice2) {
                                case 'A':
                                case 'a':
                                    cout << "Lets start it up!" << endl;
                                    //lets the user put down his own ships
                                    start(s1, s2, s3, s4, s5);
                                    //randomizes 5 enemy ships with different size and parameters
                                    ran(cs1, i);
                                    ran(cs2, i);
                                    ran(cs3, i);
                                    ran(cs4, i);
                                    ran(cs5, i);
                                    playGame(s1, s2, s3, s4, s5,
                                             cs1, cs2, cs3, cs4, cs5);
                                    menu2 = false;
                                    break;

                                case 'B':
                                case 'b':
                                    read();

                                    //puts down 5 ships that are read from a file
                                    putBoats(s1, boat, status1);
                                    putBoats(s2, boat, status2);
                                    putBoats(s3, boat, status3);
                                    putBoats(s4, boat, status4);
                                    putBoats(s5, boat, status5);

                                    //randomizes 5 enemy ships with different size and parameters
                                    ran(cs1, i);
                                    ran(cs2, i);
                                    ran(cs3, i);
                                    ran(cs4, i);
                                    ran(cs5, i);
                                    //launches the game with all 10 ships and ready to play
                                    playGame(s1, s2, s3, s4, s5,
                                             cs1, cs2, cs3, cs4, cs5);
                                    menu2 = false;
                                    break;

                                case 'C':
                                case 'c':
                                    menu2 = false;
                                    choice = false;
                                    break;
                                default:

                                    cout << "That's not an option try again!" << endl;
                                    break;
                            }
                        }
                    case 'B':
                    case 'b':
                        menu = false;
                        break;
                    default:
                        cout << "Wrong option" << endl;
                        break;
                }
            }catch (...)
            {
                cout << "Value cannot be processed"<<endl;
            }
        }
        return 0;

}

