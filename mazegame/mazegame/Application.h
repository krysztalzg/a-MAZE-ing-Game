#pragma once

#include <string>

class Player;
class Maze;

class Application {
public:
	Player* player;
	Maze* maze;

	void ApplicationMainLoop();

	Application();
	~Application();
};

