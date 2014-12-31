#include "stdafx.h"
#include "Player.h"
#include <iostream>
#include <string>

using namespace std;

Player::Player()
{
	name = "default";
	playerType = 'H';
	win = false;
	num_captured = 0;
	num_good = 0;
	num_evil = 0;
}

Player::Player(string n, char t)
{
	name = n;
	playerType = t;
	win = false;
	num_captured = 0;
	num_good = 0;
	num_evil = 0;
}

Player::~Player()
{
}

Player Player::operator = (Player &otherPlayer)
{
	name = otherPlayer.name;
	playerType = otherPlayer.playerType;
	return *this;
}

string Player::getName()
{
	return name;
}

void Player::display_name()
{
	cout << name;
}

void Player::capture(bool ge)
{
	num_captured++;
	if (ge == true)
		num_good++;
	else
		num_evil++;
}

int Player::getCaptured()
{
	return num_captured;
}

char Player::getType()
{
	return playerType;
}

void Player::setWin()
{
	win = true;
}

bool Player::getWin()
{
	return win;
}

void Player::display_me()
{
	string type;
	if (playerType == 'H')
		type = "Human";
	if (playerType == 'C')
		type = "Computer";
	cout << "My name is " << name << " and I am a " << type << "!\n";
}

int Player::getGood()
{
	return num_good;
}

int Player::getEvil()
{
	return num_evil;
}