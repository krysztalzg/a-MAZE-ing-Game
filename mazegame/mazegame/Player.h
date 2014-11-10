#pragma once
#include "Maze.h"
class Alcohol;

class Player {
public:
	int steps, fov;
	int collectedPages;
	vector <Alcohol*> collectedDrinks;
	Field* current;

	void processMove(Maze*, int);
	void setFov(int);

	Player();
	~Player();
};

