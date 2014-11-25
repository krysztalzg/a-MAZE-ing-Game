#pragma once
#include <vector>
#include <fstream>

#define MSIZE 13

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
private:
	Field *start, *end;

	vector<Field*> path;
	bool finished;

	int amountPages, amountDrinks;
	//int size;
	vector <Alcohol*> drinks;
	Page* currentPage;

public:
	//Field** fields;
	Field fields[MSIZE][MSIZE];

	bool getFinished();
	void setFinished(bool);

	Field** getFields();
	Field* getStart();
	Field* getEnd();
	vector<Field*> getPath();

	int getAmountPages();
	int getAmountDrinks();
	//int getSize();

	void setAmountPages(int);
	void setAmountDrinks(int);

	vector <Alcohol*> *getDrinks();
	Page* getCurrentPage();
	void setCurrentPage(Page*);


	void show(Player*);
	void findNeighbours(Field*);
	void generateMaze();

	void saveMaze(ofstream*);
	void loadMaze(ifstream*);
	void saveField(ofstream*, Field*);
	Field* loadField(ifstream*);

	Maze();
	~Maze();
};

