#include "Maze.h"
#include "Page.h"
#include "Alcohol.h"
#include "Player.h"


Alcohol::Alcohol(Maze* maze) {
	int r, col;
	texNo = rand() % 8;							//randomizing texture of potion from eight possible
	do {										//setting potion tile to random empty one
		r = rand() % MSIZE;
		col = rand() % MSIZE;
		for (auto drink : *maze->getDrinks()) {
			if ((drink->getColumn() == col && drink->getRow() == r) || (maze->getCurrentPage()->getColumn() == col && maze->getCurrentPage()->getRow() == r)) {
				col = r = 0;
				break;
			}
		}
	} while (maze->fields[r][col].type != ' '); 

	maze->fields[r][col].type = 'D';
	setColumn(col);								//setting starting values
	setRow(r);
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
