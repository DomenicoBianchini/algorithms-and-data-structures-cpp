#ifndef CODAPN_H
#define CODAPN_H

#include <iostream>
#include <stdexcept>
#include "coda.h"
using namespace std;

//dichiaro la classe codapn
template <class T>
class codapn;

//dichiaro la classe nodocoda
template <class T>
class nodocoda
{
	friend class codapn<T>;

public:
	nodocoda()
	{
		next = nullptr;
	}
	nodocoda(T el)
	{
		item = el;
		next = nullptr;
	}

private:
	T item;
	nodocoda<T> *next;
};

template <class T>
class codapn : public coda<T>
{
public:
	typedef nodocoda<T> *node;
	typedef typename coda<T>::value_type value_type;
	//costruttore
	codapn();
	//costruttore di copia
	codapn(const codapn<T> &);
    //distruttore
	~codapn();
	/* =================================== OPERATORI =========================================== */
	//metodo che inizializza una nuova coda
	void create();
	//metodo che restituisce true se la coda è vuota
	bool empty() const;
	//metodo che restituisce il valore in testa alla coda 
	value_type top() const;
	//metodo che rimuove un elemento dalla coda
	void dequeque();
	//metodo che inserisce un elemento nella coda
	void enqueque(value_type);
	//metodo che restituisce la lunghezza della coda
	int size() const;
	//metodo che data una coda di interi restituisce una coda di soli elementi positivi
	codapn<int> pos_coda();
	//metodo che stampa tutti gli elementi della coda
	void print() const;
	
private:
	node head;
	node tail;
	int length;
};

//metodo public
template <class T>
codapn<T>::codapn()
{
	this->create();
	head = tail = nullptr;
}

//metodo public
template <class T>
codapn<T>::codapn(const codapn<T> &coda)
{
	this->create();
	head = tail = nullptr;
	node i = coda.head;
	while (i != nullptr)
	{
		this->enqueque(i->item);
		i = i->next;
	}
}

//metodo public
template <class T>
codapn<T>::~codapn()
{
	while (!this->empty())
	{
		this->dequeque();
	}
	head = tail = nullptr;
	length = 0;
}

//metodo public
template <class T>
void codapn<T>::create()
{
	length = 0;
}

//metodo public
template <class T>
bool codapn<T>::empty() const
{
	return (length == 0);
}

//metodo public
template <class T>
typename codapn<T>::value_type codapn<T>::top() const
{
	if (!this->empty())
	{
		return (head->item);
	}
	else{
		throw std::runtime_error("La coda è vuota");
	}
}

//metodo public
template <class T>
void codapn<T>::dequeque()
{
	if (!this->empty())
	{
		node temp = head;
		head = head->next;
		delete temp;
		temp = nullptr;
		length--;
	}
	else{
		throw std::runtime_error("La coda è vuota");
	}
}

//metodo public
template <class T>
void codapn<T>::enqueque(value_type el)
{
	node temp = new nodocoda<T>(el);
	if (this->empty())
	{
		head = tail = temp;
	}
	else
	{
		tail->next = temp;
	}
	temp->next = nullptr;
	tail = temp;
	length++;
}

//metodo public
template <class T>
int codapn<T>::size() const
{
	return (length);
}

//metodo public
template <>
codapn<int> codapn<int>::pos_coda()
{
	codapn<int> coda;			 
	codapn<int> codacopy(*this); 
	while (!codacopy.empty())
	{
		int temp = codacopy.top();
		if (temp >= 0)
		{
			coda.enqueque(temp);
		}
		codacopy.dequeque();
	}
	return (coda);
}

//metodo public
template <class T>
void codapn<T>::print() const
{
	if (!this->empty())
	{
		node i = head;
		while (i != nullptr)
		{
			cout << " " << i->item << " ";
			i = i->next;
		}
	}
	else{
		throw std::runtime_error("La coda è vuota");
	}
}

#endif //CODAPN_H