#ifndef ALBERO_H
#define ALBERO_H

#include <iostream>
#include <string>
using namespace std;

//classe astratta albero n-ario
template <class I, class N>
class albero
{
public:
	//definizione dei tipi generici item e node
	typedef I item;
	typedef N node;
	//operatori
	virtual void create() = 0;
	virtual bool empty() const = 0;                       //restituisce true se l'albero n-ario è vuoto
	virtual void insRoot() = 0;                           //alloca la radice
	virtual void insFirstChild(node, item) = 0;           //inserisce un nuovo primo figlio al nodo specificato con un item
	virtual void insNextSibling(node, item) = 0;          //inserisce un nuovo nodo fratello al nodo specificato con un item
	virtual node getRoot() const = 0;                     //restituisce il riferimento alla radice
	virtual node parent(node) const = 0;                  //restituisce il riferimento al genitore
	virtual bool leaf(node) const = 0;                    //restituisce true se il nodo è foglia
	virtual node firstChild(node) const = 0;              //restituisce il riferimento al primo figlio
	virtual bool lastSibling(node) const = 0;             //restituisce true se il nodo è ultimo fratello
	virtual node nextSibling(node) const = 0;             //restituisce il riferimento al successivo fratello
	virtual void removeSubTree(node) = 0;                 //rimuove un sottoalbero
	virtual void write(node, item) = 0;                   //modifica il valore di un nodo specificato con un item
	virtual item read(node) const = 0;                    //restituisce il valore letto nel nodo specificato
	int depth() const;                                    //restituisce la profondità dell'albero n-ario
	void depth(node, int, int &) const;                   //restituisce la profondità del sottoalbero radicato nel nodo specificato 
	int width() const;                                    //restituisce la lunghezza dell'albero n-ario
	void width(node, int, int &) const;                   //restituisce la lunghezza del sottoalbero radicato nel nodo specificato 
	virtual ~albero(){};                                  //distruttore
};

//metodo public
template <class I, class N>
int albero<I, N>::depth() const
{
	int maxdepth;
	if (!empty())
	{
		maxdepth = 0;
		depth(getRoot(), 0, maxdepth);
	}
	else
	{
		maxdepth = -1;
	}
	return maxdepth;
}

//metodo public
template <class I, class N>
void albero<I, N>::depth(node curr, int currdepth, int &maxdepth) const
{
	if (!leaf(curr))
	{
		depth(firstChild(curr), currdepth + 1, maxdepth);
	}
	else
	{
		if (maxdepth < currdepth)
		{
			maxdepth = currdepth;
		}
	}
	if (!lastSibling(curr))
	{
		depth(nextSibling(curr), currdepth, maxdepth);
	}
}

//metodo public
template <class I, class N>
int albero<I, N>::width() const
{
	int maxwidth;
	if (!empty())
	{
		maxwidth = 1;
		width(getRoot(), 0, maxwidth);
	}
	else
	{
		maxwidth = 0;
	}
	return maxwidth;
}

//metodo public
template <class I, class N>
void albero<I, N>::width(node n, int currwidth, int &maxwidth) const
{
	if (leaf(n))
	{
		return;
	}
	node child = firstChild(n);
	currwidth = 0;
	while (true)
	{
		currwidth++;
		if (lastSibling(child))
		{
			break;
		}
		child = nextSibling(child);
	}
	if (maxwidth < currwidth)
	{
		maxwidth = currwidth;
	}
	child = firstChild(n);
	while (true)
	{
		width(child, currwidth, maxwidth);
		if (lastSibling(child))
		{
			break;
		}
		child = nextSibling(child);
	}
}

#endif //ALBERO_H