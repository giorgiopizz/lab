/*
c++ -o argVargC argVargC.cpp
*/

#include <iostream>
 
int main (int argc, char** argv)
{
  
  std::cout << "Ho " << argc << " argomenti" << std::endl;
  
  for (int i = 0; i < argc; i++)
    {
      std::cout << "argv[" << i << "]: " << argv[i] << std::endl;
    }
  
  return 0;
}
