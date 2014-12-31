#pragma once
#include"Player.h"

class Ghost
{
public:
	Ghost();
	Ghost(int p, int g, int c);
	~Ghost();
	void place(Player p, int x, int y, char ge, char dl);
	bool placed();
	void whiteout();
	void move(int x, int y);
	void display_ghost();
	void display_goodevil();
	void display_player();
	string get_player();
	bool goodevil();
	bool captured();
	void capture();
	int get_row();
	int get_col();
	char get_ind();  
	void display_me();
	Ghost operator = (Ghost &otherGhost);

private:
	bool isGoodEvil; //three states. good, evil
	int x_pos;
	int y_pos;
	bool isPlaced;
	bool isCaptured;
	char display;
	char darklight;
	Player owner;
	
};

