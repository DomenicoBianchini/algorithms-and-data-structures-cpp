#ifndef MULTIPLESTACK_H
#define MULTIPLESTACK_H

#include <iostream>
#include "pilapn.h"
#include "./../Liste/linkedlist.h"
using namespace std;

template <class T>
class multiplestack : public pilapn<T>
{
public:
    typedef T value_type;
    //costruttore con parametro
    multiplestack(unsigned int);
    //distruttore
    ~multiplestack();
    //metodo che inserisce un elemento nella pila specificata
    void push(value_type, unsigned int);
    //metodo che rimuove un elemento dalla pila specificata
    void pop(unsigned int);
    //metodo che stampa la pila
    void print();

private:
    pilapn<T> *stackvector;
    int m;                    //numero totale delle pile
};

//metodo public
template <class T>
multiplestack<T>::multiplestack(unsigned int n)
{
    m = n;
    stackvector = new pilapn<T>[m];
    for (int i = 0; i < m; i++)
    {
        stackvector[i].create();
    }
}

//metodo public
template <class T>
multiplestack<T>::~multiplestack()
{
    if (stackvector != nullptr)
    {
        delete[] stackvector;
        stackvector = nullptr;
    }
    m = 0;
}

//metodo public
template <class T>
void multiplestack<T>::push(value_type el, unsigned int i)
{
    if (i < m)
    {
        stackvector[i].push(el);
    }
}

//metodo public
template <class T>
void multiplestack<T>::print()
{
    for (int i = 0; i < m; i++)
    {
        if (!stackvector[i].empty())
        {
            stackvector[i].print();
            cout << "\n";
        }
        else
        {
            cout << "La pila " << i << " è vuota" << endl;
        }
    }
}

//metodo public
template <class T>
void multiplestack<T>::pop(unsigned int i)
{
    if (i < m)
    {
        if (!stackvector[i].empty())
        {
            stackvector[i].pop();
        }
        else
        {
            cout << "La pila è vuota" << endl;
        }
    }
    else
    {
        cout << "L'indice della pila non valido" << endl;
    }
}

#endif