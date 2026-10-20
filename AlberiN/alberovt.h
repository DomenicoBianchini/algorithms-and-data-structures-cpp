#ifndef ALBEROVT_H
#define ALBEROVT_H

#include <iostream>
#include "./../Liste/listvector.h"
#include "albero.h"
#define MAXNODES 100
using namespace std;

template <class I>
class alberovt : public albero<I, int>
{
public:
	typedef typename albero<I, int>::item item; 
	typedef typename albero<I, int>::node node; 
	//costruttore
	alberovt();
    //distruttore 
	~alberovt();
    /* =================================== OPERATORI =========================================== */
	//metodo che inizializza l'albero
	void create();
	//metodo che restituisce true se l'albero è vuoto
	bool empty() const;
	//metodo che alloca la radice
	void insRoot();
	//metodo che restituisce il riferimento alla radice
	node getRoot() const;
	//metodo che restituisce il riferimento al genitore del nodo specificato
	node parent(node) const;
	//metodo che restituisce true se il nodo è foglia
	bool leaf(node) const;
	//metodo che restituisce il riferimento del primo figlio
	node firstChild(node) const;
	//metodo che restituisce true se il nodo specificato è ultimo fratello
	bool lastSibling(node) const;
	//metodo che restituisce il riferimento al fratello successivo
	node nextSibling(node) const;
	//inserisce un primo figlio al nodo specificato con un item
	void insFirstChild(node, item);
	//inserisce un nodo come fratello del nodo specificato con un item
	void insNextSibling(node, item);
	//metodo che rimuove il sottoalbero radicato nel nodo specificato
	void removeSubTree(node);
	//metodo che modifica il valore di un nodo specificato con un item
	void write(node, item);
	//metodo che restituisce il valore letto nel nodo specificato
	item read(node) const;
	//metodo che stampa l'albero n-ario
	void print() const;

private:
	struct Record
	{
		item el;
		bool used;
		listvector<int> childs;     //vettore dei figli
	};
	typedef listvector<int>::position position;    //tipo posizione vettore figli
	Record nodes[MAXNODES];						   //vettore dei padri
	node root;									   //nodo radice
	int numNodes;								   //numero nodi 
};  

//metodo public
template <class I>
alberovt<I>::alberovt()
{
	this->create();
}

//metodo public
template <class I>
alberovt<I>::~alberovt()
{
	if (!this->empty())
	{
		this->removeSubTree(root);
	}
	numNodes = 0;
}

//metodo public
template <class I>
void alberovt<I>::create()
{
	numNodes = 0;
	for (int i = 0; i < MAXNODES; i++)
	{
		nodes[i].used = false;
		nodes[i].childs.create();
	}
}

//metodo public
template <class I>
bool alberovt<I>::empty() const
{
	return (numNodes == 0);
}

//metodo public
template <class I>
void alberovt<I>::insRoot()
{
	if (this->empty())
	{
		root = 0;
		nodes[0].used = true;
		numNodes++;
	}
}

//metodo public
template <class I>
typename alberovt<I>::node alberovt<I>::getRoot() const
{
	return (root);
}

//metodo public
template <class I>
typename alberovt<I>::node alberovt<I>::parent(node n) const
{
	position child;
	int p;
	for (int i = 0; i < MAXNODES; i++)
	{
		if (!nodes[i].childs.empty())
		{
			child = nodes[i].childs.begin();
			bool found = false;
			while (!nodes[i].childs.end(child) && !found)
			{
				if (nodes[i].childs.read(child) == n)
				{
					found = true;
					p = i;
				}
				child = nodes[i].childs.next(child);
			}
			if (found)
			{
				return (p);
			}
		}
	}
	return (n);
}

//metodo public
template <class I>
bool alberovt<I>::leaf(node n) const
{
	return (nodes[n].childs.empty());
}

//metodo public
template <class I>
typename alberovt<I>::node alberovt<I>::firstChild(node n) const
{
	if (!leaf(n))
	{
		return (nodes[n].childs.read(nodes[n].childs.begin()));
	}
	return (n);
}

//metodo public
template <class I>
bool alberovt<I>::lastSibling(node n) const
{
	position c;
	node p = parent(n);
	c = nodes[p].childs.begin();
	while (!nodes[p].childs.end(c))
	{
		c = nodes[p].childs.next(c);
	}
	return (n == nodes[p].childs.read(c));
}

//metodo public
template <class I>
typename alberovt<I>::node alberovt<I>::nextSibling(node n) const
{
	if (!lastSibling(n))
	{
		position c;
		node p = parent(n);
		c = nodes[p].childs.begin();
		while (!nodes[p].childs.end(c))
		{
			if (nodes[p].childs.read(c) == n)
			{
				return (nodes[p].childs.read(nodes[p].childs.next(c)));
			}
			c = nodes[p].childs.next(c);
		}
	}
	return (n); 
}

//metodo public
template <class I>
void alberovt<I>::insFirstChild(node n, item el)
{
	int k = 0;
	while ((k < MAXNODES) && (nodes[k].used == true))
	{
		k++;
	}
	if (k < MAXNODES)
	{
		nodes[k].used = true;
		numNodes++;
		nodes[k].el = el;
		nodes[n].childs.push_front(k);
	}
}

//metodo public
template <class I>
void alberovt<I>::insNextSibling(node n, item el)
{
	int k = 0;
	while ((k < MAXNODES) && (nodes[k].used == true))
	{
		k++;
	}
	if (k < MAXNODES)
	{
		nodes[k].used = true;
		numNodes++;
		nodes[k].el = el;
		node p = parent(n);
		position child = nodes[p].childs.begin();
		bool found = false;
		while (!nodes[p].childs.end(child) && !found)
		{
			if (nodes[p].childs.read(child) == n)
			{
				found = true;
			}
			child = nodes[p].childs.next(child);
		}
		nodes[p].childs.insert(k, child);
	}
}

//metodo public
template <class I>
void alberovt<I>::removeSubTree(node n)
{
	position c;
	if (!leaf(n))
	{
		while (!nodes[n].childs.empty())
		{
			removeSubTree(nodes[n].childs.read(nodes[n].childs.begin()));
		}
	}
	if (n != root)
	{
		node p = parent(n);
		c = nodes[p].childs.begin();
		while (nodes[p].childs.read(c) != n)
		{
			c = nodes[p].childs.next(c);
		}
		nodes[p].childs.erase(c);
	}
	nodes[n].used = false;
	numNodes--;
}

//metodo public
template <class I>
void alberovt<I>::write(node n, item el)
{
	if (nodes[n].used == true)
	{
		nodes[n].el = el;
	}
}

//metodo public
template <class I>
typename alberovt<I>::item alberovt<I>::read(node n) const
{
	item el;
	if (nodes[n].used == true)
	{
		return (nodes[n].el);
	}
	return (el);
}

//metodo public
template <class I>
void alberovt<I>::print() const
{
	cout << "\n{";
	for (int i = 0; i < MAXNODES; i++)
	{
		if (nodes[i].used == true)
		{
			cout << "\n " << read(i) << ": ";
			if (!leaf(i))
			{
				position child = nodes[i].childs.begin();
				while (!nodes[i].childs.end(child))
				{
					cout << read(nodes[i].childs.read(child)) << " ";
					child = nodes[i].childs.next(child);
				}
			}
		}
	}
	cout << "\n}\n";
}

#endif //ALBEROVT_H