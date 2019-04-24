#ifndef LISTA_H
#define LISTA_H
#include "pch.h"
using namespace std;

class Lista {
public:
	Lista **A; //tablica
	int **Tablica_Flag; 
	Lista * next; //wsk na kolejny element
	int W,K,V;  //ilosc wierzcholkow, ilosc krawedzi, aktualnie wybrany wierzcholek 
	int waga;
	Lista *p, *r; //wsk, usuniecie 

	//do algorytmow
	int *koszt;
	int *numer;
	bool *spt;

	void Usun_Liste();  
	void Tworz_losowo(int, float);
	void Tworz_recznie(int, float);
};

//glowna funkcja tworzaca polaczenia
void Lista::Tworz_losowo(int Wierzcholki, float G){
	int v1, v2;
	W = Wierzcholki;
	K = (int)(G*W*(W - 1)) / 200;

	A = new Lista *[W];

	for (int i = 0; i < W; i++)
		A[i] = NULL;


	Tablica_Flag = new int *[W];
	for (int i = 0; i < W; i++)
		Tablica_Flag[i] = new int[W];
	
	for (int i = 0; i < W; i++)
		for (int j = 0; j < W; j++)
			Tablica_Flag[i][j] = 0;
		
	int pom = K;
	int waga;

	if (G < 100){
		while (pom){
			v1 = rand() % W;
			v2 = rand() % W;
			waga = rand() % 10 + 1;

			if (v1 > v2 && !Tablica_Flag[v2][v1]){
				p = new Lista;
				p->V = v1;
				p->waga = waga;
				p->next = A[v2];
				A[v2] = p;
				Tablica_Flag[v2][v1] = 1;
				pom--;
			}

			if (v2 > v1 && !Tablica_Flag[v1][v2]){
				p = new Lista;
				p->V = v2;
				p->waga = waga;
				p->next = A[v1];
				A[v1] = p;
				Tablica_Flag[v1][v2] = 1;
				pom--;
			}
		}
	}
	else{
		for (int i = 0; i < W; i++){
			for (int j = 0; j < W; j++){
				if (j > i){
					waga = rand() % 10 + 1;
					p = new Lista;
					p->V = j;
					p->waga = waga;
					p->next = A[i];
					A[i] = p;
					Tablica_Flag[i][j] = 1;
				}
			}
		}
	}
}

//do testow polaczen
void Lista::Tworz_recznie(int Wierzcholki, float G) {
	int v1, v2,x;
	W = Wierzcholki;
	K = (int)(G*W*(W - 1)) / 200;
	cout << "Ilsoc Krawdzi: " << K << endl;

	A = new Lista *[W];
	for (int i = 0; i < W; i++)
		A[i] = NULL;

	for (int i = 0; i < K; i++) {
		cin >> v1 >> v2>> x;
		p = new Lista;
		p->V = v2;
		p->next = A[v1];
		A[v1] = p;
		p->waga = x;
		
	}
	cout << endl;
}

//wyswietlanie
ostream& operator << (ostream& wyjscie, Lista& L) {
	for (int i = 0; i < L.W; i++) {
		cout << "A[" << i << "] =";
		L.p = L.A[i];
		while (L.p) {
			cout << setw(3) << L.p->V<<"("<<L.p->waga<<")";
			L.p = L.p->next;
		}
		cout << endl;
	}
	return wyjscie;
}

// usuwanie pamieci
void Lista::Usun_Liste(){
	for (int i = 0; i < W; i++){
		delete[] Tablica_Flag[i];
		p = A[i];
		while (p){
			r = p;
			p=p->next;
			delete r;
		}
	}
	delete[] A;
	delete[] Tablica_Flag;

	/*
	for (int i = 0; i < W; i++)
		delete[] Tablica_Flag[i];
	delete[] Tablica_Flag;
	*/
}


