/*
c++ -o esercizio01 esercizio01.cpp

Esercizio: scrivete un programma che assegni il valore di una variabile ad
           un'altra utilizzando un puntatore. Fatevi inoltre stampare a terminale
           i valori e gli indirizzi di ogni variabile prima e dopo l'assegnazione
*/

#include <iostream>

int main()
{
  int balance;      // Dichiara un int
  int value;        // Dichiara altro int
  int* balance_ptr; // Dichiara un puntatore ad un int
  
  balance = 3200;         // Assegna un valore a balance
  balance_ptr = &balance; // Assegna come valore a balance_ptr l'indirizzo della variabile balance
  value = *balance_ptr;   // Assegna il valore del puntatore balance_ptr alla variabile value
  
  std::cout << "balance is: " << balance << '\n';
  std::cout << "balance_ptr is: " << balance_ptr << '\n';
  std::cout << "value is: " << value << '\n';
  
  return 0;
}
