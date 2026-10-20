#ifndef GRAFOLIST_H
#define GRAFOLIST_H

#include <iostream>
#include <string>
#include <stdexcept>
#include "grafo.h"
#include "./../Liste/linkedlist.h"
#define MaxDimension 100
using namespace std;

//definisco la classe contenente l'id del grafo
class nodoGrafo
{
public:
    nodoGrafo(int i)                           //costruttore con parametro id
    {
        idnode = i;
    }
    nodoGrafo()                                //costruttore di default
    {
        idnode = 0;
    }
    int getid()                                //restituisce l'id del nodo
    {
        return (idnode);
    }
    void setid(int id)                         //imposta l'id del nodo
    {
        idnode = id;
    }
    nodoGrafo &operator=(const nodoGrafo &n)   //sovraccarico operatore di assegnamento 
    {
        idnode = n.idnode;
        return *(this);
    }
    bool operator==(const nodoGrafo &n)        //sovraccarico operatore di uguaglianza 
    {
        return (idnode == n.idnode);
    }

private:
    int idnode;     //id del nodo
}; 

//definisco la classe che contiene le info dell'arco
template <class P>
class infoArco
{
public:
    P weight;
    nodoGrafo _to;
    infoArco<P> &operator=(const infoArco<P> &infoArco)
    {
        weight = infoArco.weight;
        _to = infoArco._to;
        return *(this);
    }
};

//definisco la classe che contiene le info del nodo
template <class E, class P>
class infoNodo
{
public:
    E label;
    bool empty;
    void *info;
    linkedlist<infoArco<P>> arches;
    infoNodo()
    {
        label = "";
        info = 0;
        empty = true;
    }
};

//definisco la classe listagrafo 
template <class E, class P>
class grafolist : public grafo<E, P, nodoGrafo>
{
public:
    ////definizione dei tipi generici 
    typedef E label;            //etichetta
    typedef P weight;           //peso
    typedef nodoGrafo node;     //nodo grafo
    typedef class arco<weight, node> arch;                         //arco
    typedef class grafo<label, weight, node> graph;                //grafo con etichetta, peso e nodo
    typedef typename graph::listnode listnode;                     //listanodi
    typedef typename graph::position_listnode position_listnode;   //posizione listanodi
    //costruttore
    grafolist();
    //costruttore con parametro
    grafolist(int);
    //distruttore
    ~grafolist();
    /* =================================== OPERATORI =========================================== */
    //metodo che inizializza il grafo
    void create();
    //metodo che restituisce true se il grafo è vuoto
    bool empty() const;
    //metodo che inserisce un nodo nel grafo
    void insNode(node &);
    //metodo che inserisce un arco avente il nodo uscente, il nodo entrante e il peso specificati
    void insArch(node, node, weight);
    //metodo che rimuove un nodo dal grafo
    void eraseNode(node);
    //metodo che rimuove un arco dal grafo
    void eraseArch(node, node);
    //metodo che restituisce true se il nodo specificato appartiene al grafo
    bool isNode(node) const;
    //metodo che restituisce true se i due nodi specificati formano un arco nel grafo
    bool isArch(node, node) const;
    //metodo che restituisce la lista dei nodi adiacenti al nodo specificato
    listnode adjacent(node) const;
    //metodo che restituisce la lista dei nodi che appartengono al grafo
    listnode listNode() const;
    //metodo che legge e restituisce l'etichetta del nodo specificato
    label readLabel(node) const;
    //metodo che scrive e sovrascrive l'etichetta del nodo specificato con un altra etichetta
    void writeLabel(node, label);
    //metodo che legge e restituisce il peso di un arco del grafo formato dai due nodi specificati
    weight readWeight(node, node) const;
    //metodo che scrive e sovrascrive il peso di un arco del grafo formato dai due nodi specificati
    void writeWeight(node, node, weight);
    //metodo che restituisce il numero dei nodi nel grafo
    int numNodes() const;
    //metodo che restituisce il numero degli archi nel grafo
    int numArches() const;
    //funzioni di servizio
    //metodo che restituisce true se la matrice di adiacenza è vuota
    bool isEmptyMatrix() const;
    //algoritmi di visita
    //visita in profondità
    void dfs(node) const;
    void dfs(node, int *) const;

private:
    infoNodo<E, P> *matrix;        //matrice di info nodi
    int dimension;                 //dimensione massima della matrice
    int nodes;                     //numero nodi
    int arches;                    //numero archi 
};

//metodo public
template <class E, class P>
grafolist<E, P>::grafolist()
{
    this->create();
    dimension = MaxDimension;
    arches = 0;
    matrix = new infoNodo<E, P>[dimension];
    for (int i = 0; i < dimension; i++)
    {
        matrix[i].arches.create();
    }
}

