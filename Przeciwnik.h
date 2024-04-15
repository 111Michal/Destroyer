#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Przeciwnik
{
protected:
	Clock zegar;
	Sprite ksztalt;
public:
	Przeciwnik(Texture *tekstura ,Vector2f pozycja );
	Sprite getKsztalt() { return ksztalt; }
	void przesun(float y);
	void animuj();
};

