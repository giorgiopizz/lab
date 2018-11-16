//c++ multiplot_prova.cpp multiplot.cc analyzer.cc -o multiplot `root-config --cflags --glibs`
//*** Ho provato a includere più files (sono il copia/incolla di quelli già esistenti) per verificare l'error checking e
// il layout dei grafici ***
#include "multiplot.h"

int main(){
	vector<string> files;
	files.push_back("data1.txt");
	files.push_back("data1.txt");
	files.push_back("data1.txt");
	files.push_back("data1.txt");
	files.push_back("data1.txt");
	files.push_back("data1.txt");
	vector<string> nomi;

	multiplot t(6,files,nomi,"counts");
	t.display();
	//t.save();
}
