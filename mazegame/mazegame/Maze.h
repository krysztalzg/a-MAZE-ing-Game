#pragma once
#include <vector>

#define MSIZE 15

using namespace std;

struct Field {
	int row, column;
	char type;
	bool visited;
	vector<Field*> neighbours;
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

