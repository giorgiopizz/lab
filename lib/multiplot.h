
#ifndef multiplot_h
#define multiplot_h

#include "analyzer.h"

class multiplot{
public:
	//modificato files in files_ per coerenza
	multiplot(int x, vector<string> files_,string tipo);

	void display();
private:
	int n;
	//aggiunto files_ come private
	vector <string> files_;
	string type;
	vector<analyzer*> dati;

	TApplication * app_;
	TCanvas * cnv_;
};


#endif
