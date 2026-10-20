#ifndef ALBEROBINPN_H
#define ALBEROBINPN_H

#include <iostream>
#include <string>
#include <stdexcept>
#include "alberobin.h"
using namespace std;

//dichiaro la classe albero binario
template <class I>
class alberobinpn;

//creo la classe nodo dell'albero binario
template <class I>
class nodoalberobin
{
	friend class alberobinpn<I>;

public:
	nodoalberobin()
	{
		parent = nullptr;
		sx = nullptr;
		dx = nullptr;
		level = 0;
		depth = 0;
	}
	nodoalberobin(I el)
	{
		parent = nullptr;
		sx = nullptr;
		dx = nullptr;
		item = el;
		level = 0;
		depth = 0;
	}

private:
	nodoalberobin<I> *parent;   //riferimento al nodo genitore
	nodoalberobin<I> *sx;		//riferimento al nodo sinistro
	nodoalberobin<I> *dx;		//riferimento al nodo destro
	I item;				     	//valore associato al nodo
	int level;				    //altezza del nodo
	int depth;			     	//profondità del nodo
};

template <class I>
class alberobinpn : public alberobin<I, nodoalberobin<I> *>
{
public:
	typedef typename alberobin<I, nodoalberobin<I> *>::item item;
	typedef nodoalberobin<I> *node;
	//costruttore
	alberobinpn();
	//costruttore di copia
	alberobinpn(const alberobinpn<I> &);
    //distruttore
	~alberobinpn();
    /* =================================== OPERATORI =========================================== */
	//metodo che inizializza l'albero binario
	void create();
	//metodo che restituisce true se l'albero binario è vuoto
	bool empty() const;
	//metodo che restituisce il riferimento alla radice
	node get_root() const;
	//metodo che restituisce il riferimento al genitore
	node parent(node) const;
	//metodo che restituisce il riferimento al figlio sinistro 
	node sx(node) const;
	//metodo che restituisce il riferimento al figlio destro
	node dx(node) const;
	//metodo che restituisce true se il figlio sinistro è vuoto
	bool sx_empty(node) const;
	//metodo che restituisce true se il figlio destro è vuoto
	bool dx_empty(node) const;
	//metodo che restituisce true se il nodo è foglia
	bool leaf(node) const;
	//metodo che restituisce il valore letto nel nodo specificato
	item read(node) const;
	//metodo che modifica il valore di un nodo specificato
	void write(node, item);
	//metodo che alloca la radice
	void ins_root();
	//metodo che inserisce un nodo come figlio sinistro del nodo specificato
	void ins_sx(node, item);
	//metodo che inserisce un sottoalbero come figlio sinistro del nodo specificato
	void ins_sub_sx(node, alberobinpn<I> &);
	//metodo che inserisce un nodo come figlio destro del nodo specificato
	void ins_dx(node, item);
	//metodo che inserisce un sottoalbero come figlio destro del nodo specificato
	void ins_sub_dx(node, alberobinpn<I> &);
	//metodo che rimuove un sottoalbero
	void erase(node);
	//visita in preordine dell'albero
	void preorder(node) const;
	//visita in ordine dell'albero
	void inorder(node) const;
	//visita in postordine dell'albero
	void postorder(node) const;
	//metodo che cancella da un albero di interi tutte le foglie con valore pari
	void canc_foglie_pari();
	//metodo che cancella da un sottoalbero di interi tutte le foglie con valore pari
	void canc_foglie_pari(nodoalberobin<int> *);
	//metodo che restituisce true se un nodo ha valore nullo
	bool is_empty_node(node) const;
	//metodo che restituisce la profondità del sottoalbero radicato nel nodo specificato 
	int depth(node) const;
	//metodo che restituisce la profondità dell'albero binario
	int depth() const;
	//metodo che permette di costruire un albero binario avente come figlio sinistro l'oggetto corrente e figlio destro tree
	void costr_alberobin(alberobinpn<I> &);
	//metodo che permette di incrementare il livello di tutti i nodi
	void increase_level(node);
	//metodo che restituisce il livello del nodo specificato
	int get_level(node) const;
	//metodo che scrive il valore del nodo 
	void write_level(node, int);
	//metodo che restituisce un sottoalbero a partire dal nodo specificato
	node get_sub_alberobin(node);
	//scambia i sottoalberi che hanno come radice due nodi appartenenti a due alberi distinti
	void mutation(node, node, alberobinpn<I> &);
	//sovraccarico operatore di assegnamento
	alberobinpn<I> &operator=(const alberobinpn<I> &);

private:
	//riferimento alla radice dell'albero
	nodoalberobin<I> *root;
};

//metodo public
template <class I>
alberobinpn<I>::alberobinpn()
{
	this->create();
}

//metodo public
template <class I>
alberobinpn<I>::alberobinpn(const alberobinpn<I> &alberobin)
{
	this->create();
	root = get_sub_alberobin(alberobin.root);
}

//metodo public
template <class I>
alberobinpn<I>::~alberobinpn()
{
	if (!empty())
	{
		this->erase(root);
	}
	root = nullptr;
}

