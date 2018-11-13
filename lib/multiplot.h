
#ifndef multiplot_h
#define multiplot_h

#include "analyzer.h"

class multiplot{
public:
	//modificato files in files_ per coerenza
	multiplot(int x, vector<string> files_,string tipo);
	//destructor
	~multiplot();
	//aggiunto argomento per mostrare o meno il chi2
	void display(bool chi2 = true);
	//void CanvasPartition(TCanvas * C,const int Nx,const int Ny,
	 //                    double lMargin, double rMargin,
	//                     double bMargin, double tMargin);
private:
	int n;
	string type;
	vector<analyzer*> dati;

	TApplication * app_;
	TCanvas * cnv_;
};


#endif
