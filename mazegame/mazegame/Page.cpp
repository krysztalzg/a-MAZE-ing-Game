#include "Maze.h"
#include "Page.h"
#include "Player.h"

void Page::collect(Player* player, Maze* maze) {
	player->collectedPages++;
	player->setFov(player->fov - 1);								// Picking up page decreases players FOV
	maze->currentPage->collected = true;

	if (player->collectedPages < maze->amountPages)		// Generating next page if not all got collected
		maze->currentPage = new Page(maze);
	else
		maze->end->type = ' ';					// and opening exit if player collected all pages

	for (int i = 0; i < MSIZE; ++i)				// After picking up page visibility of all fields
		for (int j = 0; j < MSIZE; ++j)			// is cleared
			maze->fields[i][j].seen = false;
}


Page::Page(Maze* maze) {
	Field* temp;

	do
		temp = &maze->fields[rand() % MSIZE][rand() % MSIZE];
	while (temp->type != ' ');

	row = temp->row;
	column = temp->column;
	collected = false;

	maze->currentPage = this;
}


Page::~Page() {}
