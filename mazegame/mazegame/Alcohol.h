#pragma once
#include "Item.h"

class Maze;

class Alcohol :	public Item {
public:
	void collect(Player*, Maze*);
	void drink(Player*, Maze*);

	Alcohol(Maze* maze);
	virtual ~Alcohol();
};

