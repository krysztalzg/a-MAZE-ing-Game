#pragma once
#include <fstream>

using namespace std;

class Player;
class Maze;

class Item {
private:
	int row, column;
	bool collected;
public:
	int getRow();
	int getColumn();
	bool getCollected();

	void setRow(int);
	void setColumn(int);
	void setCollected(bool);

	virtual void collect(Player*, Maze*) = 0;

	void save(ofstream*);
	void load(ifstream*);

	Item();
	virtual ~Item();
};

