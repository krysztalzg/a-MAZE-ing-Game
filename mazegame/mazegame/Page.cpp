#include "Maze.h"
#include "Page.h"
#include "Player.h"

void Page::collect(Player* player, Maze* maze) {
	player->setCollectedPages();
	player->setFov(player->getFov() - 1);								// Picking up page decreases players FOV
	maze->getCurrentPage()->setCollected(true);

	if (player->getCollectedPages() < maze->getAmountPages())		// Generating next page if not all got collected
		maze->setCurrentPage(new Page(maze));
	else
		maze->getEnd()->type = ' ';					// and opening exit if player collected all pages

	for (int i = 0; i < MSIZE; ++i)				// After picking up page visibility of all fields
		for (int j = 0; j < MSIZE; ++j)			// is cleared
			maze->fields[i][j].seen = false;
}


Page::Page(Maze* maze) {
	Field* temp;

	do
		temp = &maze->fields[rand() % MSIZE][rand() % MSIZE];
	while (temp->type != ' ');

	setRow(temp->row);
	setColumn(temp->column);
	setCollected(false);
}


Page::~Page() {}