//metodo public
template <class I>
void alberobinpn<I>::create()
{
	root = nullptr;
}

//metodo public
template <class I>
bool alberobinpn<I>::empty() const
{
	return (root == nullptr);
}

//metodo public
template <class I>
typename alberobinpn<I>::node alberobinpn<I>::get_root() const
{
	if (empty())
    {
        throw std::runtime_error("L'albero è vuoto");
    }
	else{
	    return (root);
	}
}

//metodo public
template <class I>
typename alberobinpn<I>::node alberobinpn<I>::parent(node n) const
{
	if (empty())
        throw std::runtime_error("L'albero è vuoto");
    else if (n == root)
        throw std::runtime_error("Il nodo radice non ha un genitore");
    else if (n == nullptr)
        throw std::runtime_error("Il nodo specificato non esiste");
    else
        return n->parent;
}

//metodo public
template <class I>
typename alberobinpn<I>::node alberobinpn<I>::sx(node n) const
{
	if (!sx_empty(n)){
        return n->sx;
	}
    else{
        throw std::runtime_error("Il nodo non ha un figlio sinistro");
	}
}

//metodo public
template <class I>
typename alberobinpn<I>::node alberobinpn<I>::dx(node n) const
{
	if (!dx_empty(n)){
        return n->dx;
	}
    else{
        throw std::runtime_error("Il nodo non ha un figlio destro");
	}
}

//metodo public
template <class I>
bool alberobinpn<I>::sx_empty(node n) const
{
	if (empty())
        throw std::runtime_error("L'albero è vuoto");
    else if (n == nullptr)
        throw std::runtime_error("Il nodo specificato non esiste");
    else
        return (n->sx == nullptr);
}

//metodo public
template <class I>
bool alberobinpn<I>::dx_empty(node n) const
{
	if (empty())
        throw std::runtime_error("L'albero è vuoto");
    else if (n == nullptr)
        throw std::runtime_error("Il nodo specificato non esiste");
    else
        return (n->dx == nullptr);
}

//metodo public
template <class I>
bool alberobinpn<I>::leaf(node n) const
{
	if (n == nullptr){
		throw std::runtime_error("Il nodo specificato non esiste");
	}
	return ((n->sx == nullptr) && (n->dx == nullptr));
}

//metodo public
template <class I>
typename alberobinpn<I>::item alberobinpn<I>::read(node n) const
{
	if (n != nullptr)
	{
		return (n->item);
	}
	else{
		throw std::runtime_error("Il nodo specificato non esiste");
	}               
}