//metodo public
template <class E, class P>
grafolist<E, P>::grafolist(int dim)
{
    this->create();
    dimension = dim;
    arches = 0;
    matrix = new infoNodo<E, P>[dimension];
    for (int i = 0; i < dimension; i++)
    {
        matrix[i].arches.create();
    }
}

//metodo public
template <class E, class P>
grafolist<E, P>::~grafolist()
{
    delete[] matrix;
    matrix = nullptr;
}

//metodo public
template <class E, class P>
void grafolist<E, P>::create()
{
    nodes = 0;
}

//metodo public
template <class E, class P>
bool grafolist<E, P>::empty() const
{
    return (nodes == 0);
}

//metodo public
template <class E, class P>
void grafolist<E, P>::insNode(node &nodegraph)
{
    if (isNode(nodegraph)) 
    {
        throw std::runtime_error("Il nodo specificato appartiene già al grafo");
    }
    int n = 0;
    if (nodes < dimension)
    {
        while (!matrix[n].empty)
        {
            n++;
        }
        nodes++;
        matrix[n].empty = false;
    }
    else
    {
        throw std::runtime_error("Il grafo ha raggiunto la capacità massima");
    }
    nodegraph.setid(n);
}

//metodo public
template <class E, class P>
void grafolist<E, P>::insArch(node n1, node n2, weight w)
{
    if(isNode(n1) && isNode(n2))
    {
        infoArco<P> infoarco;
        infoarco.weight = w;
        infoarco._to = n2;
        matrix[n1.getid()].arches.push_back(infoarco);
        arches++;
    }
    else{
        throw std::runtime_error("I nodi specificati non appartengono al grafo");
    }
}

//metodo public
template <class E, class P>
void grafolist<E, P>::eraseNode(node n)
{
    if (!isNode(n))
    {
        throw std::runtime_error("Il nodo specificato non appartiene al grafo");
        return;
    }
    bool canc = true;
    for (int i = 0; (i < dimension) && (canc); i++)
    {
        if (!matrix[n.getid()].arches.empty())
        {
            canc = false;
        }
    }
    for (int i = 0; (i < dimension) && (canc); i++)
    {
        if (!matrix[i].empty)
        {
            for (auto p = matrix[i].arches.begin(); !matrix[i].arches.end(p); p = matrix[i].arches.next(p))
            {
                if (matrix[i].arches.read(p)._to.getid() == n.getid())
                {
                    canc = false;
                }
            }
        }
    }
    if (canc)
    {
        while (!matrix[n.getid()].arches.empty())
        {
            matrix[n.getid()].arches.pop_front();
        }
        matrix[n.getid()].empty = true;
        nodes--;
    }
    else{
        throw std::runtime_error("Impossibile eliminare il nodo perché ha archi uscenti o entranti");
    }
}

//metodo public
template <class E, class P>
void grafolist<E, P>::eraseArch(node n1, node n2)
{
    if(isNode(n1) && isNode(n2))
    {
        if(isArch(n1,n2))
        {
            typename linkedlist<infoArco<P>>::position p;
            p = matrix[n1.getid()].arches.begin();
            bool found = false;
            while (!matrix[n1.getid()].arches.end(p) && !(found))
            {
                if (matrix[n1.getid()].arches.read(p)._to.getid() == n2.getid())
                {
                    found = true;
                }
                else
                {
                    p = matrix[n1.getid()].arches.next(p);
                }
            }
            if (found)
            {
                matrix[n1.getid()].arches.erase(p);
                arches--;
            }
        }
        else{
            throw std::runtime_error("Nessun arco è presente fra i due nodi specificati");
        }
    }
    else{
        throw std::runtime_error("I nodi specificati non appartengono al grafo");
    }
}

//metodo public
template <class E, class P>
bool grafolist<E, P>::isNode(node n) const
{
    return (!matrix[n.getid()].empty);
}

//metodo public
template <class E, class P>
bool grafolist<E, P>::isArch(node n1, node n2) const
{
    bool found = false;
    if(isNode(n1) && isNode(n2))
    {
        if (!matrix[n1.getid()].arches.empty())
        {
            typename linkedlist<infoArco<P>>::position p = matrix[n1.getid()].arches.begin();
            while (!matrix[n1.getid()].arches.end(p) && !(found))
            {
                if (matrix[n1.getid()].arches.read(p)._to.getid() == n2.getid())
                {
                    found = true;
                }
                p = matrix[n1.getid()].arches.next(p);
            }
        }
    }
    else{
        throw std::runtime_error("I nodi specificati non appartengono al grafo");
    }
    return (found);
}

