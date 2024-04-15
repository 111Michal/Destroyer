#pragma once
#include <SFML/Graphics.hpp>
#include "Tlo.h"
#define MAX_LICZBA_POZIOMOW 4
using namespace sf;
class Menu :public Tlo
{
private:

    Font czcionka;
    Text menu[MAX_LICZBA_POZIOMOW];
    int selectedItem;
    Sprite napis;
    Texture tekstura;
public:
    Menu(float width, float height, int *poziomtrudnosci);
   	void przesunG();
   	void przesunD();
    int getSelectedItem() { return selectedItem; }
   	void draw(RenderWindow *okienko);
    void zmienPoziom(int* poziomtrudnosci);
    void myDelay(int opoznienie);

};

