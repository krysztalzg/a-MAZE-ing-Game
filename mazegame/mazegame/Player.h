#pragma once
#include "Maze.h"

class Player {
public:
	int steps;
	Field* current;

	void processMove(Maze*, int);

	Player();
	~Player();
};

