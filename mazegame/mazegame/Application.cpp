#include <string>
#include <iostream>

#include "Player.h"
#include "Maze.h"
#include "Application.h"

using namespace std;

Application::Application() {
	maze = new Maze();
	player = new Player();
	player->current = maze->start;
	
	ApplicationMainLoop();
}


Application::~Application() {
}

void Application::ApplicationMainLoop() {
	string temp;
	bool loop = true;
	while (loop) {
		system("cls");
		maze->show();
		cin >> temp;
		switch (ApplicationStatusManager(temp)) {
		case -1:
			loop = false;
			break;
		case 1:
			system("cls");
			cout << endl << "WIN!" << endl;
			system("pause");
			loop = false;
			break;
		default:
			break;
		}
	}
}

int Application::ApplicationStatusManager(string command) {
	if (command == "end")
		return -1;
	else if (command == "up" || command == "down" || command == "left" || command == "right") {
		player->processMove(maze, command);
		if (player->current->column == 0 || player->current->column == MSIZE - 1 ||
			player->current->row == 0 || player->current->row == MSIZE - 1)
			return 1;
	}

	return 0;
}