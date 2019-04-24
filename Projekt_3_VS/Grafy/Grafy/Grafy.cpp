#include "pch.h"
#include "Macierz.h"
#include "Lista.h"
using namespace std;

//Funkcja testujaca algorytm DIjkstry dla listy i macierzy
void Testuj_D(int n, float p) {
	int roz = 100;
	float *tab_czas=new float[roz];
	
	cout << "Lista" << endl;
	for (int i = 0; i < roz; i++) {
		Lista L;
		L.Tworz_losowo(n, p);
		tab_czas[i] = Czas_Dijkstra(L);
		L.Usun_Liste();
	}
	sort(tab_czas, tab_czas + roz);
	cout << "(D) W: " << n << " Gestosc: " << p << " Mean time: " << tab_czas[roz / 2] << endl;

	cout<<"Macierz"<<endl;
	for (int i = 0; i < roz; i++) {
		Macierz M(n, p);
		M.Polacz_losowo();
		tab_czas[i] = Czas_Dijkstra(M);
		//tu sie wywoluje destruktor
	}
	sort(tab_czas, tab_czas + roz);
	cout << "(D) W: " << n << " Gestosc: " << p << " Mean czas: " << tab_czas[roz/2] << endl;
	delete[] tab_czas;
}

//Funkcja testujaca algorytm BellmanaForda dla listy i macierzy
void Testuj_BF(int n, float p) {
	 int roz = 100;
	float *tab_czas = new float[roz];

	cout<<"Lista"<<endl;
	for (int i = 0; i < roz; i++) {
		Lista L;
		L.Tworz_losowo(n,p);
		tab_czas[i] = Czas_Bellman(L);
		L.Usun_Liste();
	}
	sort(tab_czas, tab_czas + roz);
	cout << "(BF) W: " << n << " Gestosc: " << p << " Mean time: " << tab_czas[roz/2] << endl;
	
	cout<<"Macierz"<<endl;
	for (int i = 0; i < roz; i++) {
		Macierz M(n, p);
		M.Polacz_losowo();
		tab_czas[i] = Czas_Bellman(M);
		//tu sie wywoluje destruktor
	}
	sort(tab_czas, tab_czas + roz);
	cout << "(BF) W: " << n << " Gestosc: " << p << " Mean czas: " << tab_czas[roz/2] << endl;
	delete[] tab_czas;
}


int main() {
	srand(time(NULL));
	//Glowna funkcja robiaca testy
	/*
	int gestosc=25;
	int tab[5] = { 10,50,100,200,500 };
	int ilosc = tab[0];

	for(int i=0;i<=4;i++){
		gestosc = 25;
		for (int j = 0; j < 4;j++) {
			Testuj_BF(ilosc, gestosc);
			gestosc += 25;
		}
		ilosc = tab[i];
	}
	*/

	Testuj_D(5000, 100);
	//Testuj_BF(100, 100);

	return 0;
}