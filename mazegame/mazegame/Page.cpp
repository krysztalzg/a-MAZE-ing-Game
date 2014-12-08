#include "Maze.h"
#include "Page.h"
#include "Player.h"

void Page::collect(Player* player, Maze* maze) {
	player->setCollectedPages();
	player->setFov(player->getFov() - 1);							// Picking up page decreases players FOV
	maze->getCurrentPage()->setCollected(true);

	if (player->getCollectedPages() < maze->getAmountPages())		// Generating next page if not all got collected
		maze->setCurrentPage(new Page(maze));
	else
		maze->getEnd()->type = 'E';									// and opening exit if player collected all pages

	for (int i = 0; i < maze->getSize(); ++i)						// After picking up page, 
		for (int j = 0; j < maze->getSize(); ++j)					// visibility of all fields is reseted
			if (i != 0 && i != maze->getSize() - 1 && j != 0 && j != maze->getSize() - 1)
			maze->fields[i][j].seen = false;

			maze->getEnd()->seen = false;
}


Page::Page(Maze* maze) {
	Field* temp;
	/* setting potion tile to random empty one */
	do				
	temp = &maze->fields[rand() % maze->getSize()][rand() % maze->getSize()];
	while (temp->type != ' ');	
	
	/* setting starting values */
	temp->type = 'P';
	setField(temp);
	setCollected(false);
}


Page::~Page() {}
