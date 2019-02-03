/*
c++ -o testStruct testStruct.cpp
*/

#include <iostream>
#include <cstring>

#define NBOOKS 100

using namespace std;

typedef struct
{
  char title[50];
  char author[50];
  char subject[100];
  int book_id;
} book;

void printBooks (book* myBooks, unsigned int nBooks)
{
  for (unsigned int i = 0; i < nBooks; i++)
    {
      cout << "Book title : "   << (myBooks+i)->title   << endl;
      cout << "Book author : "  << (myBooks+i)->author  << endl;
      cout << "Book subject : " << (myBooks+i)->subject << endl;
      cout << "Book id : "      << (myBooks+i)->book_id << endl;
      cout << endl;
    }
}

int main()
{
  book myBooks[NBOOKS];

  strcpy(myBooks[0].title, "The C++ programming language");
  strcpy(myBooks[0].author, "Bjarne Stroustrup");
  strcpy(myBooks[0].subject, "C++ Programming");
  myBooks[0].book_id = 123456;

  strcpy(myBooks[1].title, "Thinking in C++");
  strcpy(myBooks[1].author, "Bruce Eckel");
  strcpy(myBooks[1].subject, "C++ Programming");
  myBooks[1].book_id = 654321; 

  printBooks(myBooks,2);

  return 0; 
}
