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
  1-Quick_opty
  2-Babel
  3-Merge
  4-Quick_pesy
*/
void Testuj(int rozmiar,int jaki){
  fstream plik_t;
  double pom;
  Tablica T(rozmiar,1);
  plik_t.open("times.txt",ios::app);
  switch(jaki){
  case 1:
    plik_t<<"Quick: "<<"Ilosc danych:"<<rozmiar<<endl;
    pom=Czas_Quick(T);
    plik_t<<"Czas: "<<pom<<" s"<<endl<<endl;
    break;
  case 2:
    plik_t<<"Babelkowe: "<<"Ilosc danych:"<<rozmiar<<endl;
    pom=Czas_Babel(T);
    plik_t<<"Czas: "<<pom<<" s"<<endl<<endl;
    break;
  case 3:
    plik_t<<"Merge: "<<"Ilosc danych:"<<rozmiar<<endl;
    pom=Czas_Merge(T);
    plik_t<<"Czas: "<<pom<<" s"<<endl<<endl;
    break;
  case 4:
    plik_t<<"Quick_p: "<<"Ilosc danych:"<<rozmiar<<endl;
    Tablica spec(rozmiar,2);//2
    pom=Czas_Quick(spec);
    plik_t<<"Czas: "<<pom<<" s"<<endl<<endl;
    break;
  }
}



int main(){
  srand(time(NULL));

  Testuj(100,1);
  Testuj(100,2);
  Testuj(100,3);
  Testuj(100,4);


  Testuj(1000,1);
  Testuj(1000,2);
  Testuj(1000,3);
  Testuj(1000,4);

  Testuj(10000,1);
  Testuj(10000,2);
  Testuj(10000,3);
  Testuj(10000,4);


  Testuj(100000,1);
  Testuj(100000,2);
  Testuj(100000,3);
  Testuj(100000,4);

  Testuj(1000000,1);
  Testuj(1000000,2);
  Testuj(1000000,3);
  Testuj(1000000,4);

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
