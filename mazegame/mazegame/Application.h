#pragma once

#include <string>
class Player;
class Maze;

class Application {
public:
	Player* player;
	Maze* maze;

	void ApplicationMainLoop();
	int ApplicationStatusManager(std::string);

	Application();
	~Application();
};

