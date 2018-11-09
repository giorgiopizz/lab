#include "multiplot.h"

int main(){
	string files = ["data1.txt","data2.txt"];
	multiplot t(2,files,"counts");
	t.display();
}
