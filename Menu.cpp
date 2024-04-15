#include "Menu.h"
Menu::Menu(float width, float height, int *poziomtrudnosci)
{
	selectedItem = 0;
	if (!czcionka.loadFromFile("ghostclanleft.ttf"))
	{
		return;
	}
	tekstura.loadFromFile("napis.png");
	napis.setTexture(tekstura);
	napis.setPosition(0,0);
	menu[0].setFont(czcionka);
	menu[0].setStyle(sf::Text::Bold);
	menu[0].setFillColor(Color::Cyan);
	menu[0].setString("Nowa gra");
	menu[0].setPosition(Vector2f((width / 2) - menu[0].getGlobalBounds().width / 2, (height / (MAX_LICZBA_POZIOMOW +2) * 1)+70));

	menu[1].setFont(czcionka);
	menu[1].setFillColor(Color::White);
	switch (*poziomtrudnosci)
	{
	case 3000:
		menu[1].setString("Poziom trudnosci: Latwy");
		break;
	case 1000:
		menu[1].setString("Poziom trudnosci: Sredni");
		break;
	case 500:
		menu[1].setString("Poziom trudnosci: Trudny");
		break;
	}
	menu[1].setPosition(Vector2f((width / 2) - menu[1].getGlobalBounds().width / 2, (height / (MAX_LICZBA_POZIOMOW +2) * 2)+70));

	menu[2].setFont(czcionka);
	menu[2].setFillColor(Color::White);
	menu[2].setString("Najlepsze wyniki");
	menu[2].setPosition(Vector2f((width / 2) - menu[2].getGlobalBounds().width / 2, (height / (MAX_LICZBA_POZIOMOW +2) * 3)+70));

	menu[3].setFont(czcionka);
	menu[3].setFillColor(Color::White);
	menu[3].setString("Wyjscie");
	menu[3].setPosition(Vector2f((width / 2) - menu[3].getGlobalBounds().width / 2, (height / (MAX_LICZBA_POZIOMOW + 2 ) * 4)+70));

}
void Menu::przesunG()
{
	if (selectedItem - 1 >= 0)
	{
		menu[selectedItem].setFillColor(Color::White);
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem--;
		if (selectedItem < 0)
			selectedItem = MAX_LICZBA_POZIOMOW - 1;
		menu[selectedItem].setFillColor(sf::Color::Cyan);
		menu[selectedItem].setStyle(sf::Text::Bold);
	}
}
void Menu::przesunD()
{
	if (selectedItem + 1 < MAX_LICZBA_POZIOMOW)
	{
		menu[selectedItem].setFillColor(Color::White);
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem++;
		if (selectedItem >= MAX_LICZBA_POZIOMOW)
			selectedItem = 0;
		menu[selectedItem].setFillColor(sf::Color::Cyan);
		menu[selectedItem].setStyle(sf::Text::Bold);
	}
}
void Menu::draw(RenderWindow* okienko)
{
	okienko->draw(tlo);
	okienko->draw(napis);
	for (int i = 0; i < MAX_LICZBA_POZIOMOW; i++)
	{
		okienko->draw(menu[i]);
	}
}
void Menu::zmienPoziom(int *poziomtrudnosci)
{
	switch (*poziomtrudnosci)
	{
	case 3000:
		menu[selectedItem].setString("Poziom trudnosci: Sredni");
		*poziomtrudnosci = 1000;
		break;
	case 1000:
		menu[selectedItem].setString("Poziom trudnosci: Trudny");
		*poziomtrudnosci = 500;
		break;
	case 500:
		menu[selectedItem].setString("Poziom trudnosci: Latwy");
		*poziomtrudnosci = 3000;
		break;
	}
			
}
void Menu::myDelay(int opoznienie)
{
	sf::Clock zegar;
	sf::Time czas;
	while (1)
	{
		czas = zegar.getElapsedTime();
		if (czas.asMilliseconds() > opoznienie)
		{
			zegar.restart();
			break;
		}
			
	}	
}
