#include "multiplot.h"
using namespace std;


multiplot::multiplot(int n, string* files,string tipo):n(n),type(tipo){
		for(int i=0;i<n;i++){
			(dati+i)*=new analyzer;
			(dati+i)*->setData((files+i)*, tipo);
		}
}
void multiplot::display(){
	app_ = new TApplication("myApp",NULL,NULL);
        cnv_ = new TCanvas("myCanv","myCanv",0,0,700,500);
        cnv_->Divide(2,1,0,0);
        for(int i=0;i<n;i++){
        	cnv_->cd(i);
        	if(type=="counts") (dati+i)*->getHisto->Draw();
        	if(type=="measurements") (dati+i)*->getGraph->Draw("AP");
        }
        cnv_->Modified();
        cnv_->Update();
        app_->Run();
}
