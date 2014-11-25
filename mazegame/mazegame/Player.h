#pragma once
#include "Maze.h"
#include <fstream>
#include <SFML\Graphics.hpp>

class Alcohol;

class Player {
private:
	int steps, fov;
	int collectedPages;

	Field* current;
	vector <Alcohol*> collectedDrinks;

public:
	int getSteps();
	int getFov();
	void setFov(int);

	int getCollectedPages();
	void setCollectedPages();
	vector <Alcohol*> *getCollectedDrinks();
	
	Field* getCurrent();
	void setCurrent(Field*);

	void processMove(Maze*, int, sf::View*);

	void savePlayer(ofstream*);
	void loadPlayer(ifstream*);

	Player();
	~Player();
};

