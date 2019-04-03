#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
using namespace std;

class Tablica{
  int* tab_0; //tab oryginalna
  /** kopie tablicy oryg do poszczegolnych sortowac **/
  int* tab_1;
  int* tab_2;
  int* tab_3;
  int* tab_pom; //do merga
  int rozmiar;
public:
  //  Tablica(int r); //randomowe liczby
  Tablica(int r, istream& uchwyt); //czyta liczby z pliku
  Tablica(int r,int b); //zlozony konstruktor posort tab
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

/*
  1-full random
  2-posortowane w dobrej kolej
  3-posortowane w odwrotnej kolej
  4-te same wartosci
*/
Tablica::Tablica(int r,int b){
  rozmiar=r;
  tab_0=new int[rozmiar];
  tab_1=new int[rozmiar];
  tab_2=new int[rozmiar];
  tab_3=new int[rozmiar];
  tab_pom=new int[rozmiar];
  switch(b){
  case 1:{
    for(int i=0;i<rozmiar;i++){
      tab_0[i]=rand()%rozmiar;
      tab_1[i]=tab_0[i];
      tab_2[i]=tab_0[i];
      tab_3[i]=tab_0[i];
      tab_pom[i]=0;
    }
    break;
  }
  case 2:{
    for(int i=0;i<rozmiar;i++){
      tab_0[i]=i;
      tab_1[i]=tab_0[i];
      tab_2[i]=tab_0[i];
      tab_3[i]=tab_0[i];
      tab_pom[i]=0;
    }
    break;
  }
  case 3:{
    int wyn=rozmiar-1;
    for(int i=0;i<rozmiar;i++){
      tab_0[i]=wyn;
      tab_1[i]=tab_0[i];
      tab_2[i]=tab_0[i];
      tab_3[i]=tab_0[i];
      tab_pom[i]=0;
      wyn--;
    }
    break;
  }
  case 4:{
    int pom=rand()%rozmiar;
    for(int i=0;i<rozmiar;i++){
      tab_0[i]=pom;
      tab_1[i]=tab_0[i];
      tab_2[i]=tab_0[i];
      tab_3[i]=tab_0[i];
      tab_pom[i]=0;
    }
  }
    break;
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
  for(int i=0;i<rozmiar;i++){
    tab_0[i]=0;
    tab_1[i]=0;
    tab_2[i]=0;
    tab_3[i]=0;
    tab_pom[i]=0;
  }
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


void Tablica::scal(int lewy, int pivot, int prawy){
  int i = lewy;
  int j = pivot + 1;

  for(int i = lewy;i<=prawy; i++)
    tab_pom[i] = tab_3[i];

  for(int k=lewy;k<=prawy;k++) 
    if(i<=pivot)
      if(j <= prawy)
        if(tab_pom[j]<tab_pom[i]){
          tab_3[k] = tab_pom[j];
          j++;
        }
        else{
          tab_3[k] = tab_pom[i];
          i++;
        }
      else{
        tab_3[k] = tab_pom[i];
        i++;
      }
    else{
      tab_3[k] = tab_pom[j];
      j++;
    }
}




/** Funkcje sortujace **/
void Tablica::Quick(int lewy,int prawy){
  int i = lewy;
  int j = prawy;
  int pivot = tab_1[(lewy+prawy)/2];
  //  int x=tab_1[l];


  while(i<=j){ 
    while(tab_1[i]<pivot) i++;
    while(tab_1[j]>pivot) j--;
    if(i<=j){
      swap(tab_1[i],tab_1[j]);
      i++;
      j--;
    }
  }

  if(lewy<j)
    Quick(lewy,j);
  if(i<prawy)
    Quick(i,prawy);
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


void Tablica::Merge(int lewy,int prawy){
  if (prawy<=lewy)
    return;

  int pivot=(prawy+lewy)/2;
  Merge(lewy,pivot);
  Merge(pivot+1,prawy);
  scal(lewy,pivot,prawy);
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

  koniec=clock();
  roznica=(koniec-start)/(double)CLOCKS_PER_SEC;
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

