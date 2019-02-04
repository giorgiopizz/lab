/*
c++ -o esempio05 esempio05.cpp
*/

#include <iostream>
#include <sstream>

using namespace std; 

int main ()
{
  stringstream ss;
  int anno = 1923;
  string nome = "Jonh";

  // Posso unire numeri e stringhe in un unico stream
  ss << nome << " nacque nel " << anno;
  
  // Conversione sstream -> string
  string frase = ss.str();
  cout << frase << endl;

  return 0;
}
