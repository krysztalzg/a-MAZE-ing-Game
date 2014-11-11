#include <string>

#include "Maze.h"
#include "Page.h"
#include "Alcohol.h"
#include "Player.h"

using namespace std;


void Player::processMove(Maze* maze, int move) {
	if (move == 1) {	//up
		if (maze->fields[current->row - 1][current->column].type != '#') {
			current->row--;
			steps++;
		}
	}
	else if (move == 2) {	//down
		if (maze->fields[current->row + 1][current->column].type != '#') {
			current->row++;
			steps++;
		}
	}
	else if (move == 3) {	//left
		if (maze->fields[current->row][current->column - 1].type != '#') {
			current->column--;
			steps++;
		}
	}
	else if (move == 4) {	//right
		if (maze->fields[current->row][current->column + 1].type != '#') {
			current->column++;
			steps++;
		}
	}

	/*	Collecting page	*/
	if (maze->getCurrentPage()->getColumn() == current->column && maze->getCurrentPage()->getRow() == current->row && !maze->getCurrentPage()->getCollected())
		maze->getCurrentPage()->collect(this, maze);
		
	/*	Collecting drink	*/
	for (auto drink : *maze->getDrinks())
		if (drink->getColumn() == current->column && drink->getRow() == current->row && !drink->getCollected())
			drink->collect(this, maze);
		
}


void Player::savePlayer(ofstream* ofs) {
	ofs->write((char*)&steps, sizeof(int));
	ofs->write((char*)&fov, sizeof(int));
	ofs->write((char*)&collectedPages, sizeof(int));

	ofs->write((char*)&current->row, sizeof(int));
	ofs->write((char*)&current->column, sizeof(int));
	ofs->write((char*)&current->steps, sizeof(int));
	ofs->write((char*)&current->type, sizeof(char));
	ofs->write((char*)&current->seen, sizeof(bool));

	*ofs << sizeof(collectedDrinks);
	ofs->write((char*)&collectedDrinks, sizeof(collectedDrinks));
}

void Player::loadPlayer(ifstream* ifs) {
	streamsize size;
	
	ifs->read((char*)&steps, sizeof(int));
	ifs->read((char*)&fov, sizeof(int));
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


Player::Player() {
	current = new Field();
	fov = MSIZE / 5;
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

void Player::setCurrent(Field* c) {
	current->row = c->row;
	current->column = c->column;
	current->steps = c->steps;
	current->type = c->type;
	current->seen = c->seen;
	current->visited = c->visited;
	current->neighbours = c->neighbours;
}