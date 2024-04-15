#include "Meteor.h"
Meteor::Meteor(Texture* tekstura, float y )
{
	tekstura->loadFromFile("meteor.png");
	ksztalt.setTexture(*tekstura);
	ksztalt.setPosition(Vector2f(0,y));
}
void Meteor::przesun(float x, float y)
{
	sf::Vector2f pos;
	pos.x = pos.x + x;
	pos.y = pos.y - y;
	ksztalt.move(pos);
}
void Meteor::obroc(float x)
{
	ksztalt.rotate(x);
}
void Meteor::animuj()
{
	if (zegar.getElapsedTime().asMilliseconds() > 10.0f)
	{
		przesun(3, 0.75);
		obroc(2);
		zegar.restart();
	}
}
