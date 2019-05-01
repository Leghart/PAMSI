#include "pch.h"
#include "Macierz.h"
#include "Lista.h"
using namespace std;

int roz = 100;

//Funkcja testujaca algorytm DIjkstry dla macierzy
void Testuj_D_Macierz(int n, float p) {
	float *tab_czas=new float[roz];
	float pom = 0;
	
	for (int i = 0; i < roz; i++) {
		Macierz M(n, p);
		M.Polacz_losowo();
		tab_czas[i] = Czas_Dijkstra(M);
		//tu sie wywoluje destruktor
	}
	for (int i = 0; i < roz; i++)
		pom = pom + tab_czas[i];
	pom = pom / roz;
	cout << "(Macierz Dijkstra)-> W: " << n << " Gestosc: " << p << " Mean czas: " << pom << endl;
	delete[] tab_czas;
}

//Funkcja testujaca algorytm DIjkstry dla listy
void Testuj_D_Lista(int n, float p) {
	float *tab_czas = new float[roz];
	float pom = 0;

	for (int i = 0; i < roz; i++) {
		Lista L;
		L.Tworz_losowo(n, p);
		tab_czas[i] = Czas_Dijkstra(L);
		L.Usun_Liste();
	}
	for (int i = 0; i < roz; i++)
		pom = pom + tab_czas[i];
	pom = pom / roz;
	cout << "(Lista Dijkstra)-> W: " << n << " Gestosc: " << p << " Mean time: " << pom << endl;
	delete[] tab_czas;
}

//Funkcja testujaca algorytm BellmanaForda dla macierzy
void Testuj_BF_Macierz(int n, float p) {
	float *tab_czas = new float[roz];
	float pom=0;
	for (int i = 0; i < roz; i++) {
		Macierz M(n, p);
		M.Polacz_losowo();
		tab_czas[i] = Czas_Bellman(M);
		//tu sie wywoluje destruktor
	}
	for (int i = 0; i < roz; i++)
		pom = pom + tab_czas[i];
	pom = pom / roz;
	cout << "(Bellman Macierz) W: " << n << " Gestosc: " << p << " Mean czas: " << pom << endl;
	delete[] tab_czas;
}

//Funkcja testujaca algorytm BellmanaForda dla listy
void Testuj_BF_Lista(int n, float p) {
	float *tab_czas = new float[roz];
	float pom=0;

	for (int i = 0; i < roz; i++) {
		Lista L;
		L.Tworz_losowo(n, p);
		tab_czas[i] = Czas_Bellman(L);
		L.Usun_Liste();
	}
	for (int i = 0; i < roz; i++)
		pom = pom + tab_czas[i];
	pom = pom / roz;
	cout << "(Bellman Lista)-> W: " << n << " Gestosc: " << p << " Mean time: " << pom << endl;
	delete[] tab_czas;
}


int main() {
	srand(time(NULL));

	int gestosc=25;
	int tab[5] = {100,500,1000,2000,3000 };
	int ilosc = tab[0];
	
	for (int j = 0; j <= 4; j++) {
		gestosc = 25;
		for (int i = 0; i < 4; i++) {
			Testuj_D_Macierz(ilosc, gestosc);
			gestosc += 25;
		}
		ilosc = tab[j + 1];
	}
	
	
	for (int j = 0; j <= 4; j++) {
		gestosc = 25;
		for (int i = 0; i < 4; i++) {
			Testuj_D_Lista(ilosc, gestosc);
			gestosc += 25;
		}
		ilosc = tab[j + 1];
	}
	
	int tab1[5] = { 10,50,100,500,1000 };
	ilosc = tab1[0];
	
	for (int j = 0; j <= 4; j++) {
		gestosc = 25;
		for (int i = 0; i < 4; i++) {
			Testuj_BF_Macierz(ilosc, gestosc);
			gestosc += 25;
		}
		ilosc = tab1[j + 1];
	}
	
	for (int j = 0; j <= 4; j++) {
		gestosc = 25;
		for (int i = 0; i < 4; i++) {
			Testuj_BF_Lista(ilosc, gestosc);
			gestosc += 25;
		}
		ilosc = tab1[j + 1];

	}
	
	
	return 0;
}