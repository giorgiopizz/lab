#include <iostream>
#include <cmath>
#define N 10

/*il programma memorizza 10 valori inseriti dall'utente in un array
e calcola la media e la varianza di quei valori usando puntatori*/
double media(float * array){
	double media=0;
	for(int i=0; i<N;i++){
		media+=*(array+i);
	}
	return media/N;
}
double varianza(float * array){
	float ar[N];
	for(int i=0; i<N;i++){
		ar[i]=pow(*(array+i),2);
	}
	return sqrt(media(ar)-pow(media(array),2));
}
int main(){
	float * array= new float[10];
	for(int i=0;i<N;i++){
		std::cin >> *(array+i);
	}
	std::cout << "La media dei valori inseriti è: " << media(array) << "\nLa varianza: " << varianza(array) << std::endl;
}
