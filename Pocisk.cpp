#include "Pocisk.h"
Pocisk::Pocisk(Texture *tekstura, Vector2f pozycja)
{
	tekstura->loadFromFile("bullet.png");
	ksztalt.setTexture(*tekstura);
	ksztalt.setPosition(pozycja);
}
void Pocisk::przesun(float y)
{
	Vector2f pos;
	pos.y = y;
	ksztalt.move(pos);
}
void Pocisk::animuj()
{
	if (zegar.getElapsedTime().asMilliseconds() > 10.0f)
	{
		przesun(-4);
		zegar.restart();
	}
}