#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

#include "Player.h"
#include "Maze.h"
#include "Application.h"

using namespace std;
using namespace sf;

Application::Application() {
	maze = new Maze();
	player = new Player();
	player->current = maze->start;
	
	ApplicationMainLoop();
	cout << endl << "WIN! Steps: " << player->steps << "\tShortest: " << maze->end->steps << endl;
	system("pause");
}


Application::~Application() {}

void Application::ApplicationMainLoop() {
	RenderWindow window(VideoMode(500, 500), "a-MAZE-ing Game");
	Event event;
	string temp;

	maze->show(player->current->column, player->current->row);

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
					break;
				case Keyboard::F9:
					loadGame();
					break;
				}
				if (player->current->column == 0 || player->current->column == MSIZE - 1 ||
					player->current->row == 0 || player->current->row == MSIZE - 1) {
					maze->finished = true;
					window.close();
				}

				maze->show(player->current->column, player->current->row);
			}
		}
		window.clear(Color::Black);
		window.display();
	}
}