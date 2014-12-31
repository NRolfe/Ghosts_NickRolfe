#include "stdafx.h"
#include "Game.h"
#include "Ghost.h"
#include "Player.h"
#include <iostream>
#include <string>

using namespace std;

Game::Game()
/*Default constructor creates a 6x6 array of ghost objects. A second 2x8 array of ghosts is created in this constructor to house
the ghosts captured.*/
{
	captured = 0;
	//Game board is created with 'blank' ghosts
	board = new Ghost*[6];
	for (int i = 0; i < 6; i++)
		board[i] = new Ghost[6];

	captured = new Ghost*[2];
	for (int j = 0; j < 8; j++)
		captured[j] = new Ghost[8];
}

Game::~Game()
{
	for (int i = 0; i < 6; i++)
		delete[] this->board[i];
	delete[] this->board;
}

void Game::display_board()
{
	char row = 'A';
	for (int i = 0; i < 6; i++){
		cout << row << "| ";
		for (int j = 0; j < 6; j++){
			board[i][j].display_ghost();
		}
		cout << endl;
		row++;
	}

	for (int j = 0; j < 7; j++){
		if (j == 0){
			cout << "   ";
		}
		else {
			cout << j << " ";
		}
	}
	cout << endl << endl;
}

bool Game::place_ghost(Player &p, char x, int y, char indicator, char dl)
{
	int row;
	int col = y - 1;
	bool occupied;

	//Converts converts char column indicator to corresponding array index 
	if (x == 'A' || x == 'a')
		row = 0;
	if (x == 'B' || x == 'b')
		row = 1;
	if (x == 'C' || x == 'c')
		row = 2;
	if (x == 'D' || x == 'd')
		row = 3;
	if (x == 'E' || x == 'e')
		row = 4;
	if (x == 'F' || x == 'f')
		row = 5;

	//Checks to see if space is occupied
	occupied = board[row][col].placed();

	//places ghost in location specified
	if (occupied == false){
		board[row][col].place(p, row, col, indicator, dl);
		return true;
	}
	else {
		return false;
	}
}

void Game::show_pieces_captured(Player &H, Player &C)
{
	cout << H.getName() << " |";
	for (int i = 0; i < 8; i++){
		cout << " ";
		captured[0][i].display_goodevil();
	}
	cout << endl << C.getName() << " |";
	for (int j = 0; j < 8; j++){
		cout << " ";
		captured[1][j].display_goodevil();
	}
	cout << endl << endl;
}

bool Game::move(Player &p, char indicator, char direction)
{
	int row, col;

	//Loop searches for indicator in arra and sets row and col to the row and col of the ghost which was found
	for (int i = 0; i < 6; i++){
		for (int j = 0; j < 6; j++){
			if (indicator == board[i][j].get_ind()){
				row = board[i][j].get_row();
				col = board[i][j].get_col();
			}
			if (row != 0 && col != 0)
				break;
		}
		if (row != 0 && col != 0)
			break;
	}

	//declares row and column for where the ghost will move to
	int new_row;
	int new_col;

	//depending on direction 1 will be added or subtracted from row or col. row-1 for north, row +1 south, col-1 for west, col+1 for east
	//This new value is given to new row or new col
	if (direction == 'N' || direction == 'n'){
		new_row = row - 1;
		new_col = col;
	}
	if (direction == 'S' || direction == 's'){
		new_row = row + 1;
		new_col = col;
	}
	if (direction == 'W' || direction == 'w'){
		new_col = col - 1;
		new_row = row;
	}
	if (direction == 'E' || direction == 'e'){
		new_col = col + 1;
		new_row = row;
	}

	if (new_row == 0 && new_col > 5 && p.getType() == 'H'){
		p.setWin();
		return true;
	}
	if (new_row == 6 && new_col < 0 && p.getType() == 'C'){
		p.setWin();
		return true;
	}
	if (new_row < 0 || new_row > 5 || new_col < 0 || new_col > 5){
		return false;
	}

	/*Error checking, capture, and actual movement*/
	if (board[new_row][new_col].placed() && (board[new_row][new_col].get_player() == board[row][col].get_player()))
		return false;
	if (board[new_row][new_col].placed() && (board[new_row][new_col].get_player() != board[row][col].get_player())){
		if (p.getType() == 'H'){
			//Increments correct capture data members and changes the capture bool in ghost to true. And put the captured ghost in the captured array
			captured[0][p.getCaptured()] = board[new_row][new_col];
			captured[0][p.getCaptured()].capture();
			p.capture(board[new_row][new_col].goodevil());

			//Change the old ghost to the new ghost like it is a noral blank spot. then whites out the spot your ghost was previously
			board[new_row][new_col] = board[row][col];
			board[new_row][new_col].move(new_row, new_col);
			board[row][col].whiteout();

		}
		if (p.getType() == 'C'){
			//Increments correct capture data members and changes the capture bool in ghost to true. And put the captured ghost in the captured array
			captured[1][p.getCaptured()] = board[new_row][new_col];
			captured[1][p.getCaptured()].capture();
			p.capture(board[new_row][new_col].goodevil());

			//Change the old ghost to the new ghost like it is a noral blank spot. then whites out the spot your ghost was previously
			board[new_row][new_col] = board[row][col];
			board[new_row][new_col].move(new_row, new_col);
			board[row][col].whiteout();
		}
		return true;
	}
	else{
		board[new_row][new_col] = board[row][col];
		board[new_row][new_col].move(new_row, new_col);
		board[row][col].whiteout();
		return true;
	}
}

bool Game::evaluate(Player &H, Player &C)
//checks all winning combinations and returns true if one is found. 
{
	if (H.getEvil() == 4){
		H.setWin();
		return H.getWin();
	}
	if (C.getGood() == 4){
		H.setWin();
		return H.getWin();
	}
	if (C.getEvil() == 4){
		C.setWin();
		return C.getWin();
	}
	if (H.getGood() == 4){
		C.setWin();
		return C.getWin();
	}

}
