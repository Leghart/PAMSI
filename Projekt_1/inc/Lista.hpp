#ifndef LISTA_HPP_
#define LISTA_HPP_ 
#include <iostream>
using namespace std;

template <typename T>
class List{

  template <typename B>
	class Element{
	public:
		B dane;
		Element<B>* nast=0;
		Element<B>* poprzed=0;
	};

	Element<T>* start=0;
	Element<T>* stop=0;
public:
  List(){
    start=0;
    stop=0;
  }
	void pushFront(const T& newElement);
	void pushBack(const T& newElement) ;
  void remove(const T& element);
	void insert(const T& newElement,int index){
    operator[](index) = newElement;
  }

  /* Zwraca iterator ktory moze byc dowolnie modyfikowany */
	class Iterator{
	public:
		Element<T>* element;

		Iterator(Element<T>* e){
      element = e;
    }

		bool operator!=(Iterator i){
      return element != i.element->nast;
    }
    T& operator*(){
      return element->dane;
    }
		T operator++ (){ 
      Element<T>* tmp = element;
      element = element->nast; 
      return tmp->dane;
    }
		T operator-- (){
			Element<T>* tmp = element;
			element = element->poprzed;
			return tmp->dane;
    }
	};

	Iterator begin(){
    Iterator i(start);
    return i;
  }
	Iterator end(){
    Iterator i(stop);
    return i;
  }


  /* Zwraca iterator ktoremu *i nie da sie zmienic wartosci
     czyli jedynie mozna odczytac ta wartosc
     Jedynie zmiania sie przeciazenie *i
  */
	class ConstIterator : public Iterator{
	public:
		ConstIterator(Element<T>* e) : Iterator(e){} 
		T operator*(){
      return this->element->dane;
    }
	};

	ConstIterator cbegin() const{
    ConstIterator i(start);
    return i;
  }
	ConstIterator cend() const{
    ConstIterator i(stop);
    return i;
  } 
	T& operator[](int index);

};



/*****************************************************/
/************ METODY *********************************/
/*****************************************************/


template<typename T>
T& List<T>::operator[](int index){ //umozliwia odczytnanie jak i zmiane wartosci
  int j = 0;
  for (Iterator i = begin(); i != end(); ++i) {
    if (j == index) {
      return *i; 
    }
    j++;
  }
  cout << index << " nie nalezy do 0-" << j << endl;
  T t; // cos trzeba zwrocic (i tak nie da sie tu dostac)
  return t;
}


template <typename T>
void List<T>::pushFront(const T& newElement){
  Element<T>* element = new Element<T>();
  element->dane = newElement;
  if (start == 0) { 
    start = element;
    stop = element;
  }
  else {
    start->poprzed = element;
    element->nast = start;
    start = element; 
  }
}



template <typename T>
void List<T>::pushBack(const T& newElement){
  Element<T>* element = new Element<T>();
  element->dane = newElement;
  if (start == 0) {
    start = element;
    stop = element;
  }
  else {
    stop->nast = element; 
    element->poprzed = stop; 
    stop = element; 
  }
}

template <typename T>
void List<T>::remove(const T& element){
  for (Element<T>* e = start;e!=0;){ 
    Element<T>* usun = e;
    e=e->nast;
    if (usun->dane == element) {
      Element<T>* za = usun->nast;
      Element<T>* przed = usun->poprzed;
      if (przed == 0)
        start = za;
      else
        przed->nast = za;

      if (za == 0)
        stop = przed;
      else
        za->poprzed = przed;

      delete(usun);
    }
    if (e==0) return; 
  }
}

#endif
