#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>
#include <string>
#include <iostream>
#include "Ekran.h"
#include "Arena.h"
#include "AI.h"
using namespace std;

/* PROTOTYPY: Zamiana wspolrzednych na plaszny na wygodnyy uklad odniesienia i menu*/
char dane_j[ROZ*ROZ];
char dane_d[ROZ][ROZ];
int ZwrocX(int);
char ZwrocY(int);
int Menu();
void jnad(char*);
void dnaj(char**);


/* Tryb gry umozliwiacjacy pojedynek ze sztuczna inteligencja */
int Gracz_vs_SI(Ekran &E, Arena &A, AI& AI) {
	/* zmienne startowe*/
	int x, y, gracz = 1, xk, yk, xp, yp;
	int pom[2];
	bool Czy_Lewy = false, Czy_Prawy = false, wysw = false;
	int bicie = 0;
	int punkty = 0;
	int pkt_si = 0;

	sf::RenderWindow oknoAplikacji(sf::VideoMode(800, 800, 32), "Warcaby");

	while (oknoAplikacji.isOpen()) {
		sf::Event zdarzenie;
		while (oknoAplikacji.pollEvent(zdarzenie)) {
			/* warunki zamykajace okno aplikacji*/
			{
				if (zdarzenie.type == sf::Event::Closed) {
					oknoAplikacji.close();
					return 0;
				}
				if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Escape) {
					oknoAplikacji.close();
					return 0;
				}
				if (zdarzenie.type == sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button == sf::Mouse::Middle) {
					oknoAplikacji.close();
					return 0;
				}
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

			/* jesli zostaly klikniete LPM i PPM */
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
					punkty++;
					switch (A.Kierunek_Bicia(pom)) { // to w zaleznosci w jakim kierunku jest oblicz nowe polozenie pionka
					case 0: 
					{
						pom[1] = ((int)yk - 65) - ((int)y - 65) - 1;
						pom[0] = xk - x - 1;
					}
						break;
					case 1: 
					{
						pom[1] = ((int)yk - 65) - ((int)y - 65) + 1;
						pom[0] = xk - x - 1;
					}
						break;
					case 2: 
					{
						pom[1] = ((int)yk - 65) - ((int)y - 65) - 1;
						pom[0] = xk - x + 1;
					}
						break;
					case 3: 
					{
						pom[1] = ((int)yk - 65) - ((int)y - 65) + 1;
						pom[0] = xk - x + 1;
					}
						break;
					}
					/* aktualizacja polozenia*/
					yp = ((int)y - 65) + pom[1];
					xp = x + pom[0];
				}
				Sleep(200);

				//po zbiciu wszystkich pionkow si
				if (bicie == 0 || (bicie > 0 && !A.Czy_Mozliwe_Bicie(xp, yp))) {
					if (wynik == -1) break; //aby nie tracic tury

					if (punkty == 12) {
						oknoAplikacji.close();

						/********************** Ekran zwyciestwa *******************************/
						sf::RenderWindow oknoAplikacji(sf::VideoMode(800, 800, 32), "Wygrana");
						int x, y;
						while (oknoAplikacji.isOpen()) {
							sf::Event zdarzenie;
							while (oknoAplikacji.pollEvent(zdarzenie)) {

								//obsluga LPM								
								if (zdarzenie.type == sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button == sf::Mouse::Left)
								{
									x = zdarzenie.mouseButton.x;
									y = zdarzenie.mouseButton.y;
									Czy_Lewy = true;
								}
								/* warunki zamykajace okno aplikacji*/
								{
									if (zdarzenie.type == sf::Event::Closed) {
										oknoAplikacji.close();
										return 0;
									}
									if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Escape) {
										oknoAplikacji.close();
										return 0;
									}
								}

								/* obsluga przyciskow*/
								if (Czy_Lewy == true) {
									//zakoncz
									if (x > 66 && x < 202 && y > 280 && y < 335) {
										oknoAplikacji.close();
										return 0;
									}
									//graj ponownie
									if (x < 350 && x > 15 && y < 230 && y > 160) {
										oknoAplikacji.close();
										return 1;
									}
								}

								oknoAplikacji.draw(E.Sprite_win);
								oknoAplikacji.display();
							}
						}
						/********************************************************************/
						break;
					}
					gracz++;

					/* tura SI*/
					int zbity = 0, Wektor_Przesuniecia[2], korekta[2] = { 0,0 };
					do
					{
						int punktypoprz = AI.Zwroc_punkty();
						AI.Koncowy_Ruch(A);
						A.Przesun_Pionek(AI.TabKoniec[0], AI.TabKoniec[1], AI.TabKoniec[2], AI.TabKoniec[3], gracz, E);

						if (AI.Zwroc_punkty() - punktypoprz == 1) zbity++;
						else break;

						Wektor_Przesuniecia[0] = AI.TabKoniec[2] - AI.TabKoniec[0];
						Wektor_Przesuniecia[1] = AI.TabKoniec[3] - AI.TabKoniec[1];

						/* korekta wektoru przesuniecia */					
						{
							if (Wektor_Przesuniecia[0] < 0 && Wektor_Przesuniecia[1] < 0) {
								korekta[0] = -1;
								korekta[1] = -1;
							}
							else if (Wektor_Przesuniecia[0] < 0 && Wektor_Przesuniecia[1] > 0) {
								korekta[0] = -1;
								korekta[1] = 1;
							}
							else if (Wektor_Przesuniecia[0] > 0 && Wektor_Przesuniecia[1] > 0) {
								korekta[0] = 1;
								korekta[1] = 1;
							}
							else if (Wektor_Przesuniecia[0] > 0 && Wektor_Przesuniecia[1] < 0) {
								korekta[0] = 1;
								korekta[1] = -1;
							}
						}
					} while (zbity > 0 && A.Czy_Mozliwe_Bicie(AI.TabKoniec[2] + korekta[0], AI.TabKoniec[3] + korekta[1]));

					gracz--;

					if (AI.Zwroc_punkty() == 12) {
						oknoAplikacji.close();

						/********************** Ekran przegranej *******************************/
						sf::RenderWindow oknoAplikacji(sf::VideoMode(800, 800, 32), "Przegrana");
						int x, y;
						while (oknoAplikacji.isOpen()) {
							sf::Event zdarzenie;
							while (oknoAplikacji.pollEvent(zdarzenie)) {

								//obsluga LPM							
								if (zdarzenie.type == sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button == sf::Mouse::Left)
								{
									x = zdarzenie.mouseButton.x;
									y = zdarzenie.mouseButton.y;
									Czy_Lewy = true;
								}
								/* warunki zamykajace okno aplikacji*/
								{
									if (zdarzenie.type == sf::Event::Closed) {
										oknoAplikacji.close();
										return 0;
									}

									if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Escape) {
										oknoAplikacji.close();
										return 0;
									}
								}

								/* obsluga przyciskow */
								if (Czy_Lewy == true) {
									//zakoncz
									if (x > 530 && x < 680 && y > 240 && y < 300) {
										oknoAplikacji.close();
										return 0;
									}

									//graj ponownie
									if (x < 750 && x > 420 && y < 200 && y > 140) {
										oknoAplikacji.close();
										return 1;
									}
								}

								oknoAplikacji.draw(E.Sprite_lose);
								oknoAplikacji.display();
							}
						}
						break;
					}
				}
			}
		}

		/* odswiez ulozenie pinkow na planszy*/
		{
			oknoAplikacji.draw(E.Sprite_plansza);
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
	return 0;
}

