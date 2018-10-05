#include <iostream>
//funzione fattoriale ricorsiva
int fattoriale(int x){
	int fatt=1;
	if(x>1){
		fatt=fatt*x*fattoriale(x-1);
	}
	return fatt;
}

int main(){
	int x;
	std::cin >> x;
	std::cout << "Il fattoriale di x è: " << fattoriale(x)<<std::endl;
}
