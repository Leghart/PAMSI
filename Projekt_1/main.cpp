#include <iostream>
#include <algorithm>
#include <map>
#include <stack>
#include <list>
#include <queue>
#include <vector>
using namespace std;


int main(){
  
  cout <<"---------------- OBSLUGA LISTY -----------\n:";
  list<int> l;
  cout<<"Dodajemy elementy: 1B 2B 6F 2B 4F 2B 11F 13B 2B 2B\n";
  l.push_back(1);
	l.push_back(2);
	l.push_front(6);
	l.push_back(2);
	l.push_front(4);
  l.push_back(2);
  l.push_front(11);
  l.push_back(13);
  l.push_back(2);
  l.push_back(2);
  cout<<"Usuwamy wszystkie dwojki\n";
  l.remove(2);

  cout<<"Wyswietl liste: \n";
  for (list<int>::iterator  i = l.begin(); i != l.end(); ++i) {
		cout << *i << ", ";
	}
	cout << endl;

  cout<<"Zamien liczby parzyste na 0: \n";
  for (list<int>::iterator i = l.begin(); i != l.end(); ++i) {
		if (*i%2==0){
      *i = 0;//Tu mozemy zmieniac wartosci w liscie za pomoca iteratora
    }
		cout << *i << ", ";
	}
  cout << endl;

  cout<<"Wyswietl zmieniona liste: \n";
  for (list<int>::iterator i = l.begin(); i != l.end(); ++i) {
		cout << *i << ", ";
	}
	cout << endl;



  cout<<"----- OBSLUGA STOSU -------------- \n";
  stack<int> s;
  cout<<"Dodaje element 1 \n";
  s.push(1);
  cout<<"Dodaje element 2 \n";
  s.push(2);
  cout<<"Dodaje element 3 \n";
  s.push(3);
  cout<<"Dodaje element 4 \n";
  s.push(4);
  cout<<"Wartosc szczytowa: "<<s.top()<<endl;
  s.pop();
  cout<<"Sciaga 1 element (->nastepny elt to): "<<s.top()<<endl;
  cout<<"Pozostalo elementow: "<<s.size()<<endl;
  
  
  cout<<"----- OBSLUGA KOLEJKI ---------------- \n";
  queue<char> k;
  cout<<"Dodaje element a \n";
  k.push('a');
  cout<<"Dodaje element b \n";
  k.push('b');
  cout<<"Dodaje element c \n";
  k.push('c');
  cout<<"Dodaje element d \n";
  k.push('d');
  cout<<"Wartosc szczytowa: "<<k.front()<<endl;
  k.pop();
  cout<<"Sciaga 1 element (->nastepny elt to): "<<k.front()<<endl;
  cout<<"Pozostalo elementow: "<<k.size()<<'\n';
  cout<<"Czy kolejka jest pusta: "<<k.empty()<<'\n';


  cout<<"----- OBSLUGA KOLEJKI PRIORYTETOWEJ ---------------------- \n";
  priority_queue<int,vector<int>,greater<int>> kp;
  cout<<"Dodaje element 3 \n";
  kp.push(3);
  cout<<"Dodaje element 1 \n";
  kp.push(1);
  cout<<"Dodaje element 5 \n";
  kp.push(5);
  cout<<"Dodaje element 4  \n";
  kp.push(4);
  cout<<"Dodaje element 2 \n";
  kp.push(2);
  cout<<"Elementy to: \n";
  cout<<"Pierwszy elemt to: "<<kp.top()<<'\n';
  kp.pop();
  cout<<"Sciaga 1 element (->nastepny elt to): "<<kp.top()<<endl;
  cout<<"Pozostalo elementow: "<<kp.size()<<'\n';
 

  cout<<"---- HASZ_MAPA ------------------- \n";
  map<string,string> map_h;
  cout<<"Dodajemy element Pies o kluczu dostepu klucz_a \n";
  map_h["klucz_a"]="Pies";
  cout<<"Dodajemy element Kot o kluczu dostepu klucz_b \n";
  map_h["klucz_b"]="Kot";
  cout<<"Dodajemy element Kangur o kluczu dostepu klucz_c \n";
  map_h["klucz_c"]="Kangur";
  cout<<"Usuwamy element o kodzie klucz_b \n";
  map_h.erase("klucz_b");
  cout<<"Wyswietlamy element o kluczu klucz_c: ";
  cout<<map_h["klucz_c"]<<endl;


}
