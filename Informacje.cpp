#include "Informacje.h"
Informacje::Informacje(int *wsk)
{
	zycie = 3;
	czyzapis = false;
	a.punkty = 0;
	a.poziomtrudnosci = *wsk;
	if (!czcionka.loadFromFile("ghostclanleft.ttf"))
	{
		return;
	}


	info[0].setFont(czcionka);
	info[0].setFillColor(Color::Cyan);
	info[0].setPosition(Vector2f(0, 2));
	info[0].setString("Zycie: " + std::to_string(zycie));

	info[1].setFont(czcionka);
	info[1].setFillColor(Color::Cyan);
	info[1].setPosition(Vector2f(0, 32));
	info[1].setString("Punkty: " + std::to_string(a.punkty));

}
void Informacje::zmienhp(int ile)
{
	zycie = zycie - ile;
	info[0].setString("Zycie: " + std::to_string(zycie));
}
void Informacje::resethp()
{
	zycie = 3;
	info[0].setString("Zycie: " + std::to_string(zycie));
}
void Informacje::zerujhp()
{
	zycie = 0;
	info[0].setString("Zycie: " + std::to_string(zycie));
}
void Informacje::zmienpkt(int ile)
{
	a.punkty = a.punkty + ile;
	info[1].setString("Punkty: " + std::to_string(a.punkty));
}

void Informacje::draw(RenderWindow* okienko)
{
	for (int i = 0; i < 2; i++)
	{
		okienko->draw(info[i]);
	}
}
void Informacje::zapisz(Pauza *&wsk)
{
	if (czyzapis == false)
	{
		FILE* fp;
		fp = fopen("Highscore.dat", "a+b");
		if (fp == NULL)
		{
			printf("Bladotwarcia pliku");
			return;
		}
		fwrite(&(a), sizeof(atrybuty), 1, fp);
		fclose(fp);
		

		std::cout << "Zapisano";
		wsk = new Pauza(Vector2f(200, 300), Vector2f(400, 200), "Zapisano!");
		czyzapis = true;
	}
	
}

