#include <iostream>
//funzione fattoriale tramite ciclo di ripetizione
int fattoriale(int x){
	int fatt=1;
	while(x!=0){
		fatt*=x;
		x--;
	}
	return fatt;
}

int main(){
	int x;
	std::cin >> x;
	std::cout << "Il fattoriale di x è: " << fattoriale(x)<<std::endl;
}
