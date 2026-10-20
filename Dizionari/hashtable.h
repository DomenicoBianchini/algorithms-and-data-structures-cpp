#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include <stdexcept>
#include "dizionario.h"
#include "listvector.h"
using namespace std;

template <class T>
class hash_
{
public:
	size_t operator()(const T chiave) const;
};

template <>
class hash_<string>
{
public:
	size_t operator()(const string chiave) const
	{
		unsigned long hash_value = 0;
		int lenght = (int)chiave.length();
		for (int i = 0; i < lenght; i++)
		{
			hash_value = 5 * hash_value + chiave.at(i);
		}
		return (size_t(hash_value));
	}
};

//struttura che contiene una coppia chiave valore
template <class K, class V>
struct coppia;

//classe dizionario come hashtable
template <class K, class V>
class hashtable : public dizionario<K, V>
{
public:
	typedef typename dizionario<K, V>::chiave chiave;		//tipo chiave
	typedef typename dizionario<K, V>::valore valore;       //tipo valore
	typedef listvector<valore> listavalori;			        //tipo listavalori
	typedef listvector<chiave> listachiavi;			     	//tipo listachiavi
	typedef listvector<coppia<K, V>> listacoppie;		    //tipo listacoppie
	//costruttore di default
	hashtable();
	//costruttore con parametro
	hashtable(int);
    //distruttore
	~hashtable();
    /* =================================== OPERATORI =========================================== */
	//metodo che inizializza la hashtable
	void create();
	//metodo che restituisce true se la hashtable è vuota
	bool empty() const;
	//metodo che restituisce il totale delle coppie presenti della hashtable
	int size() const;
	//metodo che ricerca la posizione della coppia con chiave K
	int search(const K &) const;
	//metodo che restituisce il riferimento della coppia con chiave K
	coppia<K, V> *find(const K &) const;
	//metodo che inserisce una coppia nella hashtable
	void insert(coppia<K, V> &);
	//metodo che restituisce true se la chiave K è presente nella hahstable
	bool member(const K &) const;
	//metodo che rimuove una coppia con chiave K
	void remove(const K &);
	//metodo che modifica il valore della coppia con chiave K con un nuovo valore
	void modify(const K &, const V &);
	//metodo che restituisce il valore da una coppia con chiave K
	const V &retrieves(const K &);
	//metodo che restituisce true se il valore è presente nella hastable
	bool containsValue(const V &);
	//metodo che restituisce true se la coppia è presente nella hashtable
	bool containsPair(const coppia<K, V> &);
	//metodo che stampa la lista delle chiavi presenti nella hashtable
	void printkeys();
	//metodo che restituisce la lista dei valori della hashtable
	listavalori values();
	//metodo che restituisce la lista delle chiavi della hashtable
	listachiavi keys();
	//metodo che raddoppia la massima capienza della hashtable mantenendo gli elementi
	void resize();
	//metodo che restituisce true se il primo dizionario è sottoinsieme del secondoo
	bool sottoinsieme(const hashtable<K, V> &);
	//metodo che restituisce il valore del divisore
	int divisor_size() const;
	//sovraccarico operatore di uguaglianza
	bool operator==(const hashtable<K, V> &);
	
private:
	coppia<K, V> **table;     //hash table
	hash_<K> hashmap;	      //associa il tipo K a un intero non negativo 
	int dsize;			      //numero di coppie nel dizionario
	int divisor;		      //divisore funzione hash
};

//metodo public
template <class K, class V>
hashtable<K, V>::hashtable()
{
	this->create();
	divisor = 100;
	table = new coppia<K, V> *[divisor];
	for (int i = 0; i < divisor; i++)
	{
		table[i] = nullptr;
	}
}

//metodo public
template <class K, class V>
hashtable<K, V>::hashtable(int the_divisor)
{
	this->create();
	divisor = the_divisor;
	table = new coppia<K, V> *[divisor];
	for (int i = 0; i < divisor; i++)
	{
		table[i] = nullptr;
	}
}

