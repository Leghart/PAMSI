#ifndef KOLEJKA_P_HPP_
#define KOLEJKA_P_HPP_ 
#include <iostream>
#include <cstdlib>
#define ROZM 5

template < typename T>
class Kolejka_prio{
public:
  T* tab_dane;
  T* tab_wag;
  int glowa;
  int ogon;
  int pojemnosc;
  int licznik;

  Kolejka_prio(int rozmiar=ROZM);
  ~Kolejka_prio();
  void push (const T& elt,int waga) ;
  T pop () ;
  int size();
  bool empty();
  T top();
  T back();
  void print();
};


template<typename T>
Kolejka_prio<T>::Kolejka_prio(int rozmiar){
  tab_dane =new T[rozmiar];
  tab_wag=new T[rozmiar];
  for(int i=0;i<rozmiar;i++){
    tab_dane[i]=0;
    tab_wag[i]=0;
  }
  pojemnosc=rozmiar;
  glowa=0;
  ogon=-1;
  licznik=0;
}

template<typename T>
Kolejka_prio<T>::~Kolejka_prio(){
  delete[] tab_dane;
  delete[] tab_wag;
}



template<typename T>
void Kolejka_prio<T>::push(const T& elt,int w){
  ogon=(ogon+1) % pojemnosc;
  tab_wag[ogon]=w;
  tab_dane[ogon]=elt;
  
  for(int i=0;i<licznik;i++){
    for(int j=0;j<licznik-1;j++){
      if(tab_wag[j]>tab_wag[j+1]){
        swap(tab_wag[j],tab_wag[j+1]);
        swap(tab_dane[j],tab_dane[j+1]);
      }
    }
  }
  licznik++;
}

template<typename T>
T Kolejka_prio<T>::pop(){
  if(ogon+1==glowa){
    cout<<"Kolejka jest pusta! \n";
    return 0;
  }
  T zm=tab_dane[glowa];
  glowa=(glowa+1)%pojemnosc;
  licznik--;
  return zm;
}


template<typename T>
int Kolejka_prio<T>::size(){
  return licznik;
}


template<typename T>
T Kolejka_prio<T>::top(){
  if(ogon+1==glowa){
    cout<<"Kolejka jest pusta! \n";
    return 0;
  }
  return tab_dane[glowa];
}

template<typename T>
T Kolejka_prio<T>::back(){
  if(ogon==0){
    cout<<"Kolejka jest pusta! \n";
    return 1;
  }
  return tab_dane[ogon];
}

template<typename T>
bool Kolejka_prio<T>::empty(){
  return (ogon+1<=glowa);
}

template<typename T>
void Kolejka_prio<T>::print(){
  if(ogon+1<=glowa){
    cout<<"Kolejka jest pusta! \n";
    return;
  }  
  for(int i=glowa;i<ogon+1;i++ )
    cout<<tab_dane[i]<<endl;
  cout<<'\n';
}

#endif

