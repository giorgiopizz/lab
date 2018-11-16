#ifndef multiplot_h
#define multiplot_h

#include "analyzer.h"

class multiplot{
public:
	//modificato files in files_ per coerenza
	multiplot(int x, vector<string> files_,vector<string> nomi_,string tipo);
	void display();
	vector<int> fatt(int n);
	//void save(TVirtualPad * tmp, int i);
	void print();
private:
	int n;
	string type;
	vector<analyzer*> dati;

	TApplication * app_;
	TCanvas * cnv_;
};


#endif
