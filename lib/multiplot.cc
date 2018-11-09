#include "multiplot.h"
using namespace std;


multiplot::multiplot(int x, vector<string> files,string tipo):n(x),type(tipo){
		for(int i=0;i<n;i++){
			dati.push_back(new analyzer(i+1));
			dati.at(i)->setData(files.at(i), tipo);
		}
}
void multiplot::display(){
	app_ = new TApplication("myApp",NULL,NULL);
        cnv_ = new TCanvas("myCanv","myCanv",0,0,1200,700);
        cnv_->Divide(2,1);

        for(int i=0;i<n;i++){
        	cnv_->cd(i+1);

        	if(type=="counts") dati.at(i)->getHisto()->Draw();
        	if(type=="measurements") dati.at(i)->getGraph()->Draw("AP");
        }
        cnv_->Modified();
        cnv_->Update();
        app_->Run();

}