//metodo public
template <class K, class V>
hashtable<K, V>::~hashtable()
{
	if (!this->empty()){
		for (int i = 0; i < divisor; i++){
			if (table[i] != nullptr){
				delete table[i];
				table[i] = nullptr;
				dsize--;
			}
		}
	}
	delete[] table;
	table = nullptr;
}

//metodo public
template <class K, class V>
void hashtable<K, V>::create()
{
	dsize = 0;
}

//metodo public
template <class K, class V>
bool hashtable<K, V>::empty() const
{
	return (dsize == 0);
}

//metodo public
template <class K, class V>
int hashtable<K, V>::size() const
{
	return (dsize);
}

//metodo public
template <class K, class V>
int hashtable<K, V>::search(const K &chiave) const
{
	int i = (int)hashmap(chiave) % divisor; 
	int j = i;
	do{
		if ((table[j] == nullptr) || (table[j]->primo == chiave)){
			return j;
		}
		j = (j + 1) % divisor; 

	} while (j != i);

	return (j); 
}

//metodo public
template <class K, class V>
coppia<K, V> *hashtable<K, V>::find(const K &chiave) const
{
	int b = search(chiave);
	if ((table[b] == nullptr) || (table[b]->primo != chiave))
	{
		return (nullptr); //nessuna corrispondenza trovata
	}
	return (table[b]);
}

//metodo public
template <class K, class V>
void hashtable<K, V>::insert(coppia<K, V> &the_pair)
{
	if (!member(the_pair.primo)){
		int b = search(the_pair.primo);
		if (table[b] == nullptr){
			//nessun elemento corrispondente e tabella non piena
			table[b] = new coppia<K, V>(the_pair);
			dsize++;
		}
		else
		{
			//controlla se duplicato o tabella piena
			if (table[b]->primo == the_pair.primo){
				//duplicato, cambia tabella[b]->secondo
				table[b]->secondo = the_pair.secondo;
			}
			else{
				throw std::runtime_error("Il dizionario è pieno"); 
			}
		}
	}
}

//metodo public
template <class K, class V>
bool hashtable<K, V>::member(const K &chiave) const
{
	if (!this->empty()){
		int position = search(chiave);
		if (table[position] != nullptr){
			return (table[position]->primo == chiave);
		}
	}
	return (false);
}

//metodo public
template <class K, class V>
void hashtable<K, V>::remove(const K &chiave)
{
	if (!this->empty()){
	    if (member(chiave)){
		    int position = search(chiave);
		    delete table[position];
		    table[position] = nullptr;
		    dsize--;

		    // Ricostruisce il cluster successivo: una cella vuota
		    // non deve interrompere la ricerca lineare.
		    position = (position + 1) % divisor;
		    while (table[position] != nullptr)
		    {
			    coppia<K, V> pair = *table[position];
			    delete table[position];
			    table[position] = nullptr;
			    dsize--;
			    insert(pair);
			    position = (position + 1) % divisor;
		    }
	    }
	    else{
		    throw std::out_of_range("La chiave non è presente");
	    }
    }
	else{
		throw std::out_of_range("Il dizionario è vuoto");
	}
}

//metodo public
template <class K, class V>
void hashtable<K, V>::modify(const K &chiave, const V &the_element)
{
	if (!this->empty()){
	    if (member(chiave)) {
		    int position = search(chiave);
		    table[position]->secondo = the_element;
	    }
	    else{
		   throw std::out_of_range("La chiave non è presente"); 
	    }
	}
	else{
		throw std::out_of_range("Il dizionario è vuoto");   
	}		
}

//metodo public
template <class K, class V>
const V &hashtable<K, V>::retrieves(const K &thechiave)
{
	if (!this->empty()){
	    if (member(thechiave)){
		    int position = search(thechiave);
		    return (table[position]->secondo);
	    }
	    else{
		    throw std::out_of_range("La chiave non è presente"); 
	    }
	}
	else{
		throw std::out_of_range("Il dizionario è vuoto"); 
	}
}

