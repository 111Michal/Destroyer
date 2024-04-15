#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Pauza.h"
using namespace sf;
typedef struct atrybuty
{

	int punkty;
	int poziomtrudnosci;
};
class Informacje
{
private:
	atrybuty a;
	Text info[2];
	Font czcionka;
	int zycie;
	bool czyzapis;

public:
	Informacje(int *wsk);
	~Informacje() { czyzapis = false; }
	void draw(RenderWindow * okienko);
	void zmienhp(int ile);
	void zmienpkt(int ile);
	int getzycie() { return zycie; }
	int getpunkty() { return a.punkty; }
	void resethp();
	void zerujhp();
	void zapisz(Pauza *&wsk);
};

