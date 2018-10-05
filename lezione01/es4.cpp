#include <iostream>
/*il programma continua a chiedere di inserire un numero
dicendo se il numero è pari o dispari. Si interrompe se 
il numero è negativo
*/
void pari(){
	std::cout<< "Pari!\n";
}
void dispari(){
	std::cout<< "Dispari!\n";
}
int main(){
	int x;
	while(1!=0){
		std::cin >> x;
		if(x%2==0 && x>0){
			pari();
		}
		else if(x%2!=0 && x>0){
			dispari();
		}
		else{
			break;
		}
	}
}
