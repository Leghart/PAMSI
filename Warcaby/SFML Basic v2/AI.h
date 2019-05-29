#ifndef AI_H
#define AI_H
#include "Arena.h"
using namespace std;

/* sztuczna inteligencja */
class AI {
	int pom[2], bicia, waga = 0;
	int TabRuch[3], TabBicie[3], TabBicieD[3];
	int WzorzecWag[ROZ][ROZ];
	int tablicaWagRuchow[ROZ][ROZ]; // const wypelnienia domyslnymi wagami
	int punkty = 0;
	bool Atak = false;
	//int PozTmp[2];
public:
	int TabKoniec[4];

	AI();
	int Zwroc_punkty() { return punkty; }
	int Ilosc_Bic(int, int, Arena&);
	int Mozliwy_Ruch_AI(int, int, Arena&);
	int Mozliwe_Bicie_AI(int, int, Arena&);
	void Koncowy_Ruch(Arena&); 
	int Czy_Mozliwe_Bicie_AI(int, int,int,int,Arena&);
	void Czy_Pod_Atakiem(int, int, Arena&);
	void Nie_Podkladaj_Sie(int, int, Arena&);
	int Mozliwe_Bicie_AI_Damka(int, int, Arena&);
};

/* zerowanie zmiennych i uzupelnienie planszy wagami startowymi
	(hierarchia pol, im dalej od linii startowej tym wieksza waga +
	uwzglenenie stref pionowych i poziomych)	*/
AI::AI() {
int wag = 1;
for (int i = 0; i < ROZ; i++){
	for (int j = 0; j < (ROZ / 2); j++){
		tablicaWagRuchow[i][j] = i + wag;
		wag++;
	}
	wag--;
	for (int j = ROZ / 2; j < ROZ; j++){
		tablicaWagRuchow[i][j] = i + wag;
		wag--;
	}
}

for (int i = 0; i < ROZ; i++)
	for (int j = 0; j < ROZ; j++)
		tablicaWagRuchow[i][j] += i;

for (int i = 0; i < 3; i++){
	TabRuch[i] = 0;
	TabBicie[i] = 0;
	TabKoniec[i] = 0;
}
// oryginal wag na planszy
for (int i = 0; i < ROZ; i++)
	for (int j = 0; j < ROZ; j++)
		WzorzecWag[i][j] = tablicaWagRuchow[i][j];

TabKoniec[3] = 0;
}

/* zwraca ilosc mozliwych bic jakie pionek moze osiagnac */
int AI::Ilosc_Bic(int xp, int yp, Arena &A){
	bicia = 0;
	int xk, yk;

	int lastx = -5, lasty = -5;

	while (Czy_Mozliwe_Bicie_AI(xp, yp, lastx, lasty,A) != -1){
		if (Czy_Mozliwe_Bicie_AI(xp, yp, lastx, lasty,A) == 0){
			xk = xp - 1;
			yk = yp - 1;
		}
		else if (Czy_Mozliwe_Bicie_AI(xp, yp, lastx, lasty,A) == 1){
			xk = xp + 1;
			yk = yp - 1;
		}
		else if (Czy_Mozliwe_Bicie_AI(xp, yp, lastx, lasty,A) == 2){
			xk = xp - 1;
			yk = yp + 1;
		}
		else if (Czy_Mozliwe_Bicie_AI(xp, yp, lastx, lasty,A) == 3){
			xk = xp + 1;
			yk = yp + 1;
		}

		switch (Czy_Mozliwe_Bicie_AI(xp, yp, lastx, lasty,A)){
		case 0:
			pom[1] = yk - yp - 1;
			pom[0] = xk - xp - 1;
		break;

		case 1:
			pom[1] = yk - yp + 1;
			pom[0] = xk - xp - 1;
		break;

		case 2:
			pom[1] = yk - yp - 1;
			pom[0] = xk - xp + 1;
		break;

		case 3:
			pom[1] = yk - yp + 1;
			pom[0] = xk - xp + 1;
		break;
		}

		if (xk == lastx && yk == lasty)	break;
	
		lastx = xk;
		lasty = yk;

		xp = xp + pom[0];
		yp = yp + pom[1];
		bicia++;
	}
	return bicia;
}

