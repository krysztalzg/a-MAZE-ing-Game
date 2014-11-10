#pragma once
#include "Item.h"

class Maze;
class Player;

class Page : public Item {
public:
	void collect(Player*, Maze*);
	Page(Maze*);
	virtual ~Page();
};

