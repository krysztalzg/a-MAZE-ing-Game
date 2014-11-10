#include <string>

#include "Maze.h"
#include "Page.h"
#include "Alcohol.h"
#include "Player.h"

using namespace std;

void Player::processMove(Maze* maze, int move) {
	maze->fields[current->row][current->column].type = ' ';
	if (move == 1) {	//up
		if (maze->fields[current->row - 1][current->column].type != '#') {
			current = &maze->fields[current->row - 1][current->column];
			steps++;
		}
	}
	else if (move == 2) {	//down
		if (maze->fields[current->row + 1][current->column].type != '#') {
			current = &maze->fields[current->row + 1][current->column];
			steps++;
		}
	}
	else if (move == 3) {	//left
		if (maze->fields[current->row][current->column - 1].type != '#') {
			current = &maze->fields[current->row][current->column - 1];
			steps++;
		}
	}
	else if (move == 4) {	//right
		if (maze->fields[current->row][current->column + 1].type != '#') {
			current = &maze->fields[current->row][current->column + 1];
			steps++;
		}
	}
	current->type = '@';
	/*	Collecting page	*/
	if (maze->currentPage->column == current->column && maze->currentPage->row == current->row && !maze->currentPage->collected)
		maze->currentPage->collect(this, maze);
		
	/*{
		/*collectedPages++;
		decreaseFov();								// Picking up page decreases players FOV
		maze->currentPage->collected = true;

		if (collectedPages < maze->amountPages)		// Generating next page if not all got collected
			maze->currentPage = new Page(maze);
		else
			maze->end->type = ' ';					// and opening exit if player collected all pages

		for (int i = 0; i < MSIZE; ++i)				// After picking up page visibility of all fields
			for (int j = 0; j < MSIZE; ++j)			// is cleared
				maze->fields[i][j].seen = false;
	}*/
	/*	Collecting drink	*/
	for (auto drink : maze->drinks) {
		if (drink->column == current->column && drink->row == current->row && !drink->collected)
			drink->collect(this, maze);
		/*{
			collectedDrinks++;
			drink->collected = true;
		}*/
	}
		
}

void Player::setFov(int f) {
	fov = f;
	if (fov == 1)
		fov = 2;
}


Player::Player() {
	fov = MSIZE / 5;
}


Player::~Player() {
}
