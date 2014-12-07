#pragma once

#include <string>
#include <map>

using namespace std;
using namespace sf;

class TextureManager {
private:
	map<string, Texture> textures;
public:
	void loadTexture(const string&, string);
	Texture& getTexture(const string&);

	TextureManager();
	virtual ~TextureManager();
};

