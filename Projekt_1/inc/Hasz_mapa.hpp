#ifndef HASZ_MAP_HPP_
#define HASZ_MAP_HPP_ 
#include <iostream>
#define ROZM 5

template<typename Klucz> // funkcja generujaca pozycje w tablicy
int ustaw(Klucz k);


template <typename Klucz , typename Wartosc>
class Hasz_mapa {
  Wartosc* tab[ROZM]={0};
public:
  void wstaw (const Klucz& k,const Wartosc& wart) ;
  void usun (const Klucz& k) ;
  Wartosc& operator[] (const Klucz& k) ;
};


template<typename Klucz, typename Wartosc>
void Hasz_mapa<Klucz,Wartosc>::wstaw(const Klucz& k,const Wartosc& wart){
  int index= ustaw(k)% ROZM ;
  Wartosc* v= new Wartosc();
  *v=wart; 
  tab[index]=v;
}


template<typename Klucz,typename Wartosc>
Wartosc& Hasz_mapa<Klucz,Wartosc>::operator[](const Klucz &k){
  int index=ustaw(k)%ROZM;
  if(tab[index]==0)
    tab[index]=new Wartosc();
  return *(tab[index]);
}


template<typename Klucz,typename Wartosc>
void Hasz_mapa<Klucz,Wartosc>::usun(const Klucz& k){
  int index=ustaw(k)%ROZM;
  delete(tab[index]);
  tab[index]=0;
}


template<typename Klucz>
int ustaw(Klucz k) {
	int suma = 0;
	for (unsigned i = 0; i < k.size(); i++) {
		suma = suma + k[i]*(i+1);
	}
	return suma;
}


#endif
