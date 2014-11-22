#include <string>
#include <iostream>
#include <fstream>
#include <SFML\System\Time.hpp>
#include <SFML\Graphics.hpp>

#include "textureManager.h"
#include "Player.h"
#include "Alcohol.h"
#include "Page.h"
#include "Maze.h"
#include "Application.h"

using namespace std;
using namespace sf;

enum texs{ BG, TILE, WALL, PLAYER, DRINK, PAGE, FOG};

Application::Application() {
	maze = new Maze();
	player = new Player();
	texManager = new textureManager();
	player->setCurrent(maze->getStart());

	window = new RenderWindow();	
	window->create(VideoMode(1280, 720), "a-MAZE-ing Game");
	window->setFramerateLimit(60);

	sprites[BG].setTexture(texManager->getTexture("background"));
	sprites[BG].setTextureRect(IntRect(0, 0, 1280, 720));
	sprites[TILE].setTexture(texManager->getTexture("tile"));
	sprites[WALL].setTexture(texManager->getTexture("wall"));
	sprites[FOG].setTexture(texManager->getTexture("fog"));
	sprites[PLAYER].setTexture(texManager->getTexture("player"));
	sprites[PAGE].setTexture(texManager->getTexture("page"));
	sprites[DRINK].setTexture(texManager->getTexture("drink"));
}

void Application::drawGame() {
	bool temp = false;
	vector <Alcohol*> drinks = *maze->getDrinks();
	window->draw(sprites[BG]);

		for (auto& rows : maze->fields) {
			for (auto& f : rows) {
				if ((abs(player->getCurrent()->column - f.column) < player->getFov() && abs(player->getCurrent()->row - f.row) < player->getFov()) ||
					(abs(player->getCurrent()->column - f.column) < player->getFov() - 1 && abs(player->getCurrent()->row - f.row) < player->getFov() + 1) ||
					(abs(player->getCurrent()->column - f.column) < player->getFov() + 1 && abs(player->getCurrent()->row - f.row) < player->getFov() - 1) ||
					maze->getFinished() || f.seen) {
					//drawing maze
					switch (f.type) {
					case '#':
						sprites[WALL].setPosition(Vector2f(f.column * 50, f.row * 50));
						window->draw(sprites[WALL]);
						break;
					case ' ':
						sprites[TILE].setPosition(Vector2f(f.column * 50, f.row * 50));
						window->draw(sprites[TILE]);
						break;
					}
				}
				else {
					sprites[FOG].setPosition(Vector2f(f.column * 50, f.row * 50));
					window->draw(sprites[FOG]);
				}
				//drawing page
				if (maze->getCurrentPage()->getColumn() == f.column && maze->getCurrentPage()->getRow() == f.row && !maze->getCurrentPage()->getCollected() && f.seen) {
					sprites[PAGE].setPosition(Vector2f(maze->getCurrentPage()->getColumn() * 50 + 12.5, maze->getCurrentPage()->getRow() * 50 + 12.5));
					window->draw(sprites[PAGE]);
				}
				//draw drinks		
				for (auto d : drinks) {
					if (d->getColumn() == f.column && d->getRow() == f.row && !d->getCollected() && f.seen) {
						sprites[DRINK].setPosition(Vector2f(d->getColumn() * 50 + 12.5, d->getRow() * 50 + 12.5));
						window->draw(sprites[DRINK]);
					}
				}
			}
		}
		//draw player
		sprites[PLAYER].setPosition(Vector2f(player->getCurrent()->column * 50 + 12.5, player->getCurrent()->row * 50 + 12.5));
		window->draw(sprites[PLAYER]);
}


void Application::ApplicationMainLoop() {
	Event event;
	string temp;
	maze->show(player);
	
	while (window->isOpen()) {
		while (window->pollEvent(event)) {
			if (event.type == Event::KeyReleased) {
				switch (event.key.code) {
				case Keyboard::Up:
				case Keyboard::W:
					player->processMove(maze, 1);
					break;
				case Keyboard::Down:
				case Keyboard::S:
					player->processMove(maze, 2);
					break;
				case Keyboard::Left:
				case Keyboard::A:
					player->processMove(maze, 3);
					break;
				case Keyboard::Right:
				case Keyboard::D:
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
					window->close();
					break;
				}
				if (player->getCurrent()->column == 0 || player->getCurrent()->column == MSIZE - 1 ||
					player->getCurrent()->row == 0 || player->getCurrent()->row == MSIZE - 1) {
					maze->setFinished(true);
					window->close();
				}
				maze->show(player);
			}
		}
		window->clear(Color::White);
		drawGame();		
		window->display();
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


Application::~Application() {}