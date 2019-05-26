#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include "Ekran.h"
#include "Arena.h"
#include "AI.h"
using namespace std;

/* Zamiana wspolrzednych na plaszny na wygondy uklad odniesienia*/
int ZwrocX(int);
char ZwrocY(int);


void Gracz_vs_SI(Ekran &E,Arena &A,AI& AI) {
	/* zmienne startowe*/
	int x, y, gracz = 1, xk, yk, xp, yp;
	int pom[2];
	bool Czy_Lewy = false, Czy_Prawy = false, wysw = false;
	int bicie = 0;
	int punkty_b = 0, punkty_c = 0;

	sf::RenderWindow oknoAplikacji(sf::VideoMode(800, 800, 32), "Warcaby");

	while (oknoAplikacji.isOpen()) {

		/* zmiana tury gracza*/
		if (wysw == false) {
			system("cls");
			cout << "TURA GRACZA " << gracz << endl;
			wysw = true;
		}
		sf::Event zdarzenie;

		while (oknoAplikacji.pollEvent(zdarzenie)) {
			/* warunki zamykajace okno aplikacji*/
			{
				if (zdarzenie.type == sf::Event::Closed)
					oknoAplikacji.close();

				if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Escape)
					oknoAplikacji.close();

				if (zdarzenie.type == sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button == sf::Mouse::Middle)
					oknoAplikacji.close();
			}

			/* wybiera polozenie startowe*/
			if (zdarzenie.type == sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button == sf::Mouse::Left)
			{
				x = ZwrocX(zdarzenie.mouseButton.y);
				y = ZwrocY(zdarzenie.mouseButton.x);
				Czy_Lewy = true;
			}

			/* wybiera polozenie koncowe*/
			if (zdarzenie.type == sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button == sf::Mouse::Right)
			{
				xk = ZwrocX(zdarzenie.mouseButton.y);
				yk = ZwrocY(zdarzenie.mouseButton.x);
				Czy_Prawy = true;
			}

			if (Czy_Lewy == true && Czy_Prawy == true) {
				wysw = false;
				bicie = 0;
				xp = xk;
				yp = (int)yk - 65;
				Czy_Lewy = false;
				Czy_Prawy = false;

				pom[1] = ((int)yk - 65) - ((int)y - 65);
				pom[0] = xk - x;

				int wynik = A.Przesun_Pionek(x, (int)y - 65, xk, (int)yk - 65, gracz, E);

				if (wynik == 1) //jesli mozliwy ruch
				{
					bicie++;
					switch (A.Kierunek_Bicia(pom)) { // to w zaleznosci w jakim kierunku jest oblicz nowe polozenie pionka
					case 0: {
						pom[1] = ((int)yk - 65) - ((int)y - 65) - 1;
						pom[0] = xk - x - 1;
					}
						break;
					case 1: {
						pom[1] = ((int)yk - 65) - ((int)y - 65) + 1;
						pom[0] = xk - x - 1;
					}
						break;
					case 2: {
						pom[1] = ((int)yk - 65) - ((int)y - 65) - 1;
						pom[0] = xk - x + 1;
					}
						break;
					case 3: {
						pom[1] = ((int)yk - 65) - ((int)y - 65) + 1;
						pom[0] = xk - x + 1;
					}
						break;
					}
					/* aktualizacja polozenia*/
					yp = ((int)y - 65) + pom[1];
					xp = x + pom[0];
				}
				gracz++;

				/* tura SI*/
				AI.Koncowy_Ruch(A);
				A.Przesun_Pionek(AI.TabKoniec[0], AI.TabKoniec[1], AI.TabKoniec[2], AI.TabKoniec[3], gracz, E);
				gracz--;
			}
		}
		/* odswiez ulozenie pinkow na planszy*/
		{
			oknoAplikacji.draw(E.Sprite);
			oknoAplikacji.draw(E.Pb1);
			oknoAplikacji.draw(E.Pb2);
			oknoAplikacji.draw(E.Pb3);
			oknoAplikacji.draw(E.Pb4);
			oknoAplikacji.draw(E.Pb5);
			oknoAplikacji.draw(E.Pb6);
			oknoAplikacji.draw(E.Pb7);
			oknoAplikacji.draw(E.Pb8);
			oknoAplikacji.draw(E.Pb9);
			oknoAplikacji.draw(E.Pb10);
			oknoAplikacji.draw(E.Pb11);
			oknoAplikacji.draw(E.Pb12);

			oknoAplikacji.draw(E.Pc1);
			oknoAplikacji.draw(E.Pc2);
			oknoAplikacji.draw(E.Pc3);
			oknoAplikacji.draw(E.Pc4);
			oknoAplikacji.draw(E.Pc5);
			oknoAplikacji.draw(E.Pc6);
			oknoAplikacji.draw(E.Pc7);
			oknoAplikacji.draw(E.Pc8);
			oknoAplikacji.draw(E.Pc9);
			oknoAplikacji.draw(E.Pc10);
			oknoAplikacji.draw(E.Pc11);
			oknoAplikacji.draw(E.Pc12);
		}
		oknoAplikacji.display();
	}
}
void Gracz_vs_Gracz(Ekran &E, Arena &A) {

	/* zmienne startowe*/
	int x, y, gracz = 1, xk, yk, xp, yp;
	int pom[2];
	bool Czy_Lewy = false, Czy_Prawy = false, wysw = false;;
	int bicie = 0;
	int punkty_b = 0, punkty_c = 0;

	sf::RenderWindow oknoAplikacji(sf::VideoMode(800, 800, 32), "Warcaby");
	E.Tworz_Plansze();
	E.Ulozenie_Pionkow();

	while (oknoAplikacji.isOpen()) {

		/* zmiana tury gracza*/
		if (wysw == false) {
			system("cls");
			cout << "TURA GRACZA " << gracz << endl;
			wysw = true;
		}
		sf::Event zdarzenie;

		while (oknoAplikacji.pollEvent(zdarzenie)) {
			/* warunki zamykajace okno aplikacji*/
			{
				if (zdarzenie.type == sf::Event::Closed)
					oknoAplikacji.close();

				if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Escape)
					oknoAplikacji.close();

				if (zdarzenie.type == sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button == sf::Mouse::Middle)
					oknoAplikacji.close();
			}

			/* wybiera polozenie startowe*/
			if (zdarzenie.type == sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button == sf::Mouse::Left)
			{
				x = ZwrocX(zdarzenie.mouseButton.y);
				y = ZwrocY(zdarzenie.mouseButton.x);
				Czy_Lewy = true;
			}

			/* wybiera polozenie koncowe*/
			if (zdarzenie.type == sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button == sf::Mouse::Right)
			{
				xk = ZwrocX(zdarzenie.mouseButton.y);
				yk = ZwrocY(zdarzenie.mouseButton.x);
				Czy_Prawy = true;
			}

			if (Czy_Lewy == true && Czy_Prawy == true) {
				wysw = false;
				bicie = 0;
				xp = xk;
				yp = (int)yk - 65;
				Czy_Lewy = false;
				Czy_Prawy = false;

				pom[1] = ((int)yk - 65) - ((int)y - 65);
				pom[0] = xk - x;

				int wynik = A.Przesun_Pionek(x, (int)y - 65, xk, (int)yk - 65, gracz, E);
				/* jesli mozliwy ruch */
				if (wynik == 1 && gracz==1) 
				{
					bicie++;
					switch (A.Kierunek_Bicia(pom)) { // to w zaleznosci w jakim kierunku jest oblicz nowe polozenie pionka
					case 0: {
						pom[1] = ((int)yk - 65) - ((int)y - 65) - 1;
						pom[0] = xk - x - 1;
					}
							break;
					case 1: {
						pom[1] = ((int)yk - 65) - ((int)y - 65) + 1;
						pom[0] = xk - x - 1;
					}
							break;
					case 2: {
						pom[1] = ((int)yk - 65) - ((int)y - 65) - 1;
						pom[0] = xk - x + 1;
					}
							break;
					case 3: {
						pom[1] = ((int)yk - 65) - ((int)y - 65) + 1;
						pom[0] = xk - x + 1;
					}
							break;
					}
					/* aktualizacja polozenia*/
					yp = ((int)y - 65) + pom[1];
					xp = x + pom[0];
				}

				gracz--;

				/* tura 2 gracza */

				bicie = 0;
				xp = xk;
				yp = (int)yk - 65;
				Czy_Lewy = false;
				Czy_Prawy = false;

				pom[1] = ((int)yk - 65) - ((int)y - 65);
				pom[0] = xk - x;

				wynik = A.Przesun_Pionek(x, (int)y - 65, xk, (int)yk - 65, gracz, E);
				/* jesli mozliwy ruch */
				if (wynik == 1 && gracz==0)
				{
					bicie++;
					switch (A.Kierunek_Bicia(pom)) { // to w zaleznosci w jakim kierunku jest oblicz nowe polozenie pionka
					case 0: {
						pom[1] = ((int)yk - 65) - ((int)y - 65) - 1;
						pom[0] = xk - x - 1;
					}
							break;
					case 1: {
						pom[1] = ((int)yk - 65) - ((int)y - 65) + 1;
						pom[0] = xk - x - 1;
					}
							break;
					case 2: {
						pom[1] = ((int)yk - 65) - ((int)y - 65) - 1;
						pom[0] = xk - x + 1;
					}
							break;
					case 3: {
						pom[1] = ((int)yk - 65) - ((int)y - 65) + 1;
						pom[0] = xk - x + 1;
					}
							break;
					}
					/* aktualizacja polozenia*/
					yp = ((int)y - 65) + pom[1];
					xp = x + pom[0];
				}

				gracz++;
			}
		}
		/* odswiez ulozenie pinkow na planszy*/
		{
			oknoAplikacji.draw(E.Sprite);
			oknoAplikacji.draw(E.Pb1);
			oknoAplikacji.draw(E.Pb2);
			oknoAplikacji.draw(E.Pb3);
			oknoAplikacji.draw(E.Pb4);
			oknoAplikacji.draw(E.Pb5);
			oknoAplikacji.draw(E.Pb6);
			oknoAplikacji.draw(E.Pb7);
			oknoAplikacji.draw(E.Pb8);
			oknoAplikacji.draw(E.Pb9);
			oknoAplikacji.draw(E.Pb10);
			oknoAplikacji.draw(E.Pb11);
			oknoAplikacji.draw(E.Pb12);

			oknoAplikacji.draw(E.Pc1);
			oknoAplikacji.draw(E.Pc2);
			oknoAplikacji.draw(E.Pc3);
			oknoAplikacji.draw(E.Pc4);
			oknoAplikacji.draw(E.Pc5);
			oknoAplikacji.draw(E.Pc6);
			oknoAplikacji.draw(E.Pc7);
			oknoAplikacji.draw(E.Pc8);
			oknoAplikacji.draw(E.Pc9);
			oknoAplikacji.draw(E.Pc10);
			oknoAplikacji.draw(E.Pc11);
			oknoAplikacji.draw(E.Pc12);
		}
		oknoAplikacji.display();
	}//koniec while open
}
void Menu() {
	Ekran E;
	Arena A;
	AI AI;

	bool menu = false;
	bool Czy_Lewy = false, Czy_Prawy = false, wysw = false;
	int xpom, ypom,wybor=0;

	E.Tworz_Plansze();
	E.Ulozenie_Pionkow();

	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("soundtrack1.wav")) {
		cout << "Nie mozna wczytac sciezki dzwiekowej" << endl;
	}
	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.setVolume(20);
	sound.play();

	sf::RenderWindow MenuGlowne(sf::VideoMode(800, 800, 32), "Menu");
	while (MenuGlowne.isOpen()){
		sf::Event zdarzenie;
		while (MenuGlowne.pollEvent(zdarzenie)) {
			//warunki zamkniecia okna
			{
				if (zdarzenie.type == sf::Event::Closed)
					MenuGlowne.close();

				if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Escape)
					MenuGlowne.close();

				if (zdarzenie.type == sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button == sf::Mouse::Middle)
					MenuGlowne.close();
			}
			if (zdarzenie.type == sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button == sf::Mouse::Left){
				xpom = zdarzenie.mouseButton.x;
				ypom = zdarzenie.mouseButton.y;
				Czy_Lewy = true;
			}
			//obsluga przyciskow
			{
				if (Czy_Lewy == true) {
					if (xpom < 246 && xpom>33 && ypom < 622 && ypom>564) {
						wybor = 1;
						menu = true;
						MenuGlowne.close();
					}
					if (xpom < 212 && xpom>36 && ypom < 679 && ypom>642) {
						wybor = 2;
						menu = true;
						MenuGlowne.close();
					}
					if (xpom < 156 && xpom>39 && ypom < 755 && ypom>709)
						MenuGlowne.close();
				}
			}
		}
		MenuGlowne.draw(E.Sprite_menu);
		MenuGlowne.display();
	}

switch(wybor){
case 1:
	Gracz_vs_Gracz(E, A);
	break;
case 2:
	Gracz_vs_SI(E, A, AI);
	break;
default:
	break;
}
}


int main(){
	Menu();
	return 0;
}

/* zamienia wspolrzedne na planszy na numer kolumny */
char ZwrocY(int y)
{
	if (y > 90 && y < 168)	return 'A';
	else if (y > 168 && y < 245) return 'B';
	else if (y > 245 && y < 325) return 'C';
	else if (y > 325 && y < 400) return 'D';
	else if (y > 400 && y < 477) return 'E';
	else if (y > 477 && y < 555) return 'F';
	else if (y > 555 && y < 633) return 'G';
	else if (y > 633 && y < 710) return 'H';
	
}

/* zamienia wspolrzedne na planszy na numer wiersza */
int ZwrocX(int x)
{
	if (x > 90 && x < 168)	return 0;
	else if (x > 168 && x < 245) return 1;
	else if (x > 245 && x < 325) return 2;
	else if (x > 325 && x < 400) return 3;
	else if (x > 400 && x < 477) return 4;
	else if (x > 477 && x < 555) return 5;
	else if (x > 555 && x < 633) return 6;
	else if (x > 633 && x < 710) return 7;
}