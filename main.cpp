//
//  main.cpp
//  Old School Game
//
//  Created by Ade Ogunleye  on 13/02/2017.
//  Copyright © 2017 Ade Ogunleye. All rights reserved.
//


#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;




int main()
//efile being Enemy file
{
    
    string id;
    int xPlace;
    int yPlace;
    
    /*ofstream eFile("EnemyPlaces.txt");
    
    cout << "Enter Player ID, x co ordinate and y co ordinate" << endl;
    cout << "Press CMD+Q to quit";
    
    while(cin >> id >> xPlace >> yPlace) {
        eFile << id << "x and y cordinates" << xPlace << yPlace << endl;
    } */
    
    ifstream eFile;
    eFile.open("EnemyPlaces.txt");
    
    
    //Check for an error
    
    if(eFile.fail()) {
        cerr << "Error, Cannot open file" <<endl;
        exit(1);
        
    }
    
    
    //This while loop reads a file until it reaches the end of that file
    while(eFile >> id >> xPlace >> yPlace) {
        cout << id << " X - Coordinate:" << xPlace << " Y - Coordinate:" << yPlace << endl;
        
    }
    
    
    
    return 0;
}

