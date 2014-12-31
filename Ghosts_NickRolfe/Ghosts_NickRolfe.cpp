// Nick Rolfe 0278479
//Compiled ~200 times. Took about 14 hours to complete

/*This file contains the game ghosts. Gameplay is described in the darules function below.
First both player and computer will place their good and evil ghosts. You will then take turns
moving your ghosts to acheive a winning board. This is obtained by reaching the top right corner 
of the board with your ghost, capturing all of the other players evil ghosts, or having the opponent capture all of your good ghosts.
have fun.*/

#include "stdafx.h"
#include "Game.h"
#include "Ghost.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <ctime>

using namespace System;
using namespace std;

void placeHuman(Game &g, Player &p);
void placeComputer(Game &g, Player &p);
void humanTurn(Game &g, Player &p);
void comTurn(Game &g, Player &p);
void daRules();

int main(array<System::String ^> ^args)
{
	//Declares necessary variables
	Game game;
	string name;
	char ghost;
	char direction;
	char playAgain = 'Y';
	bool win = false;
	Player com("aDell", 'C');

	cout << "Would you like to play Ghosts? (Y/N)\n";
	cin >> playAgain;

	while (playAgain == 'Y' || playAgain == 'y'){
		cout << "Welcome to Ghosts!! What is your name?\n";
		cin.ignore();
		getline(cin, name);
		Player human(name, 'H');

		//introductions and the rules
		cout << "\nHello ";
		human.display_name();
		cout << "!\n";
		daRules();

		//each player places their ghosts, shows starting board
		game.display_board();
		placeHuman(game, human);
		placeComputer(game, com);
		game.display_board();

		//Begins the game. Human goes first
		while (win == false){
			humanTurn(game, human);
			game.show_pieces_captured(human, com);
			win = game.evaluate(human, com);
			if (win == true){
				cout << human.getName() << " wins!!!\n";
				break;
			}
			comTurn(game, com);
			game.show_pieces_captured(human, com);
			win = game.evaluate(human, com);
			if (win == true){
				cout << com.getName() << " wins!!!\n";
				break;
			}
		}
		cout << "Play Again?? (Y/N)\n";
		cin >> playAgain;
	}
	cout << "Thanks for playing! Goodbye!\n";
	return 0;
}

void placeHuman(Game &g, Player &p)
/*Promts the user to enter coordinates to place ghosts, good followed by evil. 1-4 represent good ghosts and 5-8 represent
bad ghosts. If a user tries to place a ghost out of the 2x4 space designated by the rules the user will be asked to enter a new coordinate.
once all ghosts are placed the funnction will terminate.*/
{
	//Declares variables to store row and column. Also the indicator used in representing which ghost is which
	char row;
	int col;
	char indicator = '1'; //1-4 represent good and 5-8 represent bad
	bool valid;

	cout << p.getName() << " will begin placing ghosts!\n";

	//Places 4 good ghosts. 
	int count = 0;
	while (count < 4){
		cout << "Enter the row (E or F) then the column (2-5) you wish to place a good ghost.\n";
		cin >> row >> col;
		if ((row == 'E' || row == 'e' || row == 'F' || row == 'f') && (col == 2 || col == 3 || col == 4 || col == 5)){
			valid = g.place_ghost(p, row, col, indicator, 'G');
			if (valid){
				g.display_board();
				indicator++;
				count++;
			}
			if (valid == false)
				cout << "INVALID SPACE!! Try again.\n";
		}
		else
			cout << "INVALID SPACE!! Try again.\n";
	}

	//Places four evil ghosts
	count = 0;
	while (count < 4){
		cout << "Enter the row (E or F) then the column (2-5) you wish to place a evil ghost.\n";
		cin >> row >> col;
		if ((row == 'E' || row == 'e' || row == 'F' || row == 'f') && (col == 2 || col == 3 || col == 4 || col == 5)){
			valid = g.place_ghost(p, row, col, indicator, 'E');
			if (valid){
				g.display_board();
				indicator++;
				count++;
			}
			if (valid == false)
				cout << "INVALID SPACE!! Try again.\n";
		}
		else
			cout << "INVALID SPACE!! Try again.\n";
	}
}

