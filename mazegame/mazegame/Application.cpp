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

/* enum to easy call to sprites array */
enum texs{TILE, PLAYER, DRINK, PAGE, DOOR};

Application::Application() {
	maze = new Maze();							//first app is generating new maze
	player = new Player(maze->getStart());		//then player is created at the starting field
	texManager = new textureManager();			//textureManagare load all textures

	playerTex = rand()%8;						//players texture is randomly chosen from possible ones

	cout << endl;
	cout << "a-MAZE-ing Game" << endl << endl;
	cout << "You are trapped in a maze." << endl << "To escape You need to find all keys and exit." << endl;
	cout << "Everytime You pick key You forgot the structure of maze" << endl << "and have to explore again." << endl;
	cout << "Also with every key picked Your sight worsen." << endl << "You'll find various magic drinks on your path through maze." << endl;
	cout << "You can drink potion to improve Your sight." << endl << endl << endl;
	cout << "Keyboard control:" << endl;
	cout << "WSAD/Arrows: player movement" << endl;
	cout << "1-9: changing player texture" << endl;
	cout << "F: drink potion" << endl;
	cout << "F5: save game" << endl;
	cout << "F9: load game" << endl;
	cout << "ESC: exit game" << endl << endl;

	system("pause");

	/* creating window with given size, title and framerate */
	window = new RenderWindow();	
	window->create(VideoMode(1280, 720), "a-MAZE-ing Game");
	window->setFramerateLimit(60);

	/* connecting loaded textures with sprites */
	sprites[TILE].setTexture(texManager->getTexture("tile"));
	sprites[PLAYER].setTexture(texManager->getTexture("player"));
	sprites[PAGE].setTexture(texManager->getTexture("page"));
	sprites[DRINK].setTexture(texManager->getTexture("drink"));
	sprites[DOOR].setTexture(texManager->getTexture("door"));

	/* creating perspective centered at player 
	  (TODO: center at maze and move when player get to edge of screen) */
	camera = new View();
	camera->setCenter(Vector2f(player->getCurrent()->column * 50.0f, player->getCurrent()->row * 50.0f));
	camera->setSize(Vector2f(1280, 720));
	window->setView(*camera);

}

void Application::drawGame() {
	bool temp = false;
	vector <Alcohol*> drinks = *maze->getDrinks();
	/* drawing all fields within players field of view and all seen earlier */
		for (auto& rows : maze->fields) {
			for (auto& f : rows) {
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
					case ' ':
						sprites[TILE].setTextureRect(IntRect(100, 0, 50, 50));
						sprites[TILE].setPosition(Vector2f(f.column * 50.0f, f.row * 50.0f));
						window->draw(sprites[TILE]);
						break;
					}
					f.seen = true;
				}
				/* draw page */
				if (maze->getCurrentPage()->getColumn() == f.column && maze->getCurrentPage()->getRow() == f.row && !maze->getCurrentPage()->getCollected() && f.seen) {
					sprites[PAGE].setPosition(Vector2f(maze->getCurrentPage()->getColumn() * 50.0f + 12.5f, maze->getCurrentPage()->getRow() * 50.0f + 12.5f));
					window->draw(sprites[PAGE]);
				}
				/* draw drinks */		
				for (auto d : drinks) {
					if (d->getColumn() == f.column && d->getRow() == f.row && !d->getCollected() && f.seen) {
						sprites[DRINK].setTextureRect(IntRect(30 * d->getTexNo(), 0, 30, 50));
						sprites[DRINK].setPosition(Vector2f(d->getColumn() * 50.0f + 12.5f, d->getRow() * 50.0f));
						window->draw(sprites[DRINK]);
					}
				}
			}
		}
		/* draw player */
		sprites[PLAYER].setTextureRect(IntRect(30 * playerTex, 0, 30, 50));
		sprites[PLAYER].setPosition(Vector2f(player->getX() + 12.5f, player->getY()));
		camera->setCenter(Vector2f(player->getX() + 12.5f, player->getY()));
		window->draw(sprites[PLAYER]);

		/* draw exit if open and was seen after opening */
		if (maze->getEnd()->type == ' ' && maze->getEnd()->seen) {
			sprites[DOOR].setPosition(Vector2f(maze->getEnd()->column * 50.0f, maze->getEnd()->row * 50.0f));
			window->draw(sprites[DOOR]);
		}
		else if (!maze->getEnd()->seen){
			sprites[TILE].setTextureRect(IntRect(0, 0, 50, 50));
			sprites[TILE].setPosition(Vector2f(maze->getEnd()->column * 50.0f, maze->getEnd()->row * 50.0f));
			window->draw(sprites[TILE]);
		}
}

