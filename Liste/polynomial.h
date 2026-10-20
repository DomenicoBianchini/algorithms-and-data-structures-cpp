#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include "listvector.h"
using namespace std;

class polynomial
{
public:
    //costruttore
    polynomial();
    //distruttore
    ~polynomial();
    //metodo che restituisce il grado di un polinomio
    int grado();
    //metodo che restituisce il valore del polinomio con coefficiente x
    int valore(int x);
    //visualizza il polinomio
    void output(ostream &outStream);
    //metodo che acquisisce un polinomio dallo stream di input inStream
    void input(istream &inStream);
    //somma con il polinomio b
    void somma(const polynomial &b);
    //moltiplica con il polinomio b
    void moltiplica(const polynomial &b);
    //sovraccarico operatore di assegnamento 
    polynomial &operator=(const polynomial &);

private:
    listvector<int> l;
};

//metodo public
polynomial::polynomial()
{
    l.create(); 
}

//metodo public
polynomial::~polynomial()
{
}

//metodo public
int polynomial::grado()
{
    return (l.size());
}

//metodo public
int polynomial::valore(int x)
{
    if (l.empty())
    {
        return 0;
    }
    return l.read(x);
}

//metodo public
void polynomial::somma(const polynomial &b)
{
    auto j = b.l.begin();
    for (auto i = l.begin(); !l.end(i) && !b.l.end(j); i = l.next(i))
    {
        l.write(l.read(i) + b.l.read(j), i);
        j = b.l.next(j);
    }
    if (!b.l.end(j))
    {
        while (!b.l.end(j))
        {
            l.push_back(b.l.read(j));
            j = b.l.next(j);
        }
    }
}

//metodo public
void polynomial::output(ostream &outStream)
{
    for (auto i = l.begin(); !l.end(i); i = l.next(i))
    {
        if (l.read(i) != -1)
        {
            outStream << "[" << i << "]coefficiente: " << l.read(i) << endl;
        }
    }
}

//metodo public
void polynomial::input(istream &inStream)
{
    int grado = 0;
    int valore = 0;
    cout << "Inserire il grado del polinomio : ";
    inStream >> grado;
    cout << endl
         << "inserisci elementi: " << endl;
    int i = 0;
    while (i < grado)
    {
        cout << "\nn: ";
        inStream >> valore;
        l.push_back(valore);
        i++;
    }
}

//metodo public
void polynomial::moltiplica(const polynomial &b)
{
    listvector<int> pl;
    int s = l.size() + b.l.size() - 1;
    int it = 0;
    while (it < s)
    {
        pl.push_back(0);
        it++;
    }
    for (auto i = l.begin(); !l.end(i); i = l.next(i))
    {
        for (auto j = b.l.begin(); !b.l.end(j); j = b.l.next(j))
        {
            int product_position = i + j - 1;
            pl.write(pl.read(product_position) +
                         l.read(i) * b.l.read(j),
                     product_position);
        }
    }
    this->l = pl;
}

//metodo public
polynomial &polynomial::operator=(const polynomial &b)
{
    l = b.l;
    return *this;
}

#endif  