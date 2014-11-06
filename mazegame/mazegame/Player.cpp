#include <string>

#include "Maze.h"
#include "Player.h"

using namespace std;

void Player::processMove(Maze* maze, string move) {
	maze->fields[current->row][current->column].type = ' ';
	if (move == "up") {
		if (maze->fields[current->row - 1][current->column].type == ' ')
			current = &maze->fields[current->row - 1][current->column];
	}
	else if (move == "down") {
		if (maze->fields[current->row + 1][current->column].type == ' ')
			current = &maze->fields[current->row + 1][current->column];
	}
	else if (move == "left") {
		if (maze->fields[current->row][current->column - 1].type == ' ')
			current = &maze->fields[current->row][current->column - 1];
	}
	else if (move == "right") {
		if (maze->fields[current->row][current->column + 1].type == ' ')
			current = &maze->fields[current->row][current->column + 1];
	}
	maze->fields[current->row][current->column].type = '@';
}


Player::Player() {
}


Player::~Player() {
}
