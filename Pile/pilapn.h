#ifndef PILAPN_H
#define PILAPN_H

#include <iostream>
#include <stdexcept>
#include "pila.h"
using namespace std;

//dichiaro la classe pilapn
template <class T>
class pilapn;

//dichiaro la classe nodopila
template <class T>
class nodopila
{
	friend class pilapn<T>;

public:
	nodopila()
	{
		prev = nullptr;
	}
	nodopila(T el)
	{
		item = el;
		prev = nullptr;
	}

private:
    T item;
	nodopila<T> *prev;
};

template <class T>
class pilapn : public pila<T>
{
public:
	typedef typename pila<T>::value_type value_type;
	typedef nodopila<T> *node;
	//costruttore
	pilapn();
	//distruttore
	~pilapn();
	/* =================================== OPERATORI =========================================== */
	//metodo che inizializza una nuova pila
	void create();
	//metodo che restituisce true se la pila è vuota
	bool empty() const;
	//metodo che restituisce l'elemento in cima alla pila
	value_type top() const;
	//metodo che restituisce e rimuove l'elemento in cima alla pila
	void pop();
	//metodo che inserisce un elemento in cima alla pila
	void push(value_type);
	//metodo che inserisce un elemento in cima alla pila senza duplicarlo in base al flag del secondo parametro
	void push(value_type, bool);
	//funzione di servizio che stampa tutti gli elementi contenuti nella pila
	void print();
	//funzione di servizio che verifica se un elemento e' già presente nella pila
	bool contains(value_type) const;

private:
	nodopila<T> *head;
};

//metodo public
template <class T>
pilapn<T>::pilapn()
{
	this->create();
}

//metodo public
template <class T>
pilapn<T>::~pilapn()
{
	while (!this->empty())
	{
		this->pop();
	}
	delete head;
	head = nullptr;
}

//metodo public
template <class T>
void pilapn<T>::create()
{
	head = nullptr;
}

//metodo public
template <class T>
bool pilapn<T>::empty() const
{
	return (head == nullptr);
}

//metodo public
template <class T>
typename pilapn<T>::value_type pilapn<T>::top() const
{
	if (!this->empty())
	{
		return (head->item);
	}
	else{
		throw std::out_of_range("La pila è vuota");
	}
}

//metodo public
template <class T>
void pilapn<T>::pop()
{
	if (!this->empty())
	{
		node temp = head;
		head = head->prev;
		delete temp;
		temp = nullptr;
	}
	else{
		throw std::out_of_range("La pila è vuota");
	}
}

//metodo public
template <class T>
void pilapn<T>::push(value_type el)
{
	nodopila<T> *newHead = new nodopila<T>(el);
	newHead->prev = head;
	head = newHead;
}

//metodo public
template <class T>
void pilapn<T>::print()
{
    if (!empty())
    {
        node i = head;
        while (i != nullptr)
        {
            cout << " " << i->item << " ";
            i = i->prev;
        }
        cout << endl;
    }
    else
    {
        throw std::out_of_range("La pila è vuota");
    }
}

//metodo public
template <class T>
bool pilapn<T>::contains(value_type el) const
{
	bool found = false;
	if (!this->empty())
	{
		node i = head;
		while ((i != nullptr) && !found)
		{
			if (i->item == el)
			{
				found = true;
			}
			i = i->prev;
		}
	}
	return (found);
}

//metodo public
template <class T>
void pilapn<T>::push(value_type el, bool flag)
{
	if (!flag)
	{
		push(el);
	}
	else
	{
		if (!contains(el))
		{
			push(el);
		}
	}
}

#endif //PILAPN_H