void placeComputer(Game &g, Player &p)
{
	//Declares variables to store row and column. Also the indicator used in representing which ghost is which
	char row;
	int row_num;
	int col;
	char indicator = 'A'; //1-4 represent good and 5-8 represent bad
	bool valid;

	cout << p.getName() << " will begin placing ghosts!\n";

	//Places 4 good ghosts. 
	int count = 0;
	srand(static_cast<unsigned int>(time(0)));
	while (count < 4){
		row_num = rand() % 2;
		if (row_num == 0)
			row = 'A';
		if (row_num == 1)
			row = 'B';
		col = rand() % 4;
		col += 2;
		if ((row == 'A' || row == 'B') && (col == 2 || col == 3 || col == 4 || col == 5)){
			valid = g.place_ghost(p, row, col, indicator, 'G');
			if (valid){
				indicator++;
				count++;
			}
		}
	}

	//Places four evil ghosts
	count = 0;
	srand(static_cast<unsigned int>(time(0)));
	while (count < 4){
		row_num = rand() % 2;
		if (row_num == 0)
			row = 'A';
		if (row_num == 1)
			row = 'B';
		col = rand() % 4;
		col += 2;
		if ((row == 'A' || row == 'B') && (col == 2 || col == 3 || col == 4 || col == 5)){
			valid = g.place_ghost(p, row, col, indicator, 'E');
			if (valid){
				indicator++;
				count++;
			}
		}
	}
}

void humanTurn(Game &g, Player &p)
{
	bool valid = false;
	char ind, direction;

	//While loop runs until a legal move is made
	while (valid == false){
		cout << "Which ghost would you like to move? (1-8) \n";
		cin >> ind;
		cout << "What direction would you like to move?\n";
		cin >> direction;
		valid = g.move(p, ind, direction);
		if (valid == false)
			cout << "INVALID MOVE!! Try again!\n";
	}
	g.display_board();
}

void comTurn(Game &g, Player &p)
{
	bool valid = false;
	char ind, direction;
	int indNum, dirNum; //for converting randomly generated number to letter

	//randomly generate ghost and piece to move
	srand(static_cast<unsigned int>(time(0)));
	while (valid == false){
		
		//this block changes randomly generated nnumber to the corresponding char
		indNum = rand() % 8;
		if (indNum == 0)
			ind = 'A';
		if (indNum == 1)
			ind = 'B';
		if (indNum == 2)
			ind = 'C';
		if (indNum == 3)
			ind = 'D';
		if (indNum == 4)
			ind = 'E';
		if (indNum == 5)
			ind = 'F';
		if (indNum == 6)
			ind = 'G';
		if (indNum == 7)
			ind = 'H';

		//This block converts randomly generated number into corresponding direction
		dirNum = rand() % 4;
		if (dirNum == 0)
			direction = 'N';
		if (dirNum == 1)
			direction = 'S';
		if (dirNum == 2)
			direction= 'E';
		if (dirNum == 3)
			direction = 'W';

		valid = g.move(p, ind, direction);
	}
	g.display_board();
}

void daRules()
{
	cout << "********************************************************************************\n";
	cout << "The rules of this game are quite simple. You will start by placing 4 good and 4 bad ghosts on the board.\n";
	cout << "These 8 ghosts must be placed only in rows E and F between columns 2 and 5! \nYou'll move them once the game starts.\n";
	cout << "Once the game has started you will be able to chose one ghost per turn and move it one space.\n";
	cout << "Once you have selected a ghost to move you will be asked which direction it is \ngoing, these directions are North, South, East and West!\n";
	cout << "You can 'capture' the opponents ghosts by moving onto the space they occupy. Just don't try to move into a space occupied by one of your own ghosts!\n";
	cout << "Two win one of your good ghosts must make it to the top right corner of the map \nOR you must capture all of the opponents evil ghosts \nOR the opponent must capture all of your good ghosts!\n";
	cout << "Lets Play!\n\n";
	cout << "********************************************************************************\n\n";
}