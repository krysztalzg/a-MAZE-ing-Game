#include "Maze.h"
#include "Item.h"

using namespace std;

/* simple item serialization */
void Item::save(ofstream* ofs, Maze* maze) {
	ofs->write((char*)&field->column, sizeof(int));
	ofs->write((char*)&field->row, sizeof(int));
	ofs->write((char*)&collected, sizeof(bool));
}

/* simple item deserialization */
void Item::load(ifstream* ifs, Maze* maze) {
	int c, r;
	ifs->read((char*)&c, sizeof(int));
	ifs->read((char*)&r, sizeof(int));
	ifs->read((char*)&collected, sizeof(bool));
	field = &maze->fields[r][c];
}


Field* Item::getField() {
	return field;
}

bool Item::getCollected() {
	return collected;
}

/*
void Item::setRow(int r) {
	row = r;
}

void Item::setColumn(int c) {
	column = c;
}*/
void Item::setField(Field* f) {
	field = f;
}

void Item::setCollected(bool c) {
	collected = c;
}

Item::Item() {}


Item::~Item() {}
