#ifndef DIZIONARIO_H
#define DIZIONARIO_H

#include <iostream>
#include <string>
using namespace std;

/* 
 * Un dizionario è una collezione di coppie della forma (K,V), dove K è una chiave e
 * V è il valore associato alla chiave K
 */
template <class K, class V>
struct coppia
{
	K primo;
	V secondo;
	//metodi
	coppia() {}
	coppia(K chiave, V valore)
	{
		primo = chiave;
		secondo = valore;
	}
	coppia(coppia<K, V> &the_pair)
	{
		primo = the_pair.primo;
		secondo = the_pair.secondo;
	}
	coppia<K, V> &operator=(const coppia<K, V> &the_pair)
	{
		primo = the_pair.primo;
		secondo = the_pair.secondo;
		return *(this);
	}
	bool operator==(const coppia<K, V> &the_pair)
	{
		return ((primo == the_pair.primo) && (secondo == the_pair.secondo));
	}
	friend ostream &operator<<(ostream &os, const coppia<K, V> &mp)
	{
		os << " < " << mp.primo << ", " << mp.secondo << " > ";
		return (os);
	}
};

//classe astratta dizionario 
template <class K, class V>
class dizionario
{
public:
	//definizione dei tipi generici chiave e valore
	typedef K chiave;
	typedef V valore;
	//operatori
	virtual void create() = 0; 
	virtual bool empty() const = 0;                     //restituisce true se il dizionario è vuoto
	virtual int size() const = 0;					    //restituisce il totale delle coppie presenti nel dizionario
	virtual coppia<K, V> *find(const K &) const = 0;    //restituisce la coppia con chiave K
	virtual void insert(coppia<K, V> &) = 0;		    //inserisce la coppia nel dizionario 
	virtual void remove(const K &) = 0;				    //elimina la coppia con chiave K
	virtual void modify(const K &, const V &) = 0;	    //modifica il valore della coppia con chiave K
	virtual ~dizionario(){};
};

#endif //DIZIONARIO_H