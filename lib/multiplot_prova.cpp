//c++ multiplot_prova.cpp multiplot.cc analyzer.cc -o multiplot `root-config --cflags --glibs
#include "multiplot.h"

//ATTENZIONE: potrebbe esserci una memory leak
int main(){
	vector<string> files;
	files.push_back("data1.txt");
	files.push_back("data2.txt");
	multiplot t(2,files,"counts");
	//t.display();
}
