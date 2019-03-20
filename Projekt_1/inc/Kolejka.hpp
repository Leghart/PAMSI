#ifndef KOLEJKA_HPP_
#define KOLEJKA_HPP_ 
#define ROZM 5

#include <iostream>
using namespace std;

template <typename T>
class Kolejka{
protected:
  T *tab; 
  int pojemnosc;
  int glowa;
  int ogon;
  int licznik;
public:
  Kolejka(int size =ROZM);
  ~Kolejka();
  void push(const T& elt);
  T pop(); 
  int size();
  bool empty();
  T top();
  T back();
  void print();
};


template<typename T>
Kolejka<T>::Kolejka(int rozmiar){
  tab =new T[rozmiar];
  for(int i=0;i<rozmiar;i++)
    tab[rozmiar]=0;
  pojemnosc=rozmiar;
  glowa=0;
  ogon=-1;
  licznik=0;
}

template<typename T>
Kolejka<T>::~Kolejka(){
  delete [] tab;
}


template<typename T>
void Kolejka<T>::push(const T& elt){
  if(ogon<pojemnosc){
  ogon=(ogon+1) % pojemnosc;
  tab[ogon]=elt;
  licznik++;
  }
  else{
    cout<<"Kolejka jest pelna \n";
    return;
    }
}

template<typename T>
T Kolejka<T>::pop(){
    if(ogon+1==glowa){
    cout<<"Kolejka jest pusta! \n";
    return 0;
    }
  T zm=tab[glowa];
  glowa=(glowa+1)%pojemnosc;
  licznik--;
  return zm;
}

template<typename T>
int Kolejka<T>::size(){
  return licznik;
}

template<typename T>
T Kolejka<T>::top(){
  if(ogon+1==glowa){
    cout<<"Kolejka jest pusta! \n";
    return 0;
  }
  return tab[glowa];
}

template<typename T>
T Kolejka<T>::back(){
  if(ogon==0){
    cout<<"Kolejka jest pusta! \n";
    return 1;
    }
  return tab[ogon];
}


template<typename T>
bool Kolejka<T>::empty(){
  return (ogon+1<=glowa);
}

template<typename T>
void Kolejka<T>::print(){  
  if(ogon+1<=glowa){
    cout<<"Kolejka jest pusta! \n";
    return;
  }  
  for(int i=glowa;i<ogon+1;i++)
    cout<<tab[i]<<" ";
  cout<<'\n';
}

#endif
