#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "Highscore.h"

Highscore::Highscore(float width, float height)
{
	/*tekstura.loadFromFile("background.png");
	tlo.setTexture(tekstura);*/
	dane = NULL;
	FILE* fp;
	atrybuty buf1;
	
	fp = fopen("Highscore.dat", "r+b");
	if (fp == NULL)
	{
		//printf("Brak wynikow");
		liczba = 1;
		menu = new Text[2];
		if (!czcionka.loadFromFile("ghostclanleft.ttf"))
		{
			return;
		}
		menu[0].setFont(czcionka);
		menu[0].setFillColor(Color::White);
		menu[0].setString("Brak wynikow");
		menu[1].setFont(czcionka);
		menu[1].setFillColor(Color::Cyan);
		menu[1].setString("Esc - powrot do menu, D - wyczysc liste");
		menu[1].setPosition(Vector2f(0, 500));
		return;
	}
	else
	{
		fseek(fp, 0, SEEK_END);//przesunsiena ostatni bajt => ftell() zwrociliczba bajtoww pliku
		liczba = ftell(fp) / sizeof(atrybuty);// = liczba_bajtow/rozmiar_w_bajtach_student
		rewind(fp);

		dane = new atrybuty[liczba];
		for (int i = 0; i < liczba; i++)
		{
			fread(&buf1, sizeof(atrybuty), 1, fp);
			dane[i].punkty = buf1.punkty;
			dane[i].poziomtrudnosci = buf1.poziomtrudnosci;
		}

		fclose(fp);
		sortowanie(0, return_liczba() - 1);
		drukuj();
	}
	
}

void Highscore::drukuj()
{
	if (liczba > 5)
	{
		liczba = 5;
	}
	menu = new Text[liczba+1];
	if (!czcionka.loadFromFile("ghostclanleft.ttf"))
	{
		return;
	}
	for (int i = 0; i < liczba; i++)
	{
		menu[i].setFont(czcionka);
		menu[i].setFillColor(Color::White);

		switch (dane[i].poziomtrudnosci)
		{
		case 3000:
			menu[i].setString("Punkty: " + std::to_string(dane[i].punkty) + " | | " + "Poziom: Latwy");
			break;
		case 1000:
			menu[i].setString("Punkty: " + std::to_string(dane[i].punkty) + " | | " + "Poziom: Sredni");
			break;
		case 500:
			menu[i].setString("Punkty: " + std::to_string(dane[i].punkty) + " | | " + "Poziom: Trudny");
			break;
		}
		
		menu[i].setPosition(Vector2f(0, 100 * i));
	}
	
	menu[liczba].setFont(czcionka);
	menu[liczba].setFillColor(Color::Cyan);
	menu[liczba].setString("Esc - powrot do menu, D - wyczysc liste");
	menu[liczba].setPosition(Vector2f(0, 500));
}
void Highscore::sortowanie(int left, int right)
{
	int i = left;
	int j = right;
	int x = dane[(left + right) / 2].punkty;
	do
	{
		while (dane[i].punkty > x)
			i++;

		while (dane[j].punkty < x)
			j--;

		if (i <= j)
		{
			std::swap(dane[i].punkty, dane[j].punkty);

			i++;
			j--;
		}
	} while (i <= j);

	if (left < j) sortowanie(left, j);

	if (right > i) sortowanie(i, right);

}
void Highscore::wyczyscplik()
{
	if (remove("Highscore.dat") == 0)
	{
		delete this;
	}
}
void Highscore::draw(RenderWindow* okienko)
{
	okienko->draw(tlo);
	for (int i = 0; i < liczba+1; i++)
	{
		okienko->draw(menu[i]);
	}
}