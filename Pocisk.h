#pragma once
#include <SFML/Graphics.hpp>
#include "Przeciwnik.h"
using namespace sf;
class Pocisk
{
private:
	Sprite ksztalt;
	Clock zegar;
public:
	Pocisk(Texture * tekstura, Vector2f pozycja = Vector2f(100, 100));
	Sprite getKsztalt() { return ksztalt; }
	void przesun(float y);
	void animuj();
};

