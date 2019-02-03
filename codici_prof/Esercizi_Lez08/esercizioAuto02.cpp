/*
c++ -std=c++11 -o esercizioAuto02 esercizioAuto02.cpp
*/

#include <iostream>
#define N 100

// ##############################################
// # Test auto as return type without templates #
// ##############################################
int makeObject()
{
  return N;
}

auto testReturn() -> decltype ( makeObject() )
{
  auto val = makeObject();
  std::cout << "I use the new type: " << val << std::endl;
  return val;
}

// ####################################################
// # Test auto as return type together with templates #
// ####################################################
class builderType
{
public:
  int makeObject() const { return N; }
};


template <typename T>
auto testReturn(const T& builder) -> decltype ( builder.makeObject() )
{
  auto val = builder.makeObject();
  std::cout << "I use the new type: " << val << std::endl;
  return val;
}

int main ()
{
  testReturn ();

  builderType myBuilder;
  testReturn (myBuilder);

  return 0;
}
