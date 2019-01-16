#include <iostream>
#include <vector>
#include <string>

template<typename T>
void myGenericIterator (T& myIterable) {
 for (auto ele : myIterable)
 std::cout << ele << std::endl;
}
int main()
{
 std::string myArray[] = {"Giulia", "Alessandro", "Pietro"};
 std::vector<std::string> myVec;
 myVec.push_back(myArray[0]);
 myVec.push_back(myArray[1]);
 myVec.push_back(myArray[2]);
 myGenericIterator(myVec);
 std::cout << std::endl;
 myGenericIterator(myArray);
 return 0;
}
