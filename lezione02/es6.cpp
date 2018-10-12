//es6.cpp
#include <iostream>
#include <cstdlib>
#include <ctime>

void CreaArray(double * myArray,int dim);
void LeggiArray(double * myArray, int dim);
void SortArray(double * myArray, int dim);
int main(){
	int dim;
	std::cout << "Inserire la dimensione dell'array";
	std::cin >> dim;
	double* myArray = new double[dim];
	CreaArray(myArray,dim);
	LeggiArray(myArray,dim);
	SortArray(myArray,dim);
	LeggiArray(myArray,dim);
}

void CreaArray(double * myArray, int dim){
	srand(time(NULL));
	for(int i = 0;i<dim;++i){
		*(myArray+i)=2+(10-2) * (1. * rand()) / (1. * RAND_MAX);
		//std::cout<< *(myArray+i);
	}
}
void SortArray(double * myArray, int dim){
	//utilizza la selezione ripetuta del minimo
	double min;
	int q;
	for(int i = 0;i<dim;++i){
		q=i;
		min=myArray[i];
		for(int j=i;j<dim;++j){
			//cerco tra tutti i successivi il minimo
			if(myArray[j]<min){
				q=j;
				min=myArray[j];
			}
		}
		
		if(q!=i){
			//ovvero se il numero in analisi non è il minimo
			//li scambio
			myArray[q]=myArray[i];
			myArray[i]=min;
		}
	}
}
void LeggiArray(double * myArray, int dim){
	std::cout << "L'array è così composto:\n";
	for(int i = 0;i<dim;++i){
		std::cout << *(myArray+i)<<std::endl;
	}
}
