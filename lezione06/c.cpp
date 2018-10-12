#include "complesso.h"
#include <iostream>
#include <cmath>
using namespace std;
int main(){
	complesso c(1, -sqrt(3));
	complesso d(1, sqrt(3));
	c.Print();
	(c^10).Print();
	(c*d).Print();
	(c-d).Print();
	(c+d).Print();
}
