/*
c++ -o esempio03 esempio03.cpp
*/

#include <iostream>     
#include <fstream> 
#include <string>

int main (int argc, char** argv)
{
  // Verifica che venga passato almeno un parametro da riga di comando
  if (argc < 2)
    {
      std::cout << "Digitare il nome del file da riga di comando" << std::endl;
      std::cout << "\t./esempio03 File.txt" << std::endl;
      return 1;
    }

  std::string NomeFile = argv[1]; 	
  std::ofstream OutFile (NomeFile.c_str()); 

  // Scrittura di piu` righe (std::endl interrompe la riga)
  for (int i = 0; i < 10; i++)
    {
      OutFile << i*2 << "\t" << i*2+1 << std::endl;
    }
  OutFile.close();

  int x      = 0;
  int y      = 0;
  int Nrighe = 0;
	
  std::ifstream InFile (NomeFile.c_str());
  
  // Imposta un loop infinito interrotto con l'istruzione break
  while (true)
    {
      InFile >> x >> y;
      
      // Il metodo eof() restituisce true alla fine del file
      if (InFile.eof() == true)
	break;
      
      std::cout << x << "\t" << y << std::endl;
      Nrighe++;
    }
  InFile.close();

  std::cout << "Il file " << NomeFile << " contiene "
	    << Nrighe << " righe" << std::endl;
  
  return 0;
}
