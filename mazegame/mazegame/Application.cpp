#include <string>
#include <iostream>
#include <SFML\Window\Keyboard.hpp>
#include <SFML\Window\Event.hpp>
#include <SFML\Window.hpp>
#include <chrono>
#include <thread>

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
	cout << endl << "WIN!" << endl;
	system("pause");
}


Application::~Application() {
}

void Application::ApplicationMainLoop() {
	Window window(VideoMode(0, 0), "a-MAZE-ing Game");
	Event event;
	string temp;
	bool loop = true;
	maze->show();
	while (loop) {
		while (window.pollEvent(event)) {
			if (event.type == Event::KeyReleased) {
				/*
				if (Keyboard::isKeyPressed(Keyboard::Up)) {
					player->processMove(maze, 1);
					maze->show();
				}
				else if (Keyboard::isKeyPressed(Keyboard::Down)) {
					player->processMove(maze, 2);
					maze->show();
				}
				else if (Keyboard::isKeyPressed(Keyboard::Left)) {
					player->processMove(maze, 3);
					maze->show();
				}
				else if (Keyboard::isKeyPressed(Keyboard::Right)) {
					player->processMove(maze, 4);
					maze->show();
				}
				*/
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
				}
				if (player->current->column == 0 || player->current->column == MSIZE - 1 ||
					player->current->row == 0 || player->current->row == MSIZE - 1)
					loop = false;

				maze->show();
				//this_thread::sleep_for(chrono::milliseconds(100));
			}
		}
	}
}