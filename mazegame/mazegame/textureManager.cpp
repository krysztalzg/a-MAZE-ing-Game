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
		system("pause");
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
	loadTexture("tile", "tile.png");
	loadTexture("player", "player.png");
	loadTexture("page", "key.png");
	loadTexture("drink", "drink.png");
	loadTexture("door", "door.png");
}

textureManager::~textureManager() {}