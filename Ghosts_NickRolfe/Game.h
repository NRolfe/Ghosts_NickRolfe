#pragma once

#include "Ghost.h"
#include "Player.h"

class Game
{
public:
	Game();
	~Game();
	bool place_ghost(Player &p, char x, int y, char indicator, char dl);
	void display_board();
	void show_pieces_captured(Player &H, Player &C);
	void create_cap_array();
	void capture();
	bool move(Player &p, char ind, char direction);
	bool evaluate(Player &H, Player &C);

private:
	Ghost** board;
	Ghost** captured;
	int num_captured;
};