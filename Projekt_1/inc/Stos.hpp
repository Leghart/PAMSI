#ifndef STOS_HPP_
#define STOS_HPP_ 
#include <iostream>
#define ROZM 5
using namespace std;

template < typename T>
class Stos{
protected:
  T* tab; 
  int pojemnosc;
  int glowa; 
  int licznik;
public :
  Stos(int size =ROZM);
  ~Stos();
  void push (const T& elt);
  T pop ();
  void top();
  bool empty();
  int size();
  void print();
};


template<typename T>
Stos<T>::Stos(int rozm){
  tab=new T[rozm];
  for(int i=0;i<rozm;i++)
    tab[i]=0;
  pojemnosc=rozm;
  glowa=0;
  licznik=0;
}

template<typename T>
Stos<T>::~Stos(){
  delete[] tab;
}


template <typename T>
void Stos<T>::push(const T& elt){
  if(glowa<pojemnosc){
    tab[glowa]=elt;
    glowa++;
    licznik++;
  }
  else{
    cout<<"Stos przepelniony"<<endl;
    return;
  }
} 


template <typename T>
T Stos<T>::pop(){
  if(!glowa){
    cout<<"Brak elementow na stosie"<<endl;
    return 1;
  }
  T zdjety=tab[glowa];
  glowa--;
  licznik--;
  return zdjety;
} 


template <typename T>
bool Stos<T>::empty(){
  return (!glowa);
}

template<typename T>
int Stos<T>::size(){
  int wyn=0;
  for(int i=glowa-1;1+i>0;i--)
    wyn++;
  return wyn;
}


template<typename T>
void Stos<T>::print(){
  if(!glowa){
    cout<<"Stos jest pusty! \n";
    return;
  }
  for(int i=glowa-1;1+i>0;i--)
    cout<<tab[i]<<endl;
}

template<typename T>
void Stos<T>::top(){
  if(glowa==0){
    cout<<"Stos jest pusty! \n";
    return;
  }
  cout<<tab[glowa-1]<<endl;
}

#endif
