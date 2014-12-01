#pragma once

#include <vector>
#include <fstream>

using namespace std;

namespace std {
	template <typename T> T* begin(pair<T*, T*> const& p) { return p.first;  }
	template <typename T> T* end  (pair<T*, T*> const& p) { return p.second; }
}

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
	int size;
	vector <Alcohol*> drinks;
	Page* currentPage;

public:
	Field** fields;

	bool getFinished();
	void setFinished(bool);

	Field** getFields();
	Field* getStart();
	Field* getEnd();
	vector<Field*> getPath();

	int getAmountPages();
	int getAmountDrinks();
	int getSize();

	void setAmountPages(int);
	void setAmountDrinks(int);

	vector <Alcohol*> *getDrinks();
	Page* getCurrentPage();
	void setCurrentPage(Page*);

	void findNeighbours(Field*);
	void generateMaze();

	void saveMaze(ofstream*);
	void loadMaze(ifstream*);
	void saveField(ofstream*, Field*);
	Field* loadField(ifstream*);

	Maze();
	~Maze();
};

