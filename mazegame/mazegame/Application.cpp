#include <string>
#include <iostream>
#include <fstream>
#include <SFML\Graphics.hpp>

#include "Player.h"
#include "Alcohol.h"
#include "Page.h"
#include "Maze.h"
#include "Application.h"

using namespace std;
using namespace sf;

Application::Application() {
	maze = new Maze();
	player = new Player();
	player->setCurrent(maze->getStart());
}


Application::~Application() {}

void Application::ApplicationMainLoop() {
	RenderWindow window(VideoMode(500, 500), "a-MAZE-ing Game");
	Event event;
	string temp;

	maze->show(player);

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::KeyReleased) {
				switch (event.key.code) {
				case Keyboard::Up:
					player->processMove(maze, 1);
					break;
				case Keyboard::Down:
					player->processMove(maze, 2);
					break;
				case Keyboard::Left:
					player->processMove(maze, 3);
					break;
				case Keyboard::Right:
					player->processMove(maze, 4);
					break;
				case Keyboard::F5:
					saveGame();
					cout << endl << "Game saved" << endl;
					sleep(seconds(1));
					break;
				case Keyboard::F9:
						loadGame();
						maze->show(player);
						cout << endl << "Game loaded" << endl;
						sleep(seconds(1));
					break;
				case Keyboard::F:
					if (player->getCollectedDrinks()->size() > 0) {
						player->getCollectedDrinks()->back()->drink(player, maze);
						player->getCollectedDrinks()->pop_back();
					}
					break;
				case Keyboard::Escape:
					window.close();
					break;
				}
				if (player->getCurrent()->column == 0 || player->getCurrent()->column == MSIZE - 1 ||
					player->getCurrent()->row == 0 || player->getCurrent()->row == MSIZE - 1) {
					maze->setFinished(true);
					window.close();
				}
				maze->show(player);
			}
		}
		window.clear(Color::Black);
		window.display();
	}
	cout << endl << "Steps: " << player->getSteps() << "/" << maze->getEnd()->steps << endl;
}

void Application::saveGame() {
	ofstream ofs("game.save", ios::binary);

	maze->saveMaze(&ofs);
	player->savePlayer(&ofs);

	ofs.close();
}

void Application::loadGame() {
	ifstream ifs("game.save", ios::binary);

	maze->loadMaze(&ifs);
	player->loadPlayer(&ifs);

	ifs.close();
}