#ifndef ALBEROBINVT_H
#define ALBEROBINVT_H

#include <iostream>
#include <string>
#include "alberobin.h"
using namespace std;

template <class I>
class alberobinvt : public alberobin<I, int>
{
    static const int NIL = -1;

public:
    typedef typename alberobin<I, int>::item item;
    typedef typename alberobin<I, int>::node node;
    struct cell
    {
        node parent;
        node left;
        node right;
        item value;
        int depth = 0;
    };
    typedef struct cell cell;
    //costruttore 
    alberobinvt();
    //costruttore con parametro
    alberobinvt(int);
    //distruttore
    ~alberobinvt();
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
    //metodo che restituisce vero se il figlio destro è vuoto
    bool dx_empty(node) const;
    //metodo che restituisce true se il nodo è foglia
    bool leaf(node) const;
    //metodo che restituisce il valore letto nel nodo specificato
    item read(node) const;
    //metodo che modifica il valore di un nodo specificato
    void write(node, item);
    //metodo che che alloca la radice
    void ins_root();
    //metodo che inserisce un nodo come figlio sinistro del nodo specificato
    void ins_sx(node);
    //metodo che inserisce un nodo come figlio sinistro del nodo specificato con un item
    void ins_sx(node, item);
    //metodo che inserisce un nodo come figlio destro del nodo specificato
    void ins_dx(node);
    //metodo che inserisce un nodo come figlio destro del nodo specificato con un item
    void ins_dx(node, item);
    //metodo che rimuove un sottoalbero
    void erase(node);
    //visita in preordine dell'albero
    void preorder(node) const;
    //visita in ordine dell'albero
    void inorder(node) const;
    //visita in postordine dell'albero
    void postorder(node) const;
    //metodo che restituisce true se un nodo ha valore nullo
    bool is_empty_node(node) const;
    //metodo che restituisce la profondità del sottoalbero radicato nel nodo specificato 
    int depth(node) const;
    //metodo che restituisce la profondità dell'albero binario
    int depth() const;

private:
    int MAXLUNG;     //massima capienza
    cell *spazio;    //vettore di nodi
    int nNodi;       //numero totale nodi 
    node inizio;     //posizione della radice
    node libera;     //nodo libero
};

//metodo public
template <class I>
alberobinvt<I>::alberobinvt()
{
    MAXLUNG = 100;
    spazio = new cell[MAXLUNG];
    this->create();
}

//metodo public
template <class I>
alberobinvt<I>::alberobinvt(int N) : MAXLUNG(N)
{
    spazio = new cell[MAXLUNG];
    this->create();
}

//metodo public
template <class I>
alberobinvt<I>::~alberobinvt()
{
    erase(inizio);
    delete[] spazio;
    spazio = nullptr;
}

//metodo public
template <class I>
void alberobinvt<I>::create()
{
    inizio = NIL;
    for (int i = 0; i < MAXLUNG; i++)
    {
        spazio[i].left = (i + 1) % MAXLUNG;
    }
    libera = 0;
    nNodi = 0;
}

//metodo public
template <class I>
bool alberobinvt<I>::empty() const
{
    return (nNodi == 0);
}

//metodo public
template <class I>
typename alberobinvt<I>::node alberobinvt<I>::get_root() const
{
    return (inizio);
}

//metodo public
template <class I>
typename alberobinvt<I>::node alberobinvt<I>::parent(node n) const
{
    if (n != inizio)
    {
        return (spazio[n].parent);
    }
    else
    {
        return (n);
    }
}

//metodo public
template <class I>
typename alberobinvt<I>::node alberobinvt<I>::sx(node n) const
{
    return (spazio[n].left);
}

//metodo public
template <class I>
typename alberobinvt<I>::node alberobinvt<I>::dx(node n) const
{
    return (spazio[n].right);
}

//metodo public
template <class I>
bool alberobinvt<I>::sx_empty(node n) const
{
    return (spazio[n].left == NIL);
}

//metodo public
template <class I>
bool alberobinvt<I>::dx_empty(node n) const
{
    return (spazio[n].right == NIL);
}

//metodo public
template <class I>
bool alberobinvt<I>::leaf(node n) const
{
    return (sx_empty(n) && dx_empty(n));
}

//metodo public
template <class I>
typename alberobinvt<I>::item alberobinvt<I>::read(node n) const
{
    item value;
    if (n != NIL)
    {
        return (spazio[n].value);
    }
    return (value);
}

//metodo public
template <class I>
void alberobinvt<I>::write(node n, item v)
{
    if (n != NIL)
    {
        spazio[n].value = v;
    }
    else
    {
        cout << "Il nodo è nullo" << endl;
    }
}

//metodo public
template <class I>
void alberobinvt<I>::ins_root()
{
    if (inizio == NIL)
    {
        inizio = libera;
        libera = spazio[libera].left;
        spazio[inizio].left = NIL;
        spazio[inizio].right = NIL;
        nNodi++;
    }
}

