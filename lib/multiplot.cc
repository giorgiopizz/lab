#include "multiplot.h"

using namespace std;


multiplot::multiplot(int x, vector<string> files_,vector <string> nomi_,string tipo):n(x), type(tipo){
        //Error checking
        if(files_.empty()){
            throw invalid_argument("File is empty.") ;
        }
        else if(n <= 0 ){
            throw invalid_argument("Value must be non-zero and positive.");
        }
        //Controlla che siano contemporaneamente corretti tutti i parametri (magari supefluo)
        //l'unico non sostituibile è (files_.size() == n) che si assicura di non avere più subplots che files (o viceversa)
        string nome;
        if(n >0 && !files_.empty() && int(files_.size()) == n){
            for (int i = 0; i < n; i++) {
                if(nomi_.size()==n)
                        nome=nomi_.at(i);
                else
                        nome=to_string(i+1);
                dati.push_back(new analyzer(nome));
                dati.at(i)->setData(files_.at(i), tipo,0,200);
            }
        }else {cout << "Error while creating class object: Invalid Argument exception" <<endl;}
}
void multiplot::display(){
        //se [dati] è un oggetto valido parte l'applicazione, altrimenti blocco tutto e chiudo
        if(!dati.empty()) {

            app_ = new TApplication("myApp", NULL, NULL);
            cnv_ = new TCanvas("myCanv", "myCanv", 0, 0, 1200, 800);
            //fatt fattorizza n e divide la griglia secondo i suoi fattori
            if(fatt(n).size()!=0){
                cnv_->Divide(fatt(n).at(1),fatt(n).at(0));
            }
            else{
                cout << "Il numero di file non va bene"<<endl;
                return;
            }
           
            for (int i = 0; i < n; i++) {
                cnv_->cd(i + 1);

                if (type == "counts") {
                    dati.at(i)->getHisto()->SetFillColor(i);
        	    dati.at(i)->getHisto()->SetFillStyle(1002);
                    dati.at(i)->getHisto()->Draw();
                    gStyle->SetOptStat(1100);
                    
                }
                if (type == "measurements") {
                    dati.at(i)->getGraph()->Draw("AP");
                }
            }
            
            cnv_->Modified();
            cnv_->Update();
            app_->Run();
        }
        else{cout << "Could not start application: bad class object" <<endl;}

}
vector<int> multiplot::fatt(int n){
        vector<int> fattori;
        for(int i=0;i<=n;i++){
                for(int j=0;j<n;j++){
                        if(i*j==n&&(i!=1)){
                                fattori.push_back(i);
                                fattori.push_back(j);
                                break;
                        }
                }
        }
        return fattori;
}
/*void multiplot::save(TVirtualPad * tmp, int i){

        string file="picss/"+to_string(i+1)+".png";
        tmp->Print(file.c_str());

}*/
 Double_t multiplot::fun(Double_t * x, Double_t * par){
	
	return par[0]*exp(-0.5*pow(((x[0]-par[1])/par[2]),2))+par[3]*(exp(-x[0]/par[4]))/par[4];
}
void multiplot::print(){
        //se [dati] è un oggetto valido parte l'applicazione, altrimenti blocco tutto e chiudo
        if(!dati.empty()) {
            cnv_ = new TCanvas("myCanv", "myCanv", 0, 0, 1200, 800);
            //fatt fattorizza n e divide la griglia secondo i suoi fattori
            if(n==1){
            
            }
            else{
            	if(fatt(n).size()!=0){
            	    cnv_->Divide(fatt(n).at(1),fatt(n).at(0));
           	 }
            	else{
            	    cout << "Il numero di file non va bene"<<endl;
            	    return;
            	}
            }
            TCanvas * tmp = new TCanvas("temp","temp",0,0,1200,800);
            for (int i = 0; i < n; i++) {
                
		tmp->cd();

                if (type == "counts") {
                    dati.at(i)->getHisto()->SetFillColor(i);
        	    dati.at(i)->getHisto()->SetFillStyle(1002);
        	    //
        	    //[p0]*exp(-0.5*pow(((x-[p1])/[p2]),2))+[p3]*(exp(-x/[p4]))/[p4]
        	   
        	    TF1 * myFun = new TF1("f", fun ,0,200,5);
      	  	    myFun->SetParameter(0,300);
       		    myFun->SetParameter(1,40);
        	    myFun->SetParameter(2,5);
        	    myFun->SetParameter(3,1);
        	    myFun->SetParameter(4,10);
        	    //myFun->SetParameter(5,-1);
        	    myFun->SetParName(0,"Ampl");
        	    myFun->SetParName(1,"Mean");
        	    myFun->SetParName(2,"Sigma");
        	    
        	    dati.at(i)->getHisto()->Fit("f");
                    dati.at(i)->getHisto()->Draw();
                    gStyle->SetOptFit(1111);
                    string file="picss/"+to_string(i+1)+".png";
                    tmp->Print(file.c_str());
                    cnv_->cd(i + 1);
                    tmp->DrawClonePad();
                }
                if (type == "measurements") {
                    dati.at(i)->getGraph()->Draw("AP");
                }
  
            }
            cnv_->Print("picss/finale.png");
	    delete tmp;
        }
        else{cout << "Could not start application: bad class object" <<endl;}
}
