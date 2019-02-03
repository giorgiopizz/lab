/*
c++ -o testData testData.cpp data.cc
*/

#include <iostream>

#include "data.h"

int main() {
  data data1 (17, 11, 2017);
  std::cout << "DATA 1: ";
  data1.stampa();
  if (data1.valida()) std::cout << "VALIDA" << std::endl;
  else                std::cout << "NON VALIDA" << std::endl;
  std::cout << std::endl;
  
  data data2 (34, 01, 2013);
  std::cout << "DATA 2: ";
  data2.stampa();
  if (data2.valida()) std::cout << "VALIDA" << std::endl;
  else                std::cout << "NON VALIDA" << std::endl;
  std::cout << std::endl;
	
  data data3 (06,12,1993);
  data data4 (11,03,1993);
  std::cout << "DATA 3: ";
  data3.stampa();
  std::cout << "DATA 4: ";
  data4.stampa();

  if (data3 < data4)
    {
      std::cout << "DATA 4 < DATA 4" << std::endl;
    }
  if (data3 == data4)
    {
      std::cout << "DATA 3 == DATA 4" << std::endl;
    }
  if (data3 > data4)
    {
      std::cout << "DATA 3 > DATA 4" << std::endl;
    }

  std::cout << "\nIl numero di giorni trascorso tra data3 e DATA 4 è: " << data3.diff_giorni(data4) << "\n" << std::endl;

  std::cout << "Il giorno della settimana di DATA 1 è: " << data1.giorno_settimana() << " ";
  data1.stampa();

  std::cout << "Il giorno della settimana di DATA 3 è: " << data3.giorno_settimana() << " ";
  data3.stampa();

  std::cout << "Il giorno della settimana di DATA 4 è: " << data4.giorno_settimana() << " ";
  data4.stampa();

  data Natale (25,12,2023);
  std::cout << "\nNell'anno 2023 Natale sarà di: " << Natale.giorno_settimana() << std::endl;
}
