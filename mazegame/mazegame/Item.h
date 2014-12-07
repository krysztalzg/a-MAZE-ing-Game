#pragma once
#include <fstream>

using namespace std;

class Player;
class Maze;
struct Field;

class Item {
private:
	int row, column;
	Field* field;
	bool collected;
public:
	/*int getRow();
	int getColumn();*/
	Field* getField();
	bool getCollected();

	/*void setRow(int);
	void setColumn(int);*/
	void setField(Field*);
	void setCollected(bool);

	virtual void collect(Player*, Maze*) = 0;

	void save(ofstream*);
	void load(ifstream*);

	Item();
	virtual ~Item();
};

