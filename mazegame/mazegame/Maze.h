#pragma once
#include <vector>

#define MSIZE 11

using namespace std;

class Page;
class Alcohol;
class Player;

struct Field {
	int row, column, steps;
	char type;
	bool visited, seen;
	vector <Field*> neighbours;
};

class Maze {
public:
	Field *start, *end;
	Field fields[MSIZE][MSIZE];
	vector<Field*> path;
	bool finished;

	int amountPages, amountDrinks;
	vector <Alcohol*> drinks;
	Page* currentPage;

	//void show(int, int, int);
	void show(Player*);
	void findNeighbours(Field*);
	void generateMaze();
	Maze();
	~Maze();
};

