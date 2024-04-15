/*------------------------------------------------------------

Temat projektu: Gra komputerowa

Zakres projektu:
1. Co najmniej 4 animowane elementy
  1. Co najmniej jeden napis
  2. Co najmniej jeden element o nieregularnym kszta³cie i rozmiarze min. 10x10 punktów
2. Sta³e elementy graficzne
3. Sterowanie animacj¹ przez co najmniej jednego u¿ytkownika
4. Wybór przez u¿ytkownika co najmniej poziomu gry, okreœlaj¹cego jej trudnoœæ
5. Prezentacja ekranu Help
6. Zakoñczenie gry w dowolnym momencie
7. Zapis informacji o grze do lokalnego pliku
8. Wykorzystanie tablicy struktur do przechowywania danych, np. o u¿ytkownikach
9. Przekazanie do funkcji przez wskaŸnik
10. Realizacja szkieletu programu (i jego logiki) z wykorzystaniem technik programowania obiektowego


------------------------------------------------------------*/





/*------------------------------------------------------------

Program glowny

------------------------------------------------------------*/
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
#include <iostream>
#include <time.h>
#include "Menu.h"
#include "Gracz.h"
#include "Przeciwnik.h"
#include "Pocisk.h"
#include "Pauza.h"
#include "Informacje.h"
#include "Highscore.h"
#include "Meteor.h"
using namespace sf;


void sterujpauza(Vector2f pozycja,Vector2f rozmiar, std::string tekst, bool &flaga, Pauza *&wsk)
{
	switch (flaga)
	{
	case false:
		flaga = true;
		wsk = new Pauza(pozycja, rozmiar, tekst);
		break;
	case true:
		flaga = false;
		delete wsk;
		wsk = NULL;
		break;
	}
}

int losowanie(bool &czypierwszylos, int &pamiec)
{
	int losowa = 0, los = 0;
	bool done = 0;
	std::cout << "Pamiec: " << pamiec << std::endl;
	if (czypierwszylos == true)
	{
		losowa = rand() % 708;
		czypierwszylos = false;

		std::cout << "Pierwszy los: " << losowa << std::endl;
	}
	else
	{

		if (pamiec - 93 >= 0 && pamiec + 93 <= 707)
		{
			//losowanie z ktorego przedzialu
			los = (rand() % 2) + 1;
			std::cout << "Los do obu: " << los << std::endl;
			if (los == 1)
			{
				losowa = rand() % ((pamiec - 93) + 1);
			}
			if (los == 2)
			{
				losowa = rand() % (708 - (pamiec + 93)) + (pamiec + 93);
			}
			std::cout << "Los z obu przedzialow: " << losowa << std::endl;
			done = true;
		}
		if (pamiec - 93 >= 0 && done == false)
		{
			losowa = rand() % ((pamiec - 93) + 1);
			std::cout << "Los z lewego przedzialu: " << losowa << std::endl;
			done = true;
		}
		if (pamiec + 93 <= 707 && done == false)
		{
			losowa = rand() % (708 - (pamiec + 93)) + (pamiec + 93);
			std::cout << "Los z prawego przedzialu: " << losowa << std::endl;
			done = true;
		}

		done = false;
	}
	pamiec = losowa;
	return losowa;
}


