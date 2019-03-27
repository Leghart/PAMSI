#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
using namespace std;
//srand(time(NULL));

class Tablica{
  int* tab_0; //tab oryginalna
  /** kopie tablicy oryg do poszczegolnych sortowac **/
  int* tab_1;
  int* tab_2;
  int* tab_3;
  int* tab_pom; //do merga
  int rozmiar;
public:
  Tablica(int r); //randomowe liczby
  Tablica(int r, istream& uchwyt); //czyta liczby z pliku
  ~Tablica();

  /** Funkcje pomocnicze **/
  int Zw_roz() {return rozmiar;}
  void Wyswietl(int k);
  void scal(int l,int s,int p);

  /** Poszczegolne sortowania **/
  void Babel();
  void Quick(int l,int p);
  void Merge(int l,int p);

  /** Metoda do zapisu posortowanych danych roznych algorytmow **/
  void Wyslij(ostream& out,int k);
};


Tablica::Tablica(int r){
  rozmiar=r;
  tab_0=new int[rozmiar];
  tab_1=new int[rozmiar];
  tab_2=new int[rozmiar];
  tab_3=new int[rozmiar];
  tab_pom=new int[rozmiar];
  for(int i=0;i<rozmiar;i++){
    tab_0[i]=rand()%rozmiar;
    tab_1[i]=tab_0[i];
    tab_2[i]=tab_0[i];
    tab_3[i]=tab_0[i];
    tab_pom[i]=0;
  }
}


Tablica::Tablica(int r,istream& uchwyt){
  int tmp=0;
  rozmiar=r;
  tab_0=new int[r];
  tab_1=new int[r];
  tab_2=new int[r];
  tab_3=new int[r];
  if(!uchwyt){
    cout<<"Nie ma pliku!\n";
    return;
  }
  while(!uchwyt.eof()){
    uchwyt>>tab_0[tmp++];
    cout<<tmp<<" ";
  }
  for(int i=0;i<r;i++){
    tab_1[i]=tab_0[i];
    tab_2[i]=tab_0[i];
    tab_3[i]=tab_0[i];
  }
}


Tablica::~Tablica(){
  delete[] tab_0;
  delete[] tab_1;
  delete[] tab_2;
  delete[] tab_3;
  delete[] tab_pom;
}

/** Funkcje obslugi **/
void Tablica::Wyslij(ostream& out,int k){
  switch(k){
  case 1:
    for(int i=0;i<rozmiar;i++)
      out<<tab_1[i]<<" ";
    out<<endl;
    break;
  case 2:
    for(int i=0;i<rozmiar;i++)
      out<<tab_2[i]<<" ";
    out<<endl;
      break;
  case 3:
    for(int i=0;i<rozmiar;i++)
      out<<tab_3[i]<<" ";
    out<<endl;
      break;
  }

}


void Tablica::Wyswietl(int k){
  switch(k){
  case 0:
    for(int i=0;i<rozmiar;i++)
      cout<<tab_0[i]<<" ";
    cout<<endl;
    break;
  case 1:
    for(int i=0;i<rozmiar;i++)
      cout<<tab_1[i]<<" ";
    cout<<endl;
    break;
  case 2:
    for(int i=0;i<rozmiar;i++)
      cout<<tab_2[i]<<" ";
    cout<<endl;
    break;
  case 3:
    for(int i=0;i<rozmiar;i++)
      cout<<tab_3[i]<<" ";
    cout<<endl;
    break;
  }
}


void Tablica::scal(int l, int s, int p){
  int i = l;
  int j = s + 1;

  for(int i = l;i<=p; i++)
    tab_pom[i] = tab_3[i];

  for(int k=l;k<=p;k++) 
    if(i<=s)
      if(j <= p)
        if(tab_pom[j]<tab_pom[i])
          tab_3[k] = tab_pom[j++];
        else
          tab_3[k] = tab_pom[i++];
      else
        tab_3[k] = tab_pom[i++];
    else
      tab_3[k] = tab_pom[j++];
}




/** Funkcje sortujace **/
void Tablica::Quick(int l,int p){
  int i = l;
  int j = p;
  int x = tab_1[(l+p)/2];
  do{
    while(tab_1[i]<x)
      i++;
    while(tab_1[j]>x)
      j--;
    if(i<=j){
      swap(tab_1[i],tab_1[j]);
      i++;
      j--;
    }
  } while(i<=j);

  if(l<j)
    Quick(l,j);
  if(p>i)
    Quick(i,p);
}


void Tablica::Babel(){
  for(int i=0;i<rozmiar;i++){
    for(int j=0;j<rozmiar-1;j++){
      if(tab_2[j]>tab_2[j+1]){
        swap(tab_2[j],tab_2[j+1]);
      }
    }
  }
}


void Tablica::Merge(int l,int p){
  if (p<=l)
    return;

  int s=(p+l)/2;
  Merge(l,s);
  Merge(s+1,p);
  scal(l,s,p);
}



/** Funkcje mierzace czas trwania algorytmow **/
double Czas_Babel(Tablica& t){
  fstream plik_t;
  plik_t.open("times.txt",ios::app);
  long double roznica;
  cout.setf(ios::fixed);
  cout.precision(10);
  clock_t start, koniec;
  start=clock();

  t.Babel();

  koniec=clock();
  roznica=(koniec-start)/(double)CLOCKS_PER_SEC;
  cout.precision(5);
  ofstream plik_o("output_B.txt");
  t.Wyslij(plik_o,2);
  plik_o<<endl;
  return roznica;
}



double Czas_Quick(Tablica& t){
  fstream plik_t;
  plik_t.open("times.txt",ios::app);
  long double roznica;
  cout.setf(ios::fixed);
  cout.precision(10);
  clock_t start, koniec;
  start=clock();

  t.Quick(0,t.Zw_roz()-1);

  //  koniec=clock();
  roznica=(clock()-start)/(double)CLOCKS_PER_SEC;
  cout.precision(5);
  ofstream plik_o("output_Q.txt");
  t.Wyslij(plik_o,1);
  plik_o<<endl;
  return roznica;
}


double Czas_Merge(Tablica& t){
  fstream plik_t;
  plik_t.open("times.txt",ios::app);
  long double roznica;
  cout.setf(ios::fixed);
  cout.precision(10);
  clock_t start, koniec;
  start=clock();

  t.Merge(0,t.Zw_roz()-1);

  koniec=clock();
  roznica=(koniec-start)/(double)CLOCKS_PER_SEC;
  cout.precision(5);
  ofstream plik_o("output_M.txt");
  t.Wyslij(plik_o,3);
  plik_o<<endl;
  return roznica;
}

