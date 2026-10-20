#ifndef LISTVECTOR_H
#define LISTVECTOR_H

#include <iostream>
#include <stdexcept>
#include "linearlist.h"
using namespace std;

template <class T>
class listvector : public linearlist<T, int>
{
public:
	typedef typename linearlist<T, int>::value_type value_type;
	typedef typename linearlist<T, int>::position position;
	//costruttore di default
	listvector();
	//costruttore con parametro
	listvector(int);
	//costruttore per copia
	listvector(const listvector<T> &);
	//distruttore
	~listvector();
	/* =================================== OPERATORI =========================================== */
	//metodo che inizializza la length della lista
	void create();
	//metodo che restituisce true se la lista è vuota
	bool empty() const;
	//metodo che restituisce il valore data una posizione della lista
	value_type read(position) const;
	//metodo che scrive un valore in una posizione specificata nella lista
	void write(const value_type &, position);
	//metodo che restituisce la prima posizione della lista
	position begin() const;
	//metodo che restituisce la posizione successiva
	position next(position) const;
	//metodo che restituisce la posizione precedente
	position previous(position) const;
	//metodo che restituisce un boolean, verifica se si è arrivati alla fine della lista
	bool end(position) const;
	//metodo che restituisce la posizione dell'ultimo elemento della lista ovvero il fine lista
	position last() const;
	//metodo che inserisce un elemento in ultima posizione della lista
	void push_back(const value_type &);
	//metodo che inserisce un elemento in una posizione specificata nella lista
	void insert(const value_type &, position);
	//metodo che cancella un elemento in una posizione specificata 
	void erase(position);
	//funzioni utili
	void insertion_sort();
	//sovraccarico operatore di assegnamento
	listvector<T> &operator=(const listvector<T> &);
	//sovraccarico operatore di uguaglianza
	bool operator==(const listvector<T> &) const;

private:
	//metodo private che permette di modificare la massima dimensione dell'array
	void changeDimension(value_type *&, int, int);
	value_type *elements;    //array di elementi
	int length;			     //lunghezza
	int array_dimension;     //capienza massima
};

//metodo public
template <class T>
listvector<T>::listvector()
{
	array_dimension = 10;
	elements = new T[array_dimension];
	this->create();
}

//metodo public
template <class T>
listvector<T>::listvector(int dim)
{
	array_dimension = dim;
	elements = new T[array_dimension];
	this->create(); 
}

//metodo public
template <class T>
listvector<T>::listvector(const listvector<T> &list)
{
	this->array_dimension = list.array_dimension;
	this->length = list.length;
	this->elements = new T[array_dimension];
	for (int i = 0; i < list.array_dimension; i++)
	{
		this->elements[i] = list.elements[i];
	}
}

//metodo public
template <class T>
listvector<T>::~listvector()
{
	delete[] elements;
	elements = nullptr;
	length = 0;
	array_dimension = 0;
}

//metodo public
template <class T>
void listvector<T>::create()
{
	length = 0;
}

//metodo public
template <class T>
bool listvector<T>::empty() const
{
	return (length == 0);
}

//metodo public
template <class T>
typename listvector<T>::value_type listvector<T>::read(position pos) const
{
	if ((pos > 0) && (pos < length + 1))
	{
		return (elements[pos - 1]);
	}
	else{
		throw std::out_of_range("Posizione non valida");
	}
}

//metodo public
template <class T>
void listvector<T>::write(const value_type &el, position pos)
{
	if ((pos > 0) && (pos < length + 1))
	{
		elements[pos - 1] = el;
	}
	else{
		throw std::out_of_range("Posizione non valida");
	}
}

//metodo public
template <class T>
typename listvector<T>::position listvector<T>::begin() const
{
	return (1); 
}

//metodo public
template <class T>
typename listvector<T>::position listvector<T>::next(position pos) const
{
	if ((pos > 0) && (pos < length + 1))
	{
		return (pos + 1);
	}
	else{
		throw std::out_of_range("Posizione non valida");
	}
		
}

//metodo public
template <class T>
typename listvector<T>::position listvector<T>::previous(position pos) const
{
	if ((pos > 1) && (pos < length + 1))
	{
		return (pos - 1);
	}
	else{
		throw std::out_of_range("Posizione non valida");
	}
}

//metodo public
template <class T>
bool listvector<T>::end(position pos) const
{
	if ((pos > 0) && (pos <= length + 1))
	{
		return (pos == length + 1);
	}
	else{
		throw std::out_of_range("Posizione non valida");
	}
}


//metodo public
template <class T>
typename listvector<T>::position listvector<T>::last() const
{
	position pos = begin();
	if (empty())
	{
		return (pos);
	}
	while (!end(next(pos)))
	{
		pos = next(pos);
	}
	return (pos);
}

//metodo public
template <class T>
void listvector<T>::push_back(const value_type& e) {
    position pos = length + 1;
    insert(e,pos);
}

//metodo public
template <class T>
void listvector<T>::insert(const value_type &el, position pos)
{
	if (length == array_dimension)
	{
		changeDimension(elements, array_dimension, array_dimension * 2);
		array_dimension = array_dimension * 2;
	}
	if ((pos > 0) && (pos <= length + 1))
	{
		for (int i = length; i >= pos; i--)
		{
			elements[i] = elements[i - 1];
		}
		elements[pos - 1] = el;
		length++;
	}
}

//metodo public
template <class T>
void listvector<T>::erase(position pos)
{
	if (length < array_dimension / 2)
	{
		changeDimension(elements, array_dimension, array_dimension / 2);
		array_dimension = array_dimension / 2;
	}
	if ((pos > 0) && (pos < length + 1))
	{
		if (!empty())
		{
			for (int i = pos - 1; i < (length - 1); i++)
			{
				elements[i] = elements[i + 1];
			}
			length--;
		}
	}
}

//metodo private
template <class T>
void listvector<T>::changeDimension(value_type *&e, int oldSize, int newSize)
{
	value_type *temp = new value_type[newSize];
	int number = 0;
	if (oldSize < newSize)
	{
		number = oldSize;
	}
	else
	{
		number = newSize;
	}
	for (int i = 0; i < number; i++)
	{
		temp[i] = e[i];
	}
	delete[] e;
	e = temp;
}

//metodo public
template <class T>
listvector<T> &listvector<T>::operator=(const listvector<T> &list)
{
	if (!(*this == list))
	{
		this->array_dimension = list.array_dimension;
		this->length = list.length;
		delete[] this->elements;
		elements = new T[array_dimension];
		for (int i = 0; i < list.array_dimension; i++)
		{
			this->elements[i] = list.elements[i];
		}
	}
	return *(this);
}

//metodo public
template <class T>
bool listvector<T>::operator==(const listvector<T> &list) const
{
	if (this->size() != list.size())
	{
		return (false);
	}
	else
	{
		position pos1 = begin();
		position pos2 = list.begin();
		while (!end(pos1))
		{
			if (!(read(pos1) == read(pos2)))
			{
				return (false);
			}
			pos1 = next(pos1);
			pos2 = next(pos2);
		}
	}
	return (true);
}

//metodo public
template <class T>
void listvector<T>::insertion_sort()
{
	T temp;
	position i, j;
	for (i = 1; i < length; i++)
	{
		temp = elements[i];
		j = i - 1;
		while ((j >= 0) && (elements[j] > temp))
		{
			elements[j + 1] = elements[j];
			j--;
		}
		elements[j + 1] = temp;
	}
}

#endif //LISTVECTOR_H