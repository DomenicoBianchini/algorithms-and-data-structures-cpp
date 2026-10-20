#ifndef LINEARLIST_H
#define LINEARLIST_H

#include <iostream>
#include <string>
using namespace std;

// classe astratta ListaLineare
template <class T, class P>
class linearlist
{
public:
	//definizione del tipo generico valuetype e del tipo posizione
	typedef T value_type;
	typedef P position;
	//operatori
	virtual void create() = 0;
	virtual bool empty() const = 0;                            //restituisce true se la lista è vuota
	virtual value_type read(position) const = 0;               //legge l'elemento in una posizione specificata 
	virtual void write(const value_type &, position) = 0;      //scrive in una posizione specificata 
	virtual position begin() const = 0;			               //restituisce la posizione che punta all'inizio della lista
	virtual bool end(position) const = 0;		               //restituisce true se la posizione è l'ultima che punta alla fine della lista
	virtual position last() const = 0;			               //restituisce la posizione dell'ultimo elemento della lista
	virtual position next(position) const = 0;	               //restituisce la posizione successiva
	virtual position previous(position) const = 0;             //restituisce la posizione precedente
	virtual void insert(const value_type &, position) = 0;     //inserisce un elemento
	virtual void erase(position) = 0;                          //elimina l'elemento in una posizione specificata
	virtual ~linearlist(){};                                   //distruttore della classe astratta 
	/*			****	      		funzioni di servizio	    		****		*/
	//metodo per stampare tutti gli elementi di una lista
	friend ostream &operator<<(ostream &os, const linearlist<T, P> &l)
	{
		linearlist<T, P>::position p;
		p = l.begin();
		os << "[";
		while (!l.end(p))
		{
			if (p != l.begin())
			{
				os << ", " << l.read(p);
			}
			else
			{
				os << l.read(p);
			}
			p = l.next(p);
		}
		os << "]" << endl;
		return (os);
	}
	// metodo che restituisce la lunghezza della lista ovvero il numero di elementi
	int size() const;
	//metodo che inserisce un elemento in testa alla lista
	void push_front(const value_type &);
	//metodo che inserisce un elemento in fondo alla lista
	void push_back(const value_type &);
	//metodo che rimuove l'elemento in testa alla lista
	void pop_front();
	//metodo che rimuove l'elemento in fondo alla lista
	void pop_back();
	//metodo che pulisce la lista e restituisce una lista vuota priva di elementi
	void clear();
	//metodo che inverte gli elementi di una lista
	void reverse();
	//metodo che restituisce vero se una lista e' palindroma
	bool palindrome() const;
	//metodo che rimuove un item dalla lista
	void remove(value_type);
	//metodo che calcola il numero di elementi compresi fra due posizioni specificate
	int num_elements(position, position);
	//scambia gli elementi fra due posizioni specificate 
	void exchange(position, position);
	//metodo che restituisce true se l'elemento appartiene alla lista
	bool member(value_type) const;
};

//metodo public
template <class T, class P>
int linearlist<T, P>::size() const
{
	int count = 0;
	for (typename linearlist<T, P>::position pos = begin(); !end(pos); pos = next(pos))
	{
		count++;
	}
	return (count);
}

//metodo public
template <class T, class P>
void linearlist<T, P>::push_front(const value_type &el)
{
	insert(el, begin());
}

//metodo public
template <class T, class P>
void linearlist<T, P>::push_back(const value_type &el)
{
	if (empty())
	{
		insert(el, begin());
	}
	else
	{
		insert(el, next(last()));
	}
}

//metodo public
template <class T, class P>
void linearlist<T, P>::pop_front()
{
	erase(begin());
}

//metodo public
template <class T, class P>
void linearlist<T, P>::pop_back()
{
	erase(last());
}

//metodo public
template <class T, class P>
void linearlist<T, P>::clear()
{
	while (!this->empty())
	{
		this->pop_front();
	}
}

//metodo public
template <class T, class P>
void linearlist<T, P>::reverse()
{
	auto lastpos = last();
	int medLength = this->size() / 2;
	int i = 0;
	for (auto pos = begin(); !end(pos) && (i < medLength); pos = next(pos))
	{
		T temp = read(pos);
		write(read(lastpos), pos);
		write(temp, lastpos);
		lastpos = previous(lastpos);
		i++;
	}
}

//metodo public
template <class T, class P>
bool linearlist<T, P>::palindrome() const
{
	if (this->size() < 2)
	{
		return (true);
	}
	else
	{
		bool flag = true;
		auto prev = last();
		for (auto curr = begin(); !end(curr) && (flag); curr = next(curr))
		{
			if (read(curr) != read(prev))
			{
				flag = false;
			}
			prev = previous(prev);
		}
		return (flag);
	}
}

//metodo public
template <class T, class P>
void linearlist<T, P>::remove(value_type el)
{
	bool found = false;
	auto pos = begin();
	while (!end(pos) && !found)
	{
		if (read(pos) == el)
		{
			found = true;
		}
		else
		{
			pos = next(pos);
		}
	}
	if (found)
	{
		this->erase(pos);
	}
}

//metodo public
template <class T, class P>
int linearlist<T, P>::num_elements(position p1, position p2)
{
	int n = 0;
	auto pos = p1;
	while (!end(pos) && next(pos) != p2)
	{
		n++;
		pos = next(pos);
	}
	return (n);
}

//metodo public
template <class T, class P>
void linearlist<T, P>::exchange(position p1, position p2)
{
	if (!empty() && (p1 != p2))
	{
		T temp = read(p1);
		write(read(p2), p1);
		write(temp, p2);
	}
}

//metodo public
template <class T, class P>
bool linearlist<T, P>::member(value_type el) const
{
	bool found = false;
	if (!empty())
	{
		for (auto i = begin(); !end(i) && !found; i = next(i))
		{
			if (read(i) == el)
			{
				found = true;
			}
		}
	}
	return (found);
}

#endif //LINEARLIST_H