// ----------------------------- BELLMAN FORD -------------------------------------------
//glowny algorytm
bool BellmanFord_alg(Lista& L,int v=0) {
	Lista *pv;

	for (int i = 0; i < L.W; i++) {
		L.koszt = new int[L.W];
		L.numer = new int[L.W];
	}
	for (int i = 0; i < L.W; i++) {
		L.koszt[i] = INF;
		L.numer[i] = -1;
	}
	L.koszt[v] = 0;

	for (int i = 0; i < L.W; i++) {
		for(int x=0;x<L.W;x++)
			for(pv=L.A[x];pv;pv=pv->next)
				if (L.koszt[pv->V] > L.koszt[x] + pv->waga) {
					L.koszt[pv->V] = L.koszt[x] + pv->waga;
					L.numer[pv->V] = x;
				}
	}
	for (int x = 0; x < L.W; x++)
			if (L.koszt[x] < 0)
				return false;
	return true;
}

//wyswietlanie (nie uzywane w testowaniu)
void BellmanFord(Lista& L) {
	int *S;
	if (BellmanFord_alg(L)) {
		S = new int[L.W];
		int sptr = 0;
		for (int i = 0; i < L.W; i++) {
			cout << i << ": ";
			for (int x = i; x != -1; x = L.numer[x])
				S[sptr++] = x;

			while (sptr)
				cout << S[--sptr] << " ";
			cout << "$" << L.koszt[i] << endl;
		}
		delete[] S;
	}
	else
		cout << "Ujemny cykl" << endl;
}

//pomiar czasu algorytmu
float Czas_Bellman(Lista& L) {
	clock_t start, stop;
	float czas;
	bool test;
	start = clock();
	test = BellmanFord_alg(L);
	stop = clock();
	if (test == true) {
		czas = (float)(stop - start) / CLOCKS_PER_SEC;
		return czas;
	}
	else
		return -1;
}



//------------------------------- DIJKSTRA ---------------------------------------------------
//zwraca najkrotsze polaczenie
int minDyst(Lista& L) {
	int min = INF, min_index;
	for (int i = 0; i < L.W; i++) {
		if (L.spt[i] == false and L.koszt[i] <= min) {
			min = L.koszt[i];
			min_index = i;
		}
	}
	return min_index;
}

//wyswietla (nie uzywane w testach)
void Wyswietl(Lista& L) {
	int *S;
	S = new int[L.W];
	int sptr = 0;
	for (int i = 0; i < L.W; i++) {
		cout << i << ": ";
		for (int x = i; x != -1; x = L.numer[x])
			S[sptr++] = x;

		while (sptr)
			cout << S[--sptr] << " ";
		cout << "$" << L.koszt[i] << endl;
	}
	delete[]S;
}

//glowny algorytm
void Dijkstra(Lista& L, int wierzch_start = 0) {
	L.koszt = new int[L.W];
	L.numer = new int[L.W];
	L.spt = new bool[L.W];

	for (int i = 0; i < L.W; i++) {
		L.koszt[i] = INF;
		L.spt[i] = false;
		L.numer[i] = -1;
	}
	L.koszt[wierzch_start] = 0;

	for (int licz = 0; licz < L.W - 1; licz++) {
		int u = minDyst(L);
		L.spt[u] = true;
		for (L.p = L.A[u]; L.p; L.p = L.p->next) {
			if (!L.spt[L.p->V] and L.p->waga and L.koszt[u] != INF and L.koszt[u] + L.p->waga < L.koszt[L.p->V]) {
				L.koszt[L.p->V] = L.koszt[u] + L.p->waga;
				L.numer[L.p->V] = u;
			}
		}
	}
	//Wyswietl(L);
	delete L.koszt;
	delete L.numer;
}

//liczy czas od rozpoczenia Dijkstry do jego zakonczenia
float Czas_Dijkstra(Lista& L) {
	clock_t start, stop;
	float czas;
	start = clock();
	Dijkstra(L);
	stop = clock();
	czas = (float)(stop - start) / CLOCKS_PER_SEC;
	return czas;
}


#endif