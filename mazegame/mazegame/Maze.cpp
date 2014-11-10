#include <iostream>
#include <vector>
#include <cmath>

#include "Alcohol.h"
#include "Page.h"
#include "Player.h"
#include "Maze.h"

using namespace std;

Maze::Maze() {
	for (int i = 0; i < MSIZE; i++) {
		for (int j = 0; j < MSIZE; j++) {
			if (i == 0 || j == 0 || i == (MSIZE-1) || j == (MSIZE-1))
				fields[i][j].type = '#';
			else if ((i % 2) != 0 && (j % 2) != 0)
				fields[i][j].type = ' ';
			else
				fields[i][j].type = '#';

			fields[i][j].row = i;
			fields[i][j].column = j;
			fields[i][j].visited = false;
		}
	}
	amountDrinks = MSIZE / 5;
	amountPages = MSIZE / 10;
	generateMaze();
	finished = false;
}

void Maze::findNeighbours(Field* field) {
	int col = field->column, row = field->row;

	if (row - 2 >= 0)
	if (fields[row - 2][col].type == ' ' && !fields[row - 2][col].visited)
		field->neighbours.push_back(&fields[row - 2][col]);

	if (row + 2 < MSIZE)
	if (fields[row + 2][col].type == ' ' && !fields[row + 2][col].visited)
		field->neighbours.push_back(&fields[row + 2][col]);

	if (col - 2 >= 0)
	if (fields[row][col-2].type == ' ' && !fields[row][col-2].visited)
		field->neighbours.push_back(&fields[row][col-2]);

	if (col + 2 < MSIZE)
	if (fields[row][col + 2].type == ' ' && !fields[row][col + 2].visited)
		field->neighbours.push_back(&fields[row][col+2]);
}

//void Maze::show(int pCol, int pRow, int pFov) {
void Maze::show(Player* player) {
	bool temp = false;

	system("cls");
	for (auto& rows : fields) {
		for (auto& f : rows) {
			/*if ((abs(player->current->column - f.column) < player->fov && abs(player->current->row - f.row) < player->fov) ||
				(abs(player->current->column - f.column) < player->fov - 1 && abs(player->current->row - f.row) < player->fov + 1) ||
				(abs(player->current->column - f.column) < player->fov + 1 && abs(player->current->row - f.row) < player->fov - 1) ||
				finished || f.seen) */{
			if (currentPage->column == f.column && currentPage->row == f.row && !currentPage->collected)		// displaying page
				cout << '!';
			else {																								
				for (auto drink : drinks)
					if (drink->column == f.column && drink->row == f.row && !drink->collected) {				// if there's drink on field diplay it
						cout << '^';
						temp = true;
						break;
					}
						if (!temp)																				// otherwise display normal field - wall or empty
						cout << f.type;	
						temp = false;
			}

			f.seen = true;
			}
			/*else
			cout << ' ';*/
		}
		/*	Disaplying statiscitcs	*/
		switch (rows[0].row) {
		case 0:
			cout << player->current->row << "  " << player->current->column;
			//cout << "Shortest way: " << end->steps;
			break;
		case 2:
			cout << "Pages: " << player->collectedPages << "/" << amountPages;
			break;
		case 3:
			cout << "'Magic' drinks: " << player->collectedDrinks.size() << "/" << amountDrinks;
			break;
		case 5:
			cout << "Player FOV: " << player->fov << " fields";
			break;
		case 7:
			cout << "Press F to drink (FOV + 1)";
			break;
		}
			cout << endl;
		}

	for (auto drink : drinks)
		cout << drink->row << "-" << drink->column << "-" << drink->collected << " | ";
}

Maze::~Maze(){}


void Maze::generateMaze() {
	Field* current;
	Field* next;
	/*	Finfing starting field	*/
	do
	start = &fields[rand() % MSIZE][rand() % MSIZE];
	while (start->type != ' ');
	start->steps = 0;
	start->visited = true;

	current = start;
	/*	Generating maze with DFS algorithm	*/
	do {
		current->visited = true;
		findNeighbours(current);
		/*	If field have unvisited neighbour, create connection between them	*/
		if (!current->neighbours.empty()) {
			next = current->neighbours[rand() % current->neighbours.size()];
			fields[(current->row + next->row) / 2][(current->column + next->column) / 2].type = ' ';
			fields[(current->row + next->row) / 2][(current->column + next->column) / 2].steps = current->steps + 1;
			next->visited = true;
			next->steps = current->steps + 2;
			path.push_back(current);
			current->neighbours.clear();
			current = next;
		}
		/*	Other way go to previous field	*/
		else if (!path.empty()) {
			current = path.back();
			path.pop_back();
		}
		/*	If you returned to the start field finish generating	*/
		else {
			start->type = '@';
			break;
		}
	} while (true);

	/*	Finding finish field on the edge of maze	*/
	do
		end = &fields[rand() % MSIZE][rand() % MSIZE];
	while (!(end->type == ' ') || !(end->row == 1 || end->column == 1 || end->row == (MSIZE - 2) || end->column == (MSIZE - 2)));
	
	if (end->row == 1) {
		end = &fields[0][end->column];
		end->steps = fields[1][end->column].steps + 1;
	}
	else if (end->row == MSIZE - 2) {
		end = &fields[MSIZE - 1][end->column];
		end->steps = fields[MSIZE - 2][end->column].steps + 1;
	}
	else if (end->column == 1) {
		end = &fields[end->row][0];
		end->steps = fields[end->row][1].steps + 1;
	}
	else if (end->column == MSIZE - 2) {
		end = &fields[end->row][MSIZE - 1];
		end->steps = fields[end->row][MSIZE - 2].steps + 1;
	}
	//end->type = ' ';

	/*	Spawning 1st page and drinks	*/
	/*Page* page = new Page(this);
	pages.push_back(page);*/
	new Page(this);

	for (int drink = 0; drink < amountDrinks; ++drink)
		drinks.push_back(new Alcohol(this));
}