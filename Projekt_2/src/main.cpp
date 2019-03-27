#include <fstream>
#include <numeric>
#include <vector>
#include <ctime>
#include <iostream>
#include <unistd.h>
#include <algorithm>
#include "Tablica.hpp"
using namespace std;

/*
  1-Quick
  2-Babel
  3-Merge
*/
void Testuj(int rozmiar,int jaki){
  int ile=10;
  double tab[ile];
  double pom=0,top=0,back=0;
  fstream plik_t;
  plik_t.open("times.txt",ios::app);
  switch(jaki){
  case 1:
    plik_t<<"Quick: "<<"Ilosc danych:"<<rozmiar<<endl;
    for(int i=0;i<ile;i++){
      Tablica T(rozmiar);
      pom=Czas_Quick(T);
      tab[i]=pom;
      //      T.Wyswietl(0);  // sa rozne wartosci
      //      cout<<"**********\n";
    }
    sort(tab,tab+ile);
    top=tab[ile-1];
    back=tab[0];
    plik_t<<"Czas optymistyczny: "<<back<<endl;
    plik_t<<"Czas pesymistyczny: "<<top<<endl;
    plik_t<<"Czas sredni: "<<(top+back)/2<<endl<<endl;
    break;
  case 2:
    plik_t<<"Babelkowe: "<<"Ilosc danych:"<<rozmiar<<endl;
    for(int i=0;i<ile;i++){
      Tablica T(rozmiar);
      pom=Czas_Babel(T);
      tab[i]=pom;
    }
    sort(tab,tab+ile);
    top=tab[ile-1];
    back=tab[0];
    plik_t<<"Czas optymistyczny: "<<back<<endl;
    plik_t<<"Czas pesymistyczny: "<<top<<endl;
    plik_t<<"Czas sredni: "<<(top+back)/2<<endl<<endl;
    break;
  case 3:
    plik_t<<"Merge: "<<"Ilosc danych:"<<rozmiar<<endl;
    for(int i=0;i<ile;i++){
      Tablica T(rozmiar);
      pom=Czas_Merge(T);
      tab[i]=pom;
    }
    sort(tab,tab+ile);
    top=tab[ile-1];
    back=tab[0];
    plik_t<<"Czas optymistyczny: "<<back<<endl;
    plik_t<<"Czas pesymistyczny: "<<top<<endl;
    plik_t<<"Czas sredni: "<<(top+back)/2<<endl<<endl;
    break;
  }
}





int main(){
  srand(time(NULL));


  Testuj(10000,1);
  Testuj(10000,1);
  Testuj(10000,1);
  Testuj(10000,3);
  Testuj(10000,3);
  Testuj(10000,3);
  //  Testuj(1000000,1);
  //  Testuj(1000000,1);
  //  Testuj(1000,2);
  //  Testuj(10000,3);

  //  Tablica t1(10000000);
  //  cout<<Czas_Quick(t1)<<endl;




}




/*
  fstream plik,plik_1;
  plik.open("times.txt",ios::app);
  plik<<"Ilosc danych:    Czas trwania algo [s]:"<<endl;

  plik_1.open("input.txt",ios::app);
  for(int i=0;i<50;i++){
  plik_1<<rand()%100<<" ";
  }
*/
