#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#define TEX_NUM 7

class Player;
class Maze;
class TextureManager;

using namespace sf;

class Application {
private:
	int phase;		//0-3 splashes, 4 game
public:
	Player* player;
	Maze* maze;
	TextureManager* texManager;
	int playerTex;

	Sprite splash;
	Sprite sprites[TEX_NUM];
	RenderWindow* window;
	View* camera;

	void ApplicationMainLoop();
	void drawGame();
	void saveGame();
	void loadGame();
	void drawSplash(String);

	Application();
	~Application();
};

