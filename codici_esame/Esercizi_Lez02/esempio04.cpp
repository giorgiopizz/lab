/*
c++ -o esempio04 esempio04.cpp
*/

#include <iostream>

int main()
{
  std::cout << "\nSize of a double:        " << sizeof(double)        << " bytes"
	    << "\nSize of an int:          " << sizeof(int)           << " bytes"
	    << "\nSize of a long int:      " << sizeof(long int)      << " bytes"
	    << "\nSize of a long long int: " << sizeof(long long int) << " bytes\n";

  double x = 12345.6789;
  std::cout << "\nEnter a floating point number: ";
  std::cin >> x;
  
  // Crea un puntatore ad un intero
  int *ptr = (int *) (&x);
  std::cout << "\ndouble x = " << x << std::endl;
  std::cout << "integer representation of a double" << std::endl;
  std::cout << "(int) x = " << (int) x << std::endl;
  std::cout << "int *ptr = (int *) (&x) = " << *ptr << std::endl;
  std::cout << std::hex << *ptr << std::dec << std::endl;
  
  // Crea un puntatore ad un intero long
  long int *ptr1 = (long int *) (&x);
  std::cout << "\nlong integer representation of a double" << std::endl;
  std::cout << "(long int) x = " << (long int) x << std::endl;
  std::cout << "long Int *ptr = (long int *) (&x) = " << *ptr1 << std::endl;
  std::cout << std::hex << *ptr1 << "\n\n" << std::endl;
  
  // Crea un puntatore ad un intero long long
  long long int *ptr2 = (long long int *) (&x);
  std::cout << "\nlong long integer representation of a double" << std::endl;
  std::cout << "(long long int) x = " << (long long int) x << std::endl;
  std::cout << "long long int *ptr = (long long int *) (&x) = " << *ptr2 << std::endl;
  std::cout << std::hex << *ptr2 << "\n\n" << std::endl;
  
  return 0;	
}
