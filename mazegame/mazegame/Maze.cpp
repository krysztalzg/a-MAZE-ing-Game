#include <iostream>
#include <vector>

#include "Maze.h"

using namespace std;

Maze::Maze()
{
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
	generateMaze();
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

void Maze::show() {
	system("cls");
	for (auto& rows : fields) {
		for (auto& f : rows)
			cout << f.type;
		cout << endl;
	}
}

Maze::~Maze()
{
}


void Maze::generateMaze() {
	Field* current;
	Field* next;
	/*	Finfing starting field	*/
	do
	start = &fields[rand() % MSIZE][rand() % MSIZE];
	while (start->type != ' ');

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
			next->visited = true;
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
	
	if (end->row == 1)
		end = &fields[0][end->column];
	else if (end->row == MSIZE - 2)
		end = &fields[MSIZE - 1][end->column];
	else if (end->column == 1)
		end = &fields[end->row][0];
	else if (end->column == MSIZE - 2)
		end = &fields[end->row][MSIZE - 1];
	
	end->type = ' ';
}