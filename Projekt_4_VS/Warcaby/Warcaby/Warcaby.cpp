#include "pch.h"
#include <iostream>
#include "Arena.h"

using namespace std;



void Menu() {
	int nr;
	cout << "---------- WITAJ W GRZE WARCABY --------" << endl;
	cout << " Jesli chcesz grac z innym graczem wcisnij 1" << endl;
	cout << " Jesli chcesz garc z SI wcisnij 2" << endl;
	//cin >> nr;

	switch (1) {
	case 1:
	{
		Arena A(1);
		char warcab[2] = { 'O','X' };
		int gracz;
		int q = 0;
		cout << endl << "Gracz 1 -> O" << endl << "Gracz 2 -> X" << endl;
		cout << "Wybierz swojego championa: ";
		cin >> gracz;

		while (q != 1)
		{
			system("cls");
			A.Rysuj();
			cout << endl << "TURA GRACZA " << gracz << " -> " << warcab[gracz - 1] << endl;
			cout << "PODAJ POLOZENIE PIONKA DO PRZESUNIECIA I TO GDZIE CHCESZ GO PRZESUNAC" << endl;
			int y1, y2;
			char a, b;
			cin >> a >> y1 >> b >> y2;
			A.Przesun_Pionek((int)a - 65, y1, (int)b - 65, y2, gracz);
			system("Pause");
			system("cls");
			A.Rysuj();

			if (gracz == 2) gracz--;
			else gracz++;

			cout << endl << "TURA GRACZA " << gracz << " -> " << warcab[gracz - 1] << endl;
			cout << "PODAJ POLOZENIE PIONKA DO PRZESUNIECIA I TO GDZIE CHCESZ GO PRZESUNAC" << endl;
			cin >> a >> y1 >> b >> y2;
			A.Przesun_Pionek((int)a - 65, y1, (int)b - 65, y2, gracz);
			system("Pause");
			system("cls");
			A.Rysuj();
			gracz--;
		}
	}
	break;
	case 2:
	{
		cout << "Prace w toku" << endl;
	}
	break;
	default: cout << "Nie rozpoznano polecenia" << endl;
		break;
	}
}



int main(){
	Menu();
}
