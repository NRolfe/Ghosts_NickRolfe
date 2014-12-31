#include "stdafx.h"
#include "Ghost.h"
#include "Player.h"
#include <iostream>

using namespace std;

Ghost::Ghost()
{
	isGoodEvil = 0;			//0 = null (for blank ghost), 1 = good, 2 = evil
	x_pos = 0;
	y_pos = 0;
	display = '-';
	isPlaced = false;
}

Ghost::~Ghost()
{
}

Ghost Ghost::operator=(Ghost &otherGhost)
{
	isPlaced = otherGhost.isPlaced;
	display = otherGhost.display;
	isCaptured = otherGhost.isCaptured;
	darklight = otherGhost.darklight;
	isGoodEvil = otherGhost.isGoodEvil;
	owner = otherGhost.owner;
	return *this;
}

void Ghost::display_ghost()
//displays blank spot for a blank ghost. OR ghosts indicating number
{
	if (isPlaced)
		cout << display << " ";
	else
		cout << "- ";
}

void Ghost::place(Player p, int x, int y, char ge, char dl)
//changes members to match position and show it has been placed
{
	owner = p;
	x_pos = x;
	y_pos = y;
	display = ge;
	isPlaced = true;
	darklight = dl;
	if (dl == 'G')
		isGoodEvil = true;
	else
		isGoodEvil = false;

}

bool Ghost::placed()
{
	return isPlaced;
}

void Ghost::whiteout()
{
	display = '-';
	isPlaced = false;
	isCaptured = false;
}

void Ghost::display_goodevil()
{
	cout << darklight;
}

void Ghost::display_player()
{
	owner.display_name();
}

string Ghost::get_player()
{
	return owner.getName();
}

bool Ghost::goodevil()
{
	return isGoodEvil;
}

bool Ghost::captured()
{
	return isCaptured;
}

void Ghost::capture()
{
	isCaptured = true;
}

void Ghost::display_me()
{
	cout << "Player: " << owner.getName() << " Captured: " << isCaptured << "Good or Evil? (G for good, E for evil) "
		<< darklight;
}

int Ghost::get_row()
{
	return x_pos;
}

int Ghost::get_col()
{
	return y_pos;
}

char Ghost::get_ind()
{
	return display;
}

void Ghost::move(int x, int y)
{
	x_pos = x;
	y_pos = y;
}
