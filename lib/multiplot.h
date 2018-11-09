
#ifndef multiplot_h
#define multiplot_h

#include "analyzer.h"

class multiplot{
public:
	multiplot():n(0),dati(NULL){}
	multiplot(int n, string* files,string type);
	
	void display();
private:
	int n;
	string type;
	analyzer* dati;
	
	TApplication * app_;
	TCanvas * cnv_;
};


#endif
