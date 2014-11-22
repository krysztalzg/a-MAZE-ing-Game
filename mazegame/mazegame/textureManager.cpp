#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <iostream>

#include "textureManager.h"

using namespace std;
using namespace sf;

void textureManager::loadTexture(const string &name, string filename) {
	Texture* tex = new Texture();
	if (name == "background")
		tex->setRepeated(true);

	if (!tex->loadFromFile("textures/" + filename)) {
		cout << "Could not load" << endl;
		exit(-1);
	}
	else
		cout << "BG texture loaded" << endl;

	tex->setSmooth(true);
	this->textures[name] = *tex;

	return;
}

Texture& textureManager::getTexture(const string &texture) {
	return this->textures.at(texture);
}

textureManager::textureManager() {
	loadTexture("background", "bg2.png");
	loadTexture("tile", "tile.png");
	loadTexture("fog", "fog.png");
	loadTexture("player", "player.png");
	loadTexture("page", "page.png");
	loadTexture("wall", "wall.png");
	loadTexture("drink", "drink.png");
}

textureManager::~textureManager() {}