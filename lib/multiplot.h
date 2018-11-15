#ifndef multiplot_h
#define multiplot_h

#include "analyzer.h"
#include <TPaveText.h>

class multiplot{
public:
	//modificato files in files_ per coerenza
	multiplot(int x, vector<string> files_,vector<string> nomi_,string tipo);
	~multiplot();
	void display();
	//void setPaveText(vector<string> text, vector<string> ttext_);
	vector<int> fatt(int n);
private:
	int n;
	string type;
	vector<analyzer*> dati;
	//vector<string> text_;
	//vector<string> ttext_;
	//const char * txt_;

	TApplication * app_;
	TCanvas * cnv_;
};


#endif