//metodo public
template <class I>
void alberobinvt<I>::ins_sx(node n)
{
    if (inizio == NIL)
    {
        cout << "L'albero è vuoto" << endl;
        return;
    }
    if (n == NIL)
    {
        cout << "Il nodo è vuoto" << endl;
        return;
    }
    if (spazio[n].left != NIL)
    {
        cout << "Sinistro occupato" << endl;
        return;
    }
    if (nNodi >= MAXLUNG)
    {
        cout << "L'albero è pieno" << endl;
        return;
    }
    node q = libera;
    libera = spazio[libera].left;
    spazio[n].left = q;
    spazio[q].left = NIL;
    spazio[q].parent = n;
    spazio[q].right = NIL;
    nNodi++;
}

//metodo public
template <class I>
void alberobinvt<I>::ins_sx(node n, item v)
{
    if (inizio == NIL)
    {
        cout << "L'albero è vuoto" << endl;
        return;
    }
    if (n == NIL)
    {
        cout << "Il nodo è vuoto" << endl;
        return;
    }
    if (spazio[n].left != NIL)
    {
        cout << "Sinistro occupato" << endl;
        return;
    }
    if (nNodi >= MAXLUNG)
    {
        cout << "L'albero è pieno" << endl;
        return;
    }
    node q = libera;
    libera = spazio[libera].left;
    spazio[n].left = q;
    spazio[q].left = NIL;
    spazio[q].parent = n;
    spazio[q].right = NIL;
    spazio[q].value = v;
    nNodi++;
}

//metodo public
template <class I>
void alberobinvt<I>::ins_dx(node n)
{
    if (inizio == NIL)
    {
        cout << "L'albero è vuoto" << endl;
        return;
    }
    if (n == NIL)
    {
        cout << "Il nodo è vuoto" << endl;
        return;
    }
    if (spazio[n].right != NIL)
    {
        cout << "Destro occupato" << endl;
        return;
    }
    if (nNodi >= MAXLUNG)
    {
        cout << "L'albero è pieno" << endl;
        return;
    }
    node q = libera;
    libera = spazio[libera].left;
    spazio[n].right = q;
    spazio[q].left = NIL;
    spazio[q].parent = n;
    spazio[q].right = NIL;
    nNodi++;
}

//metodo public
template <class I>
void alberobinvt<I>::ins_dx(node n, item v)
{
    if (inizio == NIL)
    {
        cout << "L'albero è vuoto" << endl;
        return;
    }
    if (n == NIL)
    {
        cout << "Il nodo è vuoto" << endl;
        return;
    }
    if (spazio[n].right != NIL)
    {
        cout << "Destro occupato" << endl;
        return;
    }
    if (nNodi >= MAXLUNG)
    {
        cout << "L'albero è pieno" << endl;
        return;
    }
    node q = libera;
    libera = spazio[libera].left;
    spazio[n].right = q;
    spazio[q].left = NIL;
    spazio[q].parent = n;
    spazio[q].right = NIL;
    spazio[q].value = v;
    nNodi++;
}

//metodo public
template <class I>
void alberobinvt<I>::erase(node n)
{
    if (n != NIL)
    {
        if (!sx_empty(n))
        {
            erase(spazio[n].left);
        }
        if (!dx_empty(n))
        {
            erase(spazio[n].right);
        }
        if (n != inizio)
        {
            node p = parent(n);
            if (spazio[p].left == n)
            {
                spazio[p].left = NIL;
            }
            else
            {
                spazio[p].right = NIL;
            }
        }
        else
        {
            inizio = NIL;
        }
        nNodi--;
        spazio[n].left = libera;
        libera = n;
    }
}

//metodo public
template <class I>
void alberobinvt<I>::preorder(node n) const
{
    if (n == NIL)
    {
        return;
    }
    cout << " " << read(n) << " ";
    preorder(spazio[n].left);
    preorder(spazio[n].right);
}

//metodo public
template <class I>
void alberobinvt<I>::inorder(node n) const
{
    if (n == NIL)
    {
        return;
    }
    inorder(spazio[n].left);
    cout << " " << read(n) << " ";
    inorder(spazio[n].right);
}

//metodo public
template <class I>
void alberobinvt<I>::postorder(node n) const
{
    if (n == NIL)
    {
        return;
    }
    postorder(spazio[n].left);
    postorder(spazio[n].right);
    cout << " " << read(n) << " ";
}

//metodo public
template <class I>
bool alberobinvt<I>::is_empty_node(node n) const
{
    return (n == NIL);
}

//metodo public
template <class I>
int alberobinvt<I>::depth(node sub_root) const
{
    if (sub_root == NIL)
    {
        return (-1); 
    }
    int left_depth = depth(spazio[sub_root].left);
    int right_depth = depth(spazio[sub_root].right);
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
int alberobinvt<I>::depth() const
{
    int d = 0;
    if (!empty())
    {
        d = depth(get_root());
    }
    else
    {
        d = -1;
    }
    return (d);
}

#endif //ALBEROBINVT_H