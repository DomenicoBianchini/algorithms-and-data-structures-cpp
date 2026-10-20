#ifndef CODA_H
#define CODA_H

#include <iostream>
#include <string>
using namespace std;

//classe astratta coda
template <class T>
class coda
{
public:
	//definizione del tipo generico valuetype
	typedef T value_type;
	//operatori
	virtual void create() = 0;
	virtual bool empty() const = 0;             //restituisce true se la coda è vuota
	virtual value_type top() const = 0;         //restituisce il valore in testa alla coda
	virtual void dequeque() = 0;                //rimuove un elemento della coda
	virtual void enqueque(value_type) = 0;      //inserisce un elemento nella coda
	virtual int size() const = 0;               //restituisce la lunghezza della coda
	virtual ~coda() {}                          //distruttore
};

#endif //CODA_H