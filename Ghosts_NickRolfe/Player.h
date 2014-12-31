#pragma once

#include <string>

using namespace std;

class Player
{
public:
	Player();
	Player(string name, char type);
	~Player();
	void display_name();
	string getName();
	char getType();
	void display_me();
	void capture(bool ge);
	void setWin();
	bool getWin();
	int getCaptured();
	int getGood();
	int getEvil();
	Player operator = (Player &otherPlayer);

private:
	string name;
	bool win;
	int num_captured;
	int num_evil;
	int num_good;
	char playerType;
};
