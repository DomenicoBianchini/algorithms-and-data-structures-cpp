#ifndef ALBEROBIN_H
#define ALBEROBIN_H

#include <iostream>
#include <string>
using namespace std;

//classe astratta albero binario
template <class I, class N>
class alberobin
{
public:
	//definizione dei tipi generici item e node
	typedef I item;
	typedef N node;
	//operatori
	virtual void create() = 0;
	virtual bool empty() const = 0;                   //restituisce true se l'albero binario è vuoto
	virtual node get_root() const = 0;                //restituisce il riferimento alla radice
	virtual node parent(node) const = 0;              //restituisce il riferimento al genitore
	virtual node sx(node) const = 0;                  //restituisce il riferimento al figlio sinistro  
	virtual node dx(node) const = 0;                  //restituisce il riferimento al figlio destro
	virtual bool sx_empty(node) const = 0;            //restituisce true se il figlio sinistro è vuoto
	virtual bool dx_empty(node) const = 0;            //restituisce true se il figlio destro è vuoto
    virtual bool leaf(node) const = 0;                //restituisce true se il nodo è foglia
	virtual item read(node) const = 0;                //restituisce il valore letto nel nodo specificato
	virtual void write(node, item) = 0;               //modifica il valore di un nodo specificato
	virtual void ins_root() = 0;                      //alloca la radice
	virtual void ins_sx(node, item) = 0;              //inserisce un nodo come figlio sinistro del nodo specificato
	virtual void ins_dx(node, item) = 0;              //inserisce un nodo come figlio destro del nodo specificato
    virtual void erase(node) = 0;                     //rimuove un sottoalbero             
	virtual void preorder(node) const = 0;            //visita in preordine dell'albero
	virtual void inorder(node) const = 0;             //visita in ordine dell'albero
	virtual void postorder(node) const = 0;           //visita in postordine dell'albero
	virtual bool is_empty_node(node) const = 0;       //restituisce true se il nodo ha valore nullo
	virtual int depth() const = 0;                    //restituisce la profondità dell'albero binario
	void print() const;                               //stampa l'albero binario
	virtual ~alberobin(){};                           //distruttore

private:
	void printSubTree(const node) const;              //stampa il sottoalbero a partire dal nodo specificato
};

//metodo public
template <class I, class N>
void alberobin<I, N>::print() const
{
	if (!empty())
	{
		printSubTree(get_root());
	}
	else
	{
		cout << "[]" << endl;
	}
	cout << endl;
}

//metodo private
template <class I, class N>
void alberobin<I, N>::printSubTree(const node n) const
{
	cout << "[" << read(n) << ", ";
	if (!sx_empty(n))
	{
		printSubTree(sx(n));
	}
	else
	{
		cout << "NIL";
	}
	cout << ", ";
	if (!dx_empty(n))
	{
		printSubTree(dx(n));
	}
	else
	{
		cout << "NIL";
	}
	cout << " ]";
}

//metodo public
template <class I, class N>
ostream &operator<<(ostream &os, const alberobin<I, N> &t)
{
	t.print();
	return (os);
}

#endif //ALBEROBIN_H