#ifndef ALBEROPN_H
#define ALBEROPN_H

#include <iostream>
#include <stdexcept>
#include "albero.h"
#include "./../Code/codapn.h"
using namespace std;

//dichiaro la classe albero n-ario
template <class I>
class alberopn;

//creo la classe nodo dell'albero n-ario
template <class I>
class nodoalbero
{
	friend class alberopn<I>;

public:
	nodoalbero()
	{
		first = nullptr;
		next = nullptr;
		parent = nullptr;
		level = 0;
	}
	nodoalbero(I el)
	{
		first = nullptr;
		next = nullptr;
		parent = nullptr;
		item = el;
		level = 0;
	}

private:
	nodoalbero<I> *parent;   //riferimento al nodo genitore
	nodoalbero<I> *first;    //riferimanto al primo figlio
	nodoalbero<I> *next;     //riferimento al prossimo fratello 
	I item;                  //valore associato al nodo
	int level;               //altezza del nodo
};

template <class I>
class alberopn : public albero<I, nodoalbero<I> *>
{
public:
	typedef typename albero<I, nodoalbero<I> *>::item item;
	typedef nodoalbero<I> *node;
	//costruttore
	alberopn();
	//distruttore
	~alberopn();
    /* =================================== OPERATORI =========================================== */
	//metodo che inizializza l'albero n-ario
	void create();
	//metodo che restituisce true se l'albero n-ario è vuoto
	bool empty() const;
	//metodo che alloca la radice
	void insRoot();
	//metodo che inserisce un nuovo primo figlio al nodo specificato con un item
	void insFirstChild(node, item);
	//metodo che inserisce un nuovo nodo fratello al nodo specificato con un item
	void insNextSibling(node, item);
	//metodo che restituisce il riferimento alla radice
	node getRoot() const;
	//metodo che restituisce il riferimento al genitore del nodo specificato
	node parent(node) const;
	//metodo che restituisce true se un nodo è foglia
	bool leaf(node) const;
	//metodo che restituisce il riferimento al primo figlio
	node firstChild(node) const;
	//metodo che restituisce true se il nodo è ultimo fratello
	bool lastSibling(node) const;
	//metodo che restituisce il riferimento al successivo fratello
	node nextSibling(node) const;
	//metodo che inserisce un sottoalbero come primo figlio del nodo specificato
	void insFirstSubTree(node, alberopn<I> &);
	//metodo che inserisce un sottoalbero come prossimo fratello del nodo specificato
	void insSubTree(node, alberopn<I> &);
	//metodo che rimuove il sottoalbero radicato nel nodo specificato
	void removeSubTree(node);
	//metodo che modifica il valore di un nodo specificato con un item
	void write(node, item);
	//metodo che restituisce il valore letto nel nodo specificato
	item read(node) const;
	//metodo che restituisce il livello del nodo specificato
	int get_level(node) const;
	//visita in preordine dell'albero
	void preorder(node) const;
	//visita in postordine dell'albero
	void postorder(node) const;
	//visita in ampiezza dell'albero
	void bfs(node) const;
	//metodo che stampa un sottoalbero radicato nel nodo specificato
	void print(node) const;
	//metodo che stampa l'albero n-ario
	void print() const;

private:
    //riferimento alla radice dell'albero
	nodoalbero<I> *root;
};

//metodo public
template <class I>
alberopn<I>::alberopn()
{
	this->create();
}

//metodo public
template <class I>
alberopn<I>::~alberopn()
{
	if (!empty())
	{
		this->removeSubTree(root);
	
	delete root;
	root = nullptr;
    }
}

//metodo public
template <class I>
void alberopn<I>::create()
{
	root = nullptr;
}

//metodo public
template <class I>
bool alberopn<I>::empty() const
{
	return (root == nullptr);
}

//metodo public
template <class I>
void alberopn<I>::insRoot()
{
	if (this->empty())
	{
		root = new nodoalbero<I>;
	}
	else{
		throw std::runtime_error("L'albero non è vuoto");
	}
}

