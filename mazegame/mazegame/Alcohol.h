#pragma once
#include "Item.h"

class Maze;
struct Field;

class Alcohol :	public Item {
private:
	int texNo;
public:
	void collect(Player*, Maze*);
	void drink(Player*, Maze*);

	int getTexNo();

	Alcohol(Maze*);
	virtual ~Alcohol();
};

