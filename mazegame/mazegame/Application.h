#pragma once

#include <string>
#include <SFML\Graphics.hpp>

#define TEX_NUM 7

class Player;
class Maze;
class textureManager;

using namespace sf;

class Application {
public:
	Player* player;
	Maze* maze;
	textureManager* texManager;

	Sprite _background, _tile, _wall, _finish, _player, _page, _drink;
	Sprite sprites[TEX_NUM];
	RenderWindow* window;

	void ApplicationMainLoop();
	void drawGame();
	void saveGame();
	void loadGame();

	Application();
	~Application();
};

