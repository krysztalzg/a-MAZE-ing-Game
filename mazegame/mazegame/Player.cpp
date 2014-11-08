#include <string>

#include "Maze.h"
#include "Player.h"

using namespace std;

void Player::processMove(Maze* maze, int move) {
	maze->fields[current->row][current->column].type = ' ';
	if (move == 1) {	//up
		if (maze->fields[current->row - 1][current->column].type == ' ')
			current = &maze->fields[current->row - 1][current->column];
	}
	else if (move == 2) {	//down
		if (maze->fields[current->row + 1][current->column].type == ' ')
			current = &maze->fields[current->row + 1][current->column];
	}
	else if (move == 3) {	//left
		if (maze->fields[current->row][current->column - 1].type == ' ')
			current = &maze->fields[current->row][current->column - 1];
	}
	else if (move == 4) {	//right
		if (maze->fields[current->row][current->column + 1].type == ' ')
			current = &maze->fields[current->row][current->column + 1];
	}
	maze->fields[current->row][current->column].type = '@';
}


Player::Player() {
}


Player::~Player() {
}
