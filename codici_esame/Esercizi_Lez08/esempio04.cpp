/*
c++ -o esempio04 esempio04.cpp
*/

#include <iostream>     
#include <fstream> 
#include <string>
#include <vector>

int main (int argc, char** argv)
{
  // Verifica che venga passato almeno un parametro da riga di comando
  if (argc < 2)
    {
      std::cout << "Digitare il nome del file da riga di comando" << std::endl;
      std::cout << "\t./esempio04 File.txt" << std::endl;
      return 1;
    }

  int x      = 0;
  int y      = 0;
  int Nrighe = 0;

  std::string filename = argv[1];
  std::ifstream InFile (filename.c_str()); 
	
  // Metodo good() per verificare che sia possibile leggere il file
  // Se il file non è presente nella cartella, o non e` possibile aprirlo,
  // stampa un messaggio di errore
  if (InFile.good() == false)
    {
      std::cout << "Errore! Non e` possibile aprire il file " << filename << std::endl;
      return 1;
    }

  std::vector<int> vec1; // Definisce due std::vector per memorizzare i numeri contenuti nel file
  std::vector<int> vec2; // Non serve sapere a priori quanti numeri
	
  // Imposta un loop infinito interrotto con l'istruzione break
  while (true)
    {
      InFile >> x >> y;
      
      // Il metodo eof() restituisce true alla fine del file
      if (InFile.eof() == true)
	break;
      
      vec1.push_back(x); 
      vec2.push_back(y);
      Nrighe++;
    }
  InFile.close();
  
  std::cout << "Il file " << filename << " contiene " << Nrighe << " righe" << std::endl;
  std::cout << "Il vector vec1 contiene " << vec1.size() << " elementi" << std::endl;
  std::cout << "Il vector vec2 contiene " << vec2.size() << " elementi" << std::endl;
  
  for (int i = 0; i < vec1.size(); i++)
    std::cout << vec1[i] << "\t" << vec2[i] << std::endl;
  
  return 0;
}
