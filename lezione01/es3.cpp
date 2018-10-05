#include <iostream>
/*il programma richiede di inserire un numero tra due possibilità
o 1 o 2, altrimenti restituisce un errore
*/
int main(){
	int x;
	std::cin >> x;
	if(x==1){
		std::cout << x<<std::endl;
	}
	else if(x==2){
		std::cout << x<<std::endl;
	}
	else{
		std::cout << "Errore, non è stato inserito alcun numero valido"<<std::endl;
	}
}