//metodo public
template <class I>
void alberobinpn<I>::write(node n, item el)
{
	if (!this->empty())
	{
		if (n != nullptr)
		{
			n->item = el;
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
void alberobinpn<I>::ins_root()
{
	if (this->empty())
	{
		root = new nodoalberobin<I>;
	}
	else{
		throw std::runtime_error("L'albero non è vuoto");
	}
}

//metodo public
template <class I>
void alberobinpn<I>::ins_sx(node parent, item el)
{
	if (empty())
        throw std::runtime_error("L'albero è vuoto");
    else if (parent == nullptr)
        throw std::runtime_error("Il nodo specificato non esiste");
    else if (!sx_empty(parent))
        throw std::runtime_error("Il nodo ha già un figlio sinistro");
    else {
		node child = new nodoalberobin<I>(el);
		child->level = parent->level + 1;
		child->parent = parent;
		parent->sx = child;
	}
}

//metodo public
template <class I>
void alberobinpn<I>::ins_sub_sx(node parent, alberobinpn<I> &tree)
{
	if (empty())
        throw std::runtime_error("L'albero è vuoto");
    else if (parent == nullptr)
        throw std::runtime_error("Il nodo specificato non esiste");
    else if (!sx_empty(parent))
        throw std::runtime_error("Il nodo ha già un figlio sinistro");
    else {
		increase_level(tree.root);
		parent->sx = tree.root;
		tree.root->parent = parent;
		tree.root = nullptr;
		}
}

//metodo public
template <class I>
void alberobinpn<I>::ins_dx(node parent, item el)
{
	if (empty())
        throw std::runtime_error("L'albero è vuoto");
    else if (parent == nullptr)
        throw std::runtime_error("Il nodo specificato non esiste");
    else if (!dx_empty(parent))
        throw std::runtime_error("Il nodo ha già un figlio destro");
    else {
	    node child = new nodoalberobin<I>(el);
		child->level = parent->level + 1;
		child->parent = parent;
		parent->dx = child;
	}
}

//metodo public
template <class I>
void alberobinpn<I>::ins_sub_dx(node parent, alberobinpn<I> &tree)
{
	if (empty())
        throw std::runtime_error("L'albero è vuoto");
    else if (parent == nullptr)
        throw std::runtime_error("Il nodo specificato non esiste");
    else if (!dx_empty(parent))
        throw std::runtime_error("Il nodo ha già un figlio destro");
    else {
		increase_level(tree.root);
		parent->dx = tree.root;
		tree.root->parent = parent;
		tree.root = nullptr;
	}
}
	

//metodo public
template <class I>
void alberobinpn<I>::erase(node n)
{
	if (empty())
        throw std::runtime_error("L'albero è vuoto");
    else if (n == nullptr)
        throw std::runtime_error("Il nodo specificato non esiste");
    else {
		if (!sx_empty(n))
		{
			erase(n->sx);
		}
		if (!dx_empty(n))
		{
			erase(n->dx);
		}
		if (leaf(n))
		{
			if (n != root)
			{
				node p = n->parent;
				if (p != nullptr)
				{
					if (n == p->sx)
					{
						p->sx = nullptr;
					}
					else
					{
						p->dx = nullptr;
					}
				}
			}
			else
			{
				root = nullptr;
			}
			delete n;
			n = nullptr;
		}
	}
}

//metodo public
template <class I>
void alberobinpn<I>::preorder(node n) const
{
	if (n != nullptr)
	{
		cout << "\nnodo: " << read(n) << " livello: " << n->level ; 
		preorder(n->sx);
		preorder(n->dx);
	}
}

//metodo public
template <class I>
void alberobinpn<I>::inorder(node n) const
{
	if (n != nullptr)
	{
		inorder(n->sx);
		cout << " " << read(n) << " "; 
		inorder(n->dx);
	}
}

//metodo public
template <class I>
void alberobinpn<I>::postorder(node n) const
{
	if (n != nullptr)
	{
		postorder(n->sx);
		postorder(n->dx);
		cout << " " << read(n) << " ";
	}
}

//metodo public
template <>
void alberobinpn<int>::canc_foglie_pari(nodoalberobin<int> *subroot)
{
	if (subroot == nullptr)
	{
		return;
	}
	if (!leaf(subroot))
	{
		canc_foglie_pari(subroot->sx);
		canc_foglie_pari(subroot->dx);
	}
	if (leaf(subroot) && (subroot->item % 2 == 0))
	{
		erase(subroot);
	}
}

//metodo public
template <>
void alberobinpn<int>::canc_foglie_pari()
{
	this->canc_foglie_pari(this->get_root());
}

//metodo public
template <class I>
bool alberobinpn<I>::is_empty_node(node n) const
{
	return (n == nullptr);
}

//metodo public
template <class I>
int alberobinpn<I>::depth(node sub_root) const
{
	if (sub_root == nullptr)
	{
		return (-1); 
	}
	int left_depth = depth(sub_root->sx);
	int right_depth = depth(sub_root->dx);
	if (left_depth > right_depth)
	{
		return (left_depth + 1);
	}
	else
	{
		return (right_depth + 1);
	}
}

//metodo public
template <class I>
int alberobinpn<I>::depth() const
{
	return depth(this->get_root());
}

//metodo public
template <class I>
void alberobinpn<I>::increase_level(node n)
{
	if (n == nullptr)
	{
		return;
	}
	increase_level(n->sx);
	increase_level(n->dx);
	n->level++;
}

//metodo public
template <class I>
void alberobinpn<I>::costr_alberobin(alberobinpn<I> &tree)
{
	node newroot = new nodoalberobin<I>(item(NULL));
	ins_sub_sx(newroot, *this);
	ins_sub_dx(newroot, tree);
	root = newroot;
}

//metodo public
template <class I>
int alberobinpn<I>::get_level(node n) const
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
void alberobinpn<I>::write_level(node n, int l)
{
	if (!empty())
	{
		if (n != nullptr)
		{
			n->level = l;
		}
	}
}

//metodo public
template <class I>
typename alberobinpn<I>::node alberobinpn<I>::get_sub_alberobin(node i)
{
	if (i != nullptr)
	{
		node temp = new nodoalberobin<I>;
		temp->item = i->item;
		temp->level = i->level;
		temp->parent = nullptr;
		temp->sx = get_sub_alberobin(i->sx);
		temp->dx = get_sub_alberobin(i->dx);
		if (temp->sx != nullptr)
		{
			temp->sx->parent = temp;
		}
		if (temp->dx != nullptr)
		{
			temp->dx->parent = temp;
		}
		return (temp);
	}
	else
	{
		return (nullptr);
	}
}

//metodo public
template <class I>
void alberobinpn<I>::mutation(node u, node v, alberobinpn<I> &alberobin)
{
	if ((u != root) && (v != root))
	{
		if (u == u->parent->sx)
		{
			u->parent->sx = v;
		}
		else
		{
			u->parent->dx = v;
		}
		if (v == v->parent->sx)
		{
			v->parent->sx = u;
		}
		else
		{
			v->parent->dx = u;
		}
		node parent = u->parent;
		u->parent = v->parent;
		v->parent = u->parent;
	}
}

//metodo public
template <class I>
alberobinpn<I> &alberobinpn<I>::operator=(const alberobinpn<I> &alberobin)
{
	if (!empty())
	{
		this->erase(root);
	}
	root = nullptr;
	root = this->get_sub_alberobin(alberobin.root);
	return *(this);
}

#endif //ALBEROBINPN_H