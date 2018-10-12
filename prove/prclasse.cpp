//implementazione classe
#include "classe.h"
#include <iostream>
class reale: public complesso{
	public:
		reale(double reale):complesso(reale, 0){
			if(reale>0)
				sign=true;
			else
				sign=false;		
		}
		~reale();
		double valore(){
			return modulo();
		}
		bool segno(){
			return sign;
		}
	private:
		bool sign;
};
int main(){
	//double r=2, i=2;
	reale * ptr = new reale(-2);
	std::cout<< "Il modulo è: " << ptr->modulo() <<"\n"<<"Il segno è "<<ptr->segno()<<"\n";
}
