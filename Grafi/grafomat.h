#ifndef GRAFOMAT_H
#define GRAFOMAT_H

#include <iostream>
#include <stdexcept>
#include "grafo.h"
#include "./../Code/codapn.h"
#define MaxDimension 100
using namespace std;

//definisco la classe che contiene le info dell'arco
template <class P>
class infoArco
{
public:
    P weight;
    bool empty;    
    infoArco()     //costruttore di default
    {
        empty = true;
        weight = P(NULL);
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
    infoArco<P> *arches;
    infoNodo()     //costruttore di default
    {
        label = "";
        info = 0;
        empty = true;
        arches = nullptr;
    }
    ~infoNodo()   //distruttore
    {
        delete[] arches;
        arches = nullptr;
    }
};

//definisco la classe contenente l'id del grafo nella matrice di adiacenza
class nodoGrafo
{
public:
    nodoGrafo(int id)                         //costruttore con parametro id
    {
        idnode = id;
    }
    nodoGrafo()                               //costruttore di default
    {
        idnode = 0;
    }
    int getId()                               //restituisce l'id del nodo
    {
        return (idnode);
    }
    void setId(int id)                        //imposta l'id del nodo
    {
        idnode = id;
    }
    nodoGrafo &operator=(const nodoGrafo &n)  //sovraccarico operatore di assegnamento 
    {
        idnode = n.idnode;
        return *(this);
    } 
    bool operator==(const nodoGrafo &n)       //sovraccarico operatore di uguaglianza 
    {
        return (idnode == n.idnode);
    }

private:
    int idnode;     //id del nodo
};

//definisco la classe matricegrafo 
template <class E, class P>
class grafomat : public grafo<E, P, nodoGrafo>
{
public:
    //definizione dei tipi generici 
    typedef E label;           //etichetta
    typedef P weight;          //peso
    typedef nodoGrafo node;    //nodo grafo
    //ridefinisco i tipi della classe astratta
    typedef class arco<weight, node> arch;                                              //arco
    typedef typename grafo<label, weight, node>::listnode listnode;                     //listanodi
    typedef typename grafo<label, weight, node>::position_listnode position_listnode;   //posizione listanodi
    //costruttore 
    grafomat();
    //costruttore con paramentro
    grafomat(int);
    //distruttore
    ~grafomat();
    /* =================================== OPERATORI =========================================== */
    //metodo che inizializza il grafo
    void create();
    //metodo che restituisce true se il grafo è vuoto
    bool empty() const;
    //metodo che inserisce un nodo nel grafo
    void insNode(node &);
    //metodo che inserisce un arco avente il nodo uscente, il nodo entrante e il peso specificati
    void insArch(node, node, weight);
    //metodo che rimuove un nodo dalla matrice di adiacenza
    void eraseNode(node);
    //metodo che rimuove un arco entrante da un nodo della matrice di adiacenza
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
    //metodo che stampa i nodi adiacenti al nodo specifcato
    void printAdjacent(node) const;
    //stampa i nodi con gli archi associati
    void print(node) const;
    //metodo che permette di visualizzare le relazioni tra i nodi e i loro archi nella matrice di adiacenza
    void adjacencyMatrix() const;
    //algoritmi di visita
    //visita in profondità
    void dfs(node) const;
    void dfs(node, int *) const;
    //visita in ampiezza
    void bfs(node) const;
    //funzioni  utili
    //metodo che restituisce il numero di archi entranti al nodo specificato
    int inDegree(node) const;
    //metodo che restituisce il numero di archi uscenti al nodo specificato
    int outDegree(node) const;
    //metodo che restituisce la media del numero di archi uscenti per ogni nodo del grafo
    double meanOutDegree() const;
    //metodo che stampa il cammino tra due nodi del grafo se tale cammino esiste
    void dfsPath(node, node) const;
    //metodo che stampa il cammino tra due nodi del grafo avente il vettore di marcatura specificato
    void dfsPath(node, node, int *, bool &) const;
    //metodo che verifica l'esistenza di un cammino tra due nodi del grafo e se positiva lo stampa
    void findPath(node, node) const;
    //metodo che restituisce true se esiste un cammino tra due nodi del grafo avente il vettore di visite specificato 
    bool findPath(node, node, int *, bool) const;

private:
    infoNodo<E, P> *matrix;   //matrice di info nodi
    int dimension;            //dimensione massima della matrice
    int nodes;                //numero nodi
    int arches;               //numero archi 
};

//metodo public
template <class E, class P>
grafomat<E, P>::grafomat()
{
    this->create();
    arches = 0;
    dimension = MaxDimension;
    matrix = new infoNodo<E, P>[dimension];
    for (int i = 0; i < dimension; i++)
    {
        matrix[i].arches = new infoArco<P>[dimension];
    }
}

//metodo public
template <class E, class P>
grafomat<E, P>::grafomat(int dim)
{
    this->create();
    arches = 0;
    dimension = dim;
    matrix = new infoNodo<E, P>[dimension];
    for (int i = 0; i < dimension; i++)
    {
        matrix[i].arches = new infoArco<P>[dimension];
    }
}

//metodo public
template <class E, class P>
grafomat<E, P>::~grafomat()
{
    delete[] matrix;
    matrix = nullptr;
}

//metodo public
template <class E, class P>
void grafomat<E, P>::create()
{
    nodes = 0;
}

//metodo public
template <class E, class P>
bool grafomat<E, P>::empty() const
{
    return (nodes == 0);
}

//metodo public
template <class E, class P>
void grafomat<E, P>::insNode(node &nodegraph)
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
    nodegraph.setId(n);
}