/* Tryb gry umozliwiajacy gre dwoch graczy (w przyszlosci przewidziane lacze prze internet) */
int Gracz_vs_Gracz(Ekran &E, Arena &A) {
	/* zmienne startowe*/
	int x, y, gracz = 1, xk, yk, xp, yp;
	int pom[2];
	bool Czy_Lewy = false, Czy_Prawy = false, wysw = false;;
	int bicie = 0;
	int punkty1 = 0, punkty2 = 0;
	string Gracz[2] = { "Stark","Lannister" };

	sf::RenderWindow oknoAplikacji(sf::VideoMode(800, 800, 32), "Warcaby");
	E.Tworz_Plansze();
	E.Ulozenie_Pionkow();

	while (oknoAplikacji.isOpen()) {
		/* zmiana tury gracza*/
		if (wysw == false) {
			system("cls");
			cout << "TURA GRACZA " << Gracz[gracz - 1] << endl;
			wysw = true;
		}
		sf::Event zdarzenie;

		while (oknoAplikacji.pollEvent(zdarzenie)) {
			/* warunki zamykajace okno aplikacji*/
			{
				if (zdarzenie.type == sf::Event::Closed) {
					oknoAplikacji.close();
					return 0;
				}

				if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Escape) {
					oknoAplikacji.close();
					return 0;
				}

				if (zdarzenie.type == sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button == sf::Mouse::Middle) {
					oknoAplikacji.close();
					return 0;
				}
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

			/* jesli zostaly klikniete LPM i PPM */
			if (Czy_Lewy == true && Czy_Prawy == true) {
				wysw = false;
				bicie = 0;
				xp = xk;
				yp = (int)yk - 65;
				Czy_Lewy = false;
				Czy_Prawy = false;

				pom[1] = ((int)yk - 65) - ((int)y - 65);
				pom[0] = xk - x;
				//if(A.Czy_Brak_Ruchu()  )
				int wynik = A.Przesun_Pionek(x, (int)y - 65, xk, (int)yk - 65, gracz, E); 

				/* jesli mozliwy ruch */
				if (wynik == 1){
					bicie++;
					if (gracz == 1) punkty1++;
					else punkty2++;

					switch (A.Kierunek_Bicia(pom)) { // to w zaleznosci w jakim kierunku jest oblicz nowe polozenie pionka
					case 0: 
					{
						pom[1] = ((int)yk - 65) - ((int)y - 65) - 1;
						pom[0] = xk - x - 1;
					}
						break;
					case 1: 
					{
						pom[1] = ((int)yk - 65) - ((int)y - 65) + 1;
						pom[0] = xk - x - 1;
					}
						break;
					case 2: 
					{
						pom[1] = ((int)yk - 65) - ((int)y - 65) - 1;
						pom[0] = xk - x + 1;
					}
						break;
					case 3: 
					{
						pom[1] = ((int)yk - 65) - ((int)y - 65) + 1;
						pom[0] = xk - x + 1;
					}
						break;
					}
					/* aktualizacja polozenia*/
					yp = ((int)y - 65) + pom[1];
					xp = x + pom[0];
				}

				if (punkty1 == 12) {
					oknoAplikacji.close();
					/********************** Ekran zwyciestwa Stark *******************************/
					sf::RenderWindow oknoAplikacji(sf::VideoMode(800, 800, 32), "Wygrana");
					int x, y;
					while (oknoAplikacji.isOpen()) {
						sf::Event zdarzenie;
						while (oknoAplikacji.pollEvent(zdarzenie)) {

							//obsluga LPM							
							if (zdarzenie.type == sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button == sf::Mouse::Left)
							{
								x = zdarzenie.mouseButton.x;
								y = zdarzenie.mouseButton.y;
								Czy_Lewy = true;
							}
							/* warunki zamykajace okno aplikacji*/
							{
								if (zdarzenie.type == sf::Event::Closed) {
									oknoAplikacji.close();
									return 0;
								}
								if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Escape) {
									oknoAplikacji.close();
									return 0;
								}
							}

							//obsluga przyciskow
							if (Czy_Lewy == true) {
								//zakoncz
								if (x > 10 && x < 140 && y > 680 && y < 750) {
									oknoAplikacji.close();
									return 0;
								}
								//graj ponownie
								if (x < 750 && x > 480 && y < 750 && y > 690) {
									oknoAplikacji.close();
									return 1;
								}
							}

							oknoAplikacji.draw(E.Sprite_stark);
							oknoAplikacji.display();
						}
					}
					break;
				}
				if (punkty2 == 12) {
					oknoAplikacji.close();
					/********************** Ekran zwyciestwa Lannister *******************************/
					sf::RenderWindow oknoAplikacji(sf::VideoMode(800, 800, 32), "Wygrana");
					int x, y;
					while (oknoAplikacji.isOpen()) {
						sf::Event zdarzenie;
						while (oknoAplikacji.pollEvent(zdarzenie)) {

							//obsluga LMP								
							if (zdarzenie.type == sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button == sf::Mouse::Left)
							{
								x = zdarzenie.mouseButton.x;
								y = zdarzenie.mouseButton.y;
								Czy_Lewy = true;
							}
							/* warunki zamykajace okno aplikacji*/
							{
								if (zdarzenie.type == sf::Event::Closed) {
									oknoAplikacji.close();
									return 0;
								}
								if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Escape) {
									oknoAplikacji.close();
									return 0;
								}
							}

							//obsluga przycisku
							if (Czy_Lewy == true) {
								//zakoncz
								if (x > 6 && x < 115 && y > 700 && y < 750) {
									oknoAplikacji.close();
									return 0;
								}
								//graj ponownie
								if (x < 794 && x > 492 && y < 750 && y > 700) {
									oknoAplikacji.close();
									return 1;
								}
							}
							oknoAplikacji.draw(E.Sprite_lannister);
							oknoAplikacji.display();
						}
					}
					break;
				}

				//Zmiana gracza
				if (bicie == 0 && wynik != -1) { // Ruch zwyk³y bez bicia
					if (gracz == 1) gracz++;
					else gracz--;
				}
				else if ((!A.Czy_Mozliwe_Bicie(xp, yp) || !A.Czy_Mozliwe_Bicie_Damka(xp, yp)) && wynik != -1) { // Czy mozliwe jest dalsze bicie
					if (gracz == 1) gracz++;
					else gracz--;
				}
			}
		}
		/* odswiez ulozenie pinkow na planszy*/ 
		{
			oknoAplikacji.draw(E.Sprite_plansza);
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
	return 0;
}

