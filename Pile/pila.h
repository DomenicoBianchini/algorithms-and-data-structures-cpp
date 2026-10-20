#ifndef PILA_H
#define PILA_H

#include <iostream>
#include <string>
using namespace std;

//classe astratta pila
template <class T>
class pila
{
public:
	//definizione del tipo generico valuetype
	typedef T value_type;
	//operatori
	virtual void create() = 0;               
	virtual bool empty() const = 0;          //restituisce true se la lista è vuota
	virtual value_type top() const = 0;      //restituisce il valore dell'elemento in cima alla pila
	virtual void pop() = 0;                  //restituisce e rimuove l'elemento in cima alla pila
	virtual void push(value_type) = 0;       //inserisce un elemento in cima alla pila
	virtual ~pila(){};                       //distruttore della classe astratta
};

#endif //PILA_H