//metodo public
template <class E, class P>
typename grafolist<E, P>::listnode grafolist<E, P>::adjacent(node n) const
{
    listnode list;
    if (isNode(n))
    {
        if (!matrix[n.getid()].arches.empty())
        {
            for (auto i = matrix[n.getid()].arches.begin(); !matrix[n.getid()].arches.end(i); i = matrix[n.getid()].arches.next(i))
            {
                node copy(matrix[n.getid()].arches.read(i)._to.getid());
                list.push_back(copy);
            }
        }
    }
    else{
        throw std::runtime_error("Il nodo specificato non appartiene al grafo");
    }
    return (list);
}

//metodo public
template <class E, class P>
typename grafolist<E, P>::listnode grafolist<E, P>::listNode() const
{
    listnode list;
    for (int i = 0; i < dimension; i++)
    {
        if (!matrix[i].empty)
        {
            node copy(i);
            list.push_back(copy);
        }
    }
    return (list);
}

//metodo public
template <class E, class P>
E grafolist<E, P>::readLabel(node n) const
{
    return (matrix[n.getid()].label);
}

//metodo public
template <class E, class P>
void grafolist<E, P>::writeLabel(node n, E label)
{
    if(isNode(n))
    {
        matrix[n.getid()].label = label;
    }
    else{
        throw std::runtime_error("Il nodo specificato non appartiene al grafo");
    }
}

//metodo public
template <class E, class P>
typename grafolist<E, P>::weight grafolist<E, P>::readWeight(node n1, node n2) const
{
    P weight = -1;
    if (isArch(n1, n2))
    {
        bool found = false;
        auto p = matrix[n1.getid()].arches.begin();
        while (!matrix[n1.getid()].arches.end(p) && !found)
        {
            if (matrix[n1.getid()].arches.read(p)._to.getid() == n2.getid())
            {
                found = true;
            }
            else
            {
                p = matrix[n1.getid()].arches.next(p);
            }
        }
        if (found)
        {
            return (matrix[n1.getid()].arches.read(p).weight);
        }
    }
    else{
            throw std::runtime_error("Nessun arco è presente fra i due nodi specificati");
        }
    return (weight);
}

//metodo public
template <class E, class P>
void grafolist<E, P>::writeWeight(node n1, node n2, P weight)
{
    if (isArch(n1, n2))
    {
        bool found = false;
        auto p = matrix[n1.getid()].arches.begin();
        while (!matrix[n1.getid()].arches.end(p) && !found)
        {
            if (matrix[n1.getid()].arches.read(p)._to.getid() == n2.getid())
            {
                found = true;
            }
            else
            {
                p = matrix[n1.getid()].arches.next(p);
            }
        }
        if (found)
        {
            infoArco<P> infoarco;
            infoarco.weight = weight;
            infoarco._to = n2;
            matrix[n1.getid()].arches.write(infoarco, p);
        }
    }
    else{
        throw std::runtime_error("Nessun arco è presente fra i due nodi specificati");
    }
}

//metodo public
template <class E, class P>
int grafolist<E, P>::numNodes() const
{
    return (nodes);
}

//metodo public
template <class E, class P>
int grafolist<E, P>::numArches() const
{
    return (arches);
}

//metodo public
template <class E, class P>
bool grafolist<E, P>::isEmptyMatrix() const
{
    return (matrix == nullptr);
}

//metodo public
template <class E, class P>
void grafolist<E, P>::dfs(node n) const
{
    if (isNode(n))
    {
        int visitato[dimension];
        for (int i = 0; i < dimension; i++)
        {
            if (!matrix[i].empty)
            {
                visitato[i] = 0;    //nodo occupato
            }
            else
            {
                visitato[i] = -1;   //nodo vuoto
            }
        }
        dfs(n, visitato);
    }
    else{
        throw std::runtime_error("Il nodo specificato non appartiene al grafo");
    }
}

//metodo public
template <class E, class P>
void grafolist<E, P>::dfs(node n, int *visitato) const
{
    cout << " Nodo(" << readLabel(n) << ") --> ";
    visitato[n.getid()] = 1;
    listnode l = this->adjacent(n);
    if (!l.empty())
    {
        for (auto p = l.begin(); !l.end(p); p = l.next(p))
        {
            node i(l.read(p).getid());
            if (visitato[i.getid()] == 0)
            {
                dfs(i, visitato);
            }
        }
    }
    else{
        throw std::runtime_error("Il grafo è vuoto");
    }
}

#endif //GRAFOLIST_H