/* Tryb gry multiplayer */
int Multi() {
	return -1;
}

/* Menu sluzoce wyborowi trybow gry i zalaczajace muzyke*/
int Menu() {
	Ekran E;
	Arena A;
	AI AI;

	bool menu = false;
	bool Czy_Lewy = false, Czy_Prawy = false, wysw = false;
	int xpom, ypom, wybor = 0;

	E.Tworz_Plansze();
	E.Ulozenie_Pionkow();

	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("sound/soundtrack.wav")) {
		cout << "Nie mozna wczytac sciezki dzwiekowej" << endl;
	}
	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.setVolume(20);
	sound.setLoop(true);
	sound.play();

	sf::RenderWindow MenuGlowne(sf::VideoMode(800, 800, 32), "Menu");
	while (MenuGlowne.isOpen()) {
		sf::Event zdarzenie;
		while (MenuGlowne.pollEvent(zdarzenie)) {
			//warunki zamkniecia okna
			{
				if (zdarzenie.type == sf::Event::Closed) {
					MenuGlowne.close();
					return 0;
				}

				if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Escape) {
					MenuGlowne.close();
					return 0;
				}

				if (zdarzenie.type == sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button == sf::Mouse::Middle) {
					MenuGlowne.close();
					return 0;
				}
			}

			//obsluga LPM
			if (zdarzenie.type == sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button == sf::Mouse::Left) {
				xpom = zdarzenie.mouseButton.x;
				ypom = zdarzenie.mouseButton.y;
				Czy_Lewy = true;
			}
			
			//obsluga przyciskow
			{
				if (Czy_Lewy == true) {
					if (xpom < 246 && xpom>33 && ypom < 622 && ypom>564) {
						wybor = 1;
						MenuGlowne.close();
					}
					if (xpom < 212 && xpom>36 && ypom < 679 && ypom>642) {
						wybor = 2;
						MenuGlowne.close();
					}
					if (xpom < 428 && xpom>267 && ypom < 624 && ypom>569) {
						wybor = 3;
						MenuGlowne.close();
					}
					if (xpom < 156 && xpom>39 && ypom < 755 && ypom>709) {
						MenuGlowne.close();
						return 0;
					}
				}
			}
		}
		MenuGlowne.draw(E.Sprite_menu);
		MenuGlowne.display();
	}

	switch (wybor) {
	case 1:
		return Gracz_vs_Gracz(E, A);
		break;
	case 2:
		return Gracz_vs_SI(E, A, AI);
		break;
	case 3:
		cout << "Prace w toku" << endl;
		system("pause");
		break;
	default:
		break;
	}
	return 0;
}