//metodo public
template <class E, class P>
void grafomat<E, P>::insArch(node n1, node n2, weight w)
{
    if(isNode(n1) && isNode(n2))
    {
        matrix[n1.getId()].arches[n2.getId()].weight = w;
        matrix[n1.getId()].arches[n2.getId()].empty = false;
        arches++;
    }
    else{
        throw std::runtime_error("I nodi specificati non appartengono al grafo");
    }
}

//metodo public
template <class E, class P>
void grafomat<E, P>::eraseNode(node n)
{
    if (!isNode(n))
    {
        throw std::runtime_error("Il nodo specificato non appartiene al grafo");
        return;
    }
    bool canc = true;
    int i = 0;
    for (int i = 0; (i < dimension) && (canc); i++)     //controllo se n ha archi uscenti 
    {
        if (!matrix[n.getId()].arches[i].empty)
        {
            canc = false;
        }
    }
    for (int i = 0; (i < dimension) && (canc); i++)     //controllo se n ha archi entranti 
    {
        if (!matrix[i].empty && !(matrix[i].arches[n.getId()].empty))
        {
            canc = false;
        }
    }
    if (canc)
    {
        matrix[n.getId()].empty = true;
        nodes--;
    }
    else{
        throw std::runtime_error("Impossibile eliminare il nodo perché ha archi uscenti o entranti");
    }
}

