/*
c++ -o esempio02 esempio02.cpp
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
      std::cout << "\t./esempio02 File.txt" << std::endl;
      return 1;
    }
  
  // Usa un oggetto std::string per memorizzare il nome del file
  std::string NomeFile = argv[1];
  std::ofstream OutFile (NomeFile.c_str()); 
  // Con il metodo c_str() converte la string in char*, perche` i costruttori
  // di ifstream/ofstream prendono in input un puntatore a char

  int a    = 12;
  double b = 24.5;
	
  OutFile << a << "\t" << b << std::endl;
  OutFile.close();
	
  int x    = 0;
  double y = 0;
	
  std::ifstream InFile (argv[1]); 
  // Come parametro di input per i costruttori di ifstream/ofstream 
  // si puo` anche usare argv[1] (che e` char*) al posto di NomeFile.c_str()

  InFile >> x >> y;
  InFile.close();
	
  std::cout << "Il file " << NomeFile << " contiene i numeri: "
	    << x << " e " << y << std::endl;

  return 0;
}
