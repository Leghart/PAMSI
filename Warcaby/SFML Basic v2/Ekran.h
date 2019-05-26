#ifndef WYSWIETLANIE_H
#define WYSWIETLANIE _H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
using namespace std;

/* klasa odpowiedzialna na wyswietlanie graficzne gry*/
class Ekran{
public:
	sf::Texture Pionek;
	sf::Texture PionekC;
	sf::Texture DamkaB;
	sf::Texture DamkaC;
	sf::Texture Pole;
	sf::Texture texture;
	sf::Texture texture_menu;
	sf::Texture menu;
	sf::Sprite Sprite;
	sf::Sprite Sprite_menu;
	sf::Sprite Pb1, Pb2, Pb3, Pb4, Pb5, Pb6, Pb7, Pb8, Pb9, Pb10, Pb11, Pb12;
	sf::Sprite Pc1, Pc2, Pc3, Pc4, Pc5, Pc6, Pc7, Pc8, Pc9, Pc10, Pc11, Pc12;

	void Tworz_Plansze();
	void Ulozenie_Pionkow();
};


/* Wczytuje tekstury elementow planszy i menu */
void Ekran::Tworz_Plansze()
{
	texture.loadFromFile("plansza.jpg");
	texture.setSmooth(true);

	Sprite.setTexture(texture);

	texture_menu.loadFromFile("tlo.jpg");
	texture_menu.setSmooth(true);
	Sprite_menu.setTexture(texture_menu);

	Pole.loadFromFile("reset.png");
	DamkaB.loadFromFile("lannister_D.png");
	DamkaC.loadFromFile("stark_D.png");
}

/* Wczytuje i umieszcza na planszy biale i czarne pionki */
void Ekran::Ulozenie_Pionkow()
{
	Pionek.loadFromFile("lannister.png");
	Pionek.setSmooth(true);

	Pb1.setTexture(Pionek);
	Pb2.setTexture(Pionek);
	Pb3.setTexture(Pionek);
	Pb4.setTexture(Pionek);
	Pb5.setTexture(Pionek);
	Pb6.setTexture(Pionek);
	Pb7.setTexture(Pionek);
	Pb8.setTexture(Pionek);
	Pb9.setTexture(Pionek);
	Pb10.setTexture(Pionek);
	Pb11.setTexture(Pionek);
	Pb12.setTexture(Pionek);

	Pb1.setScale(1.2, 1.2);
	Pb1.setPosition(93, 93);

	Pb2.setScale(1.2, 1.2);
	Pb2.setPosition(249, 93);

	Pb3.setScale(1.2, 1.2);
	Pb3.setPosition(403, 93);

	Pb4.setScale(1.2, 1.2);
	Pb4.setPosition(557, 93);

	////////////////////////////////

	Pb5.setScale(1.2, 1.2);
	Pb5.setPosition(171, 170);

	Pb6.setScale(1.2, 1.2);
	Pb6.setPosition(325, 170);

	Pb7.setScale(1.2, 1.2);
	Pb7.setPosition(479, 170);

	Pb8.setScale(1.2, 1.2);
	Pb8.setPosition(634, 170);

	///////////////////////////////////

	Pb9.setScale(1.2, 1.2);
	Pb9.setPosition(93, 247);

	Pb10.setScale(1.2, 1.2);
	Pb10.setPosition(249, 247);

	Pb11.setScale(1.2, 1.2);
	Pb11.setPosition(403, 247);

	Pb12.setScale(1.2, 1.2);
	Pb12.setPosition(557, 247);

	//////////////////////////////////////////////////////////////////////////////////

	PionekC.loadFromFile("stark.png");
	PionekC.setSmooth(true);

	Pc1.setTexture(PionekC);
	Pc2.setTexture(PionekC);
	Pc3.setTexture(PionekC);
	Pc4.setTexture(PionekC);
	Pc5.setTexture(PionekC);
	Pc6.setTexture(PionekC);
	Pc7.setTexture(PionekC);
	Pc8.setTexture(PionekC);
	Pc9.setTexture(PionekC);
	Pc10.setTexture(PionekC);
	Pc11.setTexture(PionekC);
	Pc12.setTexture(PionekC);

	Pc1.setScale(1.2, 1.2);
	Pc1.setPosition(634, 634);

	Pc2.setScale(1.2, 1.2);
	Pc2.setPosition(479, 634);

	Pc3.setScale(1.2, 1.2);
	Pc3.setPosition(325, 634);

	Pc4.setScale(1.2, 1.2);
	Pc4.setPosition(171, 634);

	////////////////////////////////

	Pc5.setScale(1.2, 1.2);
	Pc5.setPosition(557, 557);

	Pc6.setScale(1.2, 1.2);
	Pc6.setPosition(403, 557);

	Pc7.setScale(1.2, 1.2);
	Pc7.setPosition(249, 557);

	Pc8.setScale(1.2, 1.2);
	Pc8.setPosition(93, 557);

	///////////////////////////////////

	Pc9.setScale(1.2, 1.2);
	Pc9.setPosition(634, 480);

	Pc10.setScale(1.2, 1.2);
	Pc10.setPosition(479, 480);

	Pc11.setScale(1.2, 1.2);
	Pc11.setPosition(325, 480);

	Pc12.setScale(1.2, 1.2);
	Pc12.setPosition(171, 480);
}



#endif WYSWIETLANIE_H
#pragma once
