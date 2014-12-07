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

struct Field {							//Field types:
	int row, column, steps;				//# - Wall | ' ' - Empty tile
	char type;							//P - Page | D - Drink
	bool visited, seen;					//E - Exit | @ - Player
	vector <Field*> neighbours;			

	bool operator==(const Field& field) {
		return (this->column == field.column && this->row == field.row);
	}
};


class Maze {
private:
	Field *start, *end;

	vector<Field*> path;

	int amountPages, amountDrinks;
	int size;
	vector <Alcohol*> drinks;
	Page* currentPage;

public:
	Field** fields;

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
