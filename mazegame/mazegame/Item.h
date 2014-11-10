#pragma once
class Player;
class Maze;

class Item {
public:
	int row, column;
	bool collected;
	virtual void collect(Player*, Maze*) = 0;

	Item();
	virtual ~Item();
};

