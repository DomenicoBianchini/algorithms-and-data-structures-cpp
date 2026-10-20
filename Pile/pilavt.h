#ifndef PILAVT_H
#define PILAVT_H

#include <iostream>
#include <stdexcept>
#include "pila.h"
using namespace std;

template <class T>
class pilavt : public pila<T>
{
public:
	typedef typename pila<T>::value_type value_type;
	//costruttore di default
	pilavt();
	//costruttore con paramentro 
	pilavt(int);
    //distruttore
    ~pilavt();
    /* =================================== OPERATORI =========================================== */
    //metodo che inizializza la lenght della pila
	void create();
    //metodo che restituisce true se la pila è vuota
	bool empty() const;
    //metodo che restituisce e rimuove l'elemento in cima alla pila
	value_type top() const;
    //metodo che rimuove l'elemento in cima alla pila
	void pop();
    //metodo che inserisce un elemento in cima alla pila
	void push(value_type);
    //funzione di servizio che stampa tutti gli elementi contenuti nella pila
	void print();

private:
	value_type *elements;     //array di elementi
	int length;               //lunghezza
	int head;                 //indice per la testa della pila
};

//metodo public
template <class T>
pilavt<T>::pilavt()
{
	length = 100;
	elements = new value_type[length];
	this->create();
}

//metodo public
template <class T>
pilavt<T>::pilavt(int dim)
{
	length = dim;
	elements = new value_type[length];
	this->create();
}

//metodo public
template <class T>
pilavt<T>::~pilavt()
{
	length = 0;
	head = 0;
	if (elements != nullptr)
	{
		delete[] elements;
		elements = nullptr;
	}
}

//metodo public
template <class T>
void pilavt<T>::create()
{
	head = 0;
}

//metodo public
template <class T>
bool pilavt<T>::empty() const
{
	return (head == 0);
}

//metodo public
template <class T>
typename pilavt<T>::value_type pilavt<T>::top() const
{
	if (!empty())
	{
		return (elements[head]);
	}
	else{
		throw std::out_of_range("La pila è vuota");
	}
	
}

//metodo public
template <class T>
void pilavt<T>::pop()
{
	if (!empty())
	{
        head--;
	}
	else{
		throw std::out_of_range("La pila è vuota");
	}
}

//metodo public
template <class T>
void pilavt<T>::push(value_type e1)
{
    if (head < length) 
    {
        head++;
        elements[head] = e1;
    }
    else
    {
        cout << "la pila è piena, impossibile aggiungere elementi." << endl;
    }
}


//metodo public
template <class T>
void pilavt<T>::print()
{
    if (!empty())
    {
        for (int i = head; i > 0; --i)
        {
            cout << elements[i] << " ";
        }
        cout << endl;
    }
    else
    {
        throw std::out_of_range("La pila è vuota");
    }
}

#endif //PILAVT_H