//metodo public
template <class E, class P>
void grafomat<E, P>::eraseArch(node n1, node n2)
{
    if(isNode(n1) && isNode(n2))
    {
        if(isArch(n1,n2))
        {
            matrix[n1.getId()].arches[n2.getId()].empty = true; 
            matrix[n1.getId()].arches[n2.getId()].weight = 0;   
            arches--;
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
bool grafomat<E, P>::isNode(node n) const
{
    return (!matrix[n.getId()].empty);
}

//metodo public
template <class E, class P>
bool grafomat<E, P>::isArch(node n1, node n2) const
{
    if(isNode(n1) && isNode(n2))
    {
        return (!matrix[n1.getId()].arches[n2.getId()].empty);
    }
    else{
        throw std::runtime_error("I nodi specificati non appartengono al grafo");
    }
}

//metodo public
template <class E, class P>
typename grafomat<E, P>::listnode grafomat<E, P>::adjacent(node n) const
{
    if(isNode(n)){
        listnode list;
        for (int j = 0; j < dimension; j++)
        {
            if (!matrix[n.getId()].arches[j].empty)
            {
                node copy(j); 
                list.push_back(copy);
            }
        }
        return (list);
    }
    else{
        throw std::runtime_error("Il nodo specificato non appartiene al grafo");
    }
}

//metodo public
template <class E, class P>
typename grafomat<E, P>::listnode grafomat<E, P>::listNode() const
{
    listnode list;
    for (int i = 0; i < dimension; i++)
    {
        if (!matrix[i].empty)
        {
            node nodecopy(i);
            list.push_back(nodecopy);
        }
    }
    return (list);
}

//metodo public
template <class E, class P>
typename grafomat<E, P>::label grafomat<E, P>::readLabel(node n) const
{
    if(isNode(n))
    {
        return (matrix[n.getId()].label);
    }
    else{
        throw std::runtime_error("Il nodo specificato non appartiene al grafo");
    }
}

//metodo public
template <class E, class P>
void grafomat<E, P>::writeLabel(node n, label l)
{
    if(isNode(n))
    {
        matrix[n.getId()].label = l;
    }
    else{
        throw std::runtime_error("Il nodo specificato non appartiene al grafo");
    }
}

//metodo public
template <class E, class P>
typename grafomat<E, P>::weight grafomat<E, P>::readWeight(node n1, node n2) const
{
    if(isNode(n1) && isNode(n2))
    {
        if(isArch(n1,n2))
        {
            return (matrix[n1.getId()].arches[n2.getId()].weight);
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
void grafomat<E, P>::writeWeight(node n1, node n2, weight w)
{
    if(isNode(n1) && isNode(n2))
    {
        if(isArch(n1,n2))
        {
            matrix[n1.getId()].arches[n2.getId()].weight = w;
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
int grafomat<E, P>::numNodes() const
{
    return (nodes);
}

//metodo public
template <class E, class P>
int grafomat<E, P>::numArches() const
{
    return (arches);
}

//metodo public
template <class E, class P>
bool grafomat<E, P>::isEmptyMatrix() const
{
    return (matrix == nullptr);
}

//metodo public
template <class E, class P>
void grafomat<E, P>::printAdjacent(node n) const
{
    cout << "\nNodi adiacenti: (" << readLabel(n) << "):\n";
    if (!empty())
    {
        listnode l = adjacent(n);
        position_listnode p = l.begin();
        while (!l.end(p))
        {
            cout << "\t\t    -->(" << readLabel(l.read(p)) << ")\n";
            p = l.next(p);
        }
    }
    else{
        throw std::runtime_error("Il grafo è vuoto");
    }
}

//metodo public
template <class E, class P>
void grafomat<E, P>::print(node u) const
{
    if (isNode(u))
    {
        for (int i = u.getId(); i < dimension; i++)
        {
            if (matrix[i].empty == false)
            {
                node node_n(i);
                cout << "\nNodo: " << readLabel(node_n) << "\n";
                for (int j = 0; j < dimension; j++)
                {
                    if (matrix[i].arches[j].empty == false)
                    {
                        node node_a(j);
                        cout << "\tArco: " << readLabel(node_a);
                    }
                }
            }
        }
    }
    else{
        throw std::runtime_error("Il nodo specificato non appartiene al grafo");
    }
}

//metodo public
template <class E, class P>
void grafomat<E, P>::adjacencyMatrix() const
{
    int adjacency_matrix[dimension][dimension]; 
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            adjacency_matrix[i][j] = 0;
        }
    }
    for (int i = 0; i < dimension; i++)
    {
        for (int j = i; j < dimension; j++)
        {
            if (matrix[i].arches[j].empty == false)
            {
                adjacency_matrix[i][j] = 1;
            }
            if (matrix[j].arches[i].empty == false)
            {
                adjacency_matrix[j][i] = 1;
            }
        }
    }
    cout << "\n :::::::: Matrice di adiacenza :::::::: \n";
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            cout << "\t" << adjacency_matrix[i][j];
        }
        cout << "\n";
    }
    cout << "\n";
}

//metodo public
template <class E, class P>
void grafomat<E, P>::dfs(node u) const
{
    if (isNode(u))
    {
        int vector[dimension];
        for (int i = 0; i < dimension; i++)
        {
            vector[i] = 0;
        }
        for (int i = 0; i < dimension; i++)
        {
            if (matrix[i].empty == false)
            {
                vector[i] = 1; //nodo occupato
            }
        }
        dfs(u, vector);
    }
    else{
        throw std::runtime_error("Il nodo specificato non appartiene al grafo");
    }
}

//metodo public
template <class E, class P>
void grafomat<E, P>::dfs(node u, int *visited) const
{
    cout << " (" << matrix[u.getId()].label << ") --> ";
    visited[u.getId()] = 2; 
    listnode l = adjacent(u);
    if (!l.empty())
    {
        position_listnode p = l.begin();
        while (!l.end(p))
        {
            node n = l.read(p);
            if (visited[n.getId()] == 1)
            {
                dfs(n, visited);
            }
            p = l.next(p);
        }
    }
    else{
        throw std::runtime_error("Il grafo è vuoto");
    }
}

//metodo public
template <class E, class P>
int grafomat<E, P>::inDegree(node n) const
{
    if(isNode(n))
    {
        int numArches = 0;
        for (int i = 0; i < dimension; i++)
        {
            if (!matrix[i].arches[n.getId()].empty)
            {
                numArches++;
            }
        }
        return (numArches);
    }
    else{
        throw std::runtime_error("Il nodo specificato non appartiene al grafo");
    }
}

//metodo public
template <class E, class P>
int grafomat<E, P>::outDegree(node n) const
{
    if(isNode(n))
    {
        int numArches = 0;
        for (int j = 0; j < dimension; j++)
        {
            if (!matrix[n.getId()].arches[j].empty)
            {
                numArches++;
            }
        }
        return (numArches);
    }
    else{
        throw std::runtime_error("Il nodo specificato non appartiene al grafo");
    }
}

//metodo public
template <class E, class P>
double grafomat<E, P>::meanOutDegree() const
{
    double average = 0;
    if (!this->empty())
    {
        for (int i = 0; i < dimension; i++)
        {
            if (!matrix[i].empty)
            {
                node nodegraph(i);
                average = average + outDegree(nodegraph);
            }
        }
        average = average / this->numNodes();
    }
    else{
        throw std::runtime_error("Il grafo è vuoto");
    }
    return (average);
}

//metodo public
template <class E, class P>
void grafomat<E, P>::findPath(node s, node d) const
{
    bool flag;
    int visited[dimension];
    for (int i = 0; i < dimension; i++)
    {
        if (matrix[i].empty == false)
        {
            visited[i] = 0;   //nodo occupato
        }
        else
        {
            visited[i] = -1;  //nodo vuoto
        }
    }
    //restituisce true se esiste un cammino da s in d
    flag = findPath(s, d, visited, false);

    //se flag è true lo stampa
    if (flag)
    {
        cout << "\nCammino che congiunge il nodo (" << readLabel(s) << ") al nodo (" << readLabel(d) << ") : ";
        dfsPath(s, d);
    }
    else
    {
        cout << "\nCammino non esistente tra il nodo(" << readLabel(s) << ") e il nodo(" << readLabel(d) << ")";
    }
}

//metodo public
template <class E, class P>
bool grafomat<E, P>::findPath(node s, node d, int *visited, bool found) const
{
    visited[s.getId()] = 1;
    listnode adjacentList = this->adjacent(s);
    if (!adjacentList.empty())
    {
        auto pos = adjacentList.begin();
        while (!adjacentList.end(pos) && !found)
        {
            node n = adjacentList.read(pos);
            if (n == d)
            {
                found = true;
            }
            if (visited[n.getId()] == 0)
            {
                found = findPath(n, d, visited, found);
            }
            pos = adjacentList.next(pos);
        }
    }
    return (found);
}

//metodo public
template <class E, class P>
void grafomat<E, P>::dfsPath(node s, node d) const
{
    int v[dimension];
    for (int i = 0; i < dimension; i++)
    {
        if (!matrix[i].empty)
        {
            v[i] = 0;   //nodo presente
        }
        else
        {
            v[i] = -1;  //nodo assente
        }
    }
    if (findPath(s, d, v, false))
    {
        bool found = false;
        int visited[dimension];
        for (int i = 0; i < dimension; i++)
        {
            if (!matrix[i].empty)
            {
                visited[i] = 0;   //nodo presente
            }
            else
            {
                visited[i] = -1;  //nodo assente
            }
        }
        dfsPath(s, d, visited, found);
    }
}

//metodo public
template <class E, class P>
void grafomat<E, P>::dfsPath(node s, node d, int *visited, bool &found) const
{
    cout << " (" << readLabel(s) << ") --> ";
    visited[s.getId()] = 1; 
    listnode l = adjacent(s);
    if (!l.empty())
    {
        position_listnode p = l.begin();
        while (!l.end(p) && !found)
        {
            node n = l.read(p);
            if (n == d)
            {
                cout << "(" << readLabel(n) << ")";
                found = true;
            }
            else if (visited[n.getId()] == 0)
            {
                dfsPath(n, d, visited, found);
            }
            p = l.next(p);
        }
    }
    else{
        throw std::runtime_error("Il grafo è vuoto");
    }
}

//metodo public
template <class E, class P>
void grafomat<E, P>::bfs(node n) const
{
    bool visited[dimension];
    for (int i = 0; i < dimension; i++)
    {
        visited[i] = false;
    }
    codapn<node> queque;
    visited[n.getId()] = true;
    queque.enqueque(n.getId());
    while (!queque.empty())
    {
        node i = queque.top();
        cout << " (" << readLabel(i) << ") --> ";
        queque.dequeque();
        listnode l = adjacent(i);
        if (!l.empty())
        {
            for (auto p = l.begin(); !l.end(p); p = l.next(p))
            {
                if (visited[l.read(p).getId()] == false)
                {
                    visited[l.read(p).getId()] = true;
                    queque.enqueque(l.read(p));
                }
            }
        }
        else
        {
        throw std::runtime_error("Il grafo è vuoto");
        }
    }
}

#endif //GRAFOMAT_H