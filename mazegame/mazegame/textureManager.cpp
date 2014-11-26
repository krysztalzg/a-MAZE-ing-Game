#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <iostream>

#include "textureManager.h"

using namespace std;
using namespace sf;


void textureManager::loadTexture(const string &name, string filename) {
	Texture* tex = new Texture();

	/* loading texture from file */
	if (!tex->loadFromFile("textures/" + filename)) {
		system("pause");
		exit(-1);
	}

	/* setting smoothing for texture and adding it to map of textures*/
	tex->setSmooth(true);
	this->textures[name] = *tex;

	return;
}

Texture& textureManager::getTexture(const string &texture) {
	return this->textures.at(texture);
}

/* loading all textures on texture manager creating*/
textureManager::textureManager() {
	loadTexture("tile", "tile.png");
	loadTexture("player", "player.png");
	loadTexture("page", "key.png");
	loadTexture("drink", "drink.png");
	loadTexture("door", "door.png");
}

textureManager::~textureManager() {}