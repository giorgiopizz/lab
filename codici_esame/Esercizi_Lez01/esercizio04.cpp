/*
c++ -o esercizio04 esercizio04.cpp

Esercizio: scrivere un programma che richieda all’utente di inserire un numero
           intero e che sappia riconoscere se il numero è pari o dispari (utilizzare
           l’operatore %, implementando due funzioni che stampino a schermo messaggi
           diversi nei due casi)
*/

#include <iostream>

#define EXIT 1

// Indicazione dei prototipi
void dispari (int a);
void pari    (int a);

int main ()
{
  int i;
  while (true)
    {
      std::cout << "Scrivi un numero: (" << EXIT << " per uscire) : ";
      std::cin >> i;
      if (i == EXIT) break;
      else if (i%2 == 0) pari(i);
      else dispari(i);
    }
  return 0;
}

// Definizione delle funzioni
void dispari (int a)
{
  std::cout << "Il numero e` dispari.\n";
}

void pari (int a)
{
  std::cout << "Il numero e` pari.\n";
}
