/*
c++ -o creaDati creaDati.cpp
*/

#include <iostream>     
#include <fstream> 
#include <string>
#include <cstdlib>

double randrange (double min, double max)
{
  return min + (max-min) * rand() / RAND_MAX;
}

int main (int argc, char** argv)
{
  // Verifica che vengano passati almeno due parametri da riga di comando
  if (argc < 2)
    {
      std::cout << "Digitare il nome del file da riga di comando" << std::endl;
      std::cout << "\t./creaDati dati.txt\n";
      return 1;
    }

  std::string NomeFile = argv[1];
  std::ofstream OutFile (NomeFile.c_str());
  
  for (int i = 0; i < 10000; i++)
    OutFile << randrange(0,1) << "\t" << randrange(10,20) << std::endl;
  OutFile.close();
  
  return 0;
}
