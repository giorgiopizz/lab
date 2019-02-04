/*
c++ -o esempio06 esempio06.cpp
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
  // Verifica che venga passato almeno un parametro da riga di comando
  if (argc < 2)
    {
      std::cout << "Digitare il nome del file da riga di comando" << std::endl;
      std::cout << "\t./esempio06 testo.txt" << std::endl;
      return 1;
    }

  string filename = argv[1];
  ifstream InFile (filename.c_str());

  // Metodo good() per verificare che sia possibile leggere il file
  if (InFile.good() == false)
    {
      cout << "Errore! Non è possibile aprire il file " << filename << endl;
      return 1;
    }
	
  // Usa il metodo getline (istream& is, string& str)
  // per leggere il file una riga alla volta 
  // (restituisce falso alla fine del file)

  string line, parola;
  stringstream ss;
  int nRighe = 0;
  while (getline(InFile, line))
    {
      nRighe++;
      cout << "\nRiga " << nRighe << ": " << line << endl;
      cout << "Selezione parole pari: ";
      
      int nParole = 0;
      ss << line; // Riempie lo stringstream con la riga
      while (ss >> parola) // Legge parola per parola
	{
	  nParole ++;
	  if ((nParole%2) == 0)
	    cout << parola << " ";
	  else continue;
	}
      cout << endl;
      ss.clear(); ss.str(""); // Svuota lo stringstream
    }
	
  return 0;
}
