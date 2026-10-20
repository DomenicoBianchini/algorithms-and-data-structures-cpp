#ifndef CODAP_H
#define CODAP_H

#include <iostream>
#include <string>
using namespace std;

//classe astratta coda con priorità
template <class T>
class codap
{
public:
	//definizione del tipo generico valuetype
	typedef T value_type;
	//operatori
	virtual void create() = 0;
	virtual bool empty() const = 0;           //restituisce true se la coda è vuota
	virtual value_type min() const = 0;       //restituisce l'elemento con priorità minima
	virtual void deleteMin() = 0;             //rimuove dalla coda l'elemento con priorità minima
	virtual void insert(value_type) = 0;      //inserisce un elemento nella coda
	virtual ~codap(){};                       //distruttore
};

#endif