#include "Maze.h"
#include "Page.h"
#include "Alcohol.h"
#include "Player.h"


Alcohol::Alcohol(Maze* maze) {
	int r, col;
	do {
		r = rand() % MSIZE;
		col = rand() % MSIZE;
		for (auto drink : maze->drinks) {
			if ((drink->column == col && drink->row == r) || (maze->currentPage->column == col && maze->currentPage->row == r)) {
				col = r = 0;
				break;
			}
		}
	} while (maze->fields[r][col].type != ' ');
	column = col;
	row = r;
	collected = false;
}

void Alcohol::collect(Player* player, Maze* maze) {
	player->collectedDrinks.push_back(this);
	this->collected = true;
}

void Alcohol::drink(Player* player, Maze* maze) {
	player->setFov(player->fov + 1);
	maze->amountDrinks--;
}

Alcohol::~Alcohol() {}
