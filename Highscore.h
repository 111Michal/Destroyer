#pragma once
#include <SFML/Graphics.hpp>
#include "Informacje.h"
#include "Tlo.h"

using namespace sf;
class Highscore :public Tlo
{
public:
    Highscore(float width, float height);
    void draw(RenderWindow* okienko);
    void drukuj();
    void sortowanie(int left, int right);
    int return_liczba() { return liczba; }
    void wyczyscplik();
    
private:
  
    atrybuty* dane;
    Font czcionka;
    Text * menu;
    int liczba;
    
   
};

