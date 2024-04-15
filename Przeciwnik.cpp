#include "Przeciwnik.h"
Przeciwnik::Przeciwnik(Texture *tekstura, Vector2f pozycja )
{
	tekstura->loadFromFile("enemy.png");
	ksztalt.setTexture(*tekstura);
	ksztalt.setPosition(pozycja);
}
void Przeciwnik::przesun(float y)
{
	Vector2f pos;
	pos.y = pos.y + y;
	ksztalt.move(pos);

}
void Przeciwnik::animuj()
{
	if (zegar.getElapsedTime().asMilliseconds() > 10.0f)
	{
		przesun(2);
		zegar.restart();
	}
}