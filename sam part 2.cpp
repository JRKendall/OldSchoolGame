#include <iostream>
#include "windows.h"

using namespace std;

int option;

int main()
{
	cout << "\n" << endl;
	cout << "                            (^_^)MAIN MENU(^_^)" << endl;
	cout << "\n" << endl;
	cout << "\n" << endl;
	cout << "                            Option 1- Start Game" << endl;
	cout << "\n" << endl; // used this to cleverly create spaces between the options
	cout << "                            Option 2- Information" << endl;
	cout << "\n" << endl;
	cout << "                            Option 3- Controls" << endl; // control scheme
	cout << "\n" << endl;
	cout << "                            Option 4- Quit" << endl; //exits the programme when selected
	cout << "\n" << endl;
	cout << "\n" << endl;
	cout << "          press numbers 1 to 4 depending on what option you want :)" << endl;
	// Shows all the conditional statements that can be run
	cin >> option;

	if (option == 1)
	{
		system("cls"); // this links to the game and starts it.
		cout << "The game will load up in a moment....." << endl;
		system("pause");
		return 0;


	}
	if (option == 2)
	{
		system("cls"); //information about the design of the game can be found by preesing 2 and then enter
		cout << "This game was created by a group of students at coventry university\nThe game is an rpg style game that took inspirtation from titles such as Zelda and Mario" << endl;
		cout << "Samuel was responsible for the creation of the menu as well as the initial draft for the game." << endl;
		cout << " Ade created enemy places and classes" << endl;
		cout << " Shayan helped implement the menu in the game" << endl;
		cout << "Jordan was responsible for the map creation as well as movement in the game" << endl;
		cout << "Josh oversaw the game in and contributed to various aspects" endl;
		system("pause");
		return 0;

	}
	if(option == 3)
	{
		system("cls");
		cout << "The controls" << endl;
		cout << "WASD for up, left, down and right respectively " << endl;
		cout << "5,3,1 are used to attack" << endl;
		system("pause"); // pauses the screen until another key is pressed in which case the programme closes
		return 0;


	}

	if (option == 4) // closes the window if this conditional is met
	{
		return 0;
	}
	else
	{
		cout << "Incorrect Number, please try again"<<endl; //if the conditional statements are not met then this piece of code is executed
		system("pause");
		return 0;
	}

}
