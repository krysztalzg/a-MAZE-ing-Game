#pragma once
class Item {
public:
	int row, column;
	void spawn();
	virtual void activate() = 0;

	Item();
	virtual ~Item();
};

