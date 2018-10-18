//es5
//generatore lineare congruenziale

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <TCanvas.h>
#include <TH1F.h>
#define M 2147483647
#define A 214013
#define C 2531011

int main(){
        //parte 1
        /*
        srand(time(NULL));
	int N=1000000;
        long int x=1;
	TH1D pdf ("name", "title", 1000, 0, 1);
	for (int i = 0; i< N;i++){
		x=(A*x+C)%M;
		std::cout << "Numero casuale: " << (double)x/M << std::endl;
		pdf.Fill((double)x/M);
	}
	TCanvas cnv;
	pdf.Draw();
	cnv.Print("glc.png","png");
        */
        //parte 2

        srand(time(NULL));
	int N=10000;
        long int x=1;
        double media;
        double med;
        double var;
	TH1F pdf ("name", "title", 100, 0, 1);
        double val[N];
        for(int j=0;j<N;j++){
                  //x=1;
                  media=0;
	          for (int i = 0; i< N;i++){
	                 x=(A*x+C)%M;
                         //std::cout << x<<std::endl;
		         media+=(double)x/M;
	          }
                  media/=N;
                  std::cout << media<<std::endl;
                  val[j]=media;
                  med+=media;
                  var+=media*media;
        }
        med/=N;
        var/=N;
        var=var-med*med;
        std::cout << "La media è " << med <<"\nLa varianza è: "<<var<<"\n";
        for(int i=0;i<N;i++){
                pdf.Fill((val[i]-med)/var);
        }
	TCanvas cnv;
	pdf.Draw();
	cnv.Print("glc.png","png");
        
}