/* Instrukcja obslugi */
void Instruckja() {
	string znak;

	cout << "!!! Wszytskie utwory muzyczne i grafiki zostaly zaimplementowane na uzytek wlasny a\n nie w celach komercyjnych !!!" << endl;
	cout << "Czy chcesz wyswietlic instukcje obslugi? (y):";
	cin >> znak;
	if (znak == "y" || znak == "Y") {
		cout << endl << "************ NSTRUKCJA GRY W WARCABY ****************" << endl;
		cout << " Ta wersja gry dziala nastepujaco: aby ruszac sie pionkami nalezy wybrac pionka do ruchu LPM\n a nastepnie wybrac pole w ktore ma sie poruszyc PPM." << endl;
		cout << " To samo tyczy sie bicia wroga." << endl;
		cout << " ******************* OGOLNE ZALOZENIE I ZASADY *******************" << endl;
		cout << " -pionki nie moga ruszac sie do tylu chyba ze maja mozliwe bicie" << endl;
		cout << " -nie ma przymusowego bicia" << endl;
		cout << " -mozna wykonac wielokrotne bicie" << endl;
		cout << " -damka moze poruszac sie o dowolna ilosc pol do napotkania wroga (po jego zbiciu mozliwe jest wielokrotne bicie\n w odl max 1 pola)" << endl;
		cout << " -aby wykonac wielokrotne bicie nalezy wybrac pionka ktory bedzie bil a nastepnie pionka do zbicia.\n Po zbiciu znowu nalezy wybrac pionka ktorym wykonywany byl ruch i zbic kolejnego" << endl;
		cout << endl << "Nalezy pamietac ze gra jest ciagle w wersji alfa i moga wystepowac pewne bledy i niedopracowania" << endl;
		system("pause");
	}
}

