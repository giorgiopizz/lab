#include "multiplot.h"

using namespace std;


multiplot::multiplot(int x, vector<string> files_,string tipo):n(x), type(tipo){
        //Error checking
        if(files_.empty()){
            throw invalid_argument("File is empty.") ;
        }
        else if(n <= 0 ){
            throw invalid_argument("Value must be non-zero and positive.");
        }
        //Controlla che siano contemporaneamente corretti tutti i parametri (magari supefluo)
        //l'unico non sostituibile è (files_.size() == n) che si assicura di non avere più subplots che files (o viceversa)
        if(n >0 && !files_.empty() && int(files_.size()) == n){
            for (int i = 0; i < n; i++) {
                dati.push_back(new analyzer(i + 1));
                dati.at(i)->setData(files_.at(i), tipo);
            }
        }else {cout << "Error while creating class object: Invalid Argument exception" <<endl;}
}
void multiplot::display(){
        //se [dati] è un oggetto valido parte l'applicazione, altrimenti blocco tutto e chiudo
        if(!dati.empty()) {
            app_ = new TApplication("myApp", NULL, NULL);
            cnv_ = new TCanvas("myCanv", "myCanv", 0, 0, 1200, 800);
            //soluzione momentanea per gestire il layout dei subplots in base al numero (funziona, vedi se può andare bene)
            if (n%2 == 0) {
                if (n ==2){
                    cnv_->Divide(n, n/2);
                }else if(n >=4){
                    cnv_->Divide(n/2, n/2);
                }
            }else {
                if(n ==3){
                    cnv_->Divide(n, n/2);
                }else if (n >= 5){
                    cnv_->Divide(n-(n/2), n/2);
                }
            }
            for (int i = 0; i < n; i++) {
                cnv_->cd(i + 1);

                if (type == "counts") {
                    dati.at(i)->getHisto()->Draw();
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
