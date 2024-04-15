#include "Gracz.h"
Gracz::Gracz(Vector2f pozycja )
{
	tekstura.loadFromFile("player.png");
	ksztalt.setTexture(tekstura);
	ksztalt.setPosition(pozycja);

}
void Gracz::przesun(float x)
{
	Vector2f pos;
	pos.x = pos.x + x;
	ksztalt.move(pos);
}
void Gracz::draw(RenderWindow* okienko)
{
	okienko->draw(ksztalt);
}