//metodo public
template <class I>
void alberopn<I>::insFirstChild(node nodeparent, item el)
{
	if (!this->empty())
	{
		if(nodeparent !=nullptr)
		{
		    node newchild = new nodoalbero<I>(el);
		    newchild->level = nodeparent->level + 1;
		    newchild->parent = nodeparent;
		    newchild->next = nodeparent->first;
		    nodeparent->first = newchild;
		}
		else{
		    throw std::runtime_error("Il nodo specificato non esiste");
		}
	}
	else{
		throw std::runtime_error("L'albero è vuoto");
	}
}

//metodo public
template <class I>
void alberopn<I>::insNextSibling(node nodechild, item el)
{
	if (!this->empty())
	{
	    if (nodechild != root)
	    {
		    if (nodechild != nullptr)
		    {
			    node newSibling = new nodoalbero<I>(el);
			    newSibling->level = nodechild->level;
			    newSibling->parent = nodechild->parent;
			    newSibling->next = nodechild->next;
			    nodechild->next = newSibling;
		    }
		    else{
			    throw std::runtime_error("Il nodo specificato non esiste");
		    }
	    }
	    else{
		    throw std::runtime_error("La radice non può avere fratelli successivi");
	    }
	}
	else{
		throw std::runtime_error("L'albero è vuoto");
	}
}

//metodo public
template <class I>
typename alberopn<I>::node alberopn<I>::getRoot() const
{
	if (empty())
    {
        throw std::runtime_error("L'albero è vuoto");
    }
	else
	{
	return (root);
	}
}

//metodo public
template <class I>
typename alberopn<I>::node alberopn<I>::parent(node n) const
{
	if (empty())
        throw std::runtime_error("L'albero è vuoto");
    else if (n == root)
        throw std::runtime_error("La radice non ha un genitore");
    else if (n == nullptr)
        throw std::runtime_error("Il nodo specificato non esiste");
    else
        return (n->parent);
}

//metodo public
template <class I>
bool alberopn<I>::leaf(node n) const
{
	if (n == nullptr){
		throw std::runtime_error("Il nodo specificato non esiste");
	}
	return (n->first == nullptr);
}

//metodo public
template <class I>
typename alberopn<I>::node alberopn<I>::firstChild(node n) const
{
	if (empty())
        throw std::runtime_error("L'albero è vuoto");
	else if (n == nullptr)
        throw std::runtime_error("Il nodo specificato non esiste");
	else
		return (n->first);
	
}

//metodo public
template <class I>
bool alberopn<I>::lastSibling(node n) const
{
    if (empty())
        throw std::runtime_error("L'albero è vuoto");
	else if (n == nullptr)
        throw std::runtime_error("Il nodo specificato non esiste");
	else
	    return (n->next == nullptr);
}

//metodo public
template <class I>
typename alberopn<I>::node alberopn<I>::nextSibling(node n) const
{
	if (empty())
        throw std::runtime_error("L'albero è vuoto");
	else if (n == nullptr)
        throw std::runtime_error("Il nodo specificato non esiste");
	else if (n->next == nullptr)
	    throw std::runtime_error("Il nodo specificato non ha fratelli successivi");
	else
	    return (n->next);

}

//metodo public
template <class I>
void alberopn<I>::insFirstSubTree(node nodeparent, alberopn<I> &albero)
{
	if (!this->empty() && !albero.empty())
	{
		if (nodeparent != nullptr)
		{
			node nodechild = nodeparent->first;
			nodeparent->first = albero.root;
			albero.root->parent = nodeparent;
			albero.root->next = nodechild;
			albero.root = nullptr;
		}
		else
		{
			throw std::runtime_error("Il nodo specificato non esiste");
		}
	}
	else{
		throw std::out_of_range("Uno dei due alberi è vuoto");
	}
}

