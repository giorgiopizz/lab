#include "complesso.h"
#include <iostream>
#include <cmath>
using namespace std;
int main(){
	complesso c(1, -sqrt(3));
	complesso d(1, sqrt(3));
    complesso e(c);
    cout<< "Il complesso c :";
	c.Print();
    cout<< "Il complesso d :";
    d.Print();
    cout<< "Il complesso e :";
    e.Print();
    cout<< "Il complesso c^10 :";
	(c^10).Print();
    cout<< "Il complesso prodotto :";
	(c*d).Print();
    cout<< "Il complesso sottrazione :";
	(c-d).Print();
    cout<< "Il complesso somma :";
	(c+d).Print();
}
