#ifndef CODAPVT_H
#define CODAPVT_H

#include <iostream>
#include "assert.h"
#include "codap.h"
using namespace std;

template <class T>
class codapvt : public codap<T>
{
public:
	typedef typename codap<T>::value_type value_type;
	//costruttore di default
	codapvt();
	//costruttore con parametro
	codapvt(int);
	//distruttore
	~codapvt();
    /* =================================== OPERATORI =========================================== */
	//metodo che inizializza la coda
	void create();
	//metodo che restituisce true se la coda è vuota
	bool empty() const;
	//metodo che restituisce l'elemento con priorità minima
	value_type min() const;
	//metodo che rimuove dalla coda l'elemento con priorità minima
	void deleteMin();
	//metodo che inserisce un elemento nella coda
	void insert(value_type);
	//metodo che stampa tutti gli elementi della coda
	void print() const;

private:
	//massima capienza
	int MAXLENGHT;
	//array di tipoelem
	value_type *heap;
	//riferimento all'ultimo elemento inserito
	int last;
	//metodo che aggiorna lo stato della coda quando viene inserito un elemento
	void fixUp();
	//metodo che aggiorna lo stato della coda quando viene rimosso un elemento
	void fixDown(int, int);
};

//metodo public
template <class T>
codapvt<T>::codapvt()
{
	this->create();
	MAXLENGHT = 100;
	heap = new value_type[MAXLENGHT];
}

//metodo public
template <class T>
codapvt<T>::codapvt(int N)
{
	this->create();
	MAXLENGHT = N;
	heap = new value_type[MAXLENGHT];
}

//metodo public
template <class T>
codapvt<T>::~codapvt()
{
	last = 0;
	delete[] heap;
	heap = nullptr;
}

//metodo public
template <class T>
void codapvt<T>::create()
{
	last = 0;
}

//metodo public
template <class T>
bool codapvt<T>::empty() const
{
	return (last == 0);
}

//metodo public
template <class T>
void codapvt<T>::insert(value_type v)
{
	assert(last < MAXLENGHT);
	heap[++last - 1] = v;
	fixUp();
}

//metodo public
template <class T>
typename codapvt<T>::value_type codapvt<T>::min() const
{
	assert(last != 0);
	return (heap[0]);
}

//metodo public
template <class T>
void codapvt<T>::deleteMin()
{
	assert(last != 0);
	heap[0] = heap[last - 1];
	last--;
	fixDown(1, last);
}

//metodo private
template <class T>
void codapvt<T>::fixUp()
{
	int k = last;

	while ((k > 1) && (heap[k - 1] < heap[(k / 2) - 1]))
	{
		value_type tmp;

		tmp = heap[k - 1];
		heap[k - 1] = heap[(k / 2) - 1];
		heap[k / 2 - 1] = tmp;
		k = k / 2;
	}
}

//metodo private
template <class T>
void codapvt<T>::fixDown(int k, int N)
{

	short int exchange = 1;

	while ((k <= N / 2) && (exchange))
	{
		int j = 2 * k;
		value_type tmp;
		if ((j < N) && (heap[j - 1] > heap[j]))
		{
			j++;
		}
		if (exchange = (heap[j - 1] < heap[k - 1]))
		{
			tmp = heap[k - 1];
			heap[k - 1] = heap[j - 1];
			heap[j - 1] = tmp;
			k = j;
		}
	}
}

//metodo public
template <class T>
void codapvt<T>::print() const
{
	cout << "\n[ ";
	for (int i = 0; i < last; i++)
	{
		if (i % 2 == 0)
		{
			cout << heap[i];
		}
		else
		{
			cout << "\t" << heap[i] << " - ";
		}
	}
	cout << " ]\n";
}

//metodo public
template <class T>
void print(T *A, int n)
{
	cout << "\n[";
	for (int i = 0; i < n; i++)
	{
		cout << " " << A[i] << " ";
	}
	cout << "]\n";
}

//metodo public
template <class T>
void heapsort(T *e, int n)
{
	codapvt<T> pq(n);
	for (int i = 0; i < n; i++)
	{
		pq.insert(e[i]);
	}
	for (int i = 0; i < n; i++)
	{
		e[i] = pq.min();
		pq.deleteMin();
	}
}

#endif