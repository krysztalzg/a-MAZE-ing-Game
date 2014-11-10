#pragma once
#include <vector>

#define MSIZE 11

using namespace std;

class Page;
class Alcohol;

struct Field {
	int row, column, steps;
	char type;
	bool visited, seen;
	vector <Field*> neighbours;
	vector <Alcohol*> drinks;
	Page* pages[6];
};

class Maze {
public:
	Field *start, *end;
	Field fields[MSIZE][MSIZE];
	vector<Field*> path;
	bool finished;

	void show(int, int);
	void findNeighbours(Field*);
	void generateMaze();
	Maze();
	~Maze();
};

