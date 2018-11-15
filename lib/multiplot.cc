#include "multiplot.h"

using namespace std;


multiplot::multiplot(int x, vector<string> files_,vector <string> nomi_,string tipo):n(x), type(tipo){
        //Controlla che siano contemporaneamente corretti tutti i parametri (magari supefluo)
        //l'unico non sostituibile è (files_.size() == n) che si assicura di non avere più subplots che files (o viceversa)
        string nome;

        if(n >0 && !files_.empty() && int(files_.size()) == n){
            for (int i = 0; i < n; i++) {
                if(int(nomi_.size())==n)
                        nome=nomi_.at(i);
                else
                        nome=to_string(i+1);
                dati.push_back(new analyzer(nome));
                dati.at(i)->setData(files_.at(i), tipo, "gaus");
            }
        }else {cerr << "Error while creating class object: Invalid Argument exception" <<endl;}
}
//aggiunto destructor
multiplot::~multiplot(){
    n=0;
    type="";
    dati.resize(0);
    if(cnv_) delete cnv_;
    if(app_) delete app_;
}

void multiplot::display(){
        //se [dati] è un oggetto valido parte l'applicazione, altrimenti blocco tutto e chiudo
        if(!dati.empty()) {
            app_ = new TApplication("myApp", NULL, NULL);
            cnv_ = new TCanvas("myCanv", "myCanv", 400, 100, 1200, 800);

            gStyle->SetOptFit(1111);
            gStyle->SetOptStat(1100);
            //fatt fattorizza n e divide la griglia secondo i suoi fattori
            //**con 3 e 5 viene tutto allungato e distorto, lascio qui il fix che avevo scritto:
            /*
            *    if (n%2 == 0) {
            *        n == 2 ? cnv_->Divide(n, 1) : cnv_->Divide(n/2, n/2);
            *    }else {
            *        n == 3 ? cnv_->Divide(n, n/2) : cnv_->Divide(n-(n/2), n/2);
            */
            //comunque secondo me basta solo provare a fare qualche modifica
            if(fatt(n).size()!=0){
                cnv_->Divide(fatt(n).at(1),fatt(n).at(0));
            }
            else{
                cerr << "Il numero di file non va bene"<<endl;
            }
            //vector <string> testo = {"ciao"};
            //vector <string> ttxt = {"F(t) = #sum_{i=-#infty}^{#infty}A(i)cos#[]{#frac{i}{t+i}}"};
            for (int i = 0; i < n; i++) {
                cnv_->cd(i+1);

                if (type == "counts") {
                    dati.at(i)->getHisto()->SetFillColor(i);
        	        dati.at(i)->getHisto()->SetFillStyle(1002);
                    dati.at(i)->getHisto()->Draw();
                    //setPaveText({"ciao", "mi", "so"}, {"cow","wow"});
                    /*if(chi2){
                        dati.at(i)->computeChi2();
                    }*/
                }
                if (type == "measurements") {
                    dati.at(i)->getGraph()->Draw("AP");
                    /*if(chi2){
                        dati.at(i)->computeChi2();
                    }*/
                }
            }

            cnv_->Modified();
            cnv_->Update();
            app_->Run();

        }
        else{cerr << "Could not start application: bad class object" <<endl;}

}

//**INIZIO della funzione per inserire testo nei grafici
/*void setPaveText(vector<string> text_, vector <string> ttext_){
    const char * text;
    TPaveText *pavetext = new TPaveText(.05, .1, .95,.8);

    for(int i=0; i<(int(text_.size())); i++){
        text = (text_.at(i)).c_str();
        pavetext->AddText(text);
        pavetext->Draw();
    }
    if(ttext_.size() != 0){
        for(int j=0; j<(int(ttext_.size())); j++){
            text = (ttext_.at(j)).c_str();
            pavetext->AddText(text);
            pavetext->Draw();
        }
    }
}*/

//**Lascio anche la funzione che crea Tpad con margini arbitrari

/*void CanvasPartition(TCanvas *C,const int Nx,const int Ny,
                     double lMargin, double rMargin,
                     double bMargin, double tMargin)
{
   if (!C) return;
   // Setup Pad layout:
   double vSpacing = 0.0;
   double vStep  = (1.- bMargin - tMargin - (Ny-1) * vSpacing) / Ny;
   double hSpacing = 0.0;
   double hStep  = (1.- lMargin - rMargin - (Nx-1) * hSpacing) / Nx;
   double vposd,vposu,vmard,vmaru,vfactor;
   double hposl,hposr,hmarl,hmarr,hfactor;
   for (int i=0;i<Nx;i++) {
      if (i==0) {
         hposl = 0.0;
         hposr = lMargin + hStep;
         hfactor = hposr-hposl;
         hmarl = lMargin / hfactor;
         hmarr = 0.0;
      } else if (i == Nx-1) {
         hposl = hposr + hSpacing;
         hposr = hposl + hStep + rMargin;
         hfactor = hposr-hposl;
         hmarl = 0.0;
         hmarr = rMargin / (hposr-hposl);
      } else {
         hposl = hposr + hSpacing;
         hposr = hposl + hStep;
         hfactor = hposr-hposl;
         hmarl = 0.0;
         hmarr = 0.0;
      }
      for (int j=0;j<Ny;j++) {
         if (j==0) {
            vposd = 0.0;
            vposu = bMargin + vStep;
            vfactor = vposu-vposd;
            vmard = bMargin / vfactor;
            vmaru = 0.0;
         } else if (j == Ny-1) {
            vposd = vposu + vSpacing;
            vposu = vposd + vStep + tMargin;
            vfactor = vposu-vposd;
            vmard = 0.0;
            vmaru = tMargin / (vposu-vposd);
         } else {
            vposd = vposu + vSpacing;
            vposu = vposd + vStep;
            vfactor = vposu-vposd;
            vmard = 0.0;
            vmaru = 0.0;
         }
         C->cd(0);
         char name[16];
         sprintf(name,"pad_%i_%i",i,j);
         TPad *pad = (TPad*) gROOT->FindObject(name);
         if (pad) delete pad;
         pad = new TPad(name,"",hposl,vposd,hposr,vposu);
         pad->SetLeftMargin(hmarl);
         pad->SetRightMargin(hmarr);
         pad->SetBottomMargin(vmard);
         pad->SetTopMargin(vmaru);
         pad->SetFrameBorderMode(0);
         pad->SetBorderMode(0);
         pad->SetBorderSize(0);
         pad->Draw();
      }
   }
}*/

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