/* zwraca wage najlepszego ruchu */
int AI::Mozliwy_Ruch_AI(int xp, int yp, Arena &A){
	int pom2[2];
	int wagakoncowa = 0;

	if (A.Czy_Jest_W_Arenie(xp + 1, yp + 1) && !A.Czy_Jest_Pionek(xp + 1, yp + 1)){
		pom2[0] = 1;
		pom2[1] = 1;
		if (A.Czy_Prawidlowy_Ruch(pom2, A.tablica[xp][yp])){
			wagakoncowa = tablicaWagRuchow[xp + 1][yp + 1];
			TabRuch[0] = xp + 1;
			TabRuch[1] = yp + 1;
			TabRuch[2] = wagakoncowa;
		}
	}
	pom2[0] = 1;
	pom2[1] = -1;
	if (A.Czy_Jest_W_Arenie(xp + 1, yp - 1) && !A.Czy_Jest_Pionek(xp + 1, yp - 1)){
		if (A.Czy_Prawidlowy_Ruch(pom2, A.tablica[xp][yp])){
			if (wagakoncowa < tablicaWagRuchow[xp + 1][yp - 1]){
				wagakoncowa = tablicaWagRuchow[xp + 1][yp - 1];
				TabRuch[0] = xp + 1;
				TabRuch[1] = yp - 1;
				TabRuch[2] = wagakoncowa;
			}
		}
	}
	return wagakoncowa;
}

/* zwraca wage bicia jesli bylo mozliwe */
int AI::Mozliwe_Bicie_AI(int xp, int yp, Arena &A){
	int wagakoncowa = 0;

	switch (Czy_Mozliwe_Bicie_AI(xp, yp, xp, yp,A)){
	case 0: //bicie lewo gora
		wagakoncowa = 100;
		TabBicie[0] = xp - 1;
		TabBicie[1] = yp - 1;
		TabBicie[2] = wagakoncowa;
	break;
	case 1: //bicie lewo dol
		wagakoncowa = 100;
		TabBicie[0] = xp - 1;
		TabBicie[1] = yp + 1;
		TabBicie[2] = wagakoncowa;
	break;
	case 2:	//bicie prawo gora
		wagakoncowa = 100;
		TabBicie[0] = xp + 1;
		TabBicie[1] = yp - 1;
		TabBicie[2] = wagakoncowa;
	break;
	case 3: //bicie prawo dol
		wagakoncowa = 100;
		TabBicie[0] = xp + 1;
		TabBicie[1] = yp + 1;
		TabBicie[2] = wagakoncowa;
	break;
	case -1: // nie bylo mozliwego bicia
		wagakoncowa = -1;
		TabBicie[0] = xp;
		TabBicie[1] = yp;
		TabBicie[2] = wagakoncowa;
	break;
	}
	return wagakoncowa;
}

/* przejscie po wszystkich pionach i wpisanie do tablicy najlepszego ruchu lub bicia jakie
	jest mozliwe do wykonania (xp,yp,xk,yk) */
