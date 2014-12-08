#include <string>
#include <iostream>
#include <fstream>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>

#include "textureManager.h"
#include "Player.h"
#include "Alcohol.h"
#include "Page.h"
#include "Maze.h"
#include "Application.h"

using namespace std;
using namespace sf;

/* enum to easy call to sprites array */
enum texs{TILE, PLAYER, DRINK, PAGE, DOOR};

Application::Application() {
	maze = new Maze();											//first app is generating new maze
	player = new Player(maze->getStart(), maze->getSize());		//then player is created at the starting field
	texManager = new TextureManager();							//textureManagare load all textures

	playerTex = rand()%8;										//players texture is randomly chosen from possible ones

	/* creating window with given size, title and framerate */
	window = new RenderWindow();	
	window->create(VideoMode(1280, 720), "a-MAZE-ing Game");
	window->setFramerateLimit(60);
	Vector2i windowPos = window->getPosition();
	windowPos.y -= 15;
	window->setPosition(windowPos);

	drawSplash("splash1");
	drawSplash("splash2");
	drawSplash("splash3");

	/* connecting loaded textures with sprites */
	sprites[TILE].setTexture(texManager->getTexture("tile"));
	sprites[PLAYER].setTexture(texManager->getTexture("player"));
	sprites[PAGE].setTexture(texManager->getTexture("page"));
	sprites[DRINK].setTexture(texManager->getTexture("drink"));
	sprites[DOOR].setTexture(texManager->getTexture("door"));

	/* creating perspective centered at player */
	camera = new View();
	camera->setCenter(Vector2f(player->getCurrent()->column * 50.0f, player->getCurrent()->row * 50.0f));
	camera->setSize(Vector2f(1280, 720));
	window->setView(*camera);
}

void Application::drawGame() {
	bool temp = false;
	vector <Alcohol*> drinks = *maze->getDrinks();
	/* drawing all fields within players field of view and all seen earlier */
		for (auto&& rows : make_pair(maze->fields,maze->fields+maze->getSize())) {
			for (auto& f : make_pair(rows,rows+maze->getSize())) {
				if ((abs(player->getCurrent()->column - f.column) < player->getFov() && abs(player->getCurrent()->row - f.row) < player->getFov()) ||
					(abs(player->getCurrent()->column - f.column) < player->getFov() - 1 && abs(player->getCurrent()->row - f.row) < player->getFov() + 1) ||
					(abs(player->getCurrent()->column - f.column) < player->getFov() + 1 && abs(player->getCurrent()->row - f.row) < player->getFov() - 1) || f.seen) {
					/* drawing maze tiles */
					switch (f.type) {
					case '#':
						sprites[TILE].setTextureRect(IntRect(0, 0, 50, 50));
						sprites[TILE].setPosition(Vector2f(f.column * 50.0f, f.row * 50.0f));
						window->draw(sprites[TILE]);
						break;
					/*case 'D':
					case 'P':
					case '@':
					case ' ':*/
					default:
						sprites[TILE].setTextureRect(IntRect(100, 0, 50, 50));
						sprites[TILE].setPosition(Vector2f(f.column * 50.0f, f.row * 50.0f));
						window->draw(sprites[TILE]);
						break;
					}
					f.seen = true;
				}
				/* draw page */
				if (*maze->getCurrentPage()->getField() == f && !maze->getCurrentPage()->getCollected() && f.seen) {
					sprites[PAGE].setPosition(Vector2f(maze->getCurrentPage()->getField()->column * 50.0f + 12.5f, maze->getCurrentPage()->getField()->row * 50.0f + 12.5f));
					window->draw(sprites[PAGE]);
				}
				/* draw drinks */		
				for (auto d : drinks) {
					if (*d->getField() == f && !d->getCollected() && f.seen) {
						sprites[DRINK].setTextureRect(IntRect(30 * d->getTexNo(), 0, 30, 50));
						sprites[DRINK].setPosition(Vector2f(d->getField()->column * 50.0f + 12.5f, d->getField()->row * 50.0f));
						window->draw(sprites[DRINK]);
					}
				}
			}
		}
		/* draw player */
		sprites[PLAYER].setTextureRect(IntRect(30 * playerTex, 0, 30, 50));
		sprites[PLAYER].setPosition(Vector2f(player->getX() + 12.5f, (float)player->getY()));
		window->draw(sprites[PLAYER]);

		/* draw exit if open and was seen after opening */
		sprites[TILE].setTextureRect(IntRect(0, 0, 50, 50));
		sprites[TILE].setPosition(Vector2f(maze->getEnd()->column * 50.0f, maze->getEnd()->row * 50.0f));
		window->draw(sprites[TILE]);

		if (maze->getEnd()->type == 'E' && maze->getEnd()->neighbours.size() > 0) {
			sprites[DOOR].setPosition(Vector2f(maze->getEnd()->column * 50.0f, maze->getEnd()->row * 50.0f));
			window->draw(sprites[DOOR]);
		}
}

