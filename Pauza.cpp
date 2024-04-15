#include "Pauza.h"
Pauza::Pauza(Vector2f pozycja, Vector2f rozmiar, std::string tekst)
{

	if (!czcionka.loadFromFile("ghostclanleft.ttf"))
	{
		return;
	}
	napis.setFont(czcionka);
	napis.setCharacterSize(32);
	napis.setFillColor(Color(255, 69, 0));
	napis.setString(tekst);
	textRect = napis.getLocalBounds();
	napis.setOrigin(textRect.width / 2, textRect.height / 2);
	napis.setPosition(Vector2f((rozmiar.x / 2.0f)+ pozycja.x, (rozmiar.y / 2.0f) + pozycja.y));
	

}
void Pauza::draw(RenderWindow* okienko)
{
	okienko->draw(napis);
}
