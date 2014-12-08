#pragma once
#include <fstream>

using namespace std;

class Player;
class Maze;
struct Field;

class Item {
private:
	Field* field;
	bool collected;
public:
	Field* getField();
	bool getCollected();

	void setField(Field*);
	void setCollected(bool);

	virtual void collect(Player*, Maze*) = 0;

	void save(ofstream*,Maze*);
	void load(ifstream*,Maze*);

	Item();
	virtual ~Item();
};

