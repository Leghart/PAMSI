#ifndef MACIERZ_H
#define MACIERZ_H
#include "pch.h"
using namespace std;

class Macierz{
	int W,K,G; //wierzcholki krawedzie gestosc
public:
	int **tablica; //macierz

	//do algorytmow
	int *koszt; //suma najkrotszych drog
	int *numer; //do numerowania przez jakie drogi sie idzie
	bool *spt;

	Macierz(int, float);
	~Macierz();
	int Zwroc_Wierz(){return W;}
	int Zwroc_Kraw(){return K;}
	void Polacz_losowo();
	void Polacz_recznie(); //do testow 
};

//rezerwuje pamiec i zeruje elementy macierzy
Macierz::Macierz(int w, float g){
	W = w;
	K = (int)(g*W*(W - 1)) / 200;
	G = (int)g;

	tablica = new int *[W];
	
	for (int i = 0; i < W; i++) 
		tablica[i] = new int[W];


	for (int i = 0; i < W; i++)
		for (int j = 0; j < W; j++)
			tablica[i][j] = 0;
}

//niszczy element
Macierz::~Macierz() {
	for (int i = 0; i < W; i++) {
		delete[] tablica[i];
	}
	delete[] tablica;
}

// laczy elementy z max waga 10 i tylko na macierzy trojatnej
void Macierz::Polacz_losowo() {
	int pom = K;

	if (G < 100){
		while (pom){
			int i = rand() % W;
			int j = rand() % W;

			if (j > i && !tablica[i][j]){
				pom--;
				tablica[i][j] = 1 + rand() % 10;
			}
			else if (i > j && !tablica[j][i]){
				pom--;
				tablica[j][i] = 1 + rand() % 10;
			}
		}
	}
	else {
		for (int i = 0; i < W; i++){
			for (int j = 0; j < W; j++){
				if (j > i)
					tablica[i][j] = 1 + rand() % 10;
			}
		}
	}
}

//do sprawdzania czy dobrze laczy elementy
void Macierz::Polacz_recznie(){
	int v1, v2,x;
	cout << "Ilosc krawdzi: "<<K<<endl;
	for (int i = 0; i < K; i++){
		cin >> v1 >> v2>>x;
		tablica[v1][v2] = x;
	}
}

//wyswietlenie macierzy
ostream& operator << (ostream& wyjscie, Macierz& M) {
	wyjscie << endl << "    ";
	for (int i = 0; i < M.Zwroc_Wierz(); i++)
		wyjscie << setw(3) << i;

	wyjscie << endl;
	wyjscie << "  ";
	for (int i = 0; i < M.Zwroc_Wierz() + 1; i++)
		wyjscie << setw(3) << "_";

	wyjscie << endl;
	for (int i = 0; i < M.Zwroc_Wierz(); i++) {
		wyjscie << setw(3) << i << "|";
		for (int j = 0; j < M.Zwroc_Wierz(); j++)
			wyjscie << setw(3) << M.tablica[i][j];
		wyjscie << endl;
	}
	return wyjscie;
}


//------------------------	BELLMAN FORD --------------------------------
//glowny algorytm liczenia drogi (wykorzystany w pomiarze czasu)
bool BellmanFord_alg(Macierz& M, int wierzch_start=0) {
	M.koszt = new int[M.Zwroc_Wierz()];    
	M.numer = new int[M.Zwroc_Wierz()];    
	for (int i = 0; i < M.Zwroc_Wierz(); i++) {  
		M.numer[i] = -1;  
		M.koszt[i] = INF; 
	}
	M.koszt[wierzch_start] = 0; 

	for (int i = 1; i <= M.Zwroc_Wierz(); i++) {
		for (int w = 0; w < M.Zwroc_Wierz(); w++) {
			for (int k = 0; k < M.Zwroc_Wierz(); k++) {
				if ((M.tablica[w][k] != 0) && (M.koszt[k]) >= (M.koszt[w] + M.tablica[w][k])) {
					M.koszt[k] = M.koszt[w] + M.tablica[w][k];
					M.numer[k] = w;
				}
			}
		}
	}
	for (int i = 0; i < M.Zwroc_Wierz(); i++)
		if (M.koszt[i] < 0) 
			return false;
	return true;
}

// do wyswietlenia kosztow drog i przez jakie elementy idzie
void BellmanFord(Macierz& M) {	
	int *S;
	if (BellmanFord_alg(M)) {
		S = new int[M.Zwroc_Wierz()];
		int sptr = 0;
		for (int i = 0; i < M.Zwroc_Wierz(); i++) {
			cout << i << ": ";
			for (int x = i; x != -1; x = M.numer[x])
				S[sptr++] = x;

			while (sptr)
				cout << S[--sptr] << " ";
			cout << "$" << M.koszt[i] << endl;
		}
		delete[]S;
	}
	else
		cout << "Ujemny cykl" << endl;
	delete M.koszt;
	delete M.numer;	
}

//liczy czas od rozoczecia BellmanDord_alg do jego konca
float Czas_Bellman(Macierz& M) {
	clock_t start, stop;
	float czas;
	bool test;
	start = clock();
	test=BellmanFord_alg(M);
	stop = clock();
	if (test == true) {
		czas = (float)(stop-start) / CLOCKS_PER_SEC;
		return czas;
	}
	else
		return -1;
}


//-----------------------	DIJKSTRA ---------------------------------------
//zwraca najkrotsze polaczenie
int minDyst(Macierz& M){
	int min = INF,min_index;
	for (int i = 0; i < M.Zwroc_Wierz(); i++) {
		if (M.spt[i]==false and M.koszt[i] <=min){
			min = M.koszt[i];
			min_index = i;
		}
	}
	return min_index;
}

//wyswietla (nie uzywane w testach)
void Wyswietl(Macierz& M) {
	int *S;
	S = new int[M.Zwroc_Wierz()];
	int sptr = 0;
	for (int i = 0; i < M.Zwroc_Wierz(); i++) {
		cout << i << ": ";
		for (int x = i; x != -1; x = M.numer[x])
			S[sptr++] = x;

		while (sptr)
			cout << S[--sptr] << " ";
		cout << "$" << M.koszt[i] << endl;
	}

	delete[] S;
}

//glowny algorytm
void Dijkstra(Macierz& M, int wierzch_start = 0) {
	M.koszt = new int[M.Zwroc_Wierz()];
	M.numer = new int[M.Zwroc_Wierz()];
	M.spt = new bool[M.Zwroc_Wierz()];

	for (int i = 0; i < M.Zwroc_Wierz(); i++) {
		M.koszt[i] = INF;
		M.spt[i] = false;
		M.numer[i] = -1;
	}
	M.koszt[wierzch_start] = 0;

	for (int licz = 0; licz < M.Zwroc_Wierz() - 1; licz++) {
		int u = minDyst(M);
		M.spt[u] = true;
		for (int v = 0; v < M.Zwroc_Wierz(); v++)
			if (!M.spt[v] and M.tablica[u][v] and M.koszt[u] != INF and M.koszt[u] + M.tablica[u][v] < M.koszt[v]) {
				M.koszt[v] = M.koszt[u] + M.tablica[u][v];
				M.numer[v] = u;
			}
	}
	//Wyswietl(M);
	delete M.koszt;
	delete M.numer;
}

//liczy czas od rozpoczenia Dijkstry do jego zakonczenia
float Czas_Dijkstra(Macierz& M) {
	clock_t start, stop;
	float czas;
	start = clock();
	Dijkstra(M);
	stop = clock();
	czas = (float)(stop - start)/ CLOCKS_PER_SEC;
	return czas;
}

#endif