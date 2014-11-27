#pragma once
#include "Maze.h"
#include <fstream>
#include <SFML\Graphics.hpp>

class Alcohol;
struct Field;

class Player {
private:
	int steps, fov;
	int speedX, speedY;
	int x, y;
	int collectedPages;

	Field* current;
	vector <Alcohol*> collectedDrinks;

public:
	int getSteps();
	int getFov();
	void setFov(int);

	int getSpeedX();
	int getSpeedY();
	int getY();
	int getX();
	void setSpeedX(int);
	void setSpeedY(int);
	void setX(int);
	void setY(int);

	int getCollectedPages();
	void setCollectedPages();
	vector <Alcohol*> *getCollectedDrinks();
	
	Field* getCurrent();
	//void setCurrent(Field*);

	void processMove(Maze*, int, sf::View*);
	void move(Maze*, sf::View*);
	void move2(Maze*, sf::View*);

	void savePlayer(ofstream*);
	void loadPlayer(ifstream*);

	Player(Field*);
	~Player();
};

