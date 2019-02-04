/*
c++ -o string string.cpp
*/

#include <iostream>
#include <string>

int main()	
{
  std::string frase;
  std::cout << "Inserisci una frase: ";
  getline(std::cin,frase);
  
  const char* fraseC = frase.c_str();
  std::cout << "Frase: " << fraseC << std::endl; 

  int lunghezza = frase.length();
  std::cout << "Lunghezza frase: " << lunghezza << std::endl; 
    
  std::string parola ("pizza");
  int posizione = frase.find(parola);
  std::cout << "La parola " << parola << " si trova in posizione " << posizione << std::endl;
  
  std::string parola2 ("pozza");
  int confronto = parola2.compare(parola);
  if (confronto == 0) std::cout << "Le due parole (pizza e pozza) sono uguali" << std::endl;
  else                std::cout << "Le due parole (pizza e pozza) sono diverse" << std::endl;
  
  for (int i = 0; i < parola2.length(); i++)
    std::cout << "Carattere " << i << ": " << parola2[i] << std::endl;
  
  return 0;
}