int main()
{
	int selected = 8,  poziomtrudnosci = 3000, * wskaznik = &poziomtrudnosci, pamiec = 0, los = 0;
	bool czypauza = 0, czyf1 = 0, czyprzegrana = 0, czypierwszylos = 1;

	srand(time(NULL));

	RenderWindow *window = new RenderWindow(VideoMode(800, 600), "Destroyer", sf::Style::Close);
	Texture *przeciwniktext=NULL, *pocisktext=NULL, *meteortext = NULL;
	Tlo* tlo = NULL;
	Highscore *highscore = NULL;
	Pauza* pauza = NULL;
	Pauza* zapis = NULL;
	Informacje* informacje = NULL;
	Clock* zegar[3] = { NULL, NULL,NULL };
	Gracz* gracz = NULL;
	Menu* menu = new Menu(window->getSize().x, window->getSize().y, wskaznik);

	std::vector<Przeciwnik> przeciwnik;
	std::vector<Pocisk> pocisk;
	std::vector<Meteor> meteor;


	//SoundBuffer buffer;
	//buffer.loadFromFile("376694__daleonfire__laser.wav");
	//{
	//	return 0;
	//}
	//Sound sound;
	//sound.setBuffer(buffer);
	
	window->setFramerateLimit(60);


	while (window->isOpen())
	{

		Event event;

		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window->close();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (selected == 8)
				{
					if (event.key.code == sf::Keyboard::Up )
					{
						menu->myDelay(250);
						menu->przesunG();
					}

					if (event.key.code == sf::Keyboard::Down )
					{
						menu->myDelay(250);
						menu->przesunD();
					}

					if (event.key.code == sf::Keyboard::Enter && menu->getSelectedItem() == 1)                         //klawisze dzialajace w menu
					{
						//std::cout << "Zmiana ..." << std::endl;
						menu->zmienPoziom(wskaznik);
					}
					if (event.key.code == sf::Keyboard::Enter && menu->getSelectedItem() == 2)
					{
						delete menu;
						highscore = new Highscore(window->getSize().x, window->getSize().y); // tworzenie obiektu highscore
						selected = 2;

					}
					if (event.key.code == sf::Keyboard::Enter && menu->getSelectedItem() == 3 )
					{
						window->close();
					}
					if (event.key.code == sf::Keyboard::Enter && menu->getSelectedItem() == 0)
					{
						selected = 0;

						if (menu != NULL)
						{
							delete menu;  //usuwam menu
							menu = NULL;  //
						}
						informacje = new Informacje(wskaznik);
						tlo = new Tlo();
						gracz = new Gracz;
						zegar[0] = new Clock;
						zegar[1] = new Clock;       
						zegar[2] = new Clock;// tworzenie obiektów przy starcie gry
						pocisktext = new Texture;
						przeciwniktext = new Texture;
						meteortext = new Texture;
					}
				}
				if (selected == 2)
				{
					if (event.key.code == sf::Keyboard::Escape)
					{
						delete highscore;
						highscore = NULL;
						menu = new Menu(window->getSize().x, window->getSize().y, wskaznik);
						selected = 8;
					}
					if (event.key.code == sf::Keyboard::D)
					{
						highscore->wyczyscplik();                                //usuniecie pliku
						highscore = new Highscore(window->getSize().x, window->getSize().y); //utworzenie nowego highscore
					}
				}
				if (selected == 0)
				{
				
					if (event.key.code == sf::Keyboard::Escape && czyf1 == false)
					{
						sterujpauza( Vector2f(200, 200), Vector2f(400, 200),"Czy na pewno chcesz zakonczyc?\nWynik nie zostanie zapisany\nEnter - Tak, Esc - Nie", czypauza, pauza);
						
					}
					if (event.key.code == sf::Keyboard::Escape && czyf1 == false && czyprzegrana == true)
					{
						delete informacje;
						informacje = new Informacje(wskaznik);                   //usuniecie obiektu informacje i utworzenie nowego
						czyprzegrana = false;
						if (zapis != NULL)
						{
							delete zapis;
							zapis = NULL;
						}
					}
					if (event.key.code == sf::Keyboard::F1 && czypauza == false)
					{
						sterujpauza(Vector2f(100, 200), Vector2f(600, 200),"Zestrzel nadlatujacych przeciwnikow\nPoruszanie - AD\nSpacja - strzal\nEsc - pauza\nF1 - pomoc\nWcisnij F1 aby wylaczyc okno", czyf1, pauza);
						
					}
					
					if (event.key.code == sf::Keyboard::Enter && czypauza == true)
					{
						przeciwnik.clear();
						czypierwszylos = true;
						pocisk.clear();
						meteor.clear();
						
						delete tlo;
						tlo = NULL;
						delete przeciwniktext;
						przeciwniktext = NULL;
						delete pocisktext;
						pocisktext = NULL;
						delete meteortext;
						meteortext = NULL;
						delete gracz;
						gracz = NULL;
						delete informacje;
						informacje = NULL;
						delete pauza;
						pauza = NULL;
						delete zegar[0];
						zegar[0] = NULL;
						delete zegar[1];
						zegar[1] = NULL;
						delete zegar[2];
						zegar[2] = NULL;

						if(zapis != NULL)
						{
							delete zapis;
							zapis = NULL;
						}
						

						menu = new Menu(window->getSize().x, window->getSize().y, wskaznik);
						selected = 8;
						czypauza = false;
					}
					if (event.key.code == sf::Keyboard::S && czypauza == true && czyprzegrana == true)
					{
						informacje->zapisz(zapis);
					
					}
				}
			}
		}
		if (selected == 0)
		{
			if (czypauza == 0 && czyf1 ==0)
			{

				if (Keyboard::isKeyPressed(Keyboard::Key::A))
				{
					if (gracz->getKsztalt().getPosition().x > 0)
						gracz->przesun(-8);
				}                                                                          // przesuwanie gracza
				if (Keyboard::isKeyPressed(Keyboard::Key::D))
				{
					if (gracz->getKsztalt().getPosition().x < window->getSize().x - gracz->getKsztalt().getGlobalBounds().width)
						gracz->przesun(8);
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::Space))
				{
					if (zegar[2]->getElapsedTime().asMilliseconds() > 300)
					{
						pocisk.push_back(Pocisk(pocisktext, Vector2f(gracz->getPosx() + gracz->getKsztalt().getGlobalBounds().width / 2 - 4.5, 500)));
					                        //umieszczenie pocisku
						zegar[2]->restart();
					}
				}
				
				for (size_t i = 0; i < pocisk.size(); i++)
				{
					pocisk[i].animuj();

					if (pocisk[i].getKsztalt().getPosition().y < 0)
					{
						pocisk.erase(pocisk.begin() + i);        //usuniecie pocisku gdy osiagnie koniec okna
					}

					for (size_t j = 0; j < przeciwnik.size(); j++)
					{
						if (pocisk[i].getKsztalt().getGlobalBounds().intersects(przeciwnik[j].getKsztalt().getGlobalBounds()))
						{
							przeciwnik[i].getKsztalt().getPosition().x;
							przeciwnik.erase(przeciwnik.begin() + j);                                                            ///kolizja przeciwnika i pocisku
							pocisk.erase(pocisk.begin() + i);
							informacje->zmienpkt(1);
							break;
						}
					}
				}
				
				if (zegar[0]->getElapsedTime().asMilliseconds() > poziomtrudnosci) 
				{
					
					
					przeciwnik.push_back(Przeciwnik(przeciwniktext, Vector2f(losowanie(czypierwszylos,pamiec), 0))); //losowe umieszczanie przeciwnikow
					zegar[0]->restart();
				}
				

				if (zegar[1]->getElapsedTime().asMilliseconds() > 2000)
				{
					meteor.push_back(Meteor(meteortext, rand() % window->getSize().y)); //umieszczanie meteorów
					zegar[1]->restart();
				}
				
				for (size_t i = 0; i < meteor.size(); i++)
				{
					meteor[i].animuj();
					if (meteor[i].getKsztalt().getPosition().x > window->getSize().x + 30 || meteor[i].getKsztalt().getPosition().y < -30)
					{
						meteor.erase(meteor.begin() + i);        //usuniecie meteoru gdy osiagnie koniec okna
					}
				}


				for (size_t i = 0; i < przeciwnik.size(); i++)
				{
					przeciwnik[i].animuj(); //przesuwanie przeciwnikow
					if (przeciwnik[i].getKsztalt().getPosition().y > window->getSize().y)
					{
						przeciwnik.erase(przeciwnik.begin() + i);                           //usuniecie przeciwnika po osiagnieciu krawedzi
						informacje->zmienhp(1);
					}
					if (przeciwnik[i].getKsztalt().getGlobalBounds().intersects(gracz->getKsztalt().getGlobalBounds()))
					{
						przeciwnik.erase(przeciwnik.begin() + i);                           //usuniecie przeciwnika po zderzeniu z graczem
						informacje->zerujhp();
					}
				}
				if (informacje->getzycie() <= 0)
				{
					czyprzegrana = true;
					przeciwnik.clear();
					czypierwszylos = true;
					pocisk.clear();
					meteor.clear();
													                                             //przegrana												
					czypauza = true;
					
					delete gracz;
					delete zegar[0];
					delete zegar[1];
					delete zegar[2];
					
					gracz = new Gracz;
													
					pauza = new Pauza(Vector2f(200, 200), Vector2f(400, 200), "Przegrales!!!\nEsc - Zacznij od nowa\nS - Zapisz wynik\nEnter - Powrot do menu");
					
					zegar[0] = new Clock;
					zegar[1] = new Clock;
					zegar[2] = new Clock;
					
													
				}
			}
			
		}
		

		window->clear();
		if (selected == 8)
		{
			menu->draw(window);     //rysowanie menu
		}
	
		if (selected == 0)
		{
			
			tlo->draw(window);
			
			for (size_t i = 0; i < meteor.size(); i++)
			{
				window->draw(meteor[i].getKsztalt()); //rysowanie meteorow
			}
			for (size_t i = 0; i < pocisk.size(); i++)
			{
				window->draw(pocisk[i].getKsztalt()); //rysowanie pociskow
			}
			
			gracz->draw(window);//rysowanie gracza
			
			
			for (size_t i = 0; i < przeciwnik.size(); i++)
			{
				window->draw(przeciwnik[i].getKsztalt()); //rysowanie przeciwnikow
			}
			
			
			informacje->draw(window); // punkty,zycie
					
			
			if ((czypauza == true && pauza != NULL) || (czyf1 == true && pauza != NULL))
			{
				pauza->draw(window); 
				                 //stan pauzy
			}
			if (zapis != NULL)
			{
				zapis->draw(window);
			}
			
			
		}
		if (selected == 2)
		{
			highscore->draw(window);
		}
		window->display();
	
	}
	return 0;
}