/* main application loop */
void Application::ApplicationMainLoop() {
	bool finished = false, cheats = false;
	Event event;
	string temp;

	while (window->isOpen() ) {							//looping until app window is closed
		while (window->pollEvent(event)) {				//polling next event
			if (event.type == Event::KeyReleased) {		//if it was keyboard key released
				switch (event.key.code) {				//executing appropriate action to key pressed
				case Keyboard::Numpad1:					//1-9, Num1-9 changes players texture
				case Keyboard::Num1:
					playerTex = 0;
					break;
				case Keyboard::Numpad2:
				case Keyboard::Num2:
					playerTex = 1;
					break;
				case Keyboard::Numpad3:
				case Keyboard::Num3:
					playerTex = 2;
					break;
				case Keyboard::Numpad4:
				case Keyboard::Num4:
					playerTex = 3;
					break;
				case Keyboard::Num5:
					playerTex = 4;
					break;
				case Keyboard::Numpad6:
				case Keyboard::Num6:
					playerTex = 5;
					break;
				case Keyboard::Numpad7:
				case Keyboard::Num7:
					playerTex = 6;
					break;
				case Keyboard::Numpad8:
				case Keyboard::Num8:
					playerTex = 7;
					break;
				case Keyboard::Numpad9:
				case Keyboard::Num9:
					int temp;
					do
					temp = rand() % 8;
					while (temp == playerTex);
					playerTex = temp;
					break;


				case Keyboard::Equal:						//steering view zoom
					camera->zoom(0.5f);
					break;
				case Keyboard::Dash:
					camera->zoom(1.5f);
					break;


				case Keyboard::F5:							//F5, F9 is saving and loading game
					saveGame();
					cout << endl << "Game saved" << endl;
					sleep(seconds(0.5f));
					break;
				case Keyboard::F9:
					loadGame();
					cout << endl << "Game loaded" << endl;
					sleep(seconds(0.5f));
					break;


				case Keyboard::F:							//F for drinkink potions
					if (player->getCollectedDrinks()->size() > 0) {
						player->getCollectedDrinks()->back()->drink(player, maze);
						player->getCollectedDrinks()->pop_back();
					}
					break;
				case Keyboard::Escape:						//ESC close app window
					window->close();
					break;
				case Keyboard::F4:							//debug or cheat mode
					cheats = true;							//allow to teleport by goals
					if (player->getCollectedPages() < maze->getAmountPages()) {
						player->setX(maze->getCurrentPage()->getField()->column*50.0f);
						player->setY(maze->getCurrentPage()->getField()->row*50.0f);
					}
					else {
						player->setX(maze->getEnd()->column*50.0f);
						player->setY(maze->getEnd()->row*50.0f);
						finished = true;
						window->close();
					}
					break;
				}

				/* when player step into finish field app window is closing and displaying moves statistic in console */
				if (player->getCurrent()->column == 0 || player->getCurrent()->column == maze->getSize() - 1 ||
					player->getCurrent()->row == 0 || player->getCurrent()->row == maze->getSize() - 1) {
					cout << endl << "Steps: " << player->getSteps() << "/" << maze->getEnd()->steps << endl;

					finished = true;
					window->close();
				}
			}
		}
		/* updating whole game */
		maze->endNeighbours();

		if (player->getCurrent()->column != maze->getEnd()->column || player->getCurrent()->row != maze->getEnd()->row)
			player->move(maze, camera);

		window->setView(*camera);
		window->clear(Color::Color(130, 145, 90, 255));
		drawGame();		
		window->display();
	}
	/* Displaying summary after player finish playing */
	if (cheats)
		cout << "\"Congratualtions\", you cheated. " << player->getSteps() << " steps with " << maze->getEnd()->steps << " steps shortest possible." << endl << endl << endl;
	else if (finished)
		cout << "Congratualtion, maze finished with " << player->getSteps() << " steps with " << maze->getEnd()->steps << " steps shortest possible." << endl << endl << endl;
	else
		cout << "Maze not finished. " << player->getSteps() << " steps done with " << maze->getEnd()->steps << " steps shortest possible." << endl << endl << endl;
}

/* simple serialization of all app objects */
void Application::saveGame() {
	ofstream ofs("game.save", ios::binary);

	maze->saveMaze(&ofs);
	player->savePlayer(&ofs);

	ofs.close();
}

/* simple deserialization of all app objects */
void Application::loadGame() {
	ifstream ifs("game.save", ios::binary);

	maze->loadMaze(&ifs);
	player->loadPlayer(&ifs);

	camera->setCenter(Vector2f(player->getCurrent()->column * 50.0f, player->getCurrent()->row * 50.0f));

	ifs.close();
}

void Application::drawSplash(String name) {
	Event event;
	splash.setTexture(texManager->getTexture(name));
	splash.setPosition(Vector2f(0, 0));
	window->draw(splash);
	window->display();

	do {
		window->pollEvent(event);
	} while (event.type != Event::KeyReleased || event.key.code != Keyboard::Return);

}


Application::~Application() {}