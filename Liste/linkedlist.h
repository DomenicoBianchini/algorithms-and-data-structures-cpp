#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <stdexcept>
#include "linearlist.h"
using namespace std;

//dichiaro la classe linkedlist
template <class T>
class linkedlist;

//dichiaro la classe nodolista
template <class T>
class listnode
{
	friend class linkedlist<T>;

public:
	listnode()
	{
		next = nullptr;
		prev = nullptr;
	}
	listnode(T el)
	{
		item = el;
		next = nullptr;
		prev = nullptr;
	}

private:
	T item;
	listnode<T> *next;
	listnode<T> *prev;
};

template <class T>
class linkedlist : public linearlist<T, listnode<T> *>
{
public:
	typedef typename linearlist<T, listnode<T> *>::value_type value_type;
	typedef listnode<T> *position;
	//costruttore di default
	linkedlist();
	//costruttore per copia
    linkedlist(const linkedlist<T> &);
    //distruttore
	~linkedlist();
    /* =================================== OPERATORI =========================================== */
	//metodo che inizializza una nuova lista
	void create();
	//metodo che restituisce true se la lista è vuota
	bool empty() const;
	//metodo che restituisce il valore data una posizione della lista
	value_type read(position) const;
	//metodo che scrive un valore in una posizione specificata nella lista
	void write(const value_type &, position);
	//metodo che restituisce il primo elemento della lista
	position begin() const;
	//metodo che restituisce l'ultimo elemento della lista
	position last() const;
	//metodo che restituisce un boolean, verifica se si è arrivati alla fine della lista
	bool end(position) const;
	//metodo che restituisce la posizione successiva 
	position next(position) const;
	//metodo che restituisce la posizione precedente 
	position previous(position) const;
	//metodo che inserisce un elemento in una posizione specificata nella lista
	void insert(const value_type &, position);
	//metodo che cancella un elemento in una posizione specificata 
	void erase(position);
	//funzioni utili
	/*metodo che in una lista di elementi di tipo intero, sposta
	il massimo in ultima posizione, e il minimo in prima posizione*/
	void move_min_max();
	//metodo che elimina da una lista L1 tutti gli elementi presenti nella lista L2.
	void difference(const linkedlist<T> &);
	//sovraccarico operatore di assegnamento
	linkedlist<T> &operator=(const linkedlist<T> &);
	//sovraccarico operatore di uguaglianza
	bool operator==(const linkedlist<T> &) const;
	//sovraccarico operatore di disuguaglianza
	bool operator!=(const linkedlist<T> &) const;

private:
	listnode<T> *phead;  //puntatore alla testa
	int length;			 //lunghezza della lista
};

//metodo public
template <class T>
linkedlist<T>::linkedlist()
{
	this->create();
	phead = new listnode<T>;
	phead->next = phead;
	phead->prev = phead;
}

//metodo public
template <class T>
linkedlist<T>::linkedlist(const linkedlist<T> &list)
{
	this->create();
	phead = new listnode<T>;
	phead->next = phead;
	phead->prev = phead;
	if (!list.empty())
	{
		position pos2 = list.begin();
		while (!list.end(pos2))
		{
			this->push_back(list.read(pos2));
			pos2 = pos2->next;
		}
	}
}

//metodo public
template <class T>
linkedlist<T>::~linkedlist()
{
	while (!this->empty())
	{
		this->erase(begin());
	}
	delete phead;
	phead = nullptr;
}

//metodo public
template <class T>
void linkedlist<T>::create()
{
	length = 0;
}

//metodo public
template <class T>
bool linkedlist<T>::empty() const
{
	return (length == 0);
}

//metodo public
template <class T>
typename linkedlist<T>::value_type linkedlist<T>::read(position pos) const
{
	if (!end(pos))
	{
		return (pos->item);
	}
	else{
		throw std::out_of_range("Posizione non valida");
	}
}

//metodo public
template <class T>
void linkedlist<T>::write(const value_type &el, position pos)
{
	if (!end(pos))
	{
		pos->item = el;
	}
	else{
		throw std::out_of_range("Posizione non valida");
	}
}

//metodo public
template <class T>
typename linkedlist<T>::position linkedlist<T>::begin() const
{
	return (phead->next);
}

//metodo public
template <class T>
typename linkedlist<T>::position linkedlist<T>::last() const
{
	return (phead->prev);
}

//metodo public
template <class T>
bool linkedlist<T>::end(position pos) const
{
	return (pos == phead);
}

//metodo public
template <class T>
typename linkedlist<T>::position linkedlist<T>::next(position pos) const
{
	return (pos->next);
}

//metodo public
template <class T>
typename linkedlist<T>::position linkedlist<T>::previous(position pos) const
{
	if (!end(pos))
	{
		return (pos->prev);
	}
	else
	{
		throw std::out_of_range("Posizione non valida");
	}
}

//metodo public
template <class T>
void linkedlist<T>::insert(const value_type &el, position pos)
{
	position newnode = new listnode<T>(el);
	newnode->next = pos;
	newnode->prev = pos->prev;
	pos->prev->next = newnode;
	pos->prev = newnode;
	length++;
}

//metodo public
template <class T>
void linkedlist<T>::erase(position pos)
{
	if (!empty() && !end(pos))
	{
		pos->prev->next = pos->next;
		pos->next->prev = pos->prev;
		delete pos;
		pos = nullptr;
		length--;
	}
	else{
		throw std::out_of_range("Posizione non valida");
	}
}

//metodo public
template <class T>
linkedlist<T> &linkedlist<T>::operator=(const linkedlist<T> &list)
{
	if (!(*this == list))
	{
		while (!this->empty())
		{
			this->erase(begin());
		}
		delete phead;
		phead = nullptr;
		length = 0;
		this->create();
		phead = new listnode<T>;
		phead->next = phead;
		phead->prev = phead;
		if (!list.empty())
		{
			position pos2 = list.begin();
			while (!list.end(pos2))
			{
				this->push_back(list.read(pos2));
				pos2 = pos2->next;
			}
		}
	}
	return *(this);
}

//metodo public
template <class T>
bool linkedlist<T>::operator==(const linkedlist<T> &list) const
{
	if (this->size() != list.size())
	{
		return (false);
	}
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
	return (true);
}

//metodo public
template <class T>
bool linkedlist<T>::operator!=(const linkedlist<T> &list) const
{
	return (!(*this == list));
}

//metodo public
template <>
void linkedlist<int>::move_min_max()
{
	if (!empty())
	{
		//cerco la posizione del minimo
		position minpos = begin();
		for (auto pos = begin(); !end(pos); pos = next(pos))
		{
			if (read(pos) < read(minpos))
			{
				minpos = pos;
			}
		}
		this->exchange(begin(), minpos);
		//cerco la posizione del massimo
		position maxpos = begin();
		for (auto pos = begin(); !end(pos); pos = next(pos))
		{
			if (read(pos) > read(maxpos))
			{
				maxpos = pos;
			}
		}
		this->exchange(last(), maxpos);
	}
}

//metodo public
template <class T>
void linkedlist<T>::difference(const linkedlist<T> &list)
{
	linkedlist<T> list_difference;
	if (!empty())
	{
		//rimuovo gli elementi in comune con la lista B
		for (auto i = begin(); !end(i); i = next(i))
		{
			if (!list.member(read(i)))
			{
				list_difference.push_back(read(i));
			}
		}
	}
	//assegno alla lista implicita A , la nuova lista differenza
	*this = list_difference;
}

#endif //LINKEDLIST_H