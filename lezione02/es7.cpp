#include <iostream>

int * creaVettore(int n){
	int * vect = new int[n];
}
int main(){
	int * ve=creaVettore(3);
	for(int i=0;i<3;i++){
		*(ve+i)=i;
	}
	for(int i=0;i<3;i++){
		std::cout<< *(ve+i)<<std::endl;
	}
}
