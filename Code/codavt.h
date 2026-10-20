#ifndef CODAVT_H
#define CODAVT_H

#include <iostream>
#include <stdexcept>
#include "coda.h"
#define MaxDim 100
using namespace std;

template <class T>
class codavt : public coda<T>
{
public:
	typedef typename coda<T>::value_type value_type;
	//costruttore di default 
	codavt();
	//costruttore con parametro
	codavt(int);
    //distruttore
	~codavt();
	/* =================================== OPERATORI =========================================== */
	//metodo che inizializza una coda
	void create();
	//metodo che restituisce true se la coda è vuota
	bool empty() const;
	//metodo che restituisce il valore in testa alla coda
	value_type top() const;
	//metodo che rimuove un elemento della coda 
	void dequeque();
	//metodo che inserisce un elemento nella coda
	void enqueque(value_type);
	//metodo che restituisce la lunghezza della coda
	int size() const;
	//metodo che stampa tutti gli elementi della coda
	void print() const;
	
private:
	value_type *elements;   //array di elementi
	int head;			    //cursore che punta alla testa dell'array
	int length;			    //lunghezza della coda
	int maxLength;		    //massima capienza
};

//metodo public
template <class T>
codavt<T>::codavt()
{
	this->create();
	maxLength = MaxDim;
	elements = new value_type[maxLength];
	head = 0;
}

//metodo public
template <class T>
codavt<T>::codavt(int N)
{
	this->create();
	maxLength = N;
	elements = new value_type[maxLength];
	head = 0;
}

//metodo public
template <class T>
codavt<T>::~codavt()
{
	length = 0;
	delete[] elements;
	elements = nullptr;
}

//metodo public
template <class T>
void codavt<T>::create()
{
	length = 0;
}

//metodo public
template <class T>
bool codavt<T>::empty() const
{
	return (length == 0);
}

//metodo public
template <class T>
typename codavt<T>::value_type codavt<T>::top() const
{
	if (!this->empty())
	{
		return (elements[head]);
	}
	else{
		throw std::out_of_range("La coda è vuota");
	}
}

//metodo public
template <class T>
void codavt<T>::dequeque()
{
	if (!this->empty())
	{
		head = ((head + 1) % maxLength);
		length--;
	}
	else{
		throw std::out_of_range("La coda è vuota");
	}
}

//metodo public
template <class T>
void codavt<T>::enqueque(value_type el)
{
	if (length < maxLength)
	{
		elements[((head + length) % maxLength)] = el;
		length++;
	}
}

//metodo public
template <class T>
int codavt<T>::size() const
{
	return (length);
}

//metodo public
template <class T>
void codavt<T>::print() const
{
    if (!this->empty())
    {
        for (int i = 0; i < length; ++i)
        {
            cout << " " << elements[(head + i) % maxLength] << " ";
        }
    }
	else{
		throw std::out_of_range("La coda è vuota");
	}
}

#endif //CODAVT_H