void AI::Koncowy_Ruch(Arena &A){
	waga = 0;
	for (int i = 0; i < ROZ; i++){
		for (int j = 0; j < ROZ; j++){
			if (A.tablica[i][j] == 'x'){
				Nie_Podkladaj_Sie(i, j, A);
				Czy_Pod_Atakiem(i, j, A);
				if (waga < Mozliwy_Ruch_AI(i, j, A)) {
					waga = TabRuch[2];
					TabKoniec[0] = i;
					TabKoniec[1] = j;
					TabKoniec[2] = TabRuch[0];
					TabKoniec[3] = TabRuch[1];
				}

				if (waga < Mozliwe_Bicie_AI(i, j, A)){
					waga = TabBicie[2];
					TabKoniec[0] = i;
					TabKoniec[1] = j;
					TabKoniec[2] = TabBicie[0];
					TabKoniec[3] = TabBicie[1];
					punkty++; //jako ze bicie ma najwieksza wage to jak tu sie wejdzie to bedzie ok
				}
			}
			TabRuch[0] = 0;
			TabRuch[1] = 0;
			TabRuch[2] = 0;

			TabBicie[0] = 0;
			TabBicie[1] = 0;
			TabBicie[2] = 0;
		}
	}
	for (int i = 0; i < ROZ; i++){
		for (int j = 0; j < ROZ; j++){
			//cout << tablicaWagRuchow[i][j] << " ";
			tablicaWagRuchow[i][j] = WzorzecWag[i][j];
			//cout << tablicaWagRuchow[i][j] << " ";
		}
		//cout << endl;
	}
}

/* zwraca cyfre int ktora odzwierciedla kierunek bicia */
int AI::Czy_Mozliwe_Bicie_AI(int x, int y, int xzabr, int yzabr,Arena& A)
{
	int LUp[2] = { -1,-1 };
	int RUp[2] = { -1,1 };
	int RDown[2] = { 1,1 };
	int LDown[2] = { 1,-1 };


	if (A.Czy_Jest_W_Arenie(x - 1, y - 1) && x - 1 != 7 && x - 1 != 0 && y - 1 != 7 && y - 1 != 0 && (x - 1 != xzabr || y - 1 != yzabr))
		if (A.Bicie(x - 1, y - 1, LUp)) return 0;

	if (A.Czy_Jest_W_Arenie(x - 1, y + 1) && x - 1 != 7 && x - 1 != 0 && y + 1 != 7 && y + 1 != 0 && (x - 1 != xzabr || y + 1 != yzabr))
		if (A.Bicie(x - 1, y + 1, RUp)) return 1;

	if (A.Czy_Jest_W_Arenie(x + 1, y + 1) && x + 1 != 7 && x + 1 != 0 && y + 1 != 7 && y + 1 != 0 && (x + 1 != xzabr || y + 1 != yzabr))
		if (A.Bicie(x + 1, y + 1, RDown)) return 3;

	if (A.Czy_Jest_W_Arenie(x + 1, y - 1) && x + 1 != 7 && x + 1 != 0 && y - 1 != 7 && y - 1 != 0 && (x + 1 != xzabr || y - 1 != yzabr))
		if (A.Bicie(x + 1, y - 1, LDown)) return 2;

	return -1;
}

/* Sprawdza czy pion znajdzie sie pod atakiem ze strony wroga*/
void AI::Czy_Pod_Atakiem(int xp, int yp, Arena &A)
{
	Atak = false;

	if (A.Czy_Jest_W_Arenie(xp + 1, yp + 1) && xp != 7 && xp != 0 && yp != 7 && yp != 0){
		if ((A.tablica[xp + 1][yp + 1] == 'o' || A.tablica[xp + 1][yp + 1] == 'O') && !A.Czy_Jest_Pionek(xp - 1, yp - 1)){
			tablicaWagRuchow[xp - 1][yp - 1] += 50;
			Atak = true;
		}
	}

	if (A.Czy_Jest_W_Arenie(xp + 1, yp - 1) && xp != 7 && xp != 0 && yp != 7 && yp != 0){
		if ((A.tablica[xp + 1][yp - 1] == 'o' || A.tablica[xp + 1][yp - 1] == 'O') && !A.Czy_Jest_Pionek(xp - 1, yp + 1)){
			tablicaWagRuchow[xp - 1][yp + 1] += 50;
			Atak = true;
		}
	}
}

