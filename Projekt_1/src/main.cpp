#include <iostream>
#include <algorithm>
#include <map> 
#include "Lista.hpp"
#include "Stos.hpp"
#include "Kolejka.hpp"
#include "Kolejka_prio.hpp"
#include "Hasz_mapa.hpp"


using namespace std;

int main(){


  cout <<endl<<"------- OBSLUGA LISTY ---------------------------------------------------------\n";
  List<int> l;
  cout<<"Dodajemy elementy: 1B 2B 6F 2B 4F 2B 11F 13B 2B 2B i 15 na pozycje 3\n";
  l.pushBack(1);
  l.pushBack(2);
	l.pushFront(6);
	l.pushBack(2);
	l.pushFront(4);
  l.pushBack(2);
  l.pushFront(11);
  l.pushBack(13);
  l.pushBack(2);
  l.pushBack(2);
  l.insert(15,3);
  cout<<"Usuwamy wszystkie dwojki\n";
  l.remove(2);

  cout<<"Wyswietl liste za pomoca ConstIteratora: \n";
  for (List<int>::ConstIterator i = l.cbegin(); i != l.cend(); ++i)
    cout << *i << ", ";
  cout << endl;

  cout<<"Zamien liczby parzyste na 0 i wyswietl: \n";
  for (List<int>::Iterator i = l.begin(); i != l.end(); ++i) {
    if (*i%2==0)
      *i = 0;//Tu mozemy zmieniac wartosci w liscie za pomoca iteratora
    cout << *i << ", ";
  }
  cout << endl;


  cout<<"----- OBSLUGA STOSU ------------------------------------------------------------\n";
  Stos<int> s;
  cout<<"Dodaje element 1 \n";
  s.push(1);
  cout<<"Dodaje element 2 \n";
  s.push(2);
  cout<<"Dodaje element 3 \n";
  s.push(3);
  cout<<"Dodaje element 4 \n";
  s.push(4);
  cout<<"Wartosc szczytowa: ";
  s.top();
  s.pop();
  cout<<"Sciaga 1 element (->nastepny elt to): ";
  s.top();
  cout<<"Pozostalo elementow: "<<s.size()<<endl;
  cout<<"Funkcja dodatkowa: Wyswietl wszytsko: "<<endl;
  s.print();
  cout<<endl;

  cout<<"----- OBSLUGA KOLEJKI ----------------------------------------------------------\n";
  Kolejka<char> k;
  cout<<"Dodaje element a \n";
  k.push('a');
  cout<<"Dodaje element b \n";
  k.push('b');
  cout<<"Dodaje element c \n";
  k.push('c');
  cout<<"Dodaje element d \n";
  k.push('d');
  cout<<"Element szczytowy: "<<k.top()<<endl;
  k.pop();
  cout<<"Sciaga 1 element (->nastepny elt to): "<<k.top()<<endl;
  cout<<"Pozostalo elementow: "<<k.size()<<'\n';
  cout<<"Czy kolejka jest pusta: "<<k.empty()<<'\n';
  cout<<"Funkcja dodatkowa: Wyswietl wszytsko: "<<endl;
  k.print();

  
  cout<<"----- OBSLUGA KOLEJKI PRIORYTETOWEJ --------------------------------------------\n";
  Kolejka_prio<double> kp;
  cout<<"Dodaje element 1 o wadze 20 \n";
  kp.push(1,20);
  cout<<"Dodaje element 2 o wadze 15 \n";
  kp.push(2,15);
  cout<<"Dodaje element 3 o wadze 32 \n";
  kp.push(3,32 );
  cout<<"Dodaje element 4 o wadze 12 \n";
  kp.push(4,12);
  cout<<"Dodaje element 5 o wadze 43 \n";
  kp.push(5,43);
  cout<<"Elementy to: \n";
  kp.print();
  cout<<"Pierwszy elemt to: "<<kp.top()<<'\n';
  cout<<"Sciaga 2 elementy: "<<kp.pop()<<" "<<kp.pop()<<"\n";
  cout<<"Pozostalo elementow: "<<kp.size()<<'\n';
  cout<<"Elementy to: \n";
  kp.print();
  cout<<endl;

  
  cout<<"---- HASZ_MAPA -----------------------------------------------------------------\n";
  Hasz_mapa<string,string> map_h;
  cout<<"Dodajemy element Pies o kluczu dostepu klucz_a \n";
  map_h.wstaw("klucz_a","Pies");
  cout<<"Dodajemy element Kot o kluczu dostepu klucz_b \n";
  map_h.wstaw("klucz_b","Kot");
  cout<<"Dodajemy element Kangur o kluczu dostepu klucz_c \n";
  map_h.wstaw("klucz_c","Kangur");
  cout<<"Usuwamy element o kodzie klucz_b \n";
  map_h.usun("klucz_b");
  cout<<"Wyswietlamy element o kluczu klucz_c: ";
  cout<<map_h["klucz_c"]<<endl;


  
}
