# Algoritmi e strutture dati

Raccolta di alcune strutture dati realizzate in C++ durante il corso di
Algoritmi e Strutture Dati.

## Struttura

- **Liste**: `linearlist.h` contiene la classe astratta di base. Le liste sono
  realizzate con nodi concatenati (`linkedlist`) oppure con un vettore
  (`listvector`). Sono presenti anche liste ordinate e una semplice struttura
  per i polinomi.
- **Pile**: `pila.h` definisce la classe astratta di base. `pilapn` usa nodi
  concatenati, mentre `pilavt` usa un vettore. È presente anche
  `multiplestack`, che gestisce più pile.
- **Code**: `coda.h` è la classe astratta di base delle code. `codapn` usa nodi
  concatenati, mentre `codavt` usa un vettore circolare.
- **CodeP**: `codap.h` definisce la classe astratta di base per le code con priorità.
  `codapvt` implementa la coda tramite heap e contiene anche l'algoritmo
  `heapsort`.
- **Dizionari**: `dizionario.h` contiene la classe astratta di base e
  `hashtable.h` implementa il dizionario tramite tabella hash.
- **Grafi**: `grafo.h` definisce la classe astratta di base. `grafolist` usa una
  lista di adiacenza, mentre `grafomat` usa una matrice di adiacenza.
- **AlberiBin**: `alberobin.h` contiene la classe astratta di base. Gli alberi
  binari sono implementati con nodi e puntatori (`alberobinpn`) oppure con un
  vettore (`alberobinvt`).
- **AlberiN**: `albero.h` contiene la classe astratta di base. Gli alberi n-ari
  sono implementati con nodi e puntatori (`alberopn`) oppure con un vettore
  (`alberovt`).

Le varie strutture sono state realizzate durante il corso per lo studio, le
esercitazioni e la preparazione dell'esame.

## Autore

Progetto sviluppato da **Domenico Bianchini**, Università degli Studi di Bari
Aldo Moro.
