#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <string>
#include "./../Liste/listvector.h"
using namespace std;

//classe arco
template <class P, class N>
class arco
{
public:
    N node1;       //nodo uscente 
    N node2;       //nodo entrante
    P weight;      //peso
};

//classe astratta grafo
template <class E, class P, class N>
class grafo
{
public:
    //definizione dei tipi generici 
    typedef E label;     //etichetta
    typedef P weight;    //peso
    typedef N node;      //nodo
    //definisco le classi come nuovi tipi
    typedef class arco<weight, node> arch;                      //tipo nodoarco
    typedef listvector<node> listnode;                          //tipo listanodi di grafo
    typedef typename listnode::position position_listnode;      //tipo posizione di listanodi di grafo
    typedef listvector<arch> listarch;                          //tipo listanodi di arco
    //operatori
    virtual void create() = 0;                                  
    virtual bool empty() const = 0;                             //restituisce true se il grafo è vuoto 
    virtual void insNode(node &) = 0;                           //inserisce un nodo nel grafo
    virtual void insArch(node, node, weight) = 0;               //inserisce un arco avente i nodi e il peso specificati 
    virtual void eraseNode(node) = 0;                           //elimina un nodo
    virtual void eraseArch(node, node) = 0;                     //elimina un arco
    virtual bool isNode(node) const = 0;                        //restituisce true se il nodo appartiene al grafo
    virtual bool isArch(node, node) const = 0;                  //restituisce true se i due nodi specificati formano un arco nel grafo
    virtual listnode adjacent(node) const = 0;                  //restituisce la lista dei nodi adiacenti al nodo specificato
    virtual listnode listNode() const = 0;                      //restituisce la lista dei nodi che appartengono al grafo
    virtual label readLabel(node) const = 0;                    //legge e restituisce l'etichetta del nodo specificato
    virtual void writeLabel(node, label) = 0;                   //scrive e sovrascrive l'etichetta del nodo specificato
    virtual weight readWeight(node, node) const = 0;            //legge e restituisce il peso di un arco del grafo
    virtual void writeWeight(node, node, weight) = 0;           //scrive e sovrascrive il peso di un arco del grafo
    virtual int numNodes() const = 0;                           //restituisce il numero dei nodi nel grafo
    virtual int numArches() const = 0;                          //restituisce il numero degli archi nel grafo
    virtual void dfs(node) const = 0;                           //visita in profondità
    virtual ~grafo(){};                                         //distruttore
};

#endif //GRAFO_H