#include "Maze.h"
#include "Page.h"
#include "Player.h"

void Page::collect(Player* player, Maze* maze) {
	player->setCollectedPages();
	player->setFov(player->getFov() - 1);							// Picking up page decreases players FOV
	maze->getCurrentPage()->setCollected(true);

	if (player->getCollectedPages() < maze->getAmountPages())		// Generating next page if not all got collected
		maze->setCurrentPage(new Page(maze,player->getCurrent()));
	else
		maze->getEnd()->type = ' ';									// and opening exit if player collected all pages

	for (int i = 0; i < MSIZE; ++i)									// After picking up page, 
		for (int j = 0; j < MSIZE; ++j)								// visibility of all fields is reseted
			if (i != 0 && i != MSIZE - 1 && j != 0 && j != MSIZE - 1)
			maze->fields[i][j].seen = false;

			maze->getEnd()->seen = false;
}


Page::Page(Maze* maze, Field* playerField) {
	Field* temp;
	
	/* setting potion tile to random empty one */
	do				
		temp = &maze->fields[rand() % MSIZE][rand() % MSIZE];
	while (temp->type != ' ' || temp == playerField);
	
	/* setting starting values */
	setRow(temp->row);
	setColumn(temp->column);
	setCollected(false);
}


Page::~Page() {}
