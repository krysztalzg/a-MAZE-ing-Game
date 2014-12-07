#include "Item.h"

using namespace std;

/* simple item serialization */
void Item::save(ofstream* ofs) {
	ofs->write((char*)&row, sizeof(int));
	ofs->write((char*)&column, sizeof(int));
	ofs->write((char*)&collected, sizeof(bool));
}

/* simple item deserialization */
void Item::load(ifstream* ifs) {
	ifs->read((char*)&row, sizeof(int));
	ifs->read((char*)&column, sizeof(int));
	ifs->read((char*)&collected, sizeof(bool));
}

/*
int Item::getRow() {
	return row;
}

int Item::getColumn() {
	return column;
}*/
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
