/*
c++ -o esempio01 esempio01.cpp
*/

#include <iostream>     
#include <fstream> 
#include <string> 

int main ()
{
  const char* filename = "File.txt";
  // Costruisce un oggetto di tipo ofstream passando
  // come parametro di input il nome del file
  std::ofstream OutFile (filename);

  int a         = 12;
  double b      = 24.5;
  char parola[] = "ciao";

  OutFile << a << "\t" << b << std::endl; // Scrive in output i valori delle variabili a e b
  OutFile << parola << std::endl;
  OutFile.close(); // Chiude il file

  int x    = 0;
  double y = 0;
  std::string word;
  // Apre il file in modalita` lettura
  std::ifstream InFile (filename);

  InFile >> x >> y; // Legge i numeri contenuti nel file e li memorizzo nelle variabili x e y
  InFile >> word;
  InFile.close();

  std::cout << "Il file " << filename <<
    " contiene i numeri: " << x << " e " << y << std::endl;
  std::cout << "e la parola: " << word << std::endl;
  
  return 0;
}
