#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Tlo
{
protected:
	Texture tekstura;
	Sprite tlo;
public:
	void draw(RenderWindow* okienko);
	Tlo();
};