//metodo public
template <class K, class V>
void hashtable<K, V>::printkeys()
{
	listachiavi l = keys();
	cout << l;
}

//metodo public
template <class K, class V>
bool hashtable<K, V>::containsValue(const V &value)
{
	bool found = false;
	if (!this->empty()){
		for (int i = 0; (i < divisor) && !found; i++){
			if (table[i] != nullptr){
				if (table[i]->secondo == value){
					found = true;
				}
			}
		}
	}
	return (found);
}

//metodo public
template <class K, class V>
typename hashtable<K, V>::listavalori hashtable<K, V>::values()
{
	listavalori l;
	if (!this->empty()){
		for (int i = 0; i < divisor; i++){
			if (table[i] != nullptr){
				l.push_back(table[i]->secondo);
			}
		}
	}
	return (l);
}

//metodo public
template <class K, class V>
typename hashtable<K, V>::listachiavi hashtable<K, V>::keys()
{
	listachiavi l;
	if (!empty()){
		for (int i = 0; i < divisor; i++){
			if (table[i] != nullptr){
				l.push_back(table[i]->primo);
			}
		}
	}
	return (l);
}

//metodo public
template <class K, class V>
void hashtable<K, V>::resize()
{
	//salvo tutte le coppie chiave valore
	listacoppie l;
	for (int i = 0; i < divisor; i++){
		if (table[i] != nullptr){
			coppia<K, V> pair_copy = *(table[i]);
			l.push_back(pair_copy);
		}
	}
	//cancello il vecchio stato
	for (int i = 0; i < divisor; i++){
		if (table[i] != nullptr){
			delete table[i];
			table[i] = nullptr;
			dsize--;
		}
	}
	delete[] table;
	table = nullptr;
	//creo il nuovo stato dell'oggetto raddoppiando il divisore
	this->create();
	divisor = divisor * 2;
	table = new coppia<K, V> *[divisor];
	for (int i = 0; i < divisor; i++){
		table[i] = nullptr;
	}
	if (!l.empty()){
		for (auto i = l.begin(); !l.end(i); i = l.next(i)){
			coppia<K, V> pair;
			pair.primo = l.read(i).primo;
			pair.secondo = l.read(i).secondo;
			this->insert(pair);
		}
	}
}

//metodo public
template <class K, class V>
int hashtable<K, V>::divisor_size() const
{
	return (divisor);
}

//metodo public
template <class K, class V>
bool hashtable<K, V>::operator==(const hashtable<K, V> &h)
{
	if (this->size() != h.size()){
		return (false);
	}
	listacoppie l1;
	for (int i = 0; i < divisor; i++){
		if (table[i] != nullptr){
			coppia<K, V> pair_copy = *(table[i]);
			l1.push_back(pair_copy);
		}
	}
	listacoppie l2;
	for (int i = 0; i < h.divisor; i++){
		if (h.table[i] != nullptr){
			coppia<K, V> pair_copy = *(h.table[i]);
			l2.push_back(pair_copy);
		}
	}
	return (l1 == l2);
}

//metodo public
template <class K, class V>
bool hashtable<K, V>::sottoinsieme(const hashtable<K, V> &h)
{
	bool found = true;
	for (int i = 0; (i < divisor) && found; i++){
		if (table[i] != nullptr){
			if (h.find(table[i]->primo) == nullptr){
				found = false;
			}
			else{
				found = (*(table[i]) == *(h.find(table[i]->primo)));
			}
		}
	}
	return (found);
}

//metodo public
template <class K, class V>
bool hashtable<K, V>::containsPair(const coppia<K, V> &pair)
{
	bool found = false;
	for (int i = 0; (i < divisor) && !found; i++){
		if (table[i] != nullptr){
			found = (*(table[i]) == pair);
		}
	}
	return (found);
}

#endif //HASHTABLE_H