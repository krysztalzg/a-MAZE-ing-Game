#include <cstdlib>
#include <ctime>

#include "Maze.h"

int main() {
	srand(time(NULL));
	Maze *maze = new Maze();

	maze->show();

	system("pause");
	return 0;
}