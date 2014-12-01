#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

#include "Maze.h"
#include "Page.h"
#include "Alcohol.h"
#include "Player.h"

using namespace std;
using namespace sf;

/* moving player in one of direction if there is no wall*/
void Player::move(Maze* maze, View* camera) {
	float turnTreshold = 15.0f;
	//up
	if ((Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) &&
		((maze->fields[current->row - 1][current->column].type != '#') || ((maze->fields[current->row - 1][current->column].type == '#') &&
		y > maze->fields[current->row - 1][current->column].row * 50.0f + 50.0f))) {
		
		x = maze->fields[current->row][current->column].column * 50.0f;
		y -= speedY;
	}
	
	if ((Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) &&
		((maze->fields[current->row + 1][current->column].type != '#') || ((maze->fields[current->row + 1][current->column].type == '#') &&
		y + 50.0f < maze->fields[current->row + 1][current->column].row * 50.0f))) {

		x = maze->fields[current->row][current->column].column * 50.0f;
		y += speedY;
	}
	
	if ((Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) &&
		((maze->fields[current->row][current->column - 1].type != '#') || ((maze->fields[current->row][current->column - 1].type == '#') &&
		x > maze->fields[current->row][current->column - 1].column * 50.0f + 72.5f))) {

		y = maze->fields[current->row][current->column].row * 50.0f;
		x -= speedX;
	}
	
	if ((Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) &&
		((maze->fields[current->row][current->column + 1].type != '#') || ((maze->fields[current->row][current->column + 1].type == '#') &&
		x + 50.0f < maze->fields[current->row][current->column + 1].column * 50.0f))) {

		y = maze->fields[current->row][current->column].row * 50.0f;
		x += speedX;
	}
	
	for (auto&& rows : make_pair(maze->fields, maze->fields + maze->getSize()))
	for (auto& f : make_pair(rows, rows + maze->getSize()))
	if (f.row * 50.0f >= y && f.row *50.0f + 50.0f <= y + 50.0f && f.column * 50.0f >= x && f.column*50.0f + 50.0f <= x + 50.0f
		&& !(current->row == f.row && current->column == f.column)) {
		current->type = ' ';
		current = &f;
		current->type = '@';
		steps++;
	}
			
	/* Centering camera on player */
	camera->setCenter(Vector2f(x + 12.5f, (float)y));

	/* Collecting page	if it was on target tile */
	if (maze->getCurrentPage()->getColumn() == current->column && maze->getCurrentPage()->getRow() == current->row && !maze->getCurrentPage()->getCollected())
		maze->getCurrentPage()->collect(this, maze);

	/* Collecting drink if there was one on target tile */
	for (auto drink : *maze->getDrinks())
		if (drink->getColumn() == current->column && drink->getRow() == current->row && !drink->getCollected())
			drink->collect(this, maze);
}



/* simple player serialization */
void Player::savePlayer(ofstream* ofs) {
	ofs->write((char*)&steps, sizeof(int));
	ofs->write((char*)&fov, sizeof(int));
	ofs->write((char*)&x, sizeof(int));
	ofs->write((char*)&y, sizeof(int));
	ofs->write((char*)&collectedPages, sizeof(int));

	ofs->write((char*)&current->row, sizeof(int));
	ofs->write((char*)&current->column, sizeof(int));
	ofs->write((char*)&current->steps, sizeof(int));
	ofs->write((char*)&current->type, sizeof(char));
	ofs->write((char*)&current->seen, sizeof(bool));

	*ofs << sizeof(collectedDrinks);
	ofs->write((char*)&collectedDrinks, sizeof(collectedDrinks));
}

/* simple player deserialization */
void Player::loadPlayer(ifstream* ifs) {
	streamsize size;
	
	ifs->read((char*)&steps, sizeof(int));
	ifs->read((char*)&fov, sizeof(int));
	ifs->read((char*)&x, sizeof(int));
	ifs->read((char*)&y, sizeof(int));
	ifs->read((char*)&collectedPages, sizeof(int));

	ifs->read((char*)&current->row, sizeof(int));
	ifs->read((char*)&current->column, sizeof(int));
	ifs->read((char*)&current->steps, sizeof(int));
	ifs->read((char*)&current->type, sizeof(char));
	ifs->read((char*)&current->seen, sizeof(bool));

	*ifs >> size;
	ifs->read((char*)&collectedDrinks, size);
}


void Player::setFov(int f) {
	fov = f;
	if (fov == 1)
		fov = 2;
}

/* creating player on starting field with calculated field of view */
Player::Player(Field* start, int size) {
	current = start;
	start->type = '@';

	x = start->column * 50.0f;
	y = start->row * 50.0f;

	speedX = 5;
	speedY = 5;

	fov = size / 5;
	if (fov < 2) fov = 2;
}

float Player::getX() {
	return x;
}

float Player::getY() {
	return y;
}

void Player::setX(float _x) {
	x = _x;
}

void Player::setY(float _y) {
	y = _y;
}

Player::~Player() {
}

int Player::getSteps() {
	return steps;
}

int Player::getFov() {
	return fov;
}

int Player::getCollectedPages() {
	return collectedPages;
}

void Player::setCollectedPages() {
	collectedPages++;
}

vector <Alcohol*> *Player::getCollectedDrinks() {
	return &collectedDrinks;
}

Field* Player::getCurrent() {
	return current;
}