/* main application loop */
void Application::ApplicationMainLoop() {
	Event event;
	string temp;
	maze->show(player);

	while (window->isOpen()) {
		player->move(maze, camera);						//looping until app window is closed
		while (window->pollEvent(event)) {				//polling next event
			if (event.type == Event::KeyReleased) {		//if it was keyboard key released
				switch (event.key.code) {				//executing appropriate action to key pressed
				case Keyboard::Num1:					//Num1-9 changes players texture
					playerTex = 0;
					break;
				case Keyboard::Num2:
					playerTex = 1;
					break;
				case Keyboard::Num3:
					playerTex = 2;
					break;
				case Keyboard::Num4:
					playerTex = 3;
					break;
				case Keyboard::Num5:
					playerTex = 4;
					break;
				case Keyboard::Num6:
					playerTex = 5;
					break;
				case Keyboard::Num7:
					playerTex = 6;
					break;
				case Keyboard::Num8:
					playerTex = 7;
					break;
				case Keyboard::Num9:
					int temp;
					do
						temp = rand()%8;
					while (temp == playerTex);
					playerTex = temp;
					break;
				case Keyboard::Up:							//WSAD and Arrows control players movement
				case Keyboard::W:
					//player->processMove(maze, 1, camera);
					player->setSpeedY(0);
					break;
				case Keyboard::Down:
				case Keyboard::S:
					//player->processMove(maze, 2, camera);
					player->setSpeedY(0);
					break;
				case Keyboard::Left:
				case Keyboard::A:
					//player->processMove(maze, 3, camera);
					player->setSpeedX(0);
					break;
				case Keyboard::Right:
				case Keyboard::D:
					//player->processMove(maze, 4, camera);
					player->setSpeedX(0);
					break;
				case Keyboard::F5:							//F5, F9 is saving and loading game
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
				case Keyboard::F:							//F for drinkink potions
					if (player->getCollectedDrinks()->size() > 0) {
						player->getCollectedDrinks()->back()->drink(player, maze);
						player->getCollectedDrinks()->pop_back();
					}
					break;
				case Keyboard::Escape:						//ESC close app window
					window->close();
					break;
				}											
				/* when player step into finish field app window is closing and displaying moves statistic in console */
				if (player->getCurrent()->column == 0 || player->getCurrent()->column == MSIZE - 1 ||
					player->getCurrent()->row == 0 || player->getCurrent()->row == MSIZE - 1) {
					cout << endl << "Steps: " << player->getSteps() << "/" << maze->getEnd()->steps << endl;

					maze->setFinished(true);
					window->close();
				}
				/* displaying game in console (done for testing before gui etc.) */
				maze->show(player);							
			}
			else if (event.type == Event::KeyPressed) {
				switch (event.key.code) {
				case Keyboard::Up:
				case Keyboard::W:
					player->setSpeedY(-5);
					break;
				case Keyboard::Down:
				case Keyboard::S:
					player->setSpeedY(5);
					break;
				case Keyboard::Left:
				case Keyboard::A:
					player->setSpeedX(-5);
					break;
				case Keyboard::Right:
				case Keyboard::D:
					player->setSpeedX(5);
					break;
				}
			}
		}
		/* setting perspective and drawing whole game */
		window->setView(*camera);
		window->clear(Color::Color(125,125,125,255));
		drawGame();		
		window->display();
	}
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


Application::~Application() {}