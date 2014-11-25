#pragma once
#include "Item.h"

class Maze;

class Alcohol :	public Item {
private:
	int texNo;
public:
	void collect(Player*, Maze*);
	void drink(Player*, Maze*);

	int getTexNo();

	Alcohol(Maze* maze);
	virtual ~Alcohol();
};

