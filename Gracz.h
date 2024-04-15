#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Gracz
{
private:
	Sprite ksztalt;
	Texture tekstura;
public:
	Gracz(Vector2f pozycja = Vector2f(351, 520));
	Sprite getKsztalt() { return ksztalt; }
	float getPosx() { return ksztalt.getPosition().x; }
	void przesun(float x);
	void draw(RenderWindow* okienko);

};