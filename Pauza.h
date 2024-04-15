#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
class Pauza
{
private:
	Font czcionka;
	Text napis;
	FloatRect textRect;
public:
	Pauza(Vector2f pozycja , Vector2f rozmiar, std::string tekst);
	void draw(RenderWindow* okienko);
};

