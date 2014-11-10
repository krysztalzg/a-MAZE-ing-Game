#include <string>
#include <iostream>
#include <fstream>
#include <SFML\Graphics.hpp>

#include "Player.h"
#include "Alcohol.h"
#include "Maze.h"
#include "Application.h"

using namespace std;
using namespace sf;

Application::Application() {
	maze = new Maze();
	player = new Player();
	player->current = maze->start;
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
					if (player->collectedDrinks.size() > 0) {
						player->collectedDrinks.back()->drink(player, maze);
						player->collectedDrinks.pop_back();
					}
					break;
				case Keyboard::Escape:
					window.close();
					break;
				}
				if (player->current->column == 0 || player->current->column == MSIZE - 1 ||
					player->current->row == 0 || player->current->row == MSIZE - 1) {
					maze->finished = true;
					window.close();
				}
				maze->show(player);
			}
		}
		window.clear(Color::Black);
		window.display();
	}
	cout << endl << "Steps: " << player->steps << "/" << maze->end->steps << endl;
}

void Application::saveGame() {
	ofstream ofs("game.save", ios::binary);

	for (int i = 0; i < MSIZE; ++i) {
		for (int j = 0; j < MSIZE; ++j)
			ofs.write((char*)&maze->fields[i][j], sizeof(maze->fields[i][j]));
	}
	ofs.write((char*)&maze->currentPage, sizeof(maze->currentPage));
	ofs.write((char*)&maze->drinks, sizeof(maze->drinks));
	ofs.write((char*)&player, sizeof(player));
	ofs.write((char*)&player->current, sizeof(player->current));
	ofs.close();
}

void Application::loadGame() {
	ifstream ifs("game.save", ios::binary); 
	for (int i = 0; i < MSIZE; ++i)
		for (int j = 0; j < MSIZE; ++j) {
			ifs.read((char*)&maze->fields[i][j], sizeof(maze->fields[i][j]));
			maze->fields[i][j].seen = false;
		}
	ifs.read((char*)&maze->currentPage, sizeof(maze->currentPage));
	ifs.read((char*)&maze->drinks, sizeof(maze->drinks));
	ifs.read((char*)&player, sizeof(player));
	ifs.read((char*)&player->current, sizeof(player->current));
	ifs.close();
	
}