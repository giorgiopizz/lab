#include <iostream>
#include <cmath>
#define N 10

/*il programma memorizza 10 valori inseriti dall'utente in un array
e calcola la media e la varianza di quei valori*/
double media(float array[], int n){
	double media=0;
	for(int i=0; i<n;i++){
		media+=array[i];
	}
	return media/n;
}
double varianza(float array[], int n){
	float ar[N];
	for(int i=0; i<n;i++){
		ar[i]=pow(array[i],2);
	}
	return media(ar,n)-pow(media(array,n),2);
}
int main(){
	float array[N];
	for(int i=0;i<N;i++){
		std::cin >> array[i];
	}
	std::cout << "La media dei valori inseriti è: " << media(array, N) << "\nLa varianza: " << varianza(array, N) << std::endl;
}