/* Zabezpiecza sojusznika aby nie wystawial sie na atak*/
void AI::Nie_Podkladaj_Sie(int xp, int yp, Arena &A){
	if (A.Czy_Jest_W_Arenie(xp + 1 + 1, yp + 1 + 1)){
		if (A.Czy_Jest_Pionek(xp + 1 + 1, yp + 1 + 1) && !A.Czy_Przyjaciel(A.tablica[xp][yp], A.tablica[xp + 1 + 1][yp + 1 + 1]))
			tablicaWagRuchow[xp + 1][yp + 1] = 1;
	}

	if (A.Czy_Jest_W_Arenie(xp + 1 + 1, yp + 1 - 1)){
		if (A.Czy_Jest_Pionek(xp + 1 + 1, yp + 1 - 1) && A.Czy_Jest_W_Arenie(xp + 1 - 1, yp + 1 + 1) && !A.Czy_Przyjaciel(A.tablica[xp][yp], A.tablica[xp + 1 + 1][yp + 1 - 1])){
			if (!A.Czy_Jest_Pionek(xp + 1 - 1, yp + 1 + 1))
				tablicaWagRuchow[xp + 1][yp + 1] = 1;
		}
	}

	if (A.Czy_Jest_W_Arenie(xp + 1 + 1, yp - 1 - 1)){
		if (A.Czy_Jest_Pionek(xp + 1 + 1, yp - 1 - 1) && !A.Czy_Przyjaciel(A.tablica[xp][yp], A.tablica[xp + 1 + 1][yp - 1 - 1]))
			tablicaWagRuchow[xp + 1][yp - 1] = 1;
	}

	if (A.Czy_Jest_W_Arenie(xp + 1 + 1, yp - 1 + 1)){
		if (A.Czy_Jest_Pionek(xp + 1 + 1, yp - 1 + 1) && A.Czy_Jest_W_Arenie(xp + 1 - 1, yp - 1 - 1) && !A.Czy_Przyjaciel(A.tablica[xp][yp], A.tablica[xp + 1 + 1][yp - 1 + 1])){
			if (!A.Czy_Jest_Pionek(xp + 1 - 1, yp - 1 - 1))
				tablicaWagRuchow[xp + 1][yp - 1] = 1;
		}
	}

}

/* ....................*/
int AI::Mozliwe_Bicie_AI_Damka(int xp, int yp, Arena &A)
{
	int wagakoncowa = 0;

	if (A.tablica[xp][yp] == 'X')
	{
		cout << A.licznik << endl;
		//system("pause");
		switch (A.Czy_Mozliwe_Bicie_Damka(xp, yp))
		{
		case 1:
		{
			cout << "1" << endl;
			//system("pause");
			wagakoncowa = 200;

			for (int i = 0; i <= A.licznik; i++)
			{
				xp -= 1;
				yp -= 1;
			}
			TabBicieD[0] = xp;
			TabBicieD[1] = yp;
			TabBicieD[2] = wagakoncowa;
		}
		break;

		case 2:
		{
			cout << "2" << endl;
			//system("pause");
			wagakoncowa = 200;

			for (int i = 0; i <= A.licznik; i++)
			{
				xp -= 1;
				yp += 1;
			}
			TabBicieD[0] = xp;
			TabBicieD[1] = yp;
			TabBicieD[2] = wagakoncowa;
		}
		break;

		case 3:
		{
			cout << "3" << endl;
			//system("pause");
			wagakoncowa = 200;
			for (int i = 0; i <= A.licznik; i++)
			{
				xp += 1;
				yp += 1;
			}
			TabBicieD[0] = xp;
			TabBicieD[1] = yp;
			TabBicieD[2] = wagakoncowa;
		}
		break;

		case 4:
		{
			cout << "4" << endl;
			//system("pause");
			wagakoncowa = 200;
			for (int i = 0; i <= A.licznik; i++)
			{
				xp += 1;
				yp -= 1;
			}
			TabBicieD[0] = xp;
			TabBicieD[1] = yp;
			TabBicieD[2] = wagakoncowa;
		}
		break;

		case -1:
		{
			wagakoncowa = -1;
			TabBicieD[0] = xp;
			TabBicieD[1] = yp;
			TabBicieD[2] = wagakoncowa;
		}
		break;
		}
	}

	return wagakoncowa;
}

#endif AI_H

