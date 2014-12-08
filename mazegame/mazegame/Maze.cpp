#include <iostream>
#include <vector>
#include <cmath>

#include "Alcohol.h"
#include "Page.h"
#include "Player.h"
#include "Maze.h"

using namespace std;


Maze::Maze() {
	/* player choose size of maze */
	cout << "Enter maze size (odd number from 3 to 31): ";
	cin >> size;
	if (size <= 2) {
		size = 3;
		cout << "Typed size was to small. Size set to " << size << "." << endl;
	}
	else if (size > 31) {
		size = 31;
		cout << "Typed size was to small. Size set to " << size << "." << endl;
	}
	else if (size % 2 == 0) {
		size++;
		cout << "Typed size wasn't odd. Size set to " << size << "." << endl;
	}

	fields = new Field*[size];
	for (int i = 0; i < size; ++i)
		fields[i] = new Field[size];

	for (int i = 0; i < size; i++) {									//initializing types of maze 
		for (int j = 0; j < size; j++) {								//tiles by this pattern
			if (i == 0 || j == 0 || i == (size - 1) || j == (size - 1))	//(#-wall, _ - empty):
				fields[i][j].type = '#';								//#######
			else if ((i % 2) != 0 && (j % 2) != 0)						//# # # #
				fields[i][j].type = ' ';								//#######
			else														//# # # #
				fields[i][j].type = '#';								//#######

			fields[i][j].row = i;
			fields[i][j].column = j;
			fields[i][j].visited = false;
			if (i == 0 || i == size - 1 || j == 0 || j == size - 1)		//edges of maze are always visible
				fields[i][j].seen = true;
			else
				fields[i][j].seen = false;
		}
	}
	/* ampunt of potions and pages in maze is based on it's size*/
	amountDrinks = size / 5;
	amountPages = size / 10;

	/* executing maze generation algorith */
	generateMaze();
}


/* finding all empty and not visited tiles in 2 step neighbourhood*/
void Maze::findNeighbours(Field* field) {
	int col = field->column, row = field->row;

	if (row - 2 >= 0)
	if (fields[row - 2][col].type == ' ' && !fields[row - 2][col].visited)
		field->neighbours.push_back(&fields[row - 2][col]);

	if (row + 2 < size)
	if (fields[row + 2][col].type == ' ' && !fields[row + 2][col].visited)
		field->neighbours.push_back(&fields[row + 2][col]);

	if (col - 2 >= 0)
	if (fields[row][col-2].type == ' ' && !fields[row][col-2].visited)
		field->neighbours.push_back(&fields[row][col-2]);

	if (col + 2 < size)
	if (fields[row][col + 2].type == ' ' && !fields[row][col + 2].visited)
		field->neighbours.push_back(&fields[row][col+2]);
}

void Maze::endNeighbours() {
	end->neighbours.clear();

	if (end->row - 1 >= 0)
		if (fields[end->row - 1][end->column].type == ' ' && fields[end->row - 1][end->column].seen)
			end->neighbours.push_back(&fields[end->row - 1][end->column]);

	if (end->row + 1 < size)
		if (fields[end->row + 1][end->column].type == ' ' && fields[end->row + 1][end->column].seen)
			end->neighbours.push_back(&fields[end->row + 1][end->column]);

	if (end->column - 1 >= 0)
		if (fields[end->row][end->column - 1].type == ' ' && fields[end->row][end->column - 1].seen)
			end->neighbours.push_back(&fields[end->row][end->column - 1]);

	if (end->column + 1 < size)
		if (fields[end->row][end->column + 1].type == ' ' && fields[end->row][end->column + 1].seen)
			end->neighbours.push_back(&fields[end->row][end->column + 1]);
}



Maze::~Maze(){}


void Maze::generateMaze() {
	Field* current;
	Field* next;
	/* Finfing starting field */
	do
	start = &fields[rand() % size][rand() % size];
	while (start->type != ' ');
	start->steps = 0;
	start->visited = true;
	start->type = '@';

	current = start;
	/* Generating maze with DFS algorithm */
	do {
		current->visited = true;
		findNeighbours(current);
		/* If field have unvisited neighbour, create connection between them */
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
		/* Other way go to previous field */
		else if (!path.empty()) {
			current = path.back();
			path.pop_back();
		}
		/* If you returned to the start field finish generating */
		else
			break;
	} while (true);

	/* Finding finish field on the edge of maze */
	do
	end = &fields[rand() % size][rand() % size];
	while (!(end->type == ' ') || !(end->row == 1 || end->column == 1 || end->row == (size - 2) || end->column == (size - 2)));
	
	if (end->row == 1) {
		end = &fields[0][end->column];
		end->steps = fields[1][end->column].steps + 1;
		end->neighbours.push_back(&fields[1][end->column]);
	}
	else if (end->row == size - 2) {
		end = &fields[size - 1][end->column];
		end->steps = fields[size - 2][end->column].steps + 1;
		end->neighbours.push_back(&fields[size - 2][end->column]);
	}
	else if (end->column == 1) {
		end = &fields[end->row][0];
		end->steps = fields[end->row][1].steps + 1;
		end->neighbours.push_back(&fields[end->row][1]);
	}
	else if (end->column == size - 2) {
		end = &fields[end->row][size - 1];
		end->steps = fields[end->row][size - 2].steps + 1;
		end->neighbours.push_back(&fields[end->row][1]);
	}

	/* Spawning 1st page */
	currentPage = new Page(this);

	/* Spawning drinks */
	for (int drink = 0; drink < amountDrinks; ++drink)
		drinks.push_back(new Alcohol(this));
}

/* simple field serialization */
void Maze::saveField(ofstream* ofs, Field* field) {
	ofs->write((char*)&field->row, sizeof(int));
	ofs->write((char*)&field->column, sizeof(int));
	ofs->write((char*)&field->steps, sizeof(int));
	ofs->write((char*)&field->type, sizeof(char));
	ofs->write((char*)&field->seen, sizeof(bool));
}

/* simple field deserialization */
Field* Maze::loadField(ifstream* ifs) {
	Field* field = new Field();
	ifs->read((char*)&field->row, sizeof(int));
	ifs->read((char*)&field->column, sizeof(int));
	ifs->read((char*)&field->steps, sizeof(int));
	ifs->read((char*)&field->type, sizeof(char));
	ifs->read((char*)&field->seen, sizeof(bool));

	return field;
}


/* simple maze serialization */
void Maze::saveMaze(ofstream* ofs) {
	ofs->write((char*)&size, sizeof(int));

	ofs->write((char*)&start->column, sizeof(int));
	ofs->write((char*)&start->row, sizeof(int));
	ofs->write((char*)&end->column, sizeof(int));
	ofs->write((char*)&end->row, sizeof(int));

	for (int i = 0; i < size; ++i)
	for (int j = 0; j < size; ++j)
			saveField(ofs, &fields[i][j]);

	currentPage->save(ofs, this);
	ofs->write((char*)&amountPages, sizeof(int));
	ofs->write((char*)&amountDrinks, sizeof(int));

	unsigned int dsize = drinks.size();
	ofs->write((char*)&dsize, sizeof(unsigned int));
	for (unsigned int i = 0; i < dsize; ++i)
		drinks[i]->save(ofs,this);
}

/* simple maze deserialization */
void Maze::loadMaze(ifstream* ifs) {
	unsigned int drinksSize;
	int sc, sr, ec, er;

	ifs->read((char*)&size, sizeof(int));

	ifs->read((char*)&sc, sizeof(int));
	ifs->read((char*)&sr, sizeof(int));
	ifs->read((char*)&ec, sizeof(int));
	ifs->read((char*)&er, sizeof(int));

	fields = new Field*[size];
	for (int i = 0; i < size; ++i)
		fields[i] = new Field[size];

	for (int i = 0; i < size; ++i)
	for (int j = 0; j < size; ++j)
			fields[i][j] = *(loadField(ifs));

	start = &fields[sr][sc];
	end = &fields[er][ec];

	currentPage->load(ifs,this);

	ifs->read((char*)&amountPages, sizeof(int));
	ifs->read((char*)&amountDrinks, sizeof(int));

	drinks.clear();
	ifs->read((char*)&drinksSize, sizeof(unsigned int));
	Alcohol* temp = new Alcohol(this);
	for (unsigned int i = 0; i < drinksSize; ++i) {
		temp->load(ifs, this);
		drinks.push_back(temp);
	}

	endNeighbours();
}


Field* Maze::getStart() {
	return start;
}

Field* Maze::getEnd() {
	return end;
}
vector<Field*> Maze::getPath() {
	return path;
}


int Maze::getAmountPages() {
	return amountPages;
}

int Maze::getAmountDrinks() {
	return amountDrinks;
}

vector <Alcohol*> *Maze::getDrinks() {
	return &drinks;
}

Page* Maze::getCurrentPage() {
	return currentPage;
}

void Maze::setCurrentPage(Page* p) {
	currentPage->setCollected(p->getCollected());
	currentPage->setField(p->getField());
}

void Maze::setAmountPages(int p) {
	amountPages = p;
}

void Maze::setAmountDrinks(int d) {
	amountDrinks = d;
}

int Maze::getSize() {
	return size;
}