#include "Maze.h"
#include "Page.h"
#include "Alcohol.h"
#include "Player.h"


Alcohol::Alcohol(Maze* maze) {
	int r, col;
	texNo = rand() % 8;							//randomizing texture of potion from eight possible
	do {										//setting potion tile to random empty one
		r = rand() % maze->getSize();
		col = rand() % maze->getSize();
	} while (maze->fields[r][col].type != ' '); 

	/* setting starting values */
	maze->fields[r][col].type = 'D';
	setField(&maze->fields[r][col]);
	setCollected(false);
}

/* when potion is collected add it to players collection */
void Alcohol::collect(Player* player, Maze* maze) {
	player->getCollectedDrinks()->push_back(this);
	this->setCollected(true);
}

/* drinking potion increase players field of view */
void Alcohol::drink(Player* player, Maze* maze) {
	player->setFov(player->getFov() + 1);
	maze->setAmountDrinks(maze->getAmountDrinks() - 1);
}


int Alcohol::getTexNo() {
	return texNo;
}

Alcohol::~Alcohol() {}