//metodo public
template <class I>
void alberopn<I>::insSubTree(node nodechild, alberopn<I> &albero)
{
	if (!this->empty() && !albero.empty() && (nodechild != root))
	{
		if (nodechild != nullptr)
		{
			node nodeSibling = nodechild->next;
			nodechild->next = albero.root;
			albero.root->parent = nodechild->parent;
			albero.root->next = nodeSibling;
			albero.root = nullptr;
		}
		else
		{
			throw std::runtime_error("Il nodo specificato non esiste");
		}
	}
	else{
		throw std::out_of_range("Uno dei due alberi è vuoto");
	}
}

//metodo public
template <class I>
void alberopn<I>::removeSubTree(node n)
{
	if (!this->empty())
	{
		if (n != nullptr)
		{
			while (n->first != nullptr) {
				removeSubTree(n->first);
			}
			if (n->parent != nullptr) {
				if (n->parent->first == n) {
					n->parent->first = n->next;
				} else {
					node sibling = n->parent->first;
					while (sibling != nullptr && sibling->next != n) {
						sibling = sibling->next;
					}
					if (sibling != nullptr) {
						sibling->next = n->next;
					}
				}
			} else {
				root = nullptr;
			}
			delete n;
		}
		else
		{
			throw std::runtime_error("Il nodo specificato non esiste");
	    }
	}
	else{
		throw std::runtime_error("L'albero è vuoto");
	}
}

//metodo public
template <class I>
void alberopn<I>::write(node n, item el)
{
	if (empty())
        throw std::runtime_error("L'albero è vuoto");
	else if (n == nullptr)
        throw std::runtime_error("Il nodo specificato non esiste");
	else
		n->item = el;
	
}

//metodo public
template <class I>
typename alberopn<I>::item alberopn<I>::read(node n) const
{
	if (empty())
        throw std::runtime_error("L'albero è vuoto");
	else if (n == nullptr)
        throw std::runtime_error("Il nodo specificato non esiste");
	else
		return (n->item);
}

//metodo public
template <class I>
int alberopn<I>::get_level(node n) const
{
	if (!empty())
	{
		if (n != nullptr)
		{
			return(n->level);
		}
		else{
			throw std::runtime_error("Il nodo specificato non esiste");
		}
	}
	else
	{
		throw std::runtime_error("L'albero è vuoto"); 
	}
}

//metodo public
template <class I>
void alberopn<I>::preorder(node n) const
{
	if (n != nullptr)
	{
		node child;
		cout << "\nnodo: " << read(n) << " livello: " << n->level; 
		if (!leaf(n))
		{
			child = firstChild(n);
			while (!lastSibling(child))
			{
				preorder(child);
				child = nextSibling(child);
			}
			preorder(child);
		}
	}
}

//metodo public
template <class I>
void alberopn<I>::postorder(node n) const
{
	if (n != nullptr)
	{
		node child;
		if (!leaf(n))
		{
			child = firstChild(n);
			while (!lastSibling(child))
			{
				postorder(child);
				child = nextSibling(child);
			}
			postorder(child);
		}
		cout << "\nitem: " << read(n); 
	}
}

//metodo public
template <class I>
void alberopn<I>::bfs(node n) const
{
	if (n != nullptr)
	{
		codapn<node> coda;
		coda.enqueque(n);
		while (!coda.empty())
		{
			node i = coda.top();
			coda.dequeque();
			cout << " (" << read(i) << ") ";
			i = i->first;
			while (i != nullptr)
			{
				coda.enqueque(i);
				i = i->next;
			}
		}
	}
}

//metodo public
template <class I>
void alberopn<I>::print(node n) const
{
	node p;
	cout << read(n) << ":";
	if (!leaf(n))
	{
		p = firstChild(n);
		while (!lastSibling(p))
		{
			cout << " " << read(p);
			p = nextSibling(p);
		}
		cout << " " << read(p) << "\n";
		p = firstChild(n);
		while (!lastSibling(p))
		{
			print(p);
			p = nextSibling(p);
		}
		print(p);
	}
	else
	{
		cout << "\n";
	}
}

//metodo public
template <class I>
void alberopn<I>::print() const
{
	if (!empty())
	{
		this->print(root);
	}
	else{
		throw std::runtime_error("L'albero è vuoto");
	}
}

#endif //ALBEROPN_H