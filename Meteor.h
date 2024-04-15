#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
class Meteor 
{
private:
	Clock zegar;
	Sprite ksztalt;
public:
	Sprite getKsztalt() { return ksztalt; }
	Meteor(Texture* tekstura, float y);
	void animuj();
	void obroc(float x);
	void przesun(float x, float y);
};

