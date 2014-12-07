#pragma once
#include "Maze.h"
#include <fstream>
#include <SFML/Graphics.hpp>

class Alcohol;
struct Field;

class Player {
private:
	int steps, fov;
	float x, y;
	int collectedPages;

	Field* current;
	vector <Alcohol*> collectedDrinks;

public:
	int  getSteps();
	int  getFov();
	void setFov(int);

	float getY();
	float getX();
	void  setX(float);
	void  setY(float);

	int    getCollectedPages();
	void   setCollectedPages();
	vector <Alcohol*> *getCollectedDrinks();

	Field* getCurrent();

	void move(Maze*, sf::View*);

	void savePlayer(ofstream*);
	void loadPlayer(ifstream*);

	Player(Field*, int);
	~Player();
};

