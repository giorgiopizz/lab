/*
c++ -o testConst testConst.cpp
*/

#include <iostream>

int fun01 (const int a)
{
  a = 2;
  return a;
}

void fun02 (const int* a)
{
  *a = 2;
}

void fun03 (int* const a)
{
  *a = 2;
}

void fun04 (int* const *a, int* const *b)
{
  *a = *b;
}

void fun05 (int const &a)
{
  a = 2;
}

int main(int argc, char** argv)
{
  const int a = 1;
  a = 6;
  std::cout << "a = " << a << std::endl;
  /* Change from
     const int a = 1;
     to
     int a = 1;
  */
  
  const int* b = new int(1);
  *b = 2;
  int* c = new int(3);
  b = c;
  std::cout << "b = " << *b << std::endl;
  /* Correction:
     If we mantain the definition of b then remove *b = 2;
  */
  
  int* const d = new int(1);
  *d = 2;
  int* e = new int(3);
  d = e;
  std::cout << "d = " << *d << std::endl;
  /* Correction:
     If we mantain the definition of d then remove d = e;
  */

  const int f = 1;
  std::cout << "fun01 = " << fun01(f) << std::endl;
  int g = 1;
  std::cout << "fun01 = " << fun01(g) << std::endl;
  /* Change from
     int fun01 (const int a)
     to
     int fun01 (int a)
  */

  const int* h = new int(1);
  fun02(h);
  std::cout << "h = " << *h << std::endl;
  int* i = new int(1);
  fun02(i);
  std::cout << "i = " << *i << std::endl;
  /* Change from
     void fun02 (const int* a)
     to
     void fun02 (int* a)
     And change from
     const int* h = new int(1);
     to
     int* h = new int(1);
  */

  const int* j = new int(1);
  fun03(j);
  std::cout << "j = " << *j << std::endl;
  int* k = new int(1);
  fun03(k);
  std::cout << "k = " << *k << std::endl;
  /*
    Change from
    const int* j = new int(1);
    to
    int* j = new int(1);
  */
  
  int* l = new int(1);
  int* m = new int(2);
  fun04(&l,&m);
  std::cout << "l = " << *l << std::endl;
  /* Change from
     void fun04 (int* const *a, int* const *b)
     to
     void fun04 (int* *a, int* const *b)
  */

  const int n = 1;
  fun05(n);
  std::cout << "n = " << n << std::endl;
  /* Change from
     void fun05 (int const &a)
     to
     void fun05 (int& a)
     And change from
     const int n = 1;
     to
     int n = 1;
  */
  
  return 0;
}