/* wszystkie 1 zwracane przez funkcje kontunuuja prace petli
	a 0 zatrzymuja jej prace	*/
int main() {
	Arena A(7);
	cout << "Oryginal A przed wyslaniem w postaci jednowym tab:" << endl;
	A.Wyslij_dane();
	for (int i = 0; i < 64; i++)
		cout << A.tablica_jedno[i];

	sf::IpAddress ip = sf::IpAddress::getLocalAddress();
	sf::TcpSocket socket;
	sf::TcpSocket socket_data;
	char connectionType, mode;
	unsigned int received; // do tej zmiennej zostanie zapisana iloœæ odebranych danych
	char buffer[2000];
	string text = "Jestes ";

	char data[64];
	char data1[64];
	for (int i = 0; i < 64; i++)
		data[i] = A.tablica_jedno[i];
	cout << endl;

	cout << "(s) dla serwera,(c) dla klienta: ";
	cin >> connectionType;
	if (connectionType == 's') {
		sf::TcpListener listener;
		listener.listen(2000);
		listener.accept(socket);
		text += "klientem";
		mode = 's';
	}
	else if (connectionType == 'c') {
		socket.connect(ip, 2000);
		text += "serwerem";
		mode = 'r';
	}
	int k = 0;
	bool done = false;
	while (!done) {
		if (mode == 's') {
			mode = 'r';
			k++;
			for (int i = 0; i < 64; i++)
				cout << data[i];
			cout << endl;
			if (k < 50) {
				data[k] = 'x';
			}
			if (k >= 50)
				done = true;

			if (socket.send(data, 64) != sf::Socket::Done) {
				cerr << "Nie mo¿na wys³aæ danych!\n";
				exit(1);
			}

		}
		else if (mode == 'r') {
			if (socket.receive(data1, 64, received) != sf::Socket::Done) {
				cerr << "Nie mo¿na odebraæ danych!\n";
				exit(1);
			}
			mode = 's';
		}
		else{
			cout << "Odebrano: " << received << " danych" << endl;
			mode = 's';
		}
	}
	cout << "A po zmianie:" << endl;
	A.Wpisz_dane(data1);
	for (int i = 0; i < 64; i++)
		cout << A.tablica_jedno[i];

	system("pause");
	return 0;
}

	/*
	Instruckja();
	int start = 1;
	while (start != 0) {
		start = Menu();
	}
	*/


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


/* zamienia tablice dwuwymairowa na jednowymiarowoa */
void dnaj(char** tab) {
	int z = 0;
	for (int i = 0; i < ROZ; i++)
		for (int j = 0; j < ROZ; j++)
			dane_j[z++] = tab[i][j];
}

/* zamienia tablice jednowymairowa na dwuwymiarowa */
void jnad(char* tab) {
	int z = 0;
	for (int i = 0; i < ROZ; i++)
		for (int j = 0; j < ROZ; j++)
			dane_d[i][j] = tab[z++];
}
/*
	cout << "TEST" << endl;
	cout  << "tablica jend:" << endl;
	for (int i = 0; i < 64; i++)
		cout << tab[i];
	cout << endl;
	cout << "tablica dwu:" << endl;
	for (int i = 0; i < ROZ; i++)
		for (int j = 0; j < ROZ; j++)
			cout << dane_d[i][j];
*/

/*	cout << "(s) dla serwera,(c) dla klienta: ";
	cin >> connectionType;
	if (connectionType == 's') {
		sf::TcpListener listener;
		//listener.listen(2000);
		listener.listen(64);
		listener.accept(socket);
		text += "klientem";
		mode = 's';
	}
	else if (connectionType == 'c') {
		//socket.connect(ip, 2000);
		socket.connect(ip, 64);
		text += "serwerem";
		mode = 'r';
	}
	socket.send(text.c_str(), text.length() + 1);

	socket.receive(buffer, sizeof(buffer), received);
	cout << buffer << endl;

	bool done = false;
	while (!done) {
		if (mode == 's') {
			//getline(cin, text);
			getline(cin, text);
			socket.send(text.c_str(), text.length() + 1);
			mode = 'r';
		}
		else if (mode == 'r') {
			socket.receive(buffer, sizeof(buffer), received);
			if (received > 0) {
				cout << "Odebrano: " << buffer << endl;
				mode = 's';
			}
		}
	}

	
	system("pause");
	return 0;*/