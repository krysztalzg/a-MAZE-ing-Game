#pragma once

#include <string>
#include <map>

using namespace std;
using namespace sf;

class textureManager {
private:
	map<string, Texture> textures;
public:
	void loadTexture(const string&, string);
	Texture& getTexture(const string&);

	textureManager();
	virtual ~